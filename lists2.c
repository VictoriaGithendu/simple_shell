#include "main.h"

/**
 * addVarNode - function to add a  variable at the end of a node
 * @nodHead: start of a linked list
 * @varLen: variable length
 * @varVal: variable value
 * @lenVal: value length
 * Return: pointer to the head
 */
 
r_var *addVarNode(r_var **nodHead, int varLen, char *varVal, int lenVal)
{
	r_var *sepNew, *sepTemp;

	sepNew = malloc(sizeof(r_var));
	if (sepNew == NULL)
		return (NULL);

	sepNew->len_var = varLen;
	sepNew->val = varVal;
	sepNew->len_val = lenVal;

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
 * freeVarList - function to free list
 * @nodHead: start point of a linked list
 * Return: nothing
 */
void freeVarList(r_var **nodHead)
{
	r_var *sepTemp;
	r_var *sepNew;

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
