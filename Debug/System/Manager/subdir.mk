################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Manager/Manager.cpp \
../System/Manager/Message.cpp 

OBJS += \
./System/Manager/Manager.o \
./System/Manager/Message.o 

CPP_DEPS += \
./System/Manager/Manager.d \
./System/Manager/Message.d 


# Each subdirectory must supply rules for building sources it contributes
System/Manager/%.o: ../System/Manager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


