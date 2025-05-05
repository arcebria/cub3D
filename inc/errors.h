/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:38:28 by arcebria          #+#    #+#             */
/*   Updated: 2025/05/05 16:49:06 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ARGC "Error\nInvalid number of arguments\n"
# define ERR_EXTENSION "Error\nInvalid file extension\n"
# define ERR_FILE_OPEN "Error\nFailed to open file\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_EMPTY_MAP "Error\nEmpty map\n"
# define ERR_TEXT_COLOR_PLACE "Error\nInvalid texture or color place\n"
# define ERR_TEXT_COLOR_NUMBER "Error\nInvalid number of textures or colors\n"
# define ERR_COLOR "Error\nInvalid color format\n"

# define ERR_EXTENSION_CODE 0
# define ERR_EMPTY_MAP_CODE 1
# define ERR_MALLOC_CODE 2
# define ERR_TEXT_COLOR_PLACE_CODE 3
# define ERR_TEXT_COLOR_NUMBER_CODE 4
# define ERR_COLOR_CODE 5

void    handle_error(int error_code);

#endif
