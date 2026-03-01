/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:49:32 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 19:55:29 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Allocate and initialize the texture pixel buffer.
 *
 * This buffer stores the final rendered pixels column by column
 * before being displayed on screen.
 *
 * @param engine Pointer to the main engine structure.
 */

/**
 * @brief Render one vertical textured wall slice on the screen.
 *
 * This function draws a single vertical column of a wall using the correct
 * texture, based on the raycasting result.
 *
 * In a raycasting engine (like Wolfenstein 3D), the 3D scene is rendered
 * column by column. For each screen column:
 *
 * 1. A ray is cast into the map.
 * 2. The ray hits a wall.
 * 3. The wall is projected vertically on the screen.
 * 4. A vertical slice of the correct texture is drawn.
 *
 * This function performs step 4.
 *
 * ---------------------------------------------------------------------------
 * PARAMETERS
 * ---------------------------------------------------------------------------
 *
 * @param engine
 *      Pointer to the main engine structure.
 *      Contains:
 *          - win_height       : window height
 *          - textures[][]     : all loaded textures (stored as 1D arrays)
 *          - texture_pixels[][] : final screen pixel buffer
 *
 * @param tex
 *      Texture rendering helper structure.
 *      Used to compute:
 *          - size  : texture width/height (e.g., 64)
 *          - x     : horizontal coordinate in texture
 *          - y     : vertical coordinate in texture
 *          - step  : how much to move in texture per screen pixel
 *          - pos   : current vertical texture position
 *          - index : which wall texture to use (NORTH, SOUTH, EAST, WEST)
 *
 * @param ray
 *      Result of the raycasting calculation for this column.
 *      Contains:
 *          - side        : 0 = vertical wall hit, 1 = horizontal wall hit
 *          - dir_x/y     : ray direction
 *          - wall_x      : exact hit position on the wall (range [0,1])
 *          - line_height : projected wall height on screen
 *          - draw_start  : top pixel of the wall slice on screen
 *          - draw_end    : bottom pixel of the wall slice on screen
 *
 * @param screen_x
 *      The x coordinate of the screen column being drawn.
 *
 * ---------------------------------------------------------------------------
 * STEP-BY-STEP EXPLANATION
 * ---------------------------------------------------------------------------
 *
 * STEP 1 — Select the correct wall texture
 *      Depending on which side of the wall was hit (N/S/E/W),
 *      select_wall_texture() determines which texture index to use.
 *
 * STEP 2 — Compute horizontal texture coordinate (tex->x)
 *      wall_x represents where the ray hit the wall (from 0 to 1).
 *      Multiplying by texture size gives the exact X pixel in the texture.
 *
 *      Example:
 *          wall_x = 0.5
 *          size = 64
 *          → tex->x = 32
 *
 * STEP 3 — Flip texture if needed
 *      Depending on viewing direction, the texture may need to be mirrored
 *      horizontally to avoid appearing reversed.
 *
 * STEP 4 — Compute vertical texture step
 *      step = texture_size / projected_wall_height
 *
 *      This tells us how much to move inside the texture
 *      for each vertical screen pixel.
 *
 * STEP 5 — Compute initial vertical texture position
 *      Align the texture with the projected wall so it maps correctly
 *      from top to bottom.
 *
 * STEP 6 — Draw the vertical slice
 *      For each screen pixel between draw_start and draw_end:
 *
 *          1. Compute texture Y coordinate
 *          2. Fetch the color from texture
 *          3. Optionally darken certain wall sides (fake lighting)
 *          4. Write the pixel into the screen buffer
 *
 * ---------------------------------------------------------------------------
 * MENTAL MODEL
 * ---------------------------------------------------------------------------
 *
 * Imagine the screen is built from many thin vertical strips.
 *
 * For each strip:
 *      - A ray tells us which wall was hit.
 *      - We cut a vertical slice from the wall texture.
 *      - We stretch or compress that slice to match the wall height.
 *      - We paste it onto the screen column.
 *
 * The final 3D illusion is simply thousands of these textured vertical
 * slices drawn side by side.
 *
 * This function draws ONE of those slices.
 */
void	draw_vertical_line(int x, int *buffer, t_raycast *ray, t_image *texture)
{
	int	color;
	int	y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = *(texture->addr + (int)ray->texture_coord.x
				+ (int)ray->texture_coord.y * texture->w);
		ray->texture_coord.y += ray->step;
		if (ray->wall_dir == NORTH || ray->wall_dir == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			*(buffer + x + y++ * WIN_WIDTH) = color;
	}
}
