################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/FlightMonitorManager/FlightMonitorManager.cpp 

OBJS += \
./System/Manager/FlightMonitorManager/FlightMonitorManager.o 

CPP_DEPS += \
./System/Manager/FlightMonitorManager/FlightMonitorManager.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/FlightMonitorManager/%.o: ../System/Manager/FlightMonitorManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


