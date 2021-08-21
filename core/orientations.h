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

#ifndef CORE_ORIENTATIONS_HEADER
#define CORE_ORIENTATIONS_HEADER

/* External Resources */
#include <core/vectors.h>

/* Type Declarations */
typedef struct orientation_s {
	double alpha, beta, gamma;

	/* Alpha is taken with respect to the x-axis. */
	/* Beta is taken with respect to the y-axis. */
	/* Gamma is taken with respect to the z-axis. */
} orientation_t;

/* Function Declarations */
orientation_t add_orientations(orientation_t a, orientation_t b);
orientation_t reverse_orientation(orientation_t orientation);
orientation_t scale_orientation(orientation_t orientation, double factor);

vector_t orient_vector(vector_t vector, orientation_t orientation);

#endif
