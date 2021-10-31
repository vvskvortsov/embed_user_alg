################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/freertos_kernel/event_groups.c \
../amazon-freertos/freertos_kernel/list.c \
../amazon-freertos/freertos_kernel/queue.c \
../amazon-freertos/freertos_kernel/stream_buffer.c \
../amazon-freertos/freertos_kernel/tasks.c \
../amazon-freertos/freertos_kernel/timers.c 

OBJS += \
./amazon-freertos/freertos_kernel/event_groups.o \
./amazon-freertos/freertos_kernel/list.o \
./amazon-freertos/freertos_kernel/queue.o \
./amazon-freertos/freertos_kernel/stream_buffer.o \
./amazon-freertos/freertos_kernel/tasks.o \
./amazon-freertos/freertos_kernel/timers.o 

C_DEPS += \
./amazon-freertos/freertos_kernel/event_groups.d \
./amazon-freertos/freertos_kernel/list.d \
./amazon-freertos/freertos_kernel/queue.d \
./amazon-freertos/freertos_kernel/stream_buffer.d \
./amazon-freertos/freertos_kernel/tasks.d \
./amazon-freertos/freertos_kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/freertos_kernel/%.o: ../amazon-freertos/freertos_kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c17 -D__NEWLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\board" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\source" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\amazon-freertos\freertos_kernel\include" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\drivers" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\component\uart" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\component\serial_manager" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\utilities" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\component\lists" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\device" -I"D:\work\prog\user_alg_embedded\embed_user_alg_os\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

