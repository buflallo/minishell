/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:25:41 by hlachkar          #+#    #+#             */
/*   Updated: 2022/09/24 05:02:51 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_unused(int frr, char *s1, char *s2)
{
	if (frr != -1)
	{
		if (frr == 0 && s1)
			free(s1);
		else if (frr == 1 && s2)
			free(s2);
		else if (frr == 2 && s1 && s2)
		{
			free(s1);
			free(s2);
		}
	}
}

void	join_string2(char *str, char *s2, int j)
{
	int	i;

	i = -1;
	while (s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2, int frr)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((!s1 && !s2))
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if ((!s1 && s2[0] == 0) || (s1[0] == 0 && !s2))
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	join_string2(str, s2, j);
	free_unused(frr, s1, s2);
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	char	sym;

	ptr = (char *)str;
	sym = (char)c;
	while (*ptr && !(*ptr == sym))
		ptr++;
	if (*ptr == sym)
		return (ptr);
	else
		return (NULL);
}
