################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/l3gd20.c \
../Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/lsm303dlhc.c \
../Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery.c \
../Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery_accelerometer.c \
../Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery_gyroscope.c 

OBJS += \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/l3gd20.o \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/lsm303dlhc.o \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery.o \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery_accelerometer.o \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery_gyroscope.o 

C_DEPS += \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/l3gd20.d \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/lsm303dlhc.d \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery.d \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery_accelerometer.d \
./Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/stm32f3_discovery_gyroscope.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/%.o: ../Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F411xE -I"/home/arattel/STM/Accelero_trial_1/Inc" -I/home/arattel/STM/Accelero_trial_1/Drivers/STM32F3Discovery_BSP_Drivers/Drivers/STM32F3Discovery/Inc -I/home/arattel/STM32Cube/Repository/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM32F411E-Discovery -I"/home/arattel/STM/Accelero_trial_1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/arattel/STM/Accelero_trial_1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/arattel/STM/Accelero_trial_1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/arattel/STM/Accelero_trial_1/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


