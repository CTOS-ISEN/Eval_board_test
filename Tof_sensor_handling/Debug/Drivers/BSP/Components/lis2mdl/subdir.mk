################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lis2mdl/lis2mdl.c \
../Drivers/BSP/Components/lis2mdl/lis2mdl_reg.c 

OBJS += \
./Drivers/BSP/Components/lis2mdl/lis2mdl.o \
./Drivers/BSP/Components/lis2mdl/lis2mdl_reg.o 

C_DEPS += \
./Drivers/BSP/Components/lis2mdl/lis2mdl.d \
./Drivers/BSP/Components/lis2mdl/lis2mdl_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lis2mdl/%.o Drivers/BSP/Components/lis2mdl/%.su Drivers/BSP/Components/lis2mdl/%.cyclo: ../Drivers/BSP/Components/lis2mdl/%.c Drivers/BSP/Components/lis2mdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/vl53l4cx/modules -I../Drivers/BSP/Components/vl53l4cx/porting -I../Drivers/BSP/Components/vl53l4cx -I../Drivers/BSP/53L4A2 -I../TOF/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/BSP" -I"D:/Github/Eval_board_test/ToF_sensor/TOF" -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/ToF_library" -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/Logger" -I../X-CUBE-MEMS1/Target -I../Drivers/BSP/Components/lsm6dso -I../Drivers/BSP/Components/lis2dw12 -I../Drivers/BSP/Components/lis2mdl -I../Drivers/BSP/Components/hts221 -I../Drivers/BSP/Components/lps22hh -I../Drivers/BSP/Components/stts751 -I../Drivers/BSP/IKS01A3 -I"D:/Github/Eval_board_test/ToF_sensor/Drivers/MEMS_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-lis2mdl

clean-Drivers-2f-BSP-2f-Components-2f-lis2mdl:
	-$(RM) ./Drivers/BSP/Components/lis2mdl/lis2mdl.cyclo ./Drivers/BSP/Components/lis2mdl/lis2mdl.d ./Drivers/BSP/Components/lis2mdl/lis2mdl.o ./Drivers/BSP/Components/lis2mdl/lis2mdl.su ./Drivers/BSP/Components/lis2mdl/lis2mdl_reg.cyclo ./Drivers/BSP/Components/lis2mdl/lis2mdl_reg.d ./Drivers/BSP/Components/lis2mdl/lis2mdl_reg.o ./Drivers/BSP/Components/lis2mdl/lis2mdl_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-lis2mdl

