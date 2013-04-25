.SUFFIXES : .o .c

CC = clang
CPPFLAGS = -I/opt/local/include -I../
CFLAGS = -O2
LDFLAGS = -L/opt/local/lib -L../
RM = rm
LIBS = -leno -lcunit

test : test_bicubic
	./$<

test_bicubic : test_bicubic.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LIBS) $< -o $@
