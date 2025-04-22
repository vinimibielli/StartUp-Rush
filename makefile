APP = StartUp_Rush

SRCBACKEND = backend/srcs
INCLUDEDIR = $(SRCBACKEND)/include

SOURCE = $(wildcard $(SRCBACKEND)/*.cpp)
HEADERS = $(wildcard $(INCLUDEDIR)/*.h)

CC = g++
CFLAGS = -g

all: $(APP)

$(APP): $(SOURCE) $(HEADERS)
	$(CC) -o $(APP) $(SOURCE) -I$(INCLUDEDIR)

debug: $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -o $(APP) $(SOURCE) -I$(INCLUDEDIR)

clean:
	rm *.bin