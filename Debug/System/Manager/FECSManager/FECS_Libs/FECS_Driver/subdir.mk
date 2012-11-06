################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_Driver.cpp 

OBJS += \
./System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_Driver.o 

CPP_DEPS += \
./System/Manager/FECSManager/FECS_Libs/FECS_Driver/FECS_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/FECSManager/FECS_Libs/FECS_Driver/%.o: ../System/Manager/FECSManager/FECS_Libs/FECS_Driver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


