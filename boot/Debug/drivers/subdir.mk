################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_cmp.c \
../drivers/fsl_cmt.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_crc.c \
../drivers/fsl_dac.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_dspi.c \
../drivers/fsl_dspi_edma.c \
../drivers/fsl_edma.c \
../drivers/fsl_enet.c \
../drivers/fsl_ewm.c \
../drivers/fsl_flexbus.c \
../drivers/fsl_flexcan.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_ftm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_i2c_edma.c \
../drivers/fsl_llwu.c \
../drivers/fsl_lmem_cache.c \
../drivers/fsl_lptmr.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_lpuart_edma.c \
../drivers/fsl_pdb.c \
../drivers/fsl_pit.c \
../drivers/fsl_pmc.c \
../drivers/fsl_rcm.c \
../drivers/fsl_rnga.c \
../drivers/fsl_rtc.c \
../drivers/fsl_sai.c \
../drivers/fsl_sai_edma.c \
../drivers/fsl_sdhc.c \
../drivers/fsl_sdramc.c \
../drivers/fsl_sim.c \
../drivers/fsl_smc.c \
../drivers/fsl_sysmpu.c \
../drivers/fsl_tpm.c \
../drivers/fsl_tsi_v4.c \
../drivers/fsl_uart.c \
../drivers/fsl_uart_edma.c \
../drivers/fsl_vref.c \
../drivers/fsl_wdog.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_cmp.o \
./drivers/fsl_cmt.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_crc.o \
./drivers/fsl_dac.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_dspi.o \
./drivers/fsl_dspi_edma.o \
./drivers/fsl_edma.o \
./drivers/fsl_enet.o \
./drivers/fsl_ewm.o \
./drivers/fsl_flexbus.o \
./drivers/fsl_flexcan.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_ftm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_i2c_edma.o \
./drivers/fsl_llwu.o \
./drivers/fsl_lmem_cache.o \
./drivers/fsl_lptmr.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_lpuart_edma.o \
./drivers/fsl_pdb.o \
./drivers/fsl_pit.o \
./drivers/fsl_pmc.o \
./drivers/fsl_rcm.o \
./drivers/fsl_rnga.o \
./drivers/fsl_rtc.o \
./drivers/fsl_sai.o \
./drivers/fsl_sai_edma.o \
./drivers/fsl_sdhc.o \
./drivers/fsl_sdramc.o \
./drivers/fsl_sim.o \
./drivers/fsl_smc.o \
./drivers/fsl_sysmpu.o \
./drivers/fsl_tpm.o \
./drivers/fsl_tsi_v4.o \
./drivers/fsl_uart.o \
./drivers/fsl_uart_edma.o \
./drivers/fsl_vref.o \
./drivers/fsl_wdog.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_cmp.d \
./drivers/fsl_cmt.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_crc.d \
./drivers/fsl_dac.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_dspi.d \
./drivers/fsl_dspi_edma.d \
./drivers/fsl_edma.d \
./drivers/fsl_enet.d \
./drivers/fsl_ewm.d \
./drivers/fsl_flexbus.d \
./drivers/fsl_flexcan.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_ftm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_i2c_edma.d \
./drivers/fsl_llwu.d \
./drivers/fsl_lmem_cache.d \
./drivers/fsl_lptmr.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_lpuart_edma.d \
./drivers/fsl_pdb.d \
./drivers/fsl_pit.d \
./drivers/fsl_pmc.d \
./drivers/fsl_rcm.d \
./drivers/fsl_rnga.d \
./drivers/fsl_rtc.d \
./drivers/fsl_sai.d \
./drivers/fsl_sai_edma.d \
./drivers/fsl_sdhc.d \
./drivers/fsl_sdramc.d \
./drivers/fsl_sim.d \
./drivers/fsl_smc.d \
./drivers/fsl_sysmpu.d \
./drivers/fsl_tpm.d \
./drivers/fsl_tsi_v4.d \
./drivers/fsl_uart.d \
./drivers/fsl_uart_edma.d \
./drivers/fsl_vref.d \
./drivers/fsl_wdog.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_BAREMETAL -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"J:\slavik2\embed_user_alg\boot\board" -I"J:\slavik2\embed_user_alg\boot\source" -I"J:\slavik2\embed_user_alg\boot\drivers" -I"J:\slavik2\embed_user_alg\boot\component\uart" -I"J:\slavik2\embed_user_alg\boot\component\serial_manager" -I"J:\slavik2\embed_user_alg\boot\utilities" -I"J:\slavik2\embed_user_alg\boot\component\lists" -I"J:\slavik2\embed_user_alg\boot\CMSIS" -I"J:\slavik2\embed_user_alg\boot\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


