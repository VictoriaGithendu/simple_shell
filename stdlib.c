#include "main.h"

/**
 * getLength - function to get a number's lenght
 * @num: the number who's length willl be determined
 * Return: the length of num
 */
 
int getLength(int num)
{
	unsigned int numLen;
	int len = 1;

	if (num < 0)
	{
		len++;
		numLen = num * -1;
	}
	else
	{
		numLen = num;
	}
	while (numLen > 9)
	{
		len++;
		numLen = numLen / 10;
	}

	return (len);
}


/**
 * iToA - function to convert number to string
 * @num: number to be converted
 * Return: a string
 */
 
char *iToA(int num)
{
	unsigned int numLen;
	int len = getLength(num);
	char *buffr;

	buffr = malloc(sizeof(char) * (len + 1));
	if (buffr == 0)
		return (NULL);

	*(buffr + len) = '\0';

	if (num < 0)
	{
		numLen = num * -1;
		buffr[0] = '-';
	}
	else
	{
		numLen = num;
	}

	len--;
	do {
		*(buffr + len) = (numLen % 10) + '0';
		numLen = numLen / 10;
		len--;
	}
	while (numLen > 0)
		;
	return (buffr);
}


/**
 * aToI - function to convert string to integer
 * @strn: string to be converted
 * Return: an integer value
 */
 
int aToI(char *strn)
{
	unsigned int cnt4 = 0, strSize = 0, cnt1 = 0, cnt2 = 1, cnt3 = 1, cnt;

	while (*(strn + cnt4) != '\0')
	{
		if (strSize > 0 && (*(strn + cnt4) < '0' || *(strn + cnt4) > '9'))
			break;

		if (*(strn + cnt4) == '-')
			cnt2 *= -1;

		if ((*(strn + cnt4) >= '0') && (*(strn + cnt4) <= '9'))
		{
			if (strSize > 0)
				cnt3 *= 10;
			strSize++;
		}
		cnt4++;
	}

	for (cnt = cnt4 - strSize; cnt < cnt4; cnt++)
	{
		cnt1 = cnt1 + ((*(strn + cnt) - 48) * cnt3);
		cnt3 /= 10;
	}
	return (cnt1 * cnt2);
}
