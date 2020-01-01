#--target=i686-w64-mingw32-gcc

CC = gcc
CFLAGS = -I include -Wall

vpath %.h include
vpath %.c src
vpath %.c src/citunit

citunitobjs = $(patsubst %.c, %.o, $(notdir $(wildcard src/citunit/*.c)))
citsetobjs = $(patsubst %.c, %.o, $(notdir $(wildcard src/*.c)))

OBJS = $(citunitobjs) $(citsetobjs)

TARGET = libcitset.a

.PHONY : all

all : $(TARGET)

$(TARGET) : $(OBJS)
	ar -crs $@ $^

$(OBJS) : cit_unit.h cit_def.h

$(OBJS) : %.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

vpath %.c test

testsrcs = $(notdir $(wildcard test/*.c))
tests = $(patsubst %.c, %, $(testsrcs))

.PHONY : TEST

TEST : $(tests) $(TARGET)

$(tests) : % : %.c
	$(CC) -o $@ $< $(TARGET) -I.

.PHONY : clean

clean :
	$(RM) *.o