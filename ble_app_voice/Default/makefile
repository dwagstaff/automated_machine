################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include Nordic_SDK_Source/templates/subdir.mk
-include Nordic_SDK_Source/spi_slave/subdir.mk
-include Nordic_SDK_Source/spi_master/subdir.mk
-include Nordic_SDK_Source/simple_uart/subdir.mk
-include Nordic_SDK_Source/serialization/connectivity/hal/subdir.mk
-include Nordic_SDK_Source/serialization/connectivity/codecs/s110/serializers/subdir.mk
-include Nordic_SDK_Source/serialization/connectivity/codecs/s110/middleware/subdir.mk
-include Nordic_SDK_Source/serialization/connectivity/codecs/common/subdir.mk
-include Nordic_SDK_Source/serialization/connectivity/subdir.mk
-include Nordic_SDK_Source/serialization/common/transport/debug/subdir.mk
-include Nordic_SDK_Source/serialization/common/transport/subdir.mk
-include Nordic_SDK_Source/serialization/common/struct_ser/s110/subdir.mk
-include Nordic_SDK_Source/serialization/common/subdir.mk
-include Nordic_SDK_Source/serialization/application/transport/subdir.mk
-include Nordic_SDK_Source/serialization/application/hal/subdir.mk
-include Nordic_SDK_Source/serialization/application/codecs/s110/serializers/subdir.mk
-include Nordic_SDK_Source/serialization/application/codecs/s110/middleware/subdir.mk
-include Nordic_SDK_Source/serialization/application/codecs/common/subdir.mk
-include Nordic_SDK_Source/sdk_soc/subdir.mk
-include Nordic_SDK_Source/sd_common/subdir.mk
-include Nordic_SDK_Source/nrf_nvmc/subdir.mk
-include Nordic_SDK_Source/nrf_ecb/subdir.mk
-include Nordic_SDK_Source/nrf_delay/subdir.mk
-include Nordic_SDK_Source/nrf_assert/subdir.mk
-include Nordic_SDK_Source/gzp/subdir.mk
-include Nordic_SDK_Source/ext_sensors/synaptics_touchpad/subdir.mk
-include Nordic_SDK_Source/ext_sensors/sdio/subdir.mk
-include Nordic_SDK_Source/ext_sensors/nrf6350/subdir.mk
-include Nordic_SDK_Source/ext_sensors/mpu6050/subdir.mk
-include Nordic_SDK_Source/ext_sensors/ds1624/subdir.mk
-include Nordic_SDK_Source/ext_sensors/cherry8x16/subdir.mk
-include Nordic_SDK_Source/ext_sensors/adns2080/subdir.mk
-include Nordic_SDK_Source/console/subdir.mk
-include Nordic_SDK_Source/bootloader_dfu/subdir.mk
-include Nordic_SDK_Source/ble/device_manager/subdir.mk
-include Nordic_SDK_Source/ble/ble_services/subdir.mk
-include Nordic_SDK_Source/ble/subdir.mk
-include Nordic_SDK_Source/app_common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ble_app_hrs

# Tool invocations
ble_app_hrs: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -Xlinker --gc-sections -Wl,-Map,"ble_app_hrs.map" -o "ble_app_hrs" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(S_UPPER_DEPS) ble_app_hrs
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
