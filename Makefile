CC = gcc
CFLAGS = -Wall
LIBS = -lpigpio -lpthread -lrt
TARGET = assignment2
SRCS = hw2_pigpio.c lcd.c

OBJS = $(SRCS:.c=.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	sudo ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
