CXX=g++
CFLAGS=-g -Wall -O3 -lwiringPi
TARGET=app.out
OBJS=EndstopClass.o \
	InnerFunction.o \
	GCodeWrapper.o \
	main.o

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf ./*.out ./*.o ./*.dSYM