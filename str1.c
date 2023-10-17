#include "main.h"

/**
 * strCat - function to joint two strings
 * @dest: pointer to destination of the copied string
 * @src: pointer to string to be joined to another
 * Return: the destination
 */
 
char *strCat(char *dest, const char *src)
{
	int cnt, cnt1;

	for (cnt = 0; dest[cnt] != '\0'; cnt++)
		;

	for (cnt1 = 0; src[cnt1] != '\0'; cnt1++)
	{
		dest[cnt] = src[cnt1];
		cnt++;
	}

	dest[cnt] = '\0';
	return (dest);
}


/**
 * *strCpy - function to copy a tring from one location to another
 * @dest: pointer to the location the string will be copied to
 * @src: string to be copied
 * Return: the destination
 */
 
char *strCpy(char *dest, char *src)
{

	size_t cnt;

	for (cnt = 0; src[cnt] != '\0'; cnt++)
	{
		dest[cnt] = src[cnt];
	}
	dest[cnt] = '\0';

	return (dest);
}


/**
 * strCmp - function to check similarity of two strings
 * @str1: first string for comparison
 * @str2: second string for comparison
 * Return: zero on success.
 */
 
int strCmp(char *str1, char *str2)
{
	int cnt;

	for (cnt = 0; str1[cnt] == str2[cnt] && str1[cnt]; cnt++)
		;

	if (str1[cnt] > str2[cnt])
		return (1);
	if (str1[cnt] < str2[cnt])
		return (-1);
	return (0);
}


/**
 * strChr - function to find a charater in a string
 * @str: the string to be checked into
 * @chr: character to be located
 * Return: pointer to character to be searched
 */
char *strChr(char *str, char chr)
{
	unsigned int cnt = 0;

	for (; *(str + cnt) != '\0'; cnt++)
		if (*(str + cnt) == chr)
			return (str + cnt);
	if (*(str + cnt) == chr)
		return (str + cnt);
	return ('\0');
}


/**
 * strSpn - function to determine prefix substring's length
 * @str: previous string
 * @bytNum: amount of bytes to be copied
 * Return: accepted bytes
 */
 
int strSpn(char *str, char *bytNum)
{
	int cnt, cnt1, bool;

	for (cnt = 0; *(str + cnt) != '\0'; cnt++)
	{
		bool = 1;
		for (cnt1 = 0; *(bytNum + cnt1) != '\0'; cnt1++)
		{
			if (*(str + cnt) == *(bytNum + cnt1))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (cnt);
}
