################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Algorithm/Fuzzy/Fuzzy.c \
../Algorithm/Fuzzy/rtGetInf.c \
../Algorithm/Fuzzy/rtGetNaN.c \
../Algorithm/Fuzzy/rt_nonfinite.c 

OBJS += \
./Algorithm/Fuzzy/Fuzzy.o \
./Algorithm/Fuzzy/rtGetInf.o \
./Algorithm/Fuzzy/rtGetNaN.o \
./Algorithm/Fuzzy/rt_nonfinite.o 

C_DEPS += \
./Algorithm/Fuzzy/Fuzzy.d \
./Algorithm/Fuzzy/rtGetInf.d \
./Algorithm/Fuzzy/rtGetNaN.d \
./Algorithm/Fuzzy/rt_nonfinite.d 


# Each subdirectory must supply rules for building sources it contributes
Algorithm/Fuzzy/Fuzzy.o: ../Algorithm/Fuzzy/Fuzzy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Algorithm/Fuzzy/Fuzzy.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Algorithm/Fuzzy/rtGetInf.o: ../Algorithm/Fuzzy/rtGetInf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Algorithm/Fuzzy/rtGetInf.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Algorithm/Fuzzy/rtGetNaN.o: ../Algorithm/Fuzzy/rtGetNaN.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Algorithm/Fuzzy/rtGetNaN.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Algorithm/Fuzzy/rt_nonfinite.o: ../Algorithm/Fuzzy/rt_nonfinite.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/eeprom" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Core" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/motor_controller" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/log" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/encoder" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm/MRAC" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Algorithm" -I"E:/Elastic_robot_arm/firmware/elastic_robot_arm/Drivers/Driver/system" -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Algorithm/Fuzzy/rt_nonfinite.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

