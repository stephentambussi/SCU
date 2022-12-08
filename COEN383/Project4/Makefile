# set the compiler
CC = g++
# set the flags
CFLAGS = -Wall -g3
# specify which libraries to use
LDFLAGS =
# set the object files
OBJFILES = main.o cpu.o memory.o page.o process.o
# specify the name of the desired output file
TARGET = page_replacement

all: $(TARGET)

# make the files
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

# clean the files from directory
clean:
	rm -f $(TARGET) *.o