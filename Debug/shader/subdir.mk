################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../shader/ShaderProgram.cpp \
../shader/StaticShader.cpp \
../shader/TerrainShader.cpp 

OBJS += \
./shader/ShaderProgram.o \
./shader/StaticShader.o \
./shader/TerrainShader.o 

CPP_DEPS += \
./shader/ShaderProgram.d \
./shader/StaticShader.d \
./shader/TerrainShader.d 


# Each subdirectory must supply rules for building sources it contributes
shader/%.o: ../shader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D__cplusplus=201103L -D_GLIBCXX_USE_C99_STDINT_TR1 -I../includes -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


