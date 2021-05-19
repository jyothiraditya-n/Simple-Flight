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
#include <core/orientations.h>

/* External Resources */
#include <math.h>
#include <core/vectors.h>

/* Function Definitions */
orientation_t add_orientations(orientation_t a, orientation_t b) {
	a.alpha += b.alpha;
	a.beta += b.beta;
	a.gamma += b.gamma;

	return a;
}

orientation_t reverse_orientation(orientation_t orientation) {
	orientation.alpha = -orientation.alpha;
	orientation.beta = -orientation.beta;
	orientation.gamma = -orientation.gamma;

	return orientation;
}

orientation_t scale_orientation(orientation_t orientation, double factor) {
	orientation.alpha *= factor;
	orientation.beta *= factor;
	orientation.gamma *= factor;

	return orientation;
}

vector_t orient_vector(vector_t vector, orientation_t orientation) {
	vector_t x_axis = x_vector;
	vector_t y_axis = y_vector;
	vector_t z_axis = z_vector;

	y_axis = add_vectors(scale_vector(y_axis, cos(orientation.alpha)), add_vectors(scale_vector(vector_product(x_axis, y_axis), sin(orientation.alpha)),
		scale_vector(x_axis, scalar_product(x_axis, y_axis) * (1 - cos(orientation.alpha)))));
	z_axis = add_vectors(scale_vector(z_axis, cos(orientation.alpha)), add_vectors(scale_vector(vector_product(x_axis, z_axis), sin(orientation.alpha)),
		scale_vector(x_axis, scalar_product(x_axis, z_axis) * (1 - cos(orientation.alpha)))));

	x_axis = add_vectors(scale_vector(x_axis, cos(orientation.beta)), add_vectors(scale_vector(vector_product(y_axis, x_axis), sin(orientation.beta)),
		scale_vector(y_axis, scalar_product(y_axis, x_axis) * (1 - cos(orientation.beta)))));
	z_axis = add_vectors(scale_vector(z_axis, cos(orientation.beta)), add_vectors(scale_vector(vector_product(y_axis, z_axis), sin(orientation.beta)),
		scale_vector(y_axis, scalar_product(y_axis, z_axis) * (1 - cos(orientation.beta)))));

	x_axis = add_vectors(scale_vector(x_axis, cos(orientation.gamma)), add_vectors(scale_vector(vector_product(z_axis, x_axis), sin(orientation.gamma)),
		scale_vector(z_axis, scalar_product(z_axis, x_axis) * (1 - cos(orientation.gamma)))));
	y_axis = add_vectors(scale_vector(y_axis, cos(orientation.gamma)), add_vectors(scale_vector(vector_product(z_axis, y_axis), sin(orientation.gamma)),
		scale_vector(z_axis, scalar_product(z_axis, y_axis) * (1 - cos(orientation.gamma)))));

	vector = add_vectors(scale_vector(x_axis, vector.x), add_vectors(scale_vector(y_axis, vector.y), scale_vector(z_axis, vector.z)));
	return vector;
}
