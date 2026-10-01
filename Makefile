CC := gcc
CFLAGS := -std=c23 -Wall -Wextra -Wpedantic -Iinclude

APP := app.exe

APP_SOURCES := \
	src/main.c \
	src/str_compare.c \
	src/quick_sort.c \
	src/io.c

HEADERS := \
	include/str_compare.h \
	include/quick_sort.h  \
	include/io.h

.PHONY: all run clean

all: $(APP)

$(APP): $(APP_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(APP_SOURCES) -o $@

run: $(APP)
	./$(APP)

clean:
	$(RM) $(APP)