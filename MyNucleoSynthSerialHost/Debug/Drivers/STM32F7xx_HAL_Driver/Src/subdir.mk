################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_can.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cec.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dfsdm.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma2d.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dsi.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hcd.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2s.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_irda.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_iwdg.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_jpeg.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_lptim.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mdios.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nand.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nor.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_qspi.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rng.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sd.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sdram.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spdifrx.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sram.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_usart.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_wwdg.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_adc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_crc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_fmc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_sdmmc.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c \
../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.c 

OBJS += \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_can.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cec.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dfsdm.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma2d.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dsi.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hcd.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2s.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_irda.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_iwdg.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_jpeg.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_lptim.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mdios.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nand.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nor.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_qspi.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rng.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sd.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sdram.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spdifrx.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sram.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_usart.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_wwdg.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_adc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_crc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_fmc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_sdmmc.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.o \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.o 

C_DEPS += \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_can.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cec.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_crc_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cryp_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dac_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dcmi_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dfsdm.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma2d.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dsi.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hash_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_hcd.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2s.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_irda.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_iwdg.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_jpeg.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_lptim.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_ltdc_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mdios.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nand.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nor.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_qspi.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rng.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sai_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sd.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sdram.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smartcard_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_smbus.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spdifrx.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_sram.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_usart.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_wwdg.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_adc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_crc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dac.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_dma2d.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_exti.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_fmc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_gpio.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_i2c.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_lptim.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_pwr.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rcc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rng.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_rtc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_sdmmc.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_spi.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_tim.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usart.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.d \
./Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F7xx_HAL_Driver/Src/%.o: ../Drivers/STM32F7xx_HAL_Driver/Src/%.c Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DHSE_VALUE=8000000 -DSTM32F767xx -DLSI_VALUE=32000 -DHSE_STARTUP_TIMEOUT=100 -DHSI_VALUE=16000000 -DDEBUG -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DART_ACCLERATOR_ENABLE=0 -DEXTERNAL_CLOCK_VALUE=12288000 -DVDD_VALUE=3300 -DUSE_FULL_LL_DRIVER -DPREFETCH_ENABLE=0 -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
