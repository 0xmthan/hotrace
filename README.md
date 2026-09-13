*This project has been created as part of the 42 curriculum by mtaheri, mkulbak.*

# hotrace

A fast key/value store and lookup tool, written in C for the 42 HotRace rush.

## Usage

```sh
make && make clean
./hotrace
```

The program takes no arguments and reads from standard input:

1. **Store phase:** keyword and value on alternating lines.
2. **An empty line** ends the store phase.
3. **Search phase:** one keyword per line. Prints its value, or
   `<keyword>: Not found.` if it isn't stored.

```
$> cat -e example.htr
keyword-1$
value-1$
keyword-2$
value-2$
$
keyword-1$
keyword-3$
$> ./hotrace < example.htr
value-1
keyword-3: Not found.
```

If a keyword is stored more than once, the last value stored is the one returned.

## Makefile rules

`all`, `clean`, `fclean`, `re`. Compiled with `cc -Wall -Wextra -Werror`.
