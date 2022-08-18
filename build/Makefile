CFLAGS += -c -g -Wall -Wextra -Wpedantic \
                  -Wformat=2 -Wno-unused-parameter \
                  -Wshadow -Wwrite-strings -Wstrict-prototypes \
                  -Wold-style-definition -Wredundant-decls \
                  -Wnested-externs -Wmissing-include-dirs \
                  -Wjump-misses-init -Wlogical-op -O2

PATH_TO_FILES += ../src
PATH_TO_HEADER_FILES += $(PATH_TO_FILES)/include

FILES += $(PATH_TO_FILES)/station.c $(PATH_TO_FILES)/station_run.c

.PHONY: all build clean

all: build
	@gcc *.o -o station_run

build: $(FILES)
	@gcc $(CFLAGS) $(FILES)

clean:
	@rm -rf station_run.o station_run out

clean_all:
	@rm -rf *.o station_run out