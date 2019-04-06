#include <stddef.h>
#include <stdint.h>


/**
 * _memcpy - copy memory between two non-overlapping buffers
 * @dest: buffer to store bytes in
 * @src: buffer to copy bytes from
 * @count: number of bytes to copy
 */
void _memcpy(char *dest, char const *src, size_t count)
{
	size_t i;

	for (i = 0; i < count; i++)
		dest[i] = src[i];
}


/**
 * print_int - prints an integer
 * @val: the integer
 * @fd: file descriptor to print to
 */
void print_int(int64_t val, int fd)
{
	int64_t div = 1000000000000000000l;
	char buf[20];
	char *sub = buf;
	signed char digit, leading = 1;

	if (val == 0)
	{
		write(fd, "0", 1);
		return;
	}
	if (val < 0)
		*sub++ = '-';
	while (div > 0)
	{
		digit = val / div % 10;
		digit = digit >= 0 ? digit : -digit;
		if (digit != 0 || !leading)
		{
			*sub++ = digit + '0';
			leading = 0;
		}
	}
	write(fd, buf, sub - buf);
}
