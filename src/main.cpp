#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"

/* ------------------------- Shaders ---------------------------*/
GLuint programColor;
GLuint programTexture;
Core::Shader_Loader shaderLoader;
/* ------------------------- Models ---------------------------*/
obj::Model fishModel;
obj::Model sharkModel;
obj::Model terrainModel;
obj::Model submarineModel;
obj::Model whaleModel;
obj::Model stone1Model;
obj::Model stone2Model;
obj::Model stone3Model;
obj::Model stone4Model;
obj::Model stone5Model;
/* ------------------------- Textures ---------------------------*/
GLuint textureFish;
GLuint textureShark;
GLuint textureTerrain;
GLuint textureSubmarine;
GLuint textureWhale;
GLuint textureStone1;
GLuint textureStone2;
GLuint textureStone3;
GLuint textureStone4;
GLuint textureStone5;
/* ------------------------- Camera ---------------------------*/
glm::vec3 cameraPos = glm::vec3(0, 0, 5);
glm::vec3 cameraDir; // Wektor "do przodu" kamery
glm::vec3 cameraSide; // Wektor "w bok" kamery
glm::quat rotation;
bool freeCamera = false;
glm::mat4 cameraMatrix, perspectiveMatrix;
glm::vec3 cameraPosOld;
glm::vec3 cameraDirOld;
glm::vec3 cameraSideOld;
glm::quat rotationOld;
/* ------------------------- Light ---------------------------*/
glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));
/* ------------------------- Matrix ---------------------------*/
glm::mat4 submarineModelMatrix;
glm::mat4 submarineInitialTransformation;
glm::mat4 fishModelMatrix;
glm::mat4 fishInitialTransformation;
glm::mat4 terrainInitialTransformation;
glm::mat4 terrainModelMatrix;
/* ------------------------- Mouse ---------------------------*/
glm::vec2 mousePos;
glm::vec2 mouseMove;
/* ------------------------- Objects ---------------------------*/
std::vector<std::vector<glm::vec3>> fishesPath;
unsigned fishesPathLength = 15;
unsigned fishesCount = 220;
/* ------------------------- Settings ---------------------------*/
glm::vec2 windowSize(600, 600);
bool pause = false;
float lastTime = 0;
float timer = 0;
float gameSpeed = 1;

void keyboard(unsigned char key, int x, int y)
{
	float moveSpeed = 0.1f * gameSpeed;

	if(!pause || freeCamera)
    {
        if(key == 'w') cameraPos += cameraDir * moveSpeed;
        else if(key == 's') cameraPos -= cameraDir * moveSpeed;
        else if(key == 'd') cameraPos += cameraSide * moveSpeed;
        else if(key == 'a') cameraPos -= cameraSide * moveSpeed;
    }

    if(key == 'f')
    {
        freeCamera = !freeCamera;

        if(freeCamera)
        {
            cameraPosOld = cameraPos;
            cameraDirOld = cameraDir;
            cameraSideOld = cameraSide;
            rotationOld = rotation;
        }
        else
        {
            cameraPos = cameraPosOld;
            cameraDir = cameraDirOld;
            cameraSide = cameraSideOld;
            rotation = rotationOld;
        }
    }
    else if(key == 'q')
    {
        if(gameSpeed < 10.0)
            gameSpeed += 0.1;
    }
    else if(key == 'e')
    {
        if(gameSpeed > 0.1)
            gameSpeed -= 0.1;
    }
    else if(key == 27)  // esc
    {
        glutLeaveMainLoop();
    }
    else if(key == 32) // space
    {
        pause = !pause;
    }
}

void mouse(int x, int y)
{
	glm::vec2 newMousePos(x, y);
	if(freeCamera)
	    mouseMove = (windowSize / 2.0) - newMousePos;
	mousePos = newMousePos;

	glutWarpPointer(windowSize.r / 2.0, windowSize.g / 2.0);
}

glm::mat4 createCameraMatrix()
{
	glm::quat oY = glm::angleAxis(mouseMove.r * 0.01f, glm::vec3(0, 1, 0));
	glm::quat oX = glm::angleAxis(mouseMove.g * 0.01f, glm::vec3(1, 0, 0));

	glm::quat rotationChange = oX * oY;

	rotation = rotationChange * rotation;
	rotation = glm::normalize(rotation);

	mouseMove = glm::vec2(0,0);

	cameraDir = glm::inverse(rotation) * glm::vec3(0, 0, -1);
	cameraSide = glm::inverse(rotation) * glm::vec3(1, 0, 0);

	return Core::createViewMatrixQuat(cameraPos, rotation);
}

void drawObjectColor(obj::Model * model, glm::mat4 modelMatrix, glm::vec3 color)
{
	GLuint program = programColor;

	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}

void drawObjectTexture(obj::Model * model, glm::mat4 modelMatrix, GLuint textureId)
{
	GLuint program = programTexture;

	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);
	Core::SetActiveTexture(textureId, "textureSampler", program, 0);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}
glm::vec3 catmull_rom_spline(const std::vector<glm::vec3>& cp, float t)
{
	int i0 = ((int)t - 1) % (cp.size());
	int i1 = ((int)t) % (cp.size());
	int i2 = ((int)t + 1) % (cp.size());
	int i3 = ((int)t + 2) % (cp.size());
	float local_t = glm::fract(t);
	return glm::catmullRom(cp[i0], cp[i1], cp[i2], cp[i3], local_t);
}
void renderScene()
{
    auto currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    if(pause) lastTime = currentTime;

    auto delta = currentTime - lastTime;
    lastTime = currentTime;
    timer += delta * gameSpeed;

	glutSetWindowTitle((std::string("submarine pos(") +
					std::to_string(cameraPos.r) + " , " +
					std::to_string(cameraPos.g) + " , " +
					std::to_string(cameraPos.b) + ")" +
                    std::string("timer speed = ") + std::to_string(gameSpeed)).c_str());

	// Aktualizacja macierzy widoku i rzutowania
	cameraMatrix = createCameraMatrix();
	perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	if(!freeCamera)
	{
        submarineModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f) * glm::mat4_cast(rotation);
        submarineModelMatrix *= submarineInitialTransformation;
	}
	drawObjectTexture(&submarineModel, submarineModelMatrix, textureSubmarine);

	for(auto i = 0; i < fishesCount; ++i)
	{
		auto pos = catmull_rom_spline(fishesPath[i], timer);
		glm::vec3 tangential = glm::normalize(catmull_rom_spline(fishesPath[i], timer + 0.001) -
				catmull_rom_spline(fishesPath[i], timer - 0.001));

		auto angle = atan2f(tangential.z, tangential.x);
		auto rot = glm::rotate(angle, glm::vec3(0, 1, 0));

		if(!(i % 15))
		{
			fishModelMatrix = glm::translate(pos) * rot * fishInitialTransformation;
			drawObjectTexture(&whaleModel, fishModelMatrix, textureWhale);
		}
		else if(!(i % 10))
        {
            fishModelMatrix = glm::translate(pos) * rot * fishInitialTransformation;
            drawObjectTexture(&sharkModel, fishModelMatrix, textureShark);
        }
        else
        {
            fishModelMatrix = glm::translate(pos) * rot * fishInitialTransformation;
            drawObjectTexture(&fishModel, fishModelMatrix, textureFish);
        }
	}

    //terrainModelMatrix = glm::translate(glm::vec3(0, -40, 0)) * terrainInitialTransformation;
    //drawObjectTexture(&terrainModel, terrainModelMatrix, textureTerrain);

	glutSwapBuffers();
}

void init()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");

	fishModel = obj::loadModelFromFile("models/fish.obj");
	sharkModel = obj::loadModelFromFile("models/shark.obj");
    //terrainModel = obj::loadModelFromFile("models/terrain.obj");
    submarineModel = obj::loadModelFromFile("models/submarine.obj");
	whaleModel = obj::loadModelFromFile("models/whale.obj");
    stone1Model = obj::loadModelFromFile("models/stone_1.obj");
    stone2Model = obj::loadModelFromFile("models/stone_2.obj");
    stone3Model = obj::loadModelFromFile("models/stone_3.obj");
    stone4Model = obj::loadModelFromFile("models/stone_4.obj");
    stone5Model = obj::loadModelFromFile("models/stone_5.obj");

	textureFish = Core::LoadTexture("textures/fish.png");
	textureShark = Core::GenerateTexture(255, 0, 255);
	//textureTerrain = Core::LoadTexture("textures/terrain.png");
    textureSubmarine = Core::LoadTexture("textures/submarine.png");
	textureWhale = Core::LoadTexture("textures/submarine.png");
	textureStone1 =  Core::LoadTexture("textures/stone_1.png");
    textureStone2 =  Core::LoadTexture("textures/stone_2.png");
    textureStone3 =  Core::LoadTexture("textures/stone_3.png");
    textureStone4 =  Core::LoadTexture("textures/stone_4.png");
    textureStone5 =  Core::LoadTexture("textures/stone_5.png");

    submarineInitialTransformation =
			glm::translate(glm::vec3(0,-7.0f,0)) *
			glm::rotate(glm::radians(180.0f), glm::vec3(0,1,0)) *
			glm::scale(glm::vec3(0.05));

	fishInitialTransformation =
			glm::translate(glm::vec3(0,-0.6f,0)) *
			glm::rotate(glm::radians(180.0f), glm::vec3(0,1,0)) *
			glm::scale(glm::vec3(0.1));

	terrainInitialTransformation =
            glm::translate(glm::vec3(0, 0, 0)) *
            glm::rotate(glm::radians(180.0f), glm::vec3(0,1,0)) *
            glm::scale(glm::vec3(1.0, 1.0, 1.0));

	fishesPath.resize(fishesCount);
	for(auto i = 0; i < fishesCount; ++i)
	{
		auto x = glm::linearRand(-30.0, 30.0);
		auto y = glm::linearRand(-30.0, 30.0);
		auto z = glm::linearRand(-30.0, 30.0);

		fishesPath[i].resize(fishesPathLength);
		fishesPath[i][0] = glm::vec3(x,y,z);

		for(auto j = 1; j < fishesPathLength; ++j)
		{
			auto x = glm::linearRand(-3, 3);
			auto y = glm::linearRand(-3, 3);
			auto z = glm::linearRand(-3, 3);

			auto vec = glm::vec3(x,y,z);

			fishesPath[i][j] = fishesPath[i][j - 1] + vec;

			if(fishesPath[i][j].r > 30) 		fishesPath[i][j].r -= vec.r * 1.5;
			else if( fishesPath[i][j].r < -30)	fishesPath[i][j].r += vec.r * 1.5;
			if(fishesPath[i][j].g > 30)			fishesPath[i][j].g -= vec.g * 1.5;
			else if(fishesPath[i][j].g < -30)	fishesPath[i][j].g += vec.g * 1.5;
			if(fishesPath[i][j].b > 30) 		fishesPath[i][j].b -= vec.b * 1.5;
			else if(fishesPath[i][j].b < -30) 	fishesPath[i][j].b += vec.b * 1.5;
		}
	}
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowSize.r, windowSize.g);
	glutCreateWindow("OpenGL Pierwszy Program");
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(300, 300);

	glutMainLoop();

	shutdown();

	return 0;
}
