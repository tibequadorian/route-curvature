CC       = gcc
CFLAGS   = -Wall
LDFLAGS  = -lm
OBJFILES = src/route.o src/main.o
TARGET   = route-curvature

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) src/.*.swp

