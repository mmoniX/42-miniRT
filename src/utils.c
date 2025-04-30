/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gahmed <gahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:09:34 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/30 13:49:16 by gahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	check_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (!filename || len < 4)
		return (FAIL);
	if (ft_strncmp(filename + len - 3, ".rt", 3) != 0)
	{
		perror(filename);
		return (FAIL);
	}
	return (SUCCESS);
}

float	ft_atof(const char *str)
{
	float	num;
	float	frac;
	int		sign;
	int		i;

	num = 0;
	frac = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		frac = frac * 10 + (str[i++] - '0');
	frac /= pow(10, i - (ft_strchr(str, '.') - str) - 1);
	return (sign * (num + frac));
}

void	free_array(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*normalize_whitespace(char *str)
{
	int		i;
	char	*new_str;

	new_str = malloc(sizeof(char) * (strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str == '\t')
			new_str[i++] = ' ';
		else
			new_str[i++] = *str;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*
num = 0;
frac = 0;
frac_pos = 0.1;
sign = 1;
i = 0;
while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
    i++;
if (str[i] == '-' || str[i] == '+')
    if (str[i++] == '-')
        sign = -1;
while (str[i] >= '0' && str[i] <= '9')
    num = num * 10 + (str[i++] - '0');
if (str[i] == '.')
    i++;
while (str[i] >= '0' && str[i] <= '9')
{
    frac += frac_pos * (str[i++] - '0');
    frac_pos *= 0.1;
}
return (sign * (num + frac));
*/