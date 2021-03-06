#include "dynarray.h"

static int	realloc_content(t_dynarray *arr)
{
	void	*tmp;
	int		prev_size;

	prev_size = arr->byte_size;
	arr->byte_size *= 2;
	free(arr->tmp);
	if (!(tmp = malloc(arr->byte_size))
		|| !(arr->tmp = malloc(arr->byte_size)))
		return (-1);
	ft_memcpy(tmp, arr->c, prev_size);
	free(arr->c);
	arr->c = tmp;
	return (0);
}

int			check_space(t_dynarray *arr)
{
	++arr->nb_cells;
	while (arr->nb_cells * arr->cell_size >= arr->byte_size)
	{
		if (realloc_content(arr))
			return (-1);
	}
	return (0);
}
