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
CMAKE_SOURCE_DIR = /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi

# Include any dependencies generated for this target.
include CMakeFiles/BCI_NeuroRace.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BCI_NeuroRace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BCI_NeuroRace.dir/flags.make

CMakeFiles/BCI_NeuroRace.dir/main.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/BCI_NeuroRace.dir/main.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/main.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/main.c

CMakeFiles/BCI_NeuroRace.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/main.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/main.c > CMakeFiles/BCI_NeuroRace.dir/main.c.i

CMakeFiles/BCI_NeuroRace.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/main.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/main.c -o CMakeFiles/BCI_NeuroRace.dir/main.c.s

CMakeFiles/BCI_NeuroRace.dir/filtering.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/filtering.c.o: ../filtering.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/BCI_NeuroRace.dir/filtering.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/filtering.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/filtering.c

CMakeFiles/BCI_NeuroRace.dir/filtering.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/filtering.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/filtering.c > CMakeFiles/BCI_NeuroRace.dir/filtering.c.i

CMakeFiles/BCI_NeuroRace.dir/filtering.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/filtering.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/filtering.c -o CMakeFiles/BCI_NeuroRace.dir/filtering.c.s

CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.o: ../boardInitializer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/boardInitializer.c

CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/boardInitializer.c > CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.i

CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/boardInitializer.c -o CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.s

CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.o: ../BitConversion.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/BitConversion.c

CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/BitConversion.c > CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.i

CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/BitConversion.c -o CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.s

CMakeFiles/BCI_NeuroRace.dir/calibrator.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/calibrator.c.o: ../calibrator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/BCI_NeuroRace.dir/calibrator.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/calibrator.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/calibrator.c

CMakeFiles/BCI_NeuroRace.dir/calibrator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/calibrator.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/calibrator.c > CMakeFiles/BCI_NeuroRace.dir/calibrator.c.i

CMakeFiles/BCI_NeuroRace.dir/calibrator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/calibrator.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/calibrator.c -o CMakeFiles/BCI_NeuroRace.dir/calibrator.c.s

CMakeFiles/BCI_NeuroRace.dir/sampler.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/sampler.c.o: ../sampler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/BCI_NeuroRace.dir/sampler.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/sampler.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/sampler.c

CMakeFiles/BCI_NeuroRace.dir/sampler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/sampler.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/sampler.c > CMakeFiles/BCI_NeuroRace.dir/sampler.c.i

CMakeFiles/BCI_NeuroRace.dir/sampler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/sampler.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/sampler.c -o CMakeFiles/BCI_NeuroRace.dir/sampler.c.s

CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.o: ../fftWorker.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/fftWorker.c

CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/fftWorker.c > CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.i

CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/fftWorker.c -o CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.s

CMakeFiles/BCI_NeuroRace.dir/controller.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/controller.c.o: ../controller.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/BCI_NeuroRace.dir/controller.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/controller.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/controller.c

CMakeFiles/BCI_NeuroRace.dir/controller.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/controller.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/controller.c > CMakeFiles/BCI_NeuroRace.dir/controller.c.i

CMakeFiles/BCI_NeuroRace.dir/controller.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/controller.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/controller.c -o CMakeFiles/BCI_NeuroRace.dir/controller.c.s

CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.o: CMakeFiles/BCI_NeuroRace.dir/flags.make
CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.o: ../signalHandlers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.o"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.o   -c /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/signalHandlers.c

CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.i"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/signalHandlers.c > CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.i

CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.s"
	/home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc-4.8.3 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/signalHandlers.c -o CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.s

# Object files for target BCI_NeuroRace
BCI_NeuroRace_OBJECTS = \
"CMakeFiles/BCI_NeuroRace.dir/main.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/filtering.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/calibrator.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/sampler.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/controller.c.o" \
"CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.o"

# External object files for target BCI_NeuroRace
BCI_NeuroRace_EXTERNAL_OBJECTS =

BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/main.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/filtering.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/boardInitializer.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/BitConversion.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/calibrator.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/sampler.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/fftWorker.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/controller.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/signalHandlers.c.o
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/build.make
BCI_NeuroRace: CMakeFiles/BCI_NeuroRace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable BCI_NeuroRace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BCI_NeuroRace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BCI_NeuroRace.dir/build: BCI_NeuroRace

.PHONY : CMakeFiles/BCI_NeuroRace.dir/build

CMakeFiles/BCI_NeuroRace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BCI_NeuroRace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BCI_NeuroRace.dir/clean

CMakeFiles/BCI_NeuroRace.dir/depend:
	cd /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi /home/lhrobs/Documents/GitHub/BCI-RomeCup/BCI_NeuroRace/cmake-build-debug-raspberry-pi/CMakeFiles/BCI_NeuroRace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BCI_NeuroRace.dir/depend

