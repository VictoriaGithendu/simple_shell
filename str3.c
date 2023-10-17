#include "main.h"

/**
 * revString - function to print string in reverse
 * @str: string input
 * Return: nothing
 */
void revString(char *str)
{
	int cnt4 = 0, cnt, cnt1;
	char *strn, tempStor;

	while (cnt4 >= 0)
	{
		if (str[cnt4] == '\0')
			break;
		cnt4++;
	}
	strn = str;

	for (cnt = 0; cnt < (cnt4 - 1); cnt++)
	{
		for (cnt1 = cnt + 1; cnt1 > 0; cnt1--)
		{
			tempStor = *(strn + cnt1);
			*(strn + cnt1) = *(strn + (cnt1 - 1));
			*(strn + (cnt1 - 1)) = tempStor;
		}
	}
}
