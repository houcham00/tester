/*
** EPITECH PROJECT, 2023
** built-in
** File description:
** add cd, env and others
*/

#include "include/minishell.h"

void cmd_exit(char **cmd)
{
    if (my_strcmp(cmd[0], "exit") == 0) {
        exit(0);
    }
}

void call_func(int pos, char **cmd, char **env, ctrl_t *l)
{
    switch (pos) {
    case 0:
        cmd_cd(cmd, l);
        break;
    case 1:
        cmd_exit(cmd);
        break;
    case 2:
        cmd_env(l);
        break;
    case 3:
        my_unsetenv(cmd, l);
        break;
    case 4:
        my_setenv(cmd, l);
        break;
    }
}

int line_error(char *var)
{
    char c = var[0];
    if (c == '|' || c == '>' || c == '<') {
        write(2, "Invalid null command.\n", 22); return 1;
    }
    char d = var[1];
    if ((c == '|' && d == '|') || (c == '<' && d == '<')
        || (c == '>' && d == '>')) {
        write(2, "Invalid null command.\n", 22); return 2;
    }
    int l = my_strlen(line); char c = var[l];
    if (c == '|' || c == '>' || c == '<') {
        write(2, "Invalid null command.\n", 22); return 3;
    }
    char d = var[l - 1];
    if ((c == '|' && d == '|') || (c == '<' && d == '<')
        || (c == '>' && d == '>')) {
        write(2, "Invalid null command.\n", 22); return 4;
    }
    return 0;
}

char *tokens(char *s, int idx, int *del)
{
    int nbr = 0; int sign = 1; int x = idx;
    while (s[x] != ' ' && s[x] != '\t' && s[x] != '\0') {
        if (s[x] == '-') {
            sign = sign * (-1);
        }
        if (s[x] >= 48 && s[x] <= 57) {
            nbr *= 10;
            nbr += s[x] - 48;
            *del += 1;
        } x++;
    }
    return (nbr * sign);
}

float *str_to_arr(char *string, int type)
{
    int idx = 0; int j = 0; int c_atof = 0;
    int i = 1; int del = 0; float *arr = (float *)malloc(sizeof(float) * type);
    while (string[i] != '\0') {
        del = 0;
        if (string[i] >= '0' && string[i] <= '9') {
            idx = i;
            arr[j] = tokens(string, idx, &del);
            j++;
            i = idx + del;
            c_atof++;
        } else {
            i++;
        }
    }
    return ((c_atof == type) ? arr : NULL);
}

char *tokens(char *s, int *start, int *end)
{
    int len = *end - *start; int j = 0;
    char *tmp = (char *)malloc(sizeof(char) * (len + 1));
    for (int i = *start; i < *end; i++) {
        tmp[j] = s[i];
        j++;
    }
    tmp[j] = '\0';
    return tmp;
}

char redirection_call(char *s, int i, int *start, int *end)
{
    char c = s[i]; char d = s[i + 1]; char **cmd = NULL;
    if (c == '>') {
        build_for_redirection();
        //faire le build avant de vérifier la redirection
    }
    if (c == '<') {
        cmd = split_cmd(var, " \n\t\r");
    }
    if (c == '>' && d == '>') {
        cmd = split_cmd(var, " \n\t\r");
    }
    if (c == '<' && d == '<') {
        cmd = split_cmd(var, " \n\t\r");
    }
}

int is_redirection(char c)
{
    char c = s[i]; char d = s[i + 1];
    if (c == '>') return 1;
    if (c == '<') return 2;
    if (c == '>' && d == '>') return 3;
    if (c == '<' && d == '<') return 4;
    return 0;
}

char *manage_cmd_line(char *s, char **env, ctrl_t *list)
{
    int *start = 0; int *end = 0; int j = 0; char *tmp = NULL;
    char **pipe_cmd = NULL; int red; int is_sep = 0;
    char *m = (char *)malloc(sizeof(char) * my_strlen(s) + 1);
    for (int i = 0; s[i]; i++) {
        if (s[i] == ';') {
            *end = i - 1; tmp = tokens(s, start, end); build(tmp, env, list);
            *start = i + 1; is_sep += 1;
        }
        if (s[i] == '|') {
            *end = i - 1; pipe_cmd = pipe_str_list(s, start, end);
            call_pipe_builder(pipe_cmd); *start = i + 1; is_sep += 1;
        }
        if ((red = is_redirection(s[i])) != 0) {
            int val[2] = {red, i};
            tmp = redirection_call(s, val, start, end);
            (red, )
                *end = i;
            *start = i; is_sep += 1;
        }
    }
    if (is_sep == 0) build(s, env, list);
    return;
}

char *clean_line(char *s)
{
    int check = line_error(line);
    if (check == 0) return NULL;
    for (int i = 0; s[i]; i++) {
    }
}

void build(char *var, char **env, ctrl_t *list)
{
    char list_of_cmd[][10] = {"cd", "exit", "env", "unsetenv", "setenv"};
    int nbr_cmd = 5; int pos = -1; int test = line_error(var);
    if (test == 0) {
        char **cmd = split_cmd(var, " \n\t\r");
        if (cmd[0] != NULL) {
            pos = check_built_in(cmd[0], list_of_cmd, nbr_cmd);
            if (pos >= 0) {
                call_func(pos, cmd, env, list);
            } else {
                execve_call(cmd, env);
            }
        }
        free_cmd_tab(cmd);
    }
}
