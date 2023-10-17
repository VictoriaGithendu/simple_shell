#include "main.h"

/**
 * cdShell - function that swithces to current directoy
 * @inf: stucture for data containing argument variables
 * Return: 1 if successful
 */

int cdShell(data_shell *inf)
{
char *inpt;
int isHome, isHomeAlt, isDash;
inpt = inf->args[1];
if (inpt != NULL)
{
isHome = strCmp("$HOME", inpt);
isHomeAlt = strCmp("~", inpt);
isDash = strCmp("--", inpt);
}
if (inpt == NULL || !isHome || !isHomeAlt || !isDash)
{
cdHome(inf);
return (1);
}
if (strCmp("-", inpt) == 0)
{
cdPrev(inf);
return (1);
}
if (strCmp(".", inpt) == 0 || strCmp("..", inpt) == 0)
{
cdDot(inf);
return (1);
}
cdTo(inf);
return (1);
}

