.SUFFIXES : .o .c

CC = clang
#CPPFLAGS = -DVERBOSE
CPPFLAGS =
CFLAGS = -O2
AR = ar
ARFLAGS = cru
LD = clang
LDFLAGS = -dynamiclib -install_name ${HOME}/src/libeno/libeno.dylib
RM = rm
DOXYGEN = doxygen
MAKEHEADERS = makeheaders

TARGET = libeno
SRCS = alf.c bicubic.c biquadratic.c cubic_hermite.c endian.c emath.c sphere.c
OBJS = $(SRCS:.c=.o)
HDRS = $(SRCS:.c=.h)

all : $(MAKEHEADERS) headers $(TARGET).dylib

$(TARGET).dylib : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(TARGET).a : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

headers :
	./$(MAKEHEADERS) *.[ch]

.c.o :
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

$(MAKEHEADERS) : makeheaders.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $(MAKEHEADERS)

test :
	cd test
	make

doc :
	$(DOXYGEN)

clean :
	$(RM) -f $(TARGET).* $(OBJS)

distclean :
	$(RM) -f $(TARGET).* $(OBJS) $(HDRS) $(MAKEHEADERS)

$(HDRS) : $(SRCS)
