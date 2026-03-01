/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:27:21 by mbah              #+#    #+#             */
/*   Updated: 2026/03/01 22:58:23 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file input_handler.c
 * @brief Handles keyboard and mouse input
 * for player movement and rotation.
 *
 * This file contains functions to process
 * key press and release events to update
 * the player's movement and rotation state.
 * It also includes logic to handle
 * mouse motion for camera rotation,
 * with horizontal wrapping to allow infinite
 * rotation without hitting window edges.
 */
#include "cub3d.h"

/**
 * @brief Handle key press events.
 *
 * Updates the player's movement and rotation state when a key is pressed.
 * No movement or rotation is applied directly here.
 *
 * @param key Pressed key code.
 * @param engine Pointer to the main engine structure.
 * @return Always returns 0.
 */
static int	handle_key_press(int key, t_engine *engine)
{
	t_input	*input;

	input = &engine->player.inputs;
	if (key == KEY_ESC)
		mlx_loop_end(engine->mlx);
	if (key == KEY_W)
		input->w = true;
	if (key == KEY_S)
		input->s = true;
	if (key == KEY_A)
		input->a = true;
	if (key == KEY_D)
		input->d = true;
	if (key == KEY_LEFT)
		input->left = true;
	if (key == KEY_RIGHT)
		input->right = true;
	if (key == XK_f)
		input->zoom = true;
	return (0);
}

/**
 * @brief Handle key release events.
 *
 * Resets the corresponding movement or rotation state when a key is released.
 *
 * @param key Released key code.
 * @param engine Pointer to the main engine structure.
 * @return Always returns 0.
 */
static int	handle_key_release(int key, t_input *input)
{
	if (key == KEY_W)
		input->w = false;
	if (key == KEY_S)
		input->s = false;
	if (key == KEY_A)
		input->a = false;
	if (key == KEY_D)
		input->d = false;
	if (key == KEY_LEFT)
		input->left = false;
	if (key == KEY_RIGHT)
		input->right = false;
	if (key == XK_f)
		input->zoom = false;
	return (0);
}

/**
 * @brief Wrap mouse position horizontally when reaching window edges.
 *

	* This allows infinite horizontal mouse movement for continuous camera rotation.
 *
 * @param engine Pointer to the main engine structure.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 */
static void	wrap_mouse_x_position(t_engine *engine, int x, int y)
{
	if (x > WIN_WIDTH - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_move_mouse(engine, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = WIN_WIDTH - DIST_EDGE_MOUSE_WRAP;
		mlx_move_mouse(engine, x, y);
	}
}

/**
 * @brief Handle mouse motion events.
 *
 * Rotates the player view depending on horizontal mouse movement.
 *
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param engine Pointer to the main engine structure.
 * @return Always returns 0.
 */
static int	handle_mouse_motion(int x, int y, t_engine *engine)
{
	static int	old_x = WIN_WIDTH / 2;

	wrap_mouse_x_position(engine, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		rotate(&engine->player.dir, &engine->player.plane, -ROTSPEED);
	else if (x > old_x)
		rotate(&engine->player.dir, &engine->player.plane, +ROTSPEED);
	return (0);
}

/**
 * @brief Register keyboard and mouse input hooks.
 *
 * Sets up event listeners for keyboard input and optional mouse motion.
 *
 * @param engine Pointer to the main engine structure.
 */
void	register_input_hooks(t_engine *engine)
{
	mlx_hook(engine->win, EVENT_KEY_PRESS, MASK_KEY_PRESS, handle_key_press,
		engine);
	mlx_hook(engine->win, EVENT_KEY_RELEASE, MASK_KEY_RELEASE,
		handle_key_release, &engine->player.inputs);
	if (BONUS)
	{
		mlx_hook(engine->win, EVENT_MOUSE_MOVE, MASK_POINTER_MOTION,
			handle_mouse_motion, engine);
	}
}
