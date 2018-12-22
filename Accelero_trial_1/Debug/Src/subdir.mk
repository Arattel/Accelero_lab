################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/i2c.c \
../Src/i2s.c \
../Src/l3gd20.c \
../Src/lsm303dlhc.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32f411e_discovery.c \
../Src/stm32f411e_discovery_accelerometer.c \
../Src/stm32f411e_discovery_gyroscope.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/usb_otg.c 

OBJS += \
./Src/gpio.o \
./Src/i2c.o \
./Src/i2s.o \
./Src/l3gd20.o \
./Src/lsm303dlhc.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32f411e_discovery.o \
./Src/stm32f411e_discovery_accelerometer.o \
./Src/stm32f411e_discovery_gyroscope.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/usb_otg.o 

C_DEPS += \
./Src/gpio.d \
./Src/i2c.d \
./Src/i2s.d \
./Src/l3gd20.d \
./Src/lsm303dlhc.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32f411e_discovery.d \
./Src/stm32f411e_discovery_accelerometer.d \
./Src/stm32f411e_discovery_gyroscope.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F411xE -I"/home/arattel/STM/Accelero_trial_1/Inc" -I/home/arattel/STM32Cube/Repository/STM32Cube_FW_F4_V1.21.0/Drivers/BSP/STM32F411E-Discovery -I"/home/arattel/STM/Accelero_trial_1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/arattel/STM/Accelero_trial_1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/arattel/STM/Accelero_trial_1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/arattel/STM/Accelero_trial_1/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


