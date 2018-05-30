################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../toolbox/CallbackBase.cpp \
../toolbox/Maths.cpp 

OBJS += \
./toolbox/CallbackBase.o \
./toolbox/Maths.o 

CPP_DEPS += \
./toolbox/CallbackBase.d \
./toolbox/Maths.d 


# Each subdirectory must supply rules for building sources it contributes
toolbox/%.o: ../toolbox/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D__cplusplus=201103L -D_GLIBCXX_USE_C99_STDINT_TR1 -I../includes -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


