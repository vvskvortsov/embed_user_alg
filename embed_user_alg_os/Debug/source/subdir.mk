################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/MK66F18_Project.cpp \
../source/cpp_config.cpp 

C_SRCS += \
../source/semihost_hardfault.c 

OBJS += \
./source/MK66F18_Project.o \
./source/cpp_config.o \
./source/semihost_hardfault.o 

CPP_DEPS += \
./source/MK66F18_Project.d \
./source/cpp_config.d 

C_DEPS += \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=gnu++17 -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=0 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DSERIAL_PORT_TYPE_SWO=1 -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\drivers" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\uart" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\utilities" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\serial_manager" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\lists" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\include" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\CMSIS" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\template\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\device" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\drivers" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\uart" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\serial_manager" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\utilities" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\lists" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\include" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\CMSIS" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\template\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\device" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\board" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\source" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\amazon-freertos\freertos_kernel\include" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c17 -D__NEWLIB__ -DSERIAL_PORT_TYPE_SWO=1 -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=0 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\drivers" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\uart" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\utilities" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\serial_manager" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\lists" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\include" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\CMSIS" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\template\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\device" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\drivers" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\uart" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\serial_manager" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\utilities" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\component\lists" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\include" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\CMSIS" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\freertos\template\ARM_CM4F" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\device" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\board" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\source" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\amazon-freertos\freertos_kernel\include" -I"J:\Dev\local_mode\embed_user_alg\embed_user_alg_os\amazon-freertos\freertos_kernel\portable\GCC\ARM_CM4F" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


