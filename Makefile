CC=        gcc
CFLAGS=    -O0        \
           -g         \
	   -ggdb      \
	   -std=gnu99 \
	   -Wall      \
	   -Werror    \
	   -Wextra

LFLAGS=

%.o : %.c
	$(CC) -c $(CFLAGS) $(<) -o $(@)

test_state: state.o
	$(CC) $(LFLAGS) $(^) -o $(@)

test_maybe: maybe.o
	$(CC) $(LFLAGS) $(^) -o $(@)

clean:
	-rm -f test_state
	-rm -f test_maybe
	-rm -f core
	-rm -f *.o
