Srcs := $(wildcard *.c)
Outs := $(patsubst %.c, %, $(Srcs))

CC := gcc
CFLAGS = -Wall -g -lpthread

ALL: $(Outs) 

%: %.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean rebuild ALL

clean:
	$(RM) $(Outs)
rebuild: clean ALL
