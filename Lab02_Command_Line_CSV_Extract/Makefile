CFLAGS = -Wall

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

MKDIR_P = mkdir -p

.PHONY: directories

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o ./build/$@ $<

directories: 
	$MKDIR_P ./build
# runtest: 