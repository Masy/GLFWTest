# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\marce\Documents\Projekte\cpp\GLFWTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GLFWTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GLFWTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GLFWTest.dir/flags.make

CMakeFiles/GLFWTest.dir/main.cpp.obj: CMakeFiles/GLFWTest.dir/flags.make
CMakeFiles/GLFWTest.dir/main.cpp.obj: CMakeFiles/GLFWTest.dir/includes_CXX.rsp
CMakeFiles/GLFWTest.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GLFWTest.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GLFWTest.dir\main.cpp.obj -c C:\Users\marce\Documents\Projekte\cpp\GLFWTest\main.cpp

CMakeFiles/GLFWTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GLFWTest.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\marce\Documents\Projekte\cpp\GLFWTest\main.cpp > CMakeFiles\GLFWTest.dir\main.cpp.i

CMakeFiles/GLFWTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GLFWTest.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\marce\Documents\Projekte\cpp\GLFWTest\main.cpp -o CMakeFiles\GLFWTest.dir\main.cpp.s

CMakeFiles/GLFWTest.dir/FThread.cpp.obj: CMakeFiles/GLFWTest.dir/flags.make
CMakeFiles/GLFWTest.dir/FThread.cpp.obj: CMakeFiles/GLFWTest.dir/includes_CXX.rsp
CMakeFiles/GLFWTest.dir/FThread.cpp.obj: ../FThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GLFWTest.dir/FThread.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GLFWTest.dir\FThread.cpp.obj -c C:\Users\marce\Documents\Projekte\cpp\GLFWTest\FThread.cpp

CMakeFiles/GLFWTest.dir/FThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GLFWTest.dir/FThread.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\marce\Documents\Projekte\cpp\GLFWTest\FThread.cpp > CMakeFiles\GLFWTest.dir\FThread.cpp.i

CMakeFiles/GLFWTest.dir/FThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GLFWTest.dir/FThread.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\marce\Documents\Projekte\cpp\GLFWTest\FThread.cpp -o CMakeFiles\GLFWTest.dir\FThread.cpp.s

CMakeFiles/GLFWTest.dir/deps/glad/glad.c.obj: CMakeFiles/GLFWTest.dir/flags.make
CMakeFiles/GLFWTest.dir/deps/glad/glad.c.obj: CMakeFiles/GLFWTest.dir/includes_C.rsp
CMakeFiles/GLFWTest.dir/deps/glad/glad.c.obj: ../deps/glad/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/GLFWTest.dir/deps/glad/glad.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\GLFWTest.dir\deps\glad\glad.c.obj   -c C:\Users\marce\Documents\Projekte\cpp\GLFWTest\deps\glad\glad.c

CMakeFiles/GLFWTest.dir/deps/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GLFWTest.dir/deps/glad/glad.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\marce\Documents\Projekte\cpp\GLFWTest\deps\glad\glad.c > CMakeFiles\GLFWTest.dir\deps\glad\glad.c.i

CMakeFiles/GLFWTest.dir/deps/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GLFWTest.dir/deps/glad/glad.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\marce\Documents\Projekte\cpp\GLFWTest\deps\glad\glad.c -o CMakeFiles\GLFWTest.dir\deps\glad\glad.c.s

# Object files for target GLFWTest
GLFWTest_OBJECTS = \
"CMakeFiles/GLFWTest.dir/main.cpp.obj" \
"CMakeFiles/GLFWTest.dir/FThread.cpp.obj" \
"CMakeFiles/GLFWTest.dir/deps/glad/glad.c.obj"

# External object files for target GLFWTest
GLFWTest_EXTERNAL_OBJECTS =

GLFWTest.exe: CMakeFiles/GLFWTest.dir/main.cpp.obj
GLFWTest.exe: CMakeFiles/GLFWTest.dir/FThread.cpp.obj
GLFWTest.exe: CMakeFiles/GLFWTest.dir/deps/glad/glad.c.obj
GLFWTest.exe: CMakeFiles/GLFWTest.dir/build.make
GLFWTest.exe: deps/glfw/src/libglfw3.a
GLFWTest.exe: CMakeFiles/GLFWTest.dir/linklibs.rsp
GLFWTest.exe: CMakeFiles/GLFWTest.dir/objects1.rsp
GLFWTest.exe: CMakeFiles/GLFWTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable GLFWTest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GLFWTest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GLFWTest.dir/build: GLFWTest.exe

.PHONY : CMakeFiles/GLFWTest.dir/build

CMakeFiles/GLFWTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GLFWTest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GLFWTest.dir/clean

CMakeFiles/GLFWTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\marce\Documents\Projekte\cpp\GLFWTest C:\Users\marce\Documents\Projekte\cpp\GLFWTest C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug C:\Users\marce\Documents\Projekte\cpp\GLFWTest\cmake-build-debug\CMakeFiles\GLFWTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GLFWTest.dir/depend
