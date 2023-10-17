#include "main.h"

/**
 * errorEnv - function to display evn error message in get_env
 * @inf: stucture for data containing argument variables
 * Return: displays the error message
 */
char *errorEnv(data_shell *inf)
{
int len;
char *err;
char *strCnt;
char *stmnt;
strCnt = iToA(inf->counter);
stmnt = ": Unable to add/remove from environment\n";
len = strLength(inf->av[0]) + strLength(strCnt);
len += strLength(inf->args[0]) + strLength(stmnt) + 4;
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
strCat(err, stmnt);
strCat(err, "\0");
free(strCnt);
return (err);
}
/**
 * errorPath - function to display error message for path
 * @inf: stucture for data containing argument variables
 * Return: displays string error message
 */
char *errorPath(data_shell *inf)
{
int len;
char *strCnt;
char *err;
strCnt = iToA(inf->counter);
len = strLength(inf->av[0]) + strLength(strCnt);
len += strLength(inf->args[0]) + 24;
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
strCat(err, ": Permission denied\n");
strCat(err, "\0");
free(strCnt);
return (err);
}
