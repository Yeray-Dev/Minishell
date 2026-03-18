/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:12:41 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 10:36:27 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//. HEADS

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <stddef.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include "../Libft/libft.h"
# include "minishell_type.h"
# include "minishell_parse.h"
# include "minishell_builtin.h"
# include "minishell_executor.h"

#endif
// docker run -it --rm -v $(pwd):/minishell minishell-dev