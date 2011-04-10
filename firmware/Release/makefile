################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LED-Cube-firmware.lss \

FLASH_IMAGE += \
LED-Cube-firmware.hex \

EEPROM_IMAGE += \
LED-Cube-firmware.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: LED-Cube-firmware.elf secondary-outputs

# Tool invocations
LED-Cube-firmware.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,LED-Cube-firmware.map,--cref -mmcu=atmega2560 -o"LED-Cube-firmware.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LED-Cube-firmware.lss: LED-Cube-firmware.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S LED-Cube-firmware.elf  >"LED-Cube-firmware.lss"
	@echo 'Finished building: $@'
	@echo ' '

LED-Cube-firmware.hex: LED-Cube-firmware.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex LED-Cube-firmware.elf  "LED-Cube-firmware.hex"
	@echo 'Finished building: $@'
	@echo ' '

LED-Cube-firmware.eep: LED-Cube-firmware.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex LED-Cube-firmware.elf  "LED-Cube-firmware.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LED-Cube-firmware.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 LED-Cube-firmware.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) LED-Cube-firmware.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
