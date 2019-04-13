#include <stdlib.h>
#include <unistd.h>
#include "common.h"


/**
 * _getline - takes the user input and puts it in a string
 * @line: the line to put into a string
 * @size: the size of the buffer line is put into
 * @fd: file descriptor
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **line, size_t *size, int fd)
{
	static size_t unused, terminated;
	size_t i, j, total;
	ssize_t count = 0;

	if (*line == NULL)
	{
		*size = 128, *line = malloc(128);
		if (*line == NULL)
			error(NULL);
	}
	else if (unused != 0)
	{
		for (i = 0; line[0][i] != '\0'; i++)
			;
		line[0][i] = terminated;
		for (j = 0; j < unused; j++, i++)
			line[0][j] = line[0][i];
	}
	total = unused;
	do {
		for (i = total - count; i < total; i++)
		{
			if (line[0][i] == '\n')
			{
				if (++i < total)
					terminated = line[0][i];
				line[0][i] = '\0', unused = total - i;
				return (i);
			}
		}
		total += count = read(fd, *line + total, *size - total);
		if (total == *size)
			*line = _realloc(*line, *size *= 2);
	} while (count > 0);
	if (count < 0)
		error(NULL);
	else if (count == 0 && total < 1)
		return (-1);
	unused = 0, line[0][total] = '\0';
	return (total);
}
