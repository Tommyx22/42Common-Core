#include "../includes/fdf.h"

static int  expose_handle(t_fdf *fdf)
{
    render(fdf);
    return (0);
}

int main(int ac, char **av)
{
    char    *file_name;
    t_fdf   *fdf;

    if (ac == 2)
    {
        file_name = av[1];
        fdf = init_project(file_name);
        render(fdf);
        mlx_key_hook(fdf->win, &key_pressed, fdf);
        mlx_hook(fdf->win, 17, 0, &close_all, NULL);
        mlx_expose_hook(fdf->win, &expose_handle, fdf);
        mlx_loop(fdf->mlx);
    }
    return (0);
}
