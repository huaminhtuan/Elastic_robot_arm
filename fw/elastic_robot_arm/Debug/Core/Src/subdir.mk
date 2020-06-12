################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/stm32f4xx_hal_msp.o: ../Core/Src/stm32f4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_msp.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_it.o: ../Core/Src/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_it.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f4xx.o: ../Core/Src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f4xx.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

