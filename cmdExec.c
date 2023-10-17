#include "main.h"

/**
 * isCdir - function that checks current directory for ":"
 * @dirPath: pointer to the directory path
 * @cnt: indes pointer
 * Return: 1 on success, otherwise 0
 */

int isCdir(char *dirPath, int *cnt)
{
if (dirPath[*cnt] == ':')
return (1);
while (dirPath[*cnt] != ':' && dirPath[*cnt])
{
*cnt += 1;
}
if (dirPath[*cnt])
*dirPath += 1;
return (0);
}


/**
 * cmdWhich - function to check for a command
 * @cmd: poiner to name of command
 * @env: double pointer to environment variable
 * Return: NULL
 */

char *cmdWhich(char *cmd, char **env)
{
char *cmdPath, *ptrPath, *tokenPath, *direc;
int dirLen, cmdLen, cnt;
struct stat st;
cmdPath = get_environ("PATH", env);
if (cmdPath)
{
ptrPath = strDup(cmdPath);
cmdLen = strLength(cmd);
tokenPath = strTok(ptrPath, ":");
cnt = 0;
while (tokenPath != NULL)
{
if (isCdir(cmdPath, &cnt))
if (stat(cmd, &st) == 0)
return (cmd);
dirLen = strLength(tokenPath);
direc = malloc(dirLen + cmdLen + 2);
strCpy(direc, tokenPath);
strCat(direc, "/");
strCat(direc, cmd);
strCat(direc, "\0");
if (stat(direc, &st) == 0)
{
free(ptrPath);
return (direc);
}
free(direc);
tokenPath = strTok(NULL, ":");
}
free(ptrPath);
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}
if (cmd[0] == '/')
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}


/**
 * isExec - function to check if a command is executable
 * @inf: stucture for data containing argument variables
 * Return: 0 if unsuccessful otherwise any number
 */

int isExec(data_shell *inf)
{
struct stat st;
int cnt;
char *inpt;
inpt = inf->args[0];
for (cnt = 0; inpt[cnt]; cnt++)
{
if (inpt[cnt] == '.')
{
if (inpt[cnt + 1] == '.')
return (0);
if (inpt[cnt + 1] == '/')
continue;
else
break;
}
else if (inpt[cnt] == '/' && cnt != 0)
{
if (inpt[cnt + 1] == '.')
continue;
cnt++;
break;
}
else
break;
}
if (cnt == 0)
return (0);
if (stat(inpt + cnt, &st) == 0)
{
return (cnt);
}
handle_error(inf, 127);
return (-1);
}


/**
 * checkCmdError - function to check if user has access permission
 * @direc: pointer to destination
 * @inf: stucture for data containing argument variables
 * Return: 0 on success, otherwise 1
 */

int checkCmdError(char *direc, data_shell *inf)
{
if (direc == NULL)
{
handle_error(inf, 127);
return (1);
}
if (strCmp(inf->args[0], direc) != 0)
{
if (access(direc, X_OK) == -1)
{
handle_error(inf, 126);
free(direc);
return (1);
}
free(direc);
}
else
{
if (access(inf->args[0], X_OK) == -1)
{
handle_error(inf, 126);
return (1);
}
}
return (0);
}


/**
 * cmdExec - function to execute commands
 * @inf: stucture for data containing argument variables
 * Return: 1 on success.
 */

int cmdExec(data_shell *inf)
{
pid_t procId;
pid_t wpd;
int state;
int exect;
char *direc;
(void) wpd;
exect = isExec(inf);
if (exect == -1)
return (1);
if (exect == 0)
{
direc = cmdWhich(inf->args[0], inf->_environ);
if (checkCmdError(direc, inf) == 1)
return (1);
}
procId = fork();
if (procId == 0)
{
if (exect == 0)
direc = cmdWhich(inf->args[0], inf->_environ);
else
direc = inf->args[0];
execve(direc + exect, inf->args, inf->_environ);
}
else if (procId < 0)
{
perror(inf->av[0]);
return (1);
}
else
{
do {
wpd = waitpid(procId, &state, WUNTRACED);
} while (!WIFEXITED(state) && !WIFSIGNALED(state));
}
inf->status = state / 256;
return (1);
}
