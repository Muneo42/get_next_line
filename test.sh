rm -f get_next_line
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=64 -I. get_next_line.c get_next_line_utils.c test.c -o get_next_line
./get_next_line < tests/lorem_ipsum
rm -f get_next_line
