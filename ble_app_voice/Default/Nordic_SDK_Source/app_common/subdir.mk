################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_button.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_fifo.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_gpiote.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_scheduler.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_timer.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_trace.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_uart.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_uart_fifo.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/crc16.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/hci_mem_pool.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/hci_slip.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/hci_transport.c \
C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/pstorage.c 

OBJS += \
./Nordic_SDK_Source/app_common/app_button.o \
./Nordic_SDK_Source/app_common/app_fifo.o \
./Nordic_SDK_Source/app_common/app_gpiote.o \
./Nordic_SDK_Source/app_common/app_scheduler.o \
./Nordic_SDK_Source/app_common/app_timer.o \
./Nordic_SDK_Source/app_common/app_trace.o \
./Nordic_SDK_Source/app_common/app_uart.o \
./Nordic_SDK_Source/app_common/app_uart_fifo.o \
./Nordic_SDK_Source/app_common/crc16.o \
./Nordic_SDK_Source/app_common/hci_mem_pool.o \
./Nordic_SDK_Source/app_common/hci_slip.o \
./Nordic_SDK_Source/app_common/hci_transport.o \
./Nordic_SDK_Source/app_common/pstorage.o 

C_DEPS += \
./Nordic_SDK_Source/app_common/app_button.d \
./Nordic_SDK_Source/app_common/app_fifo.d \
./Nordic_SDK_Source/app_common/app_gpiote.d \
./Nordic_SDK_Source/app_common/app_scheduler.d \
./Nordic_SDK_Source/app_common/app_timer.d \
./Nordic_SDK_Source/app_common/app_trace.d \
./Nordic_SDK_Source/app_common/app_uart.d \
./Nordic_SDK_Source/app_common/app_uart_fifo.d \
./Nordic_SDK_Source/app_common/crc16.d \
./Nordic_SDK_Source/app_common/hci_mem_pool.d \
./Nordic_SDK_Source/app_common/hci_slip.d \
./Nordic_SDK_Source/app_common/hci_transport.d \
./Nordic_SDK_Source/app_common/pstorage.d 


# Each subdirectory must supply rules for building sources it contributes
Nordic_SDK_Source/app_common/app_button.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_button.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_fifo.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_fifo.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_gpiote.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_gpiote.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_scheduler.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_scheduler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_timer.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_trace.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_trace.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_uart.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/app_uart_fifo.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/app_uart_fifo.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/crc16.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/crc16.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/hci_mem_pool.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/hci_mem_pool.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/hci_slip.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/hci_slip.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/hci_transport.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/hci_transport.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Nordic_SDK_Source/app_common/pstorage.o: C:/Users/dwagstaff/Google\ Drive/SDK/nrf51_sdk_v6_1_0_b2ec2e6/nrf51822/Source/app_common/pstorage.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2  -g -DBOARD_NRF6310 -DBLE_STACK_SUPPORT_REQD -DNRF51 -DDEBUG_NRF_USER -DS110 -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\arm-none-eabi\include" -I"C:\Program Files (x86)\GNU Tools ARM Embedded\4.8 2013q4\lib\gcc\arm-none-eabi\4.8.3\include" -I"C:\Users\dwagstaff\workspace\ble_app_voice" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\device_manager" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\app_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\ble\ble_services" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\s110" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sd_common" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\gcc" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\bootloader_dfu" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include" -I"C:\Users\dwagstaff\Google Drive\SDK\nrf51_sdk_v6_1_0_b2ec2e6\nrf51822\Include\sdk" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


