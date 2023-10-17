#include "main.h"

/**
 * repChar - function that checks for repetiotion of characters
 * @inpt: pointer to string input
 * @cnt: counter
 * Return: number of repeated characters
 */

int repChar(char *inpt, int cnt)
{
if (*(inpt - 1) == *inpt)
return (repChar(inpt - 1, cnt + 1));
return (cnt);
}

/**
 * sepError - function to find syntax errors
 * @inpt: string input to be checked
 * @cnt: counter
 * @prevRd: previous read character
 * Return: error index on success, otherwise 0
 */

int sepError(char *inpt, int cnt, char prevRd)
{
int cnt1;
cnt1 = 0;
if (*inpt == '\0')
return (0);
if (*inpt == ' ' || *inpt == '\t')
return (sepError(inpt + 1, cnt + 1, prevRd));
if (*inpt == ';')
if (prevRd == '|' || prevRd == '&' || prevRd == ';')
return (cnt);
if (*inpt == '|')
{
if (prevRd == ';' || prevRd == '&')
return (cnt);
if (prevRd == '|')
{
cnt1 = repChar(inpt, 0);
if (cnt1 == 0 || cnt1 > 1)
return (cnt);
}
}
if (*inpt == '&')
{
if (prevRd == ';' || prevRd == '|')
return (cnt);
if (prevRd == '&')
{
cnt1 = repChar(inpt, 0);
if (cnt1 == 0 || cnt1 > 1)
return (cnt);
}
}
return (sepError(inpt + 1, cnt + 1, *inpt));
}


/**
 * firstChar -function that points to the first character in a string
 * @inpt: pointer to string input
 * @cnt: index counter
 * Return: 0 on success, 1 if unsucessful
 */

int firstChar(char *inpt, int *cnt)
{
for (*cnt = 0; inpt[*cnt]; *cnt += 1)
{
if (inpt[*cnt] == ' ' || inpt[*cnt] == '\t')
continue;
if (inpt[*cnt] == ';' || inpt[*cnt] == '|' || inpt[*cnt] == '&')
return (-1);
break;
}
return (0);
}


/**
 * printSyntaxError - function that outputs an error if found
 * @inf: stucture for data containing argument variables
 * @inpt: pointer to string input
 * @cnt: pointer to error index
 * @bool: variable that checks errror message
 * Return: no return
 */

void printSyntaxError(data_shell *inf, char *inpt, int cnt, int bool)
{
char *stmnt1, *stmnt2, *stmnt3, *err, *cnt1;
int len;
if (inpt[cnt] == ';')
{
if (bool == 0)
stmnt1 = (inpt[cnt + 1] == ';' ? ";;" : ";");
else
stmnt1 = (inpt[cnt - 1] == ';' ? ";;" : ";");
}
if (inpt[cnt] == '|')
stmnt1 = (inpt[cnt + 1] == '|' ? "||" : "|");
if (inpt[cnt] == '&')
stmnt1 = (inpt[cnt + 1] == '&' ? "&&" : "&");
stmnt2 = ": Syntax error: \"";
stmnt3 = "\" unexpected\n";
cnt1 = iToA(inf->counter);
len = strLength(inf->av[0]) + strLength(cnt1);
len += strLength(stmnt1) + strLength(stmnt2) + strLength(stmnt3) + 2;
err = malloc(sizeof(char) * (len + 1));
if (err == 0)
{
free(cnt1);
return;
}
strCpy(err, inf->av[0]);
strCat(err, ": ");
strCat(err, cnt1);
strCat(err, stmnt2);
strCat(err, stmnt1);
strCat(err, stmnt3);
strCat(err, "\0");
write(STDERR_FILENO, err, len);
free(err);
free(cnt1);
}


/**
 * checkSyntaxError - function that checks and prints out syntax error message
 * @inf: stucture for data containing argument variables
 * @inpt: pointer to string input
 * Return: 0 on success otherise 1
 */

int checkSyntaxError(data_shell *inf, char *inpt)
{
int start1 = 0;
int fChar = 0;
int cnt = 0;
fChar = firstChar(inpt, &start1);
if (fChar == -1)
{
printSyntaxError(inf, inpt, start1, 0);
return (1);
}
cnt = sepError(inpt + start1, 0, *(inpt + start1));
if (cnt != 0)
{
printSyntaxError(inf, inpt, start1 + cnt, 1);
return (1);
}
return (0);
}
