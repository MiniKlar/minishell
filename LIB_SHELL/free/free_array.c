/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:21:38 by lomont            #+#    #+#             */
/*   Updated: 2025/06/19 13:20:56 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
