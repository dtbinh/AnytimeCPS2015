
FLAGS=
HID_SRC=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -ludev -pthread
	HID_SRC = hid-linux.c
endif
ifeq ($(UNAME_S),Darwin)
	FLAGS = -framework IOKit -framework CoreFoundation
	HID_SRC = hid-mac.c
endif

spr: sp.c $(HID_SRC)
	gcc -Wall -I. -g $^ $(FLAGS) -o $@

clean:
	rm -f spr
