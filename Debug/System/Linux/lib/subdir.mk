################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Linux/lib/alt_functions.c \
../System/Linux/lib/error_functions.c \
../System/Linux/lib/get_num.c 

OBJS += \
./System/Linux/lib/alt_functions.o \
./System/Linux/lib/error_functions.o \
./System/Linux/lib/get_num.o 

C_DEPS += \
./System/Linux/lib/alt_functions.d \
./System/Linux/lib/error_functions.d \
./System/Linux/lib/get_num.d 


# Each subdirectory must supply rules for building sources it contributes
System/Linux/lib/%.o: ../System/Linux/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


