################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/GNSS1A1/gnss1a1_gnss.c 

OBJS += \
./Drivers/BSP/GNSS1A1/gnss1a1_gnss.o 

C_DEPS += \
./Drivers/BSP/GNSS1A1/gnss1a1_gnss.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/GNSS1A1/%.o Drivers/BSP/GNSS1A1/%.su Drivers/BSP/GNSS1A1/%.cyclo: ../Drivers/BSP/GNSS1A1/%.c Drivers/BSP/GNSS1A1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../GNSS/Target -I../X-CUBE-MEMS1/Target -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -I../Drivers/BSP/GNSS1A1 -I../Drivers/BSP/Components/lsm6dso -I../Drivers/BSP/Components/lis2mdl -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers" -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers/Logger" -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers/MEMS_library" -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers/GNSS_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-GNSS1A1

clean-Drivers-2f-BSP-2f-GNSS1A1:
	-$(RM) ./Drivers/BSP/GNSS1A1/gnss1a1_gnss.cyclo ./Drivers/BSP/GNSS1A1/gnss1a1_gnss.d ./Drivers/BSP/GNSS1A1/gnss1a1_gnss.o ./Drivers/BSP/GNSS1A1/gnss1a1_gnss.su

.PHONY: clean-Drivers-2f-BSP-2f-GNSS1A1

