################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../renderEngine/Display.cpp \
../renderEngine/EntityRenderer.cpp \
../renderEngine/Loader.cpp \
../renderEngine/MasterRenderer.cpp \
../renderEngine/TerrainRenderer.cpp 

OBJS += \
./renderEngine/Display.o \
./renderEngine/EntityRenderer.o \
./renderEngine/Loader.o \
./renderEngine/MasterRenderer.o \
./renderEngine/TerrainRenderer.o 

CPP_DEPS += \
./renderEngine/Display.d \
./renderEngine/EntityRenderer.d \
./renderEngine/Loader.d \
./renderEngine/MasterRenderer.d \
./renderEngine/TerrainRenderer.d 


# Each subdirectory must supply rules for building sources it contributes
renderEngine/%.o: ../renderEngine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D__cplusplus=201103L -D_GLIBCXX_USE_C99_STDINT_TR1 -I../includes -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


