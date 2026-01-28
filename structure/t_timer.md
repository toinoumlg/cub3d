# t\_timer

Structure containing variable for `get_time_of_day()` as well as delta\_time and time

```c
typedef struct s_timer
{
	struct timeval	last_frame;
	struct timeval	current_time;
	double			time; // time since begin
	double			delta_time; // time between frames
}					t_timer;
```
