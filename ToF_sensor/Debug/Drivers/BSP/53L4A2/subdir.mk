################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/53L4A2/53l4a2_ranging_sensor.c 

OBJS += \
./Drivers/BSP/53L4A2/53l4a2_ranging_sensor.o 

C_DEPS += \
./Drivers/BSP/53L4A2/53l4a2_ranging_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/53L4A2/%.o Drivers/BSP/53L4A2/%.su Drivers/BSP/53L4A2/%.cyclo: ../Drivers/BSP/53L4A2/%.c Drivers/BSP/53L4A2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/vl53l4cx/modules -I../Drivers/BSP/Components/vl53l4cx/porting -I../Drivers/BSP/Components/vl53l4cx -I../Drivers/BSP/53L4A2 -I../TOF/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-53L4A2

clean-Drivers-2f-BSP-2f-53L4A2:
	-$(RM) ./Drivers/BSP/53L4A2/53l4a2_ranging_sensor.cyclo ./Drivers/BSP/53L4A2/53l4a2_ranging_sensor.d ./Drivers/BSP/53L4A2/53l4a2_ranging_sensor.o ./Drivers/BSP/53L4A2/53l4a2_ranging_sensor.su

.PHONY: clean-Drivers-2f-BSP-2f-53L4A2

