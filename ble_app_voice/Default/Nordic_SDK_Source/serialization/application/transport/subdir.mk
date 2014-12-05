################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/application/transport/app_mailbox.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/application/transport/ser_sd_transport.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/application/transport/ser_softdevice_handler.c 

OBJS += \
./Nordic_SDK_Source/serialization/application/transport/app_mailbox.o \
./Nordic_SDK_Source/serialization/application/transport/ser_sd_transport.o \
./Nordic_SDK_Source/serialization/application/transport/ser_softdevice_handler.o 

C_DEPS += \
./Nordic_SDK_Source/serialization/application/transport/app_mailbox.d \
./Nordic_SDK_Source/serialization/application/transport/ser_sd_transport.d \
./Nordic_SDK_Source/serialization/application/transport/ser_softdevice_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Nordic_SDK_Source/serialization/application/transport/app_mailbox.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/application/transport/app_mailbox.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/application/transport/ser_sd_transport.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/application/transport/ser_sd_transport.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/application/transport/ser_softdevice_handler.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/application/transport/ser_softdevice_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


