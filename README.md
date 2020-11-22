# 42_get_next_line
The project of Ecole 42

Calling your function get_next_line in a loop will then allow you to read the text
available on a file descriptor one line at a time until the EOF.

Your read must use the BUFFER_SIZE defined during compilation to read from
a file or from stdin.

Compilation will be done this way : gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32
get_next_line.c get_next_line_utils.c
