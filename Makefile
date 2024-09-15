cc= gcc
cflags= -Wall -Werror -Wextra
output= lush
source= lush.c

all: $(output)

$(output): $(source)
	$(cc) $(cflags) $< -o $@

clean:
	rm -f $(output)

rebuild: clean all