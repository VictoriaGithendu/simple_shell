#include "main.h"

/**
 * addSepNodeEnd - function to add a separator found at the end of a sep_list
 * @nodHead: the start point of a linked list
 * @nodSep: variable for separator
 * Return: pointer to head
 */
sep_list *addSepNodeEnd(sep_list **nodHead, char nodSep)
{
	sep_list *sepNew, *sepTemp;

	sepNew = malloc(sizeof(sep_list));
	if (sepNew == NULL)
		return (NULL);

	sepNew->separator = nodSep;
	sepNew->next = NULL;
	sepTemp = *nodHead;

	if (sepTemp == NULL)
	{
		*nodHead = sepNew;
	}
	else
	{
		while (sepTemp->next != NULL)
			sepTemp = sepTemp->next;
		sepTemp->next = sepNew;
	}

	return (*nodHead);
}


/**
 * freeSepList - function to free a separator list
 * @nodHead: variable for the start point of a linked list
 * Return: nothing
 */
 
void freeSepList(sep_list **nodHead)
{
	sep_list *sepTemp;
	sep_list *sepNew;

	if (nodHead != NULL)
	{
		sepNew = *nodHead;
		while ((sepTemp = sepNew) != NULL)
		{
			sepNew = sepNew->next;
			free(sepTemp);
		}
		*nodHead = NULL;
	}
}


/**
 * addLineNodeEnd - function to add a command at the end of a node
 * @nodHead: start of alinked list
 * @cmdLine: variable for the commadn line
 * Return: pointer to head
 */
 
line_list *addLineNodeEnd(line_list **nodHead, char *cmdLine)
{
	line_list *sepNew, *sepTemp;

	sepNew = malloc(sizeof(line_list));
	if (sepNew == NULL)
		return (NULL);

	sepNew->line = cmdLine;
	sepNew->next = NULL;
	sepTemp = *nodHead;

	if (sepTemp == NULL)
	{
		*nodHead = sepNew;
	}
	else
	{
		while (sepTemp->next != NULL)
			sepTemp = sepTemp->next;
		sepTemp->next = sepNew;
	}

	return (*nodHead);
}


/**
 * freeLineList - function to free a line list
 * @nodHead: start point of a linked list
 * Return: nothing
 */
 
void freeLineList(line_list **nodHead)
{
	line_list *sepTemp;
	line_list *sepNew;

	if (nodHead != NULL)
	{
		sepNew = *nodHead;
		while ((sepTemp = sepNew) != NULL)
		{
			sepNew = sepNew->next;
			free(sepTemp);
		}
		*nodHead = NULL;
	}
}
