# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

#Suppress display of executed commands.
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
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP

# Include any dependencies generated for this target.
include CMakeFiles/snow.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/snow.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/snow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/snow.dir/flags.make

CMakeFiles/snow.dir/main.cpp.obj: CMakeFiles/snow.dir/flags.make
CMakeFiles/snow.dir/main.cpp.obj: main.cpp
CMakeFiles/snow.dir/main.cpp.obj: CMakeFiles/snow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/snow.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/snow.dir/main.cpp.obj -MF CMakeFiles\snow.dir\main.cpp.obj.d -o CMakeFiles\snow.dir\main.cpp.obj -c C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP\main.cpp

CMakeFiles/snow.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snow.dir/main.cpp.i"
	C:\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP\main.cpp > CMakeFiles\snow.dir\main.cpp.i

CMakeFiles/snow.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snow.dir/main.cpp.s"
	C:\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP\main.cpp -o CMakeFiles\snow.dir\main.cpp.s

# Object files for target snow
snow_OBJECTS = \
"CMakeFiles/snow.dir/main.cpp.obj"

# External object files for target snow
snow_EXTERNAL_OBJECTS =

snow.exe: CMakeFiles/snow.dir/main.cpp.obj
snow.exe: CMakeFiles/snow.dir/build.make
snow.exe: CMakeFiles/snow.dir/linklibs.rsp
snow.exe: CMakeFiles/snow.dir/objects1.rsp
snow.exe: CMakeFiles/snow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable snow.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\snow.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/snow.dir/build: snow.exe
.PHONY : CMakeFiles/snow.dir/build

CMakeFiles/snow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\snow.dir\cmake_clean.cmake
.PHONY : CMakeFiles/snow.dir/clean

CMakeFiles/snow.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP C:\Users\qazse\Documents\GitHub\CCpp\DSA_CPP\CMakeFiles\snow.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/snow.dir/depend

