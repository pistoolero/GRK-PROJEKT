cmake_minimum_required (VERSION 3.8)
project (GRK)

include(${GRK_SOURCE_DIR}/cmake/macros.cmake)

grk_set_option(GRK_VERSION_MAJOR 1 STRING "major version of grk")
grk_set_option(GRK_VERSION_MINOR 0 STRING "minor version of grk")
grk_set_option(GRK_VERSION ${GRK_VERSION_MAJOR}.${GRK_VERSION_MINOR} STRING "version of grk")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "Install prefix (e.g. /usr/local/)" FORCE)
endif()
if(UNIX OR WIN32)
	include(GNUInstallDirs)
	grk_set_option(GRK_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}" PATH "runtime install dir path")
else()
	message(FATAL_ERROR "Could not set install folders for this platform!")
endif()

set(CMAKE_MODULE_PATH
	"${GRK_SOURCE_DIR}/cmake/modules/"
)
set(sources
	${GRK_SOURCE_DIR}/src/Camera.cpp
	${GRK_SOURCE_DIR}/src/main.cpp
	${GRK_SOURCE_DIR}/src/picopng.cpp
	${GRK_SOURCE_DIR}/src/Render_Utils.cpp
	${GRK_SOURCE_DIR}/src/Shader_Loader.cpp
	${GRK_SOURCE_DIR}/src/Texture.cpp
     )
set(headers
	${GRK_SOURCE_DIR}/include/Camera.h
	${GRK_SOURCE_DIR}/include/objload.h
	${GRK_SOURCE_DIR}/include/picopng.h
	${GRK_SOURCE_DIR}/include/Render_Utils.h
	${GRK_SOURCE_DIR}/include/Shader_Loader.h
	${GRK_SOURCE_DIR}/include/Texture.h
	${GRK_SOURCE_DIR}/include/perlin.h
	)
set(resources
	${GRK_SOURCE_DIR}/models
	${GRK_SOURCE_DIR}/shaders
	${GRK_SOURCE_DIR}/textures
)

add_executable(grk ${headers} ${sources})

target_include_directories(grk PUBLIC
	$<BUILD_INTERFACE:${GRK_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${GRK_SOURCE_DIR}/extlibs/glm/include>
)
set(GLEW_ROOT ${GRK_SOURCE_DIR}/extlibs/glew)
set(Freeglut_ROOT ${GRK_SOURCE_DIR}/extlibs/freeglut)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
	target_link_libraries(grk ${OPENGL_LIBRARIES})
endif()

find_package(Freeglut REQUIRED)
if(Freeglut_FOUND)
	include_directories(${Freeglut_INCLUDE_DIR})
	target_link_libraries(grk ${Freeglut_LIBRARY})
endif()

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIR})
	target_link_libraries(grk ${GLEW_LIBRARY})
endif()

install(TARGETS grk
		RUNTIME DESTINATION ${GRK_RUNTIME_INSTALL_DIR}
)
install(DIRECTORY ${resources}
		DESTINATION ${GRK_RUNTIME_INSTALL_DIR}
)



