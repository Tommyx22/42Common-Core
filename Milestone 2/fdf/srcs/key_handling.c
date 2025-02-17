#include "../includes/fdf.h"

static void key_translate(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_RIGHT)
        fdf->cam->move_x += 10;
    else if (keycode == KEY_LEFT)
        fdf->cam->move_x -= 10;
    else if (keycode == KEY_DOWN)
        fdf->cam->move_y += 10;
    else if (keycode == KEY_UP)
        fdf->cam->move_y -= 10;
}

static void key_scaling(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_PLUS)
        fdf->cam->scale += 1;
    else if (keycode == KEY_MINUS)
        fdf->cam->scale -= 1;
    else if (keycode == KEY_Z && fdf->cam->scale > -1)
        fdf->cam->scale_z -=  0.1;
    else if (keycode == KEY_X && fdf->cam->scale < 1)
        fdf->cam->move_y += 0.1;
}

static void key_rotate(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_S)
        fdf->cam->alpha -= (5 * ANG_1);
    else if (keycode == KEY_W)
        fdf->cam->alpha += (5 * ANG_1);
    else if (keycode == KEY_A)
        fdf->cam->gamma -= (5 * ANG_1);
    else if (keycode == KEY_D)
        fdf->cam->gamma += (5 * ANG_1);
    else if (keycode == KEY_Q)
        fdf->cam->beta -= (5 * ANG_1);
    else if (keycode == KEY_E)
        fdf->cam->beta += (5 * ANG_1);
}

static void key_views(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_P)
        fdf->cam->projection = PERSPECTIVE;
    else if (keycode == KEY_I)
        fdf->cam->projection = ISOMETRIC;
    else if (keycode == KEY_O)
        fdf->cam->projection = TOP;
}

int key_pressed(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_ESC)
        close_all(fdf);
    else if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP \
		|| keycode == KEY_DOWN)
        key_translate(keycode, fdf);
    else if(keycode == KEY_PLUS || keycode == KEY_MINUS || keycode == KEY_Z \
		|| keycode == KEY_X)
        key_scaling(keycode, fdf);
    else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D \
		|| keycode == KEY_Q || keycode == KEY_W || keycode == KEY_E)
        key_rotate(keycode, fdf);
    else if (keycode == KEY_P || keycode == KEY_I || keycode == KEY_O)
        key_views(keycode, fdf);
    else if (keycode == KEY_SPACE)
    {
        if(fdf->cam->color_Pal == FALSE)
            fdf->cam->color_Pal = TRUE;
        else
            fdf->cam->color_Pal = FALSE;
    }
    else if (keycode == KEY_R)
        reset(fdf);
    render(fdf);
    return (0);
}
