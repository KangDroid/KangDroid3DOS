CXX=g++
CXXFLAGS=-Wall -Wno-unused-variable -O3 -g -lwiringPi -lpthread -I../include
TARGET=app.out
OBJS=coord.o\
	timer.o\
	PinClass.o \
	InnerFunction.o \
	EndstopClass.o \
	GCodeWrapper.o \
	MotorControlClass.o \
	AxisControlClass.o \
	main.o \

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf ./*.o ./*.out