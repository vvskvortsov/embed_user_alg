################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/boot.c \
../source/semihost_hardfault.c 

OBJS += \
./source/boot.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/boot.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_BAREMETAL -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"J:\slavik2\embed_user_alg\boot\board" -I"J:\slavik2\embed_user_alg\boot\source" -I"J:\slavik2\embed_user_alg\boot\drivers" -I"J:\slavik2\embed_user_alg\boot\component\uart" -I"J:\slavik2\embed_user_alg\boot\component\serial_manager" -I"J:\slavik2\embed_user_alg\boot\utilities" -I"J:\slavik2\embed_user_alg\boot\component\lists" -I"J:\slavik2\embed_user_alg\boot\CMSIS" -I"J:\slavik2\embed_user_alg\boot\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


