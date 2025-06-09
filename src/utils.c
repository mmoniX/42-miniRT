/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:09:34 by mmonika           #+#    #+#             */
/*   Updated: 2025/06/09 18:10:16 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
	int	i;

	i = 0;
	if (!arr)
		return ;
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
		return (free(new_str), NULL);
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

int	rgba_channel(t_col col)
{
	int	alpha;

	alpha = 0xFF;
	return ((col.red << 24) | (col.green << 16) | (col.blue << 8) | alpha);
}

t_col	clamp_color(t_col col)
{
	col.red = fmin(255, fmax(0, col.red));
	col.green = fmin(255, fmax(0, col.green));
	col.blue = fmin(255, fmax(0, col.blue));
	return (col);
}
