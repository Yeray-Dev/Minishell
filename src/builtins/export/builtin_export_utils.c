/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:42:56 by jugarcia          #+#    #+#             */
/*   Updated: 2026/03/12 12:42:56 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Extrae el nombre de la variable antes del '=' */
char *get_var_name(const char *arg)
{
    int i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    return ft_substr(arg, 0, i);
}

/* Comprueba si un identificador es válido para export */
int is_valid_identifier(const char *str)
{
    int i;
    if (!str || !str[0] || str[0] == '=')
        return 0;
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return 0;
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

/* Copia segura del array de entorno */
char **env_copy(char **env)
{
    int i = 0;
    char **copy;
    while (env[i])
        i++;
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (env[i])
    {
        copy[i] = ft_strdup(env[i]);
        if (!copy[i])
        {
            while (i > 0)
                free(copy[--i]);
            free(copy);
            return NULL;
        }
        i++;
    }
    copy[i] = NULL;
    return copy;
}

/* Ordena el array de entorno alfabéticamente */
void env_sort(char **env)
{
    int i = 0;
    char *tmp;
    while (env[i + 1])
    {
        if (ft_strcmp(env[i], env[i + 1]) > 0)
        {
            tmp = env[i];
            env[i] = env[i + 1];
            env[i + 1] = tmp;
            i = 0;
        }
        else
            i++;
    }
}

/* Imprime una variable en formato declare -x */
void print_export(char *var)
{
    int i = 0;
    if (!var || !ft_strcmp(var, "_="))
        return;
    printf("declare -x ");
    while (var[i] && var[i] != '=')
        printf("%c", var[i++]);
    if (var[i] == '=')
        printf("=\"%s\"", var + i + 1);
    printf("\n");
}