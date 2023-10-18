#include "main.h"
/**
 * assign_line_buf - assigns the line buffer for get_line
 * @linep: pointer that store the input str
 * @buf: str that is been called to line
 * @x: size of line buffer
 * @y: size of buffer input
 */
void assign_line_buf(char **linep, size_t *x, char *buf, size_t y)
{

	if (*linep == NULL)
	{
		if  (y > BUFSIZE)
			*x = y;
		else
			*x = BUFSIZE;
		*linep = buf;
	}
	else if (*x < y)
	{
		if (y > BUFSIZE)
			*x = y;
		else
			*x = BUFSIZE;
		*linep = buf;
	}
	else
	{
		strCpy(*linep, buf);
		free(buf);
	}
}
/**
 * read_line_input - Read inpt from stream
 * @line_buffer: buffer that stores the input line
 * @line_size: size of line buffer
 * @stream: stream to read from
 * Return: The number of bytes read
 */
ssize_t read_line_input(char **line_buffer, size_t *line_size, FILE *stream)
{
	int x;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char character = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (character != '\n')
	{
		x = read(STDIN_FILENO, &character, 1);
		if (x == -1 || (x == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (x == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = reAlloc(buffer, input, input + 1);
		buffer[input] = character;
		input++;
	}
	buffer[input] = '\0';
	assign_line_buf(line_buffer, line_size, buffer, input);
	retval = input;
	if (x != 0)
		input = 0;
	return (retval);
}
/**
 * read_input_line - reads and returns an input line.
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_input_line(int *i_eof)
{
	char *input_str = NULL;
	size_t buffer_size = 0;

	*i_eof = read_line_input(&input_str, &buffer_size, stdin);

	return (input_str);
}
