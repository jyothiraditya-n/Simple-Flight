/* Simple Flight Copyright (C) 2019 Jyothiraditya Nellakra */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program. If not, see <https://www.gnu.org/licenses/>. */

/* Include the header file. */
#include <graphics/variables.h>

/* External Resources */
#include <stdbool.h>
#include <stddef.h>

/* Variable Definitions */
char *screen = 0;
size_t screen_height = 0;
size_t screen_width = 0;

char *graphics_file = 0;
orientation_t viewport_orientation = {0.0, 0.0, 0.0};
vector_t viewport_position = {0.0, 0.0, 0.0};

vector_t display_scale = {0.0, 0.0, 0.0};
double render_distance = 0.0;
double render_density = 0.0;
bool graphics_ready;

size_t *plane_body_point_counts = 0;
vector_t **plane_body_point_positions = 0;
