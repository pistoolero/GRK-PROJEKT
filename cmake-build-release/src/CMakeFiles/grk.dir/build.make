# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\JetBrains\CLion 2018.1.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\JetBrains\CLion 2018.1.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\Grk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\Grk\cmake-build-release

# Include any dependencies generated for this target.
include src/CMakeFiles/grk.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/grk.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/grk.dir/flags.make

src/CMakeFiles/grk.dir/shaderLoader.cpp.obj: src/CMakeFiles/grk.dir/flags.make
src/CMakeFiles/grk.dir/shaderLoader.cpp.obj: src/CMakeFiles/grk.dir/includes_CXX.rsp
src/CMakeFiles/grk.dir/shaderLoader.cpp.obj: ../src/shaderLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\Grk\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/grk.dir/shaderLoader.cpp.obj"
	cd /d D:\Projects\Grk\cmake-build-release\src && D:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\grk.dir\shaderLoader.cpp.obj -c D:\Projects\Grk\src\shaderLoader.cpp

src/CMakeFiles/grk.dir/shaderLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grk.dir/shaderLoader.cpp.i"
	cd /d D:\Projects\Grk\cmake-build-release\src && D:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\Grk\src\shaderLoader.cpp > CMakeFiles\grk.dir\shaderLoader.cpp.i

src/CMakeFiles/grk.dir/shaderLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grk.dir/shaderLoader.cpp.s"
	cd /d D:\Projects\Grk\cmake-build-release\src && D:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\Grk\src\shaderLoader.cpp -o CMakeFiles\grk.dir\shaderLoader.cpp.s

src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.requires:

.PHONY : src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.requires

src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.provides: src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.requires
	$(MAKE) -f src\CMakeFiles\grk.dir\build.make src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.provides.build
.PHONY : src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.provides

src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.provides.build: src/CMakeFiles/grk.dir/shaderLoader.cpp.obj


# Object files for target grk
grk_OBJECTS = \
"CMakeFiles/grk.dir/shaderLoader.cpp.obj"

# External object files for target grk
grk_EXTERNAL_OBJECTS =

src/libgrk.dll: src/CMakeFiles/grk.dir/shaderLoader.cpp.obj
src/libgrk.dll: src/CMakeFiles/grk.dir/build.make
src/libgrk.dll: ../extlibs/freeglut/lib/libfreeglut.dll.a
src/libgrk.dll: ../extlibs/glew/lib/glew32.lib
src/libgrk.dll: src/CMakeFiles/grk.dir/linklibs.rsp
src/libgrk.dll: src/CMakeFiles/grk.dir/objects1.rsp
src/libgrk.dll: src/CMakeFiles/grk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Projects\Grk\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libgrk.dll"
	cd /d D:\Projects\Grk\cmake-build-release\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\grk.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/grk.dir/build: src/libgrk.dll

.PHONY : src/CMakeFiles/grk.dir/build

src/CMakeFiles/grk.dir/requires: src/CMakeFiles/grk.dir/shaderLoader.cpp.obj.requires

.PHONY : src/CMakeFiles/grk.dir/requires

src/CMakeFiles/grk.dir/clean:
	cd /d D:\Projects\Grk\cmake-build-release\src && $(CMAKE_COMMAND) -P CMakeFiles\grk.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/grk.dir/clean

src/CMakeFiles/grk.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Projects\Grk D:\Projects\Grk\src D:\Projects\Grk\cmake-build-release D:\Projects\Grk\cmake-build-release\src D:\Projects\Grk\cmake-build-release\src\CMakeFiles\grk.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/grk.dir/depend
