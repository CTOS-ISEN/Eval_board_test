################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/GNSS_library/GNSS_library.c 

OBJS += \
./Drivers/GNSS_library/GNSS_library.o 

C_DEPS += \
./Drivers/GNSS_library/GNSS_library.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GNSS_library/%.o Drivers/GNSS_library/%.su Drivers/GNSS_library/%.cyclo: ../Drivers/GNSS_library/%.c Drivers/GNSS_library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/vl53l4cx/modules -I../Drivers/BSP/Components/vl53l4cx/porting -I../Drivers/BSP/Components/vl53l4cx -I../TOF/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/BSP" -I"D:/Github/Eval_board_test/ToF_sensor/TOF" -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/ToF_library" -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/Logger" -I../X-CUBE-MEMS1/Target -I../Drivers/BSP/Components/lsm6dso -I../Drivers/BSP/Components/lis2dw12 -I../Drivers/BSP/Components/lis2mdl -I../Drivers/BSP/Components/hts221 -I../Drivers/BSP/Components/lps22hh -I../Drivers/BSP/Components/stts751 -I../Drivers/BSP/IKS01A3 -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/MEMS_library" -I../GNSS/Target -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -I../Drivers/BSP/GNSS1A1 -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/GNSS_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-GNSS_library

clean-Drivers-2f-GNSS_library:
	-$(RM) ./Drivers/GNSS_library/GNSS_library.cyclo ./Drivers/GNSS_library/GNSS_library.d ./Drivers/GNSS_library/GNSS_library.o ./Drivers/GNSS_library/GNSS_library.su

.PHONY: clean-Drivers-2f-GNSS_library

