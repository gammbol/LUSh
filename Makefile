cc= gcc
cflags= -Wall -Werror -Wextra
output= lush
source= lush.c

all: $(output)

$(output): $(source)
	$(cc) $(cflags) $< -o $@

debug: $(source)
	$(cc) $(cflags) -g $(source) -o $(output)

clean:
	rm -f $(output)

rebuild: clean all
