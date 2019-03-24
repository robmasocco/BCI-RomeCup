cmake_minimum_required(VERSION 3.13)
project(BCI_SamplingTest C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# ARM toolchain settings
set(CMAKE_FIND_ROOT_PATH /home/lhrobs/raspberrypi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
include_directories(/home/lhrobs/raspberrypi/rootfs/usr/local/include)
link_directories(/home/lhrobs/raspberrypi/rootfs/usr/local/lib)

add_executable(BCI_SamplingTest main.c boardInitializer.c SPI_Definitions.h
        sampler.c BCI_SamplingTest.h BitConversion.c fftWorker.c printer.c filtering.c)
target_link_libraries(BCI_SamplingTest pthread bcm2835 fftw3 m)
target_compile_definitions(BCI_SamplingTest PUBLIC BANDPASS)
