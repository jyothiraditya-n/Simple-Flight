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

#ifndef CORE_INTERPOLATIONS_HEADER
#define CORE_INTERPOLATIONS_HEADER

/* Function Declarations */
double lint(double v1, double v2, double t);
double blint(double v1, double v2, double v3, double v4, double t1, double t2);
double tlint(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double t1, double t2, double t3);

#endif
