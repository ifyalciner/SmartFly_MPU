################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/FECSManager/FECSManager.cpp 

OBJS += \
./System/Manager/FECSManager/FECSManager.o 

CPP_DEPS += \
./System/Manager/FECSManager/FECSManager.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/FECSManager/%.o: ../System/Manager/FECSManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


