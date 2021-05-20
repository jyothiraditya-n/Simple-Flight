/* Simple Flight (C) 2019-2021 Jyothiraditya Nellakra
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>. */

#include "math.h"

#include <math.h>

const SFv_t SFv_i = {1.0, 0.0, 0.0};
const SFv_t SFv_j = {0.0, 1.0, 0.0};
const SFv_t SFv_k = {0.0, 0.0, 0.0};

double SFv_len(SFv_t vec) {
	return pow(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z, 0.5);
}

SFv_t SFv_norm(SFv_t vec) {
	return SFv_scale(vec, 1 / SFv_len(vec));
}

SFv_t SFv_scale(SFv_t vec, double factor) {
	vec.x *= factor;
	vec.y *= factor;
	vec.z *= factor;

	return vec;
}

SFv_t SFv_add(SFv_t a, SFv_t b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;

	return a;
}

double SFv_dot(SFv_t a, SFv_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

SFv_t SFv_cross(SFv_t a, SFv_t b) {
	SFv_t vec;

	vec.x = (a.y * b.z) - (b.y * a.z);
	vec.y = (b.x * a.z) - (a.x * b.z);
	vec.z = (a.x * b.y) - (b.x * a.y);

	return vec;
}