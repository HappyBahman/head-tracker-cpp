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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Programs\programming\openGL\ogl-master\ogl-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/flags.make

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/includes_C.rsp
external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj: E:/Programs/programming/openGL/ogl-master/ogl-master/external/glfw-3.1.2/tests/cursor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj"
	cd /d C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests && E:\Programs\programming\MINGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cursor.dir\cursor.c.obj   -c E:\Programs\programming\openGL\ogl-master\ogl-master\external\glfw-3.1.2\tests\cursor.c

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cursor.dir/cursor.c.i"
	cd /d C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests && E:\Programs\programming\MINGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\Programs\programming\openGL\ogl-master\ogl-master\external\glfw-3.1.2\tests\cursor.c > CMakeFiles\cursor.dir\cursor.c.i

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cursor.dir/cursor.c.s"
	cd /d C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests && E:\Programs\programming\MINGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\Programs\programming\openGL\ogl-master\ogl-master\external\glfw-3.1.2\tests\cursor.c -o CMakeFiles\cursor.dir\cursor.c.s

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.requires:

.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.requires

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.provides: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.requires
	$(MAKE) -f external\glfw-3.1.2\tests\CMakeFiles\cursor.dir\build.make external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.provides.build
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.provides

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.provides.build: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj


# Object files for target cursor
cursor_OBJECTS = \
"CMakeFiles/cursor.dir/cursor.c.obj"

# External object files for target cursor
cursor_EXTERNAL_OBJECTS =

external/glfw-3.1.2/tests/cursor.exe: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj
external/glfw-3.1.2/tests/cursor.exe: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/build.make
external/glfw-3.1.2/tests/cursor.exe: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/tests/cursor.exe: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/linklibs.rsp
external/glfw-3.1.2/tests/cursor.exe: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/objects1.rsp
external/glfw-3.1.2/tests/cursor.exe: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cursor.exe"
	cd /d C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cursor.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/build: external/glfw-3.1.2/tests/cursor.exe

.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/build

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/requires: external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/cursor.c.obj.requires

.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/requires

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/clean:
	cd /d C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests && $(CMAKE_COMMAND) -P CMakeFiles\cursor.dir\cmake_clean.cmake
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/clean

external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Programs\programming\openGL\ogl-master\ogl-master E:\Programs\programming\openGL\ogl-master\ogl-master\external\glfw-3.1.2\tests C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests C:\Users\Bahman\Documents\_EDJUCATION\8thSemester\new\build\build\external\glfw-3.1.2\tests\CMakeFiles\cursor.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/cursor.dir/depend

