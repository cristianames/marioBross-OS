################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Orquestador.c \
../Planificador.c \
../Plataforma.c \
../logger.c 

OBJS += \
./Orquestador.o \
./Planificador.o \
./Plataforma.o \
./logger.o 

C_DEPS += \
./Orquestador.d \
./Planificador.d \
./Plataforma.d \
./logger.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/utnso/GITHUB/tp-2013-2c-the-grid/Commons-Library -I/home/utnso/GITHUB/tp-2013-2c-the-grid/Biblioteca -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


