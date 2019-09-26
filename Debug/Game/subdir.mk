################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game/gamecontroller.cpp \
../Game/gamesession.cpp \
../Game/herzsolo.cpp \
../Game/shuffler.cpp 

OBJS += \
./Game/gamecontroller.o \
./Game/gamesession.o \
./Game/herzsolo.o \
./Game/shuffler.o 

CPP_DEPS += \
./Game/gamecontroller.d \
./Game/gamesession.d \
./Game/herzsolo.d \
./Game/shuffler.d 


# Each subdirectory must supply rules for building sources it contributes
Game/%.o: ../Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


