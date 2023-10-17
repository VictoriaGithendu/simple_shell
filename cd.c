#include "main.h"

/**
 * cdDot - function that edits the parent directory
 * @inf: stucture for data containing argument variables
 * Return: nothing
 */
void cdDot(data_shell *inf)
{
char pwDir[PATH_MAX];
char *direc, *cpPwd, *cpStrtokPwd;
getcwd(pwDir, sizeof(pwDir));
cpPwd = strDup(pwDir);
_setenviron("OLDPWD", cpPwd, inf);
direc = inf->args[1];
if (strCmp(".", direc) == 0)
{
_setenviron("PWD", cpPwd, inf);
free(cpPwd);
return;
}
if (strCmp("/", cpPwd) == 0)
{
free(cpPwd);
return;
}
cpStrtokPwd = cpPwd;
revString(cpStrtokPwd);
cpStrtokPwd = strTok(cpStrtokPwd, "/");
if (cpStrtokPwd != NULL)
{
cpStrtokPwd = strTok(NULL, "\0");
if (cpStrtokPwd != NULL)
revString(cpStrtokPwd);
}
if (cpStrtokPwd != NULL)
{
chdir(cpStrtokPwd);
_setenviron("PWD", cpStrtokPwd, inf);
}
else
{
chdir("/");
_setenviron("PWD", "/", inf);
}
inf->status = 0;
free(cpPwd);
}


/**
 * cdTo - function to change to user given directory
 * @inf: stucture for data containing argument variables
 * Return: nothing
 */

void cdTo(data_shell *inf)
{
char pwDir[PATH_MAX];
char *direc, *cpPwd, *cpDir;
getcwd(pwDir, sizeof(pwDir));
direc = inf->args[1];
if (chdir(direc) == -1)
{
handle_error(inf, 2);
return;
}
cpPwd = strDup(pwDir);
_setenviron("OLDPWD", cpPwd, inf);
cpDir = strDup(direc);
_setenviron("PWD", cpDir, inf);
free(cpPwd);
free(cpDir);
inf->status = 0;
chdir(direc);
}

/**
 * cdPrev - function that changes to previous directory
 * @inf: stucture for data containing argument variables
 * Return: nothing
 */

void cdPrev(data_shell *inf)
{
char pwDir[PATH_MAX];
char *pPwd, *pOldPwd, *cpPwd, *cpOldPwd;
getcwd(pwDir, sizeof(pwDir));
cpPwd = strDup(pwDir);
pOldPwd = get_environ("OLDPWD", inf->_environ);
if (pOldPwd == NULL)
cpOldPwd = cpPwd;
else
cpOldPwd = strDup(pOldPwd);
_setenviron("OLDPWD", cpPwd, inf);
if (chdir(cpOldPwd) == -1)
_setenviron("PWD", cpPwd, inf);
else
_setenviron("PWD", cpOldPwd, inf);
pPwd = get_environ("PWD", inf->_environ);
write(STDOUT_FILENO, pPwd, strLength(pPwd));
write(STDOUT_FILENO, "\n", 1);
free(cpPwd);
if (pOldPwd)
free(cpOldPwd);
inf->status = 0;
chdir(pPwd);
}

/**
 * cdHome - function to move to home directory
 * @inf: stucture for data containing argument variables
 * Return: nothing
 */

void cdHome(data_shell *inf)
{
char *pPwd, *hm;
char pwDir[PATH_MAX];
getcwd(pwDir, sizeof(pwDir));
pPwd = strDup(pwDir);
hm = get_environ("HOME", inf->_environ);
if (hm == NULL)
{
_setenviron("OLDPWD", pPwd, inf);
free(pPwd);
return;
}
if (chdir(hm) == -1)
{
handle_error(inf, 2);
free(pPwd);
return;
}
_setenviron("OLDPWD", pPwd, inf);
_setenviron("PWD", hm, inf);
free(pPwd);
inf->status = 0;
}
