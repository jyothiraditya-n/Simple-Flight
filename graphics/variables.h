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

#ifndef GRAPHICS_VARIABLES_HEADER
#define GRAPHICS_VARIABLES_HEADER

/* External Resources */
#include <stdbool.h>
#include <stddef.h>
#include <core/orientations.h>
#include <core/vectors.h>

/* Variable Declarations */
char *screen;
size_t screen_height, screen_width;

char *graphics_file;
orientation_t viewport_orientation;
vector_t viewport_position;

vector_t display_scale;
double render_density, render_distance;
bool graphics_ready;

size_t *plane_body_point_counts;
vector_t **plane_body_point_positions;

#endif
