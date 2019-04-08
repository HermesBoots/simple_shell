#include <stddef.h>
#include <stdint.h>
#include <unistd.h>


/**
 * _strncmp - compare at most the n bytes of two strings
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes
 *
 * Return: -1, 0, 1 if string is less, equal to or grater than respectively
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (n > i)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (-1);
		if (s1[i] == s2[i])
			i++;
		else
			return (-1);
	}
	return (0);
}


/**
 * _strncpy - copy some bytes between strings
 * @dest: string to copy bytes into
 * @src: string to copy bytes from
 * @count: maximum number of bytes to copy
 *
 * Return: number of characters copied
 */
size_t _strncpy(char *dest, char const *src, size_t count)
{
	char const *s;
	char *d;

	for (d = dest, s = src; count > 0 && *s != '\0'; s++, d++, count--)
		*d = *s;
	*d = '\0';
	return (s - src);
}


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
 * @buffer: buffer to print bytes into
 * @val: value to print
 *
 * Return: number of bytes written
 */
size_t print_int(char *buffer, int64_t val)
{
	int64_t div = 1000000000000000000l;
	char *sub;
	signed char digit, leading = 1;

	sub = buffer;
	if (val == 0)
	{
		*sub = '0';
		return (1);
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
			/**
			 * sub++ can go here if ++ was not after *sub++.
			 * ++ is evaluated after the entire line is resolved
			 */
			leading = 0;
		}
		div /= 10;
	}
	/**
	 * address minus address is just a number. Contiguous memory.
	 * Hence array pointer - array pointer gives you the correct
	 * byte count.
	 */
	return (sub - buffer);
}
