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

#ifndef CORE_VECTORS_HEADER
#define CORE_VECTORS_HEADER

/* Type Declarations */
typedef struct vector_s {
	double x, y, z;

	/* Z is the cross product of x and y. */
	/* Y is the cross product of z and x. */
	/* X is the cross product of y and z. */
} vector_t;

/* Variable Declarations */
vector_t null_vector, infinite_vector;
vector_t x_vector, y_vector, z_vector;

/* Function Declarations */
double scalar_length(vector_t vector);
vector_t direction_vector(vector_t vector);

vector_t add_vectors(vector_t a, vector_t b);
vector_t reverse_vector(vector_t vector);
vector_t scale_vector(vector_t vector, double factor);

double scalar_product(vector_t a, vector_t b);
vector_t vector_product(vector_t a, vector_t b);

#endif
