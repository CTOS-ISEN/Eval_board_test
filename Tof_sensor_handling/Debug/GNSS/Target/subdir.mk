################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GNSS/Target/gnss_lib_config.c \
../GNSS/Target/stm32_bus_ex.c 

OBJS += \
./GNSS/Target/gnss_lib_config.o \
./GNSS/Target/stm32_bus_ex.o 

C_DEPS += \
./GNSS/Target/gnss_lib_config.d \
./GNSS/Target/stm32_bus_ex.d 


# Each subdirectory must supply rules for building sources it contributes
GNSS/Target/%.o GNSS/Target/%.su GNSS/Target/%.cyclo: ../GNSS/Target/%.c GNSS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../GNSS/Target -I../X-CUBE-MEMS1/Target -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -I../Drivers/BSP/GNSS1A1 -I../Drivers/BSP/Components/lsm6dso -I../Drivers/BSP/Components/lis2mdl -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers" -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers/Logger" -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers/MEMS_library" -I"C:/Users/adrie/STM32CubeIDE/technical_project/Tof_sensor_handling/Drivers/GNSS_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GNSS-2f-Target

clean-GNSS-2f-Target:
	-$(RM) ./GNSS/Target/gnss_lib_config.cyclo ./GNSS/Target/gnss_lib_config.d ./GNSS/Target/gnss_lib_config.o ./GNSS/Target/gnss_lib_config.su ./GNSS/Target/stm32_bus_ex.cyclo ./GNSS/Target/stm32_bus_ex.d ./GNSS/Target/stm32_bus_ex.o ./GNSS/Target/stm32_bus_ex.su

.PHONY: clean-GNSS-2f-Target

