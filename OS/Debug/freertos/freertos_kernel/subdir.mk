################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/croutine.c \
../freertos/freertos_kernel/event_groups.c \
../freertos/freertos_kernel/list.c \
../freertos/freertos_kernel/queue.c \
../freertos/freertos_kernel/stream_buffer.c \
../freertos/freertos_kernel/tasks.c \
../freertos/freertos_kernel/timers.c 

OBJS += \
./freertos/freertos_kernel/croutine.o \
./freertos/freertos_kernel/event_groups.o \
./freertos/freertos_kernel/list.o \
./freertos/freertos_kernel/queue.o \
./freertos/freertos_kernel/stream_buffer.o \
./freertos/freertos_kernel/tasks.o \
./freertos/freertos_kernel/timers.o 

C_DEPS += \
./freertos/freertos_kernel/croutine.d \
./freertos/freertos_kernel/event_groups.d \
./freertos/freertos_kernel/list.d \
./freertos/freertos_kernel/queue.d \
./freertos/freertos_kernel/stream_buffer.d \
./freertos/freertos_kernel/tasks.d \
./freertos/freertos_kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/%.o: ../freertos/freertos_kernel/%.c freertos/freertos_kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__NEWLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\board" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\source" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\freertos\freertos_kernel\include" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\drivers" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\drivers\freertos" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\component\uart" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\component\serial_manager" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\utilities" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\component\lists" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\CMSIS" -I"C:\Users\skvortsov\Documents\MCUXpressoIDE_11.5.1_7266\workspace\OS\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


