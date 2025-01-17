################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.c \
../Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.c 

OBJS += \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.o \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.d \
./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l4cx/modules/%.o Drivers/BSP/Components/vl53l4cx/modules/%.su Drivers/BSP/Components/vl53l4cx/modules/%.cyclo: ../Drivers/BSP/Components/vl53l4cx/modules/%.c Drivers/BSP/Components/vl53l4cx/modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/vl53l4cx/modules -I../Drivers/BSP/Components/vl53l4cx/porting -I../Drivers/BSP/Components/vl53l4cx -I../TOF/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/BSP" -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/TOF" -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/ToF_library" -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/Logger" -I../X-CUBE-MEMS1/Target -I../Drivers/BSP/Components/lsm6dso -I"C:/Users/adrie/STM32CubeIDE/technical_project/CTOS_Hardware/Drivers/MEMS_library" -I../GNSS/Target -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -I../Drivers/BSP/GNSS1A1 -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/BSP/Components/lis2mdl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cx-2f-modules

clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cx-2f-modules:
	-$(RM) ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_calibration.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_core.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_debug.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_api_preset_modes.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_core_support.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_dmax.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen3.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_algos_gen4.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_char.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_core.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_hist_funcs.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_nvm_debug.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_register_funcs.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_sigma_estimate.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_silicon_core.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_wait.su ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.cyclo ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.d ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.o ./Drivers/BSP/Components/vl53l4cx/modules/vl53lx_xtalk.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l4cx-2f-modules

