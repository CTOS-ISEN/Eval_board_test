################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.c \
../Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.c 

OBJS += \
./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.o \
./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.o 

C_DEPS += \
./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.d \
./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/lib_gnss/LibGNSS/Src/%.o Middlewares/ST/lib_gnss/LibGNSS/Src/%.su Middlewares/ST/lib_gnss/LibGNSS/Src/%.cyclo: ../Middlewares/ST/lib_gnss/LibGNSS/Src/%.c Middlewares/ST/lib_gnss/LibGNSS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/vl53l4cx/modules -I../Drivers/BSP/Components/vl53l4cx/porting -I../Drivers/BSP/Components/vl53l4cx -I../TOF/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/BSP" -I"D:/Github/Eval_board_test/ToF_sensor/TOF" -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/ToF_library" -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/Logger" -I../X-CUBE-MEMS1/Target -I../Drivers/BSP/Components/lsm6dso -I../Drivers/BSP/Components/lis2dw12 -I../Drivers/BSP/Components/lis2mdl -I../Drivers/BSP/Components/hts221 -I../Drivers/BSP/Components/lps22hh -I../Drivers/BSP/Components/stts751 -I../Drivers/BSP/IKS01A3 -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/MEMS_library" -I../GNSS/Target -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -I../Drivers/BSP/GNSS1A1 -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/GNSS_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-lib_gnss-2f-LibGNSS-2f-Src

clean-Middlewares-2f-ST-2f-lib_gnss-2f-LibGNSS-2f-Src:
	-$(RM) ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.cyclo ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.d ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.o ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_data.su ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.cyclo ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.d ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.o ./Middlewares/ST/lib_gnss/LibGNSS/Src/gnss_parser.su

.PHONY: clean-Middlewares-2f-ST-2f-lib_gnss-2f-LibGNSS-2f-Src

