################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Driver/eeprom/eeprom.c 

OBJS += \
./Drivers/Driver/eeprom/eeprom.o 

C_DEPS += \
./Drivers/Driver/eeprom/eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Driver/eeprom/eeprom.o: ../Drivers/Driver/eeprom/eeprom.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/Driver/eeprom" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Core" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/Driver/motor_controller" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/Driver/log" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Algorithm/MRAC" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Algorithm/Fuzzy" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Algorithm" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/Driver/system" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/Driver/incremental_encoder" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/Driver/absolute_encoder" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Core/Inc" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/elastic_robot_arm/source/fw/elastic_robot_arm/Drivers/CMSIS/Include" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Driver/eeprom/eeprom.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

