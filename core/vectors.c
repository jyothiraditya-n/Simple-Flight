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
#include <core/vectors.h>

/* External Resources */
#include <math.h>

/* Variable Definitions */
vector_t null_vector = {0.0, 0.0, 0.0};
vector_t infinite_vector = {INFINITY, INFINITY, INFINITY};

vector_t x_vector = {1.0, 0.0, 0.0};
vector_t y_vector = {0.0, 1.0, 0.0};
vector_t z_vector = {0.0, 0.0, 1.0};

/* Function Definitions */
double scalar_length(vector_t vector) {
	return pow(pow(vector.x, 2.0) + pow(vector.y, 2.0) + pow(vector.z, 2.0), 0.5);
}

vector_t direction_vector(vector_t vector) {
	double length = scalar_length(vector);

	if(length != 0.0) {
		vector.x /= length;
		vector.y /= length;
		vector.z /= length;

		return vector;
	}

	else return null_vector;
}

vector_t add_vectors(vector_t a, vector_t b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;

	return a;
}

vector_t reverse_vector(vector_t vector) {
	vector.x = -vector.x;
	vector.y = -vector.y;
	vector.z = -vector.z;

	return vector;
}

vector_t scale_vector(vector_t vector, double factor) {
	vector.x *= factor;
	vector.y *= factor;
	vector.z *= factor;

	return vector;
}

double scalar_product(vector_t a, vector_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vector_t vector_product(vector_t a, vector_t b) {
	vector_t vector;

	vector.x = (a.y * b.z) - (b.y * a.z);
	vector.y = (b.x * a.z) - (a.x * b.z);
	vector.z = (a.x * b.y) - (b.x * a.y);

	return vector;
}
