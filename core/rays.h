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

#ifndef CORE_RAYS_HEADER
#define CORE_RAYS_HEADER

/* External Resources */
#include <core/vectors.h>

/* Type Declarations */
typedef struct ray_s {
	vector_t a, b;
} ray_t;

/* Function Declarations */
vector_t get_ray_position(ray_t ray, double lambda);
vector_t complete_ray_position_yz(ray_t ray, double x);
vector_t complete_ray_position_xz(ray_t ray, double y);
vector_t complete_ray_position_xy(ray_t ray, double z);

#endif
