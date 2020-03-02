################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Game/consoleplayer.cpp \
../Game/gamecontroller.cpp \
../Game/gamesession.cpp \
../Game/herzsolosession.cpp \
../Game/randomplayer.cpp \
../Game/sauspielsession.cpp \
../Game/shuffler.cpp \
../Game/tcpplayer.cpp 

OBJS += \
./Game/consoleplayer.o \
./Game/gamecontroller.o \
./Game/gamesession.o \
./Game/herzsolosession.o \
./Game/randomplayer.o \
./Game/sauspielsession.o \
./Game/shuffler.o \
./Game/tcpplayer.o 

CPP_DEPS += \
./Game/consoleplayer.d \
./Game/gamecontroller.d \
./Game/gamesession.d \
./Game/herzsolosession.d \
./Game/randomplayer.d \
./Game/sauspielsession.d \
./Game/shuffler.d \
./Game/tcpplayer.d 


# Each subdirectory must supply rules for building sources it contributes
Game/%.o: ../Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


