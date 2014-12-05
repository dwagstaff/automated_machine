################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/app_scheduler.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_cmd_decoder.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_dtm_cmd_decoder.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_error_handling.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_event_encoder.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_handlers.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_pkt_decoder.c 

OBJS += \
./Nordic_SDK_Source/serialization/connectivity/app_scheduler.o \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_cmd_decoder.o \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_dtm_cmd_decoder.o \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_error_handling.o \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_event_encoder.o \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_handlers.o \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_pkt_decoder.o 

C_DEPS += \
./Nordic_SDK_Source/serialization/connectivity/app_scheduler.d \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_cmd_decoder.d \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_dtm_cmd_decoder.d \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_error_handling.d \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_event_encoder.d \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_handlers.d \
./Nordic_SDK_Source/serialization/connectivity/ser_conn_pkt_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
Nordic_SDK_Source/serialization/connectivity/app_scheduler.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/app_scheduler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/connectivity/ser_conn_cmd_decoder.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_cmd_decoder.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/connectivity/ser_conn_dtm_cmd_decoder.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_dtm_cmd_decoder.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/connectivity/ser_conn_error_handling.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_error_handling.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/connectivity/ser_conn_event_encoder.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_event_encoder.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/connectivity/ser_conn_handlers.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_handlers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/serialization/connectivity/ser_conn_pkt_decoder.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/serialization/connectivity/ser_conn_pkt_decoder.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


