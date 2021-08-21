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
#include <physics/variables.h>

/* External Resources */
#include <stddef.h>

#include <core/orientations.h>
#include <core/vectors.h>
#include <physics/bodies.h>

/* Variable Definitions */
char *plane_file = 0;

body_t *plane_bodies = 0;
size_t plane_body_count = 0;

orientation_t plane_orientation = {0.0, 0.0, 0.0};
vector_t plane_position = {0.0, 0.0, 0.0};

orientation_t plane_angular_velocity = {0.0, 0.0, 0.0};
vector_t plane_velocity = {0.0, 0.0, 0.0};
