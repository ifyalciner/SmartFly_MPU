################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/FECSManager/Serial/AsyncSerial.cpp \
../System/Manager/FECSManager/Serial/BufferedAsyncSerial.cpp 

OBJS += \
./System/Manager/FECSManager/Serial/AsyncSerial.o \
./System/Manager/FECSManager/Serial/BufferedAsyncSerial.o 

CPP_DEPS += \
./System/Manager/FECSManager/Serial/AsyncSerial.d \
./System/Manager/FECSManager/Serial/BufferedAsyncSerial.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/FECSManager/Serial/%.o: ../System/Manager/FECSManager/Serial/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


