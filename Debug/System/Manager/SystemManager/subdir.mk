################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/SystemManager/SystemManager.cpp 

OBJS += \
./System/Manager/SystemManager/SystemManager.o 

CPP_DEPS += \
./System/Manager/SystemManager/SystemManager.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/SystemManager/%.o: ../System/Manager/SystemManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


