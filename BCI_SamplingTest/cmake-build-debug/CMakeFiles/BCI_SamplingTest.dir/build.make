# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/lhrobs/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lhrobs/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lhrobs/CLionProjects/BCI_SamplingTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BCI_SamplingTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BCI_SamplingTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BCI_SamplingTest.dir/flags.make

CMakeFiles/BCI_SamplingTest.dir/main.c.o: CMakeFiles/BCI_SamplingTest.dir/flags.make
CMakeFiles/BCI_SamplingTest.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/BCI_SamplingTest.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_SamplingTest.dir/main.c.o   -c /home/lhrobs/CLionProjects/BCI_SamplingTest/main.c

CMakeFiles/BCI_SamplingTest.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_SamplingTest.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/CLionProjects/BCI_SamplingTest/main.c > CMakeFiles/BCI_SamplingTest.dir/main.c.i

CMakeFiles/BCI_SamplingTest.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_SamplingTest.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/CLionProjects/BCI_SamplingTest/main.c -o CMakeFiles/BCI_SamplingTest.dir/main.c.s

# Object files for target BCI_SamplingTest
BCI_SamplingTest_OBJECTS = \
"CMakeFiles/BCI_SamplingTest.dir/main.c.o"

# External object files for target BCI_SamplingTest
BCI_SamplingTest_EXTERNAL_OBJECTS =

BCI_SamplingTest: CMakeFiles/BCI_SamplingTest.dir/main.c.o
BCI_SamplingTest: CMakeFiles/BCI_SamplingTest.dir/build.make
BCI_SamplingTest: CMakeFiles/BCI_SamplingTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable BCI_SamplingTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BCI_SamplingTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BCI_SamplingTest.dir/build: BCI_SamplingTest

.PHONY : CMakeFiles/BCI_SamplingTest.dir/build

CMakeFiles/BCI_SamplingTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BCI_SamplingTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BCI_SamplingTest.dir/clean

CMakeFiles/BCI_SamplingTest.dir/depend:
	cd /home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lhrobs/CLionProjects/BCI_SamplingTest /home/lhrobs/CLionProjects/BCI_SamplingTest /home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug /home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug /home/lhrobs/CLionProjects/BCI_SamplingTest/cmake-build-debug/CMakeFiles/BCI_SamplingTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BCI_SamplingTest.dir/depend
