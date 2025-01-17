################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MEMS_library/MEMS_library.c 

OBJS += \
./Drivers/MEMS_library/MEMS_library.o 

C_DEPS += \
./Drivers/MEMS_library/MEMS_library.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MEMS_library/%.o Drivers/MEMS_library/%.su Drivers/MEMS_library/%.cyclo: ../Drivers/MEMS_library/%.c Drivers/MEMS_library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/vl53l4cx/modules -I../Drivers/BSP/Components/vl53l4cx/porting -I../Drivers/BSP/Components/vl53l4cx -I../TOF/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/BSP" -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/TOF" -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/ToF_library" -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/Logger" -I../X-CUBE-MEMS1/Target -I../Drivers/BSP/Components/lsm6dso -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/MEMS_library" -I../GNSS/Target -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -I../Drivers/BSP/GNSS1A1 -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/BSP/Components/lis2mdl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-MEMS_library

clean-Drivers-2f-MEMS_library:
	-$(RM) ./Drivers/MEMS_library/MEMS_library.cyclo ./Drivers/MEMS_library/MEMS_library.d ./Drivers/MEMS_library/MEMS_library.o ./Drivers/MEMS_library/MEMS_library.su

.PHONY: clean-Drivers-2f-MEMS_library

