################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/MPU_System.cpp \
../System/MPU_SystemAllInclude.cpp \
../System/main.cpp 

OBJS += \
./System/MPU_System.o \
./System/MPU_SystemAllInclude.o \
./System/main.o 

CPP_DEPS += \
./System/MPU_System.d \
./System/MPU_SystemAllInclude.d \
./System/main.d 


# Each subdirectory must supply rules for building sources it contributes
System/%.o: ../System/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


