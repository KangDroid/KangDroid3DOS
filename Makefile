CXX=g++
CFLAGS=-g -Wall -O3 -lwiringPi -Iinclude
TARGET=app.out

SRC=src/EndstopClass.cpp\
	src/InnerFunction.cpp\
	src/GCodeWrapper.cpp\
	src/main.cpp

all: $(OBJS)
	$(CXX) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf ./*.out ./*.o ./*.dSYM