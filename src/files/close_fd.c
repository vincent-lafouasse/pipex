/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:31:12 by poss              #+#    #+#             */
/*   Updated: 2024/08/20 12:32:43 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_files.h"
#include <unistd.h>

void	close_fd(int *fd)
{
	if (!fd || *fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}
