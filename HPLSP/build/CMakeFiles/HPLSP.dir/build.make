# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/angusli/Code/HPLSP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/angusli/Code/HPLSP/build

# Include any dependencies generated for this target.
include CMakeFiles/HPLSP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HPLSP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HPLSP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HPLSP.dir/flags.make

CMakeFiles/HPLSP.dir/src/main.cpp.o: CMakeFiles/HPLSP.dir/flags.make
CMakeFiles/HPLSP.dir/src/main.cpp.o: /home/angusli/Code/HPLSP/src/main.cpp
CMakeFiles/HPLSP.dir/src/main.cpp.o: CMakeFiles/HPLSP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/angusli/Code/HPLSP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HPLSP.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HPLSP.dir/src/main.cpp.o -MF CMakeFiles/HPLSP.dir/src/main.cpp.o.d -o CMakeFiles/HPLSP.dir/src/main.cpp.o -c /home/angusli/Code/HPLSP/src/main.cpp

CMakeFiles/HPLSP.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HPLSP.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angusli/Code/HPLSP/src/main.cpp > CMakeFiles/HPLSP.dir/src/main.cpp.i

CMakeFiles/HPLSP.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HPLSP.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angusli/Code/HPLSP/src/main.cpp -o CMakeFiles/HPLSP.dir/src/main.cpp.s

# Object files for target HPLSP
HPLSP_OBJECTS = \
"CMakeFiles/HPLSP.dir/src/main.cpp.o"

# External object files for target HPLSP
HPLSP_EXTERNAL_OBJECTS =

HPLSP: CMakeFiles/HPLSP.dir/src/main.cpp.o
HPLSP: CMakeFiles/HPLSP.dir/build.make
HPLSP: CMakeFiles/HPLSP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/angusli/Code/HPLSP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HPLSP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HPLSP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HPLSP.dir/build: HPLSP
.PHONY : CMakeFiles/HPLSP.dir/build

CMakeFiles/HPLSP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HPLSP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HPLSP.dir/clean

CMakeFiles/HPLSP.dir/depend:
	cd /home/angusli/Code/HPLSP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/angusli/Code/HPLSP /home/angusli/Code/HPLSP /home/angusli/Code/HPLSP/build /home/angusli/Code/HPLSP/build /home/angusli/Code/HPLSP/build/CMakeFiles/HPLSP.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/HPLSP.dir/depend

