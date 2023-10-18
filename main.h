#ifndef _MAIN_H_
#define _MAIN_H_

/* libraries used */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>


/* structures */

/**
 * struct data - data structure with relevant data
 * @status: shell status pointer
 * @av: argument vector
 * @input: user input
 * @args: input element from user
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: shell process ID
 */

typedef struct data
{
char **av;
char *input;
char **args;
int status;
int counter;
char **_environ;
char *pid;
} data_shell;


/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */

typedef struct sep_list_s
{
char separator;
struct sep_list_s *next;
} sep_list;


/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
char *line;
struct line_list_s *next;
} line_list;



/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variable
 */

typedef struct r_var_list
{
int len_var;
char *val;
int len_val;
struct r_var_list *next;
} r_var;


/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */

typedef struct builtin_s
{
char *name;
int (*f)(data_shell *datash);
} builtin_t;


/* macros */
#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"


/* Pointer to array of strings */
extern char **environ;

/* prototypes */

/* lists1.c */
sep_list *addSepNodeEnd(sep_list **, char);
void freeSepList(sep_list **);
line_list *addLineNodeEnd(line_list **, char *);
void freeLineList(line_list **);

/* lists2.c */
r_var *addVarNode(r_var **, int, char *, int);
void freeVarList(r_var **);

/* str1.c */
char *strCat(char *, const char *);
char *strCpy(char *, char *);
int strCmp(char *, char *);
char *strChr(char *, char);
int strSpn(char *, char *);

/* mem.c */
void memCpy(void *, const void *, unsigned int);
void *reAlloc(void *, unsigned int, unsigned int);
char **reAllocDp(char **, unsigned int, unsigned int);

/* str2.c */
char *strDup(const char *);
int strLength(const char *);
int cmpChars(char str[], const char *);
char *strTok(char str[], const char *);
int isDigit(const char *);

/* str3.c */
void revString(char *);

/* syntErr.c */
int repChar(char *, int);
int sepError(char *, int, char);
int firstChar(char *, int *);
void printSyntaxError(data_shell *, char *, int, int bool);
int checkSyntaxError(data_shell *, char *);

/* shell.c */
char *remove_comments(char *input);
void run_shell(data_shell *data_struct);

/* string_split.c */
char *swap_special_chars(char *input, int bool);
void addNode(sep_list **head_s, line_list **head_l, char *input);
void move_to_nxt(sep_list **sep_l, line_list **line_l, data_shell *);
int execute_commands(data_shell *data_struct, char *input);
char **spliLine(char *input);

/* var.c */
void check_env_alt(r_var **var_list, char *input_str, data_shell *data_struct);
int find_var(r_var **var_l, char *input_s, char *stat, data_shell *);
char *rep_var(r_var **var_l, char *input_s, char *new_input, int new_length);
char *rep_str_var(char *input_str, data_shell *data_struct);

/* line.c */
void assign_line_buffer(char **linep, size_t *x, char *buf, size_t y);
ssize_t read_line_input(char **line_buffer, size_t *line_size, FILE *stream);
char *read_input_line(int *i_eof);

/* cmdExec.c */
int isCdir(char *path, int *i);
char *cmdWhich(char *cmd, char **_environ);
int isExec(data_shell *datash);
int checkCmdError(char *dir, data_shell *datash);
int cmdExec(data_shell *datash);

/* environ.c */
char *get_environ(const char *name, char **_environ);
int print_environ(data_shell *data_struct);
int cmp_environ_var(const char *environ_var, const char *name);

/* environ1.c */
char *dup_inf(char *cmd_name, char *cmd_value);
void _setenviron(char *cmd_name, char *cmd_value, data_shell *data_struct);
int _set_environ(data_shell *data_struct);
int _unset_environ(data_shell *data_struct);

/* cd.c */
void cdDot(data_shell *);
void cdTo(data_shell *);
void cdPrev(data_shell *);
void cdHome(data_shell *);

/* cShell.c */
int cdShell(data_shell *);

/* builtin.c */
int (*find_builtin(char *command))(data_shell *data_struct);
int execute_line(data_shell *data_struct);

/* exit.c */
int exit_shell(data_shell *data_struct);

/* stdlib.c*/
int getLength(int);
char *iToA(int);
int aToI(char *);

/* errors1.c */
char *cdStrcat(data_shell *, char *, char *, char *);
char *getCdError(data_shell *);
char *errorNotFound(data_shell *);
char *errorExitShell(data_shell *);

/* errors2.c */
char *errorEnv(data_shell *);
char *errorPath(data_shell *);

/* error.c */
int handle_error(data_shell *data_struct, int err_val);

/* handle_sigint.c */
void handle_sigint(int signal);

/* help1.c*/
void envHelp(void);
void setenvHelp(void);
void unsetenvHelp(void);
void generalHelp(void);
void exitHelp(void);

/* help2.c*/
void infHelp(void);
void aliasHelp(void);
void cdHelp(void);

/* help.c */
int handle_help(data_shell *data_struct);

#endif
