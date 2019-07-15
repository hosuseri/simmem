TARGET = simmem.exe
OBJS = \
	simmem.o

CC = gcc
CCPLUS = g++
CFLAGS = -Wall -O0 -g

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

.cc.o:
	$(CCPLUS) $(CFLAGS) -c $<
