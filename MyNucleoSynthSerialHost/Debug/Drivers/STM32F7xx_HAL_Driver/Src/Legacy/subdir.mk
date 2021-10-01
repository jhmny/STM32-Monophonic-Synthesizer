################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F7xx_HAL_Driver/Src/Legacy/stm32f7xx_hal_can.c 

OBJS += \
./Drivers/STM32F7xx_HAL_Driver/Src/Legacy/stm32f7xx_hal_can.o 

C_DEPS += \
./Drivers/STM32F7xx_HAL_Driver/Src/Legacy/stm32f7xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F7xx_HAL_Driver/Src/Legacy/%.o: ../Drivers/STM32F7xx_HAL_Driver/Src/Legacy/%.c Drivers/STM32F7xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DHSE_VALUE=8000000 -DSTM32F767xx -DLSI_VALUE=32000 -DHSE_STARTUP_TIMEOUT=100 -DHSI_VALUE=16000000 -DDEBUG -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DART_ACCLERATOR_ENABLE=0 -DEXTERNAL_CLOCK_VALUE=12288000 -DVDD_VALUE=3300 -DUSE_FULL_LL_DRIVER -DPREFETCH_ENABLE=0 -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

