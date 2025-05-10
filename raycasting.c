#include <stdlib.h>
#include <math.h>
#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void    draw_coluer(int x, int y,t_data *img,int colouer)
{
    int j = 0;
    int i = 0;
    while (i < 32)
    {

        j = 0;
        while (j < 32)
        {
            my_mlx_pixel_put(img, (x+j), (y+i), colouer);
            j++;
        }
        i++;
    }
    
}
void    draw(int map[10][10],t_data *img)
{
    int i = 0;
    int j = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 10)
        {
            if(map[i][j] == 1)
                draw_coluer(j*32,i*32,img,0xFF0000);
            else
                draw_coluer(j*32,i*32,img,0xFFFFFF);
            j++;
        }
        i++;
    }

}
int main()
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    int map[10][10]={{1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,0,1,0,1},
                    {1,0,1,0,0,1,0,1,0,1},
                    {1,0,1,1,0,1,0,1,0,1},
                    {1,0,1,0,0,1,0,1,0,1},
                    {1,0,0,0,0,0,0,0,0,1},
                    {1,1,0,0,0,0,0,0,0,1},
                    {1,0,1,1,0,1,0,1,0,1},
                    {1,0,0,1,0,1,0,1,0,1},
                    {1,1,1,1,1,1,1,1,1,1},};
    mlx = mlx_init();
    mlx_win=mlx_new_window(mlx,10*32,10* 32,"raycasting");
    img.img = mlx_new_image(mlx, 10 * 32, 10 * 32);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    draw(map,&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

}