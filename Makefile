.SUFFIXES : .o .c

CC = clang
CPPFLAGS =
CFLAGS = -O2
AR = ar
ARFLAGS = cru
RM = rm
DOXYGEN = doxygen
MAKEHEADERS = makeheaders

TARGET = libeno
SRCS = bicubic.c
OBJS = $(SRCS:.c=.o)
HDRS = $(SRCS:.c=.h)

all : $(MAKEHEADERS) $(HDRS) $(TARGET).a

$(TARGET).a : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.c.o :
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

.c.h :
	./$(MAKEHEADERS) $<

$(MAKEHEADERS) : makeheaders.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $(MAKEHEADERS)

test :
	cd test
	make

doc :
	$(DOXYGEN)

clean :
	$(RM) -f $(TARGET).a $(OBJS)

distclean :
	$(RM) -f $(TARGET).a $(OBJS) $(HDRS) $(MAKEHEADERS)
