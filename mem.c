#include "main.h"

/**
 * _memcpy - a function to copy data from one void pointer to another
 * @newptr: pointer to the adress where the data is copied
 * @ptr: the data to be copied
 * @size: variable for new pointer size
 * Return: nothing
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - function that reallocates memory
 * @ptr: pointer to previous memory
 * @old_size: size of previous memory
 * @new_size: size of pointer to new memory
 * Return: new size on success or 0 wehn malloc fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp -  function for memory allocation for the case of a double ptr
 * @ptr: pointer to previous memory block
 * @old_size: size of pointer to previous memory
 * @new_size:  current size of pointer to memory
 * Return: new size on success else NULL if malloc fails
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
