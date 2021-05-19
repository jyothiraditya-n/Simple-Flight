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
#include <core/rays.h>

/* External Resources */
#include <core/vectors.h>

/* Function Definitions */
vector_t get_ray_position(ray_t ray, double lambda) {
	if(lambda >= 0) return add_vectors(ray.a, scale_vector(ray.b, lambda));
	else return infinite_vector;
}

vector_t complete_ray_position_yz(ray_t ray, double x) {
	double lambda;

	if(ray.b.x != 0.0) {
		lambda = (x - ray.a.x) / ray.b.x;

		if(lambda >= 0) return add_vectors(ray.a, scale_vector(ray.b, lambda));
		else return infinite_vector;
	}

	else return infinite_vector;
}

vector_t complete_ray_position_xz(ray_t ray, double y) {
	double lambda;

	if(ray.b.y != 0.0) {
		lambda = (y - ray.a.y) / ray.b.y;

		if(lambda >= 0) return add_vectors(ray.a, scale_vector(ray.b, lambda));
		else return infinite_vector;
	}

	else return infinite_vector;
}

vector_t complete_ray_position_xy(ray_t ray, double z) {
	double lambda;

	if(ray.b.z != 0.0) {
		lambda = (z - ray.a.z) / ray.b.z;

		if(lambda >= 0) return add_vectors(ray.a, scale_vector(ray.b, lambda));
		else return infinite_vector;
	}

	else return infinite_vector;
}
