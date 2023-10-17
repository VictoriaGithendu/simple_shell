#include "main.h"

/**
 * strDup - function to create a duplicate of a string
 * @str: pointer to character
 * Return: string duplicate
 */
 
char *strDup(const char *str)
{
	char *newStr;
	size_t lenStr;

	lenStr = strLength(str);
	newStr = malloc(sizeof(char) * (lenStr + 1));
	if (newStr == NULL)
		return (NULL);
	memCpy(newStr, str, lenStr + 1);
	return (newStr);
}


/**
 * strLength - function that determines a string's length
 * @str: pointer to string
 * Return: length of string
 */
int strLength(const char *str)
{
	int lenStr;

	for (lenStr = 0; str[lenStr] != 0; lenStr++)
	{
	}
	return (lenStr);
}


/**
 * cmpChars - function to compare characters in a string
 * @str: string to be input
 * @delim: the separator
 * Return: 1 on success 0 if not
 */
int cmpChars(char str[], const char *delim)
{
	unsigned int cnt, cnt1, cnt2;

	for (cnt = 0, cnt2 = 0; str[cnt]; cnt++)
	{
		for (cnt1 = 0; delim[cnt1]; cnt1++)
		{
			if (str[cnt] == delim[cnt1])
			{
				cnt2++;
				break;
			}
		}
	}
	if (cnt == cnt2)
		return (1);
	return (0);
}


/**
 * strTok - function to split string into items or words
 * @str: string input
 * @delim: the separating character
 * Return: tokenized string
 */
 
char *strTok(char str[], const char *delim)
{
	static char *splitr, *strEnd;
	char *strStart;
	unsigned int cnt, bool;

	if (str != NULL)
	{
		if (cmpChars(str, delim))
			return (NULL);
		splitr = str; /*Store first address*/
		cnt = strLength(str);
		strEnd = &str[cnt]; /*Store last address*/
	}
	strStart = splitr;
	if (strStart == strEnd) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitr; splitr++)
	{
		/*Breaking loop finding the next token*/
		if (splitr != strStart)
			if (*splitr && *(splitr - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (cnt = 0; delim[cnt]; cnt++)
		{
			if (*splitr == delim[cnt])
			{
				*splitr = '\0';
				if (splitr == strStart)
					strStart++;
				break;
			}
		}
		if (bool == 0 && *splitr) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (strStart);
}


/**
 * isDigit - function to locate numbers in a string
 * @str: string input
 * Return: 1 if succcessful, otherwise 0
 */
 
int isDigit(const char *str)
{
	unsigned int cnt;

	for (cnt = 0; str[cnt]; cnt++)
	{
		if (str[cnt] < 48 || str[cnt] > 57)
			return (0);
	}
	return (1);
}
