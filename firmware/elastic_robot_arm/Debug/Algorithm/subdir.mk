################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Algorithm/controller.c 

OBJS += \
./Algorithm/controller.o 

C_DEPS += \
./Algorithm/controller.d 


# Each subdirectory must supply rules for building sources it contributes
Algorithm/controller.o: ../Algorithm/controller.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Algorithm/controller.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

