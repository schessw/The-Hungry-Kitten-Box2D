# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = C:\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Box2D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Box2D\Build

# Include any dependencies generated for this target.
include HelloWorld/CMakeFiles/HelloWorld.dir/depend.make

# Include the progress variables for this target.
include HelloWorld/CMakeFiles/HelloWorld.dir/progress.make

# Include the compile flags for this target's objects.
include HelloWorld/CMakeFiles/HelloWorld.dir/flags.make

HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.obj: HelloWorld/CMakeFiles/HelloWorld.dir/flags.make
HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.obj: HelloWorld/CMakeFiles/HelloWorld.dir/includes_CXX.rsp
HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.obj: ../HelloWorld/HelloWorld.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Box2D\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.obj"
	cd /d C:\Box2D\Build\HelloWorld && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HelloWorld.dir\HelloWorld.cpp.obj -c C:\Box2D\HelloWorld\HelloWorld.cpp

HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloWorld.dir/HelloWorld.cpp.i"
	cd /d C:\Box2D\Build\HelloWorld && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Box2D\HelloWorld\HelloWorld.cpp > CMakeFiles\HelloWorld.dir\HelloWorld.cpp.i

HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloWorld.dir/HelloWorld.cpp.s"
	cd /d C:\Box2D\Build\HelloWorld && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Box2D\HelloWorld\HelloWorld.cpp -o CMakeFiles\HelloWorld.dir\HelloWorld.cpp.s

# Object files for target HelloWorld
HelloWorld_OBJECTS = \
"CMakeFiles/HelloWorld.dir/HelloWorld.cpp.obj"

# External object files for target HelloWorld
HelloWorld_EXTERNAL_OBJECTS =

HelloWorld/HelloWorld.exe: HelloWorld/CMakeFiles/HelloWorld.dir/HelloWorld.cpp.obj
HelloWorld/HelloWorld.exe: HelloWorld/CMakeFiles/HelloWorld.dir/build.make
HelloWorld/HelloWorld.exe: Box2D/libBox2D.a
HelloWorld/HelloWorld.exe: HelloWorld/CMakeFiles/HelloWorld.dir/linklibs.rsp
HelloWorld/HelloWorld.exe: HelloWorld/CMakeFiles/HelloWorld.dir/objects1.rsp
HelloWorld/HelloWorld.exe: HelloWorld/CMakeFiles/HelloWorld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Box2D\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HelloWorld.exe"
	cd /d C:\Box2D\Build\HelloWorld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HelloWorld.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
HelloWorld/CMakeFiles/HelloWorld.dir/build: HelloWorld/HelloWorld.exe

.PHONY : HelloWorld/CMakeFiles/HelloWorld.dir/build

HelloWorld/CMakeFiles/HelloWorld.dir/clean:
	cd /d C:\Box2D\Build\HelloWorld && $(CMAKE_COMMAND) -P CMakeFiles\HelloWorld.dir\cmake_clean.cmake
.PHONY : HelloWorld/CMakeFiles/HelloWorld.dir/clean

HelloWorld/CMakeFiles/HelloWorld.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Box2D C:\Box2D\HelloWorld C:\Box2D\Build C:\Box2D\Build\HelloWorld C:\Box2D\Build\HelloWorld\CMakeFiles\HelloWorld.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : HelloWorld/CMakeFiles/HelloWorld.dir/depend
