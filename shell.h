#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* Constants */
#define BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/* Function Prototypes */

/* main.c */
int _eputs(const char *str);
int _eputchar(char c);
int hsh(void);

/* builtin.c */
void print_error(char *command, int count);
void print_number(int n);
int _myexit(char **args);
int _mycd(char **args);

/* environ.c */
int _mysetenv(char **args);
int _myunsetenv(char **args);

/* history.c */
void _putsfd(int fd, const char *str);

/* lists1.c */
char *convert_number(int num);

/* vars.c */
char *convert_number(int num);

/* shell_loop.c */
char *find_cmd(char *cmd);
void execute(char **args);

/* getLine.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *remove_comments(char *line);

/* tokenizer.c */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
int is_delim(char c, char *delim);

#endif /* SHELL_H */
