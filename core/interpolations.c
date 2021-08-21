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
#include <core/interpolations.h>

/* Function Definitions */
double lint(double v1, double v2, double t) {
	return v1 + (t * (v2 - v1));
}

double blint(double v1, double v2, double v3, double v4, double t1, double t2) {
	return lint(v1, v2, t1) + (t2 * (lint(v3, v4, t1) - lint(v1, v2, t1)));
}

double tlint(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double t1, double t2, double t3) {
	return blint(v1, v1, v3, v4, t1, t2) + (t3 * (blint(v5, v6, v7, v8, t1, t2) - blint(v1, v1, v3, v4, t1, t2)));
}
