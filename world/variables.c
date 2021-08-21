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
#include <world/variables.h>

/* External Resources */
#include <stddef.h>

#include <core/vectors.h>

/* Variable Definitions */
char *world_file = 0;
double **world_datapoints = 0;
size_t world_datapoint_count = 0;
double world_datapoint_size = 0.0;

double world_gravity = 0.0;
double air_density = 0.0;
