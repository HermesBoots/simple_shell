#include <stddef.h>


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
