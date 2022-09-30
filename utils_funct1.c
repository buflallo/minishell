/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funct1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 02:57:47 by hlachkar          #+#    #+#             */
/*   Updated: 2022/09/22 04:08:02 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_enter(void)
{
	if (g_vars.line[0] == '\0' || ft_is_space())
	{
		free(g_vars.line);
		return (1);
	}
	return (0);
}

void	*realloc_array(char **arg, char *str)
{
	char	**new_arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg && arg[i])
		i++;
	new_arg = (char **)malloc(sizeof(char *) * (i + 2));
	while (arg && j < i)
	{
		new_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	new_arg[j++] = ft_strdup(str);
	new_arg[j] = NULL;
	if (i> 0)
		free_2(arg);
	if (str)
		free(str);
	return (new_arg);
}

void	free_2(char **tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	if (tmp)
		free(tmp);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest && dest[i] != '\0')
		i++;
	j = 0;
	while (src && src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*join_3_str(char *s1, char *s2, char *s3)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	if (s3)
		str = ft_strcat(str, s3);
	return (str);
}
