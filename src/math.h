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

#ifndef SF_MATH_H
#define SF_MATH_H

typedef struct _SFv_s {
	double x, y, z;

} SFv_t;

typedef struct _SFo_t {
	double alpha, beta, gamma;
	
} SFo_t;

extern const SFv_t SFv_i, SFv_j, SFv_k;

extern double SFv_len(SFv_t vec);
extern SFv_t SFv_norm(SFv_t vec);

extern SFv_t SFv_scale(SFv_t vec, double factor);
extern SFv_t SFv_add(SFv_t a, SFv_t b);

extern double SFv_dot(SFv_t a, SFv_t b);
extern SFv_t SFv_cross(SFv_t a, SFv_t b);

#endif