################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC.cpp \
../Button.cpp \
../cplusplus.cpp \
../EEPROM.cpp \
../LCD.cpp \
../LineTrack.cpp \
../Robocar.cpp \
../robocar_ll.cpp \
../Servo.cpp \
../Timer3.cpp \
../Wheel.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
Button.o \
cplusplus.o \
EEPROM.o \
LCD.o \
LineTrack.o \
Robocar.o \
robocar_ll.o \
Servo.o \
Timer3.o \
Wheel.o

OBJS_AS_ARGS +=  \
ADC.o \
Button.o \
cplusplus.o \
EEPROM.o \
LCD.o \
LineTrack.o \
Robocar.o \
robocar_ll.o \
Servo.o \
Timer3.o \
Wheel.o

C_DEPS +=  \
ADC.d \
Button.d \
cplusplus.d \
EEPROM.d \
LCD.d \
LineTrack.d \
Robocar.d \
robocar_ll.d \
Servo.d \
Timer3.d \
Wheel.d

C_DEPS_AS_ARGS +=  \
ADC.d \
Button.d \
cplusplus.d \
EEPROM.d \
LCD.d \
LineTrack.d \
Robocar.d \
robocar_ll.d \
Servo.d \
Timer3.d \
Wheel.d

OUTPUT_FILE_PATH +=Robocar_6_2(4).elf

OUTPUT_FILE_PATH_AS_ARGS +=Robocar_6_2(4).elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler























./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega1284p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega1284p" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Robocar_6_2(4).map" -Wl,--start-group -Wl,-llamos -Wl,-llamos  -Wl,--end-group -Wl,-L".." -Wl,-L"C:\Users\student\Downloads\Nicolas\Robocar_S2\Robocar"  -Wl,--gc-sections -mrelax -mmcu=atmega1284p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega1284p"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Robocar_6_2(4).elf" "Robocar_6_2(4).hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Robocar_6_2(4).elf" "Robocar_6_2(4).eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Robocar_6_2(4).elf" > "Robocar_6_2(4).lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Robocar_6_2(4).elf" "Robocar_6_2(4).srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Robocar_6_2(4).elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Robocar_6_2(4).elf" "Robocar_6_2(4).a" "Robocar_6_2(4).hex" "Robocar_6_2(4).lss" "Robocar_6_2(4).eep" "Robocar_6_2(4).map" "Robocar_6_2(4).srec" "Robocar_6_2(4).usersignatures"
	