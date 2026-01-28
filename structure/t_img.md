# t\_img

Structure containing all data when creating an image with MinilibX

```c
typedef struct s_img
{
	void			*ptr; // pointer to the img_t struct for mlx functions 
	char			*addr; // pointer to the first pixel
	int				bpp; // bits per pixel
	int				lenght; // 
	int				end; // endian
	int				w; // widht
	int				h; // height
}					t_img;
```
