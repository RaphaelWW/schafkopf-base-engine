################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game/gamecontroller.cpp \
../Game/gamesession.cpp \
../Game/gametype.cpp \
../Game/herzsolosession.cpp \
../Game/sauspielsession.cpp \
../Game/serialize.cpp \
../Game/shuffler.cpp 

OBJS += \
./Game/gamecontroller.o \
./Game/gamesession.o \
./Game/gametype.o \
./Game/herzsolosession.o \
./Game/sauspielsession.o \
./Game/serialize.o \
./Game/shuffler.o 

CPP_DEPS += \
./Game/gamecontroller.d \
./Game/gamesession.d \
./Game/gametype.d \
./Game/herzsolosession.d \
./Game/sauspielsession.d \
./Game/serialize.d \
./Game/shuffler.d 


# Each subdirectory must supply rules for building sources it contributes
Game/%.o: ../Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/raphael/eclipse-workspace/Schafkopf" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


