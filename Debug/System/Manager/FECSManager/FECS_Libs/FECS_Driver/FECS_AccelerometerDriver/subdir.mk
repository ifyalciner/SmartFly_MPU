################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_AccelerometerDriver/FECS_AccelerometerDriver.cpp 

OBJS += \
./System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_AccelerometerDriver/FECS_AccelerometerDriver.o 

CPP_DEPS += \
./System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_AccelerometerDriver/FECS_AccelerometerDriver.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_AccelerometerDriver/%.o: ../System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_AccelerometerDriver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


