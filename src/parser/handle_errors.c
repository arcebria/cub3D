#include "../../inc/cub3D.h"

void    handle_error(int error_code)
{
    if (error_code == ERR_EXTENSION_CODE)
        ft_putstr_fd(ERR_EXTENSION, 2);
    else if (error_code == ERR_EMPTY_MAP_CODE)
        ft_putstr_fd(ERR_EMPTY_MAP, 2);
    else if (error_code == ERR_MALLOC_CODE)
        ft_putstr_fd(ERR_MALLOC, 2);
    else if (error_code == ERR_TEXT_COLOR_PLACE_CODE)
        ft_putstr_fd(ERR_TEXT_COLOR_PLACE, 2);
    else if (error_code == ERR_TEXT_COLOR_NUMBER_CODE)
        ft_putstr_fd(ERR_TEXT_COLOR_NUMBER, 2);
    else if (error_code == ERR_COLOR_CODE)
        ft_putstr_fd(ERR_COLOR, 2);
    exit(error_code);
}
