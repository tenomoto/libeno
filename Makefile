.SUFFIXES : .o .c

CC = clang
#CPPFLAGS = -DVERBOSE
CPPFLAGS =
CFLAGS = -O2
AR = ar
ARFLAGS = cru
LD = clang
LDFLAGS = -dynamiclib -install_name ${HOME}/local/lib/libeno.dylib
RM = rm
DOXYGEN = doxygen
MAKEHEADERS = makeheaders

TARGET = libeno
SRCS = air.c earth.c isa.c alf.c bicubic.c biquadratic.c cubic_hermite.c endian.c \
  sphere.c sigmap.c moist.c extrapolate.c search.c cubic_lagrange.c xreal.c emath.c
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
