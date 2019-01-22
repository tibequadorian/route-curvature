CC       = gcc
CFLAGS   = -Wall
LDFLAGS  =
OBJFILES = src/route.o src/main.o
TARGET   = route-curvature

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

