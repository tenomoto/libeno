.SUFFIXES : .o .c

CC = clang
CPPFLAGS = -I/opt/local/include -I.. -DVERBOSE
CFLAGS = -O2
LDFLAGS = -L/opt/local/lib -lcunit -L.. -leno
RM = rm
PROGS = test_alf test_bicubic test_endian test_cubic_hermite test_biquadratic test_sphere test_emath

all : $(PROGS)

$(PROGS) : ../libeno.dylib

clean :
	rm -f $(PROGS)
