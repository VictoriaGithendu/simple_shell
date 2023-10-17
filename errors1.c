#include "main.h"

/**
 * cdStrcat - function to join cd error message
 * @inf: stucture for data containing argument variables
 * @stmnt: information to be displayed
 * @err: display message
 * @strCnt: line counter
 * Return: the error message
 */

char *cdStrcat(data_shell *inf, char *stmnt, char *err, char *strCnt)
{
char *illegFlag;
strCpy(err, inf->av[0]);
strCat(err, ": ");
strCat(err, strCnt);
strCat(err, ": ");
strCat(err, inf->args[0]);
strCat(err, stmnt);
if (inf->args[1][0] == '-')
{
illegFlag = malloc(3);
illegFlag[0] = '-';
illegFlag[1] = inf->args[1][1];
illegFlag[2] = '\0';
strCat(err, illegFlag);
free(illegFlag);
}
else
{
strCat(err, inf->args[1]);
}
strCat(err, "\n");
strCat(err, "\0");
return (err);
}

/**
 * getCdError - function to display cd error message in get_cd
 * @inf: stucture for data containing argument variables
 * Return: displays error message
 */

char *getCdError(data_shell *inf)
{
int len, idLen;
char *err, *strCnt, *stmnt;
strCnt = iToA(inf->counter);
if (inf->args[1][0] == '-')
{
stmnt = ": Illegal option ";
idLen = 2;
}
else
{
stmnt = ": can't cd to ";
idLen = strLength(inf->args[1]);
}
len = strLength(inf->av[0]) + strLength(inf->args[0]);
len += strLength(strCnt) + strLength(stmnt) + idLen + 5;
err = malloc(sizeof(char) * (len + 1));
if (err == 0)
{
free(strCnt);
return (NULL);
}
err = cdStrcat(inf, stmnt, err, strCnt);
free(strCnt);
return (err);
}

/**
 * errorNotFound - function for the case - error not found
 * @inf: stucture for data containing argument variables
 * Return: displays error message
 */

char *errorNotFound(data_shell *inf)
{
int len;
char *err;
char *strCnt;
strCnt = iToA(inf->counter);
len = strLength(inf->av[0]) + strLength(strCnt);
len += strLength(inf->args[0]) + 16;
err = malloc(sizeof(char) * (len + 1));
if (err == 0)
{
free(err);
free(strCnt);
return (NULL);
}
strCpy(err, inf->av[0]);
strCat(err, ": ");
strCat(err, strCnt);
strCat(err, ": ");
strCat(err, inf->args[0]);
strCat(err, ": not found\n");
strCat(err, "\0");
free(strCnt);
return (err);
}

/**
 * errorExitShell - function for error message in get_exit
 * @inf: stucture for data containing argument variables
 * Return: displays error message
 */

char *errorExitShell(data_shell *inf)
{
int len;
char *err;
char *strCnt;
strCnt = iToA(inf->counter);
len = strLength(inf->av[0]) + strLength(strCnt);
len += strLength(inf->args[0]) + strLength(inf->args[1]) + 23;
err = malloc(sizeof(char) * (len + 1));
if (err == 0)
{
free(strCnt);
return (NULL);
}
strCpy(err, inf->av[0]);
strCat(err, ": ");
strCat(err, strCnt);
strCat(err, ": ");
strCat(err, inf->args[0]);
strCat(err, ": Illegal number: ");
strCat(err, inf->args[1]);
strCat(err, "\n\0");
free(strCnt);
return (err);
}
