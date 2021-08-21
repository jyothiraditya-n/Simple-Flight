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
#include <world/main.h>

/* External Resources */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/find.h>
#include <core/interpolations.h>
#include <core/vectors.h>
#include <interface/variables.h>
#include <physics/variables.h>
#include <world/variables.h>

/* Function Definitions */
void *world_main() {
	char buffer[4096] = {0};

	world_datapoint_count = find_size(world_file, "datapoint_count");
	world_datapoint_size = find_value(world_file, "datapoint_size");

	world_gravity = find_value(world_file, "gravity");
	air_density = find_value(world_file, "air_density");

	world_datapoints = calloc(world_datapoint_count, sizeof(double *));
	for(size_t x = 0; x < world_datapoint_count; ++x) {
		world_datapoints[x] = calloc(world_datapoint_count, sizeof(double));

		for(size_t z = 0; z < world_datapoint_count; ++z) {
			sprintf(buffer, "%zu.%zu", x, z);
			world_datapoints[x][z] = find_value(world_file, buffer);
			buffer[0] = 0;
		}
	}

	return 0;
}

double world_height(double x, double z) {
	size_t integer_x, integer_z;

	if((world_datapoint_count != 0) && (world_datapoint_size != 0.0)) {
		x /= world_datapoint_size;
		z /= world_datapoint_size;

		while(x < 0.0) x += (double) world_datapoint_count;
		while(x > (double) world_datapoint_count) x -= (double) world_datapoint_count;
		while(z < 0.0) z += (double) world_datapoint_count;
		while(z > (double) world_datapoint_count) z -= (double) world_datapoint_count;

		integer_x = (size_t) x;
		x -= (double) integer_x;
		integer_z = (size_t) z;
		z -= (double) integer_z;

		if(x < 0.5) {
			if(z < 0.5) {
				if(integer_x == 0) {
					if(integer_z == 0) return blint(world_datapoints[world_datapoint_count - 1][world_datapoint_count - 1],
						world_datapoints[0][world_datapoint_count - 1], world_datapoints[world_datapoint_count - 1][0],
						world_datapoints[0][0], x + 0.5, z + 0.5);

					else return blint(world_datapoints[world_datapoint_count - 1][integer_z - 1], world_datapoints[0][integer_z - 1],
						world_datapoints[world_datapoint_count - 1][integer_z], world_datapoints[0][integer_z], x + 0.5, z + 0.5);
				}

				else {
					if(integer_z == 0) return blint(world_datapoints[integer_x - 1][world_datapoint_count - 1],
						world_datapoints[integer_x][world_datapoint_count - 1],
						world_datapoints[integer_x - 1][0], world_datapoints[integer_x][0], x + 0.5, z + 0.5);

					else return blint(world_datapoints[integer_x - 1][integer_z - 1], world_datapoints[integer_x][integer_z - 1],
						world_datapoints[integer_x - 1][integer_z], world_datapoints[integer_x][integer_z], x + 0.5, z + 0.5);
				}
			}

			else if(z > 0.5) {
				if(integer_x == 0) {
					if(integer_z == world_datapoint_count - 1) return blint(world_datapoints[world_datapoint_count - 1][integer_z],
						world_datapoints[0][integer_z], world_datapoints[world_datapoint_count - 1][0], world_datapoints[0][0], x + 0.5, z);

					else return blint(world_datapoints[world_datapoint_count - 1][integer_z], world_datapoints[0][integer_z],
						world_datapoints[world_datapoint_count - 1][integer_z + 1], world_datapoints[0][integer_z + 1], x + 0.5, z);
				}

				else {
					if(integer_z == world_datapoint_count - 1) return blint(world_datapoints[integer_x - 1][integer_z],
						world_datapoints[integer_x][integer_z], world_datapoints[integer_x - 1][0], world_datapoints[integer_x][0], x + 0.5, z);

					else return blint(world_datapoints[integer_x - 1][integer_z], world_datapoints[integer_x][integer_z],
						world_datapoints[integer_x - 1][integer_z + 1], world_datapoints[integer_x][integer_z + 1], x + 0.5, z);
				}
			}

			else {
				if(integer_x == 0) return lint(world_datapoints[world_datapoint_count - 1][integer_z], world_datapoints[0][integer_z], x + 0.5);

				else return lint(world_datapoints[integer_x - 1][integer_z], world_datapoints[integer_x][integer_z], x + 0.5);
			}
		}

		else if(x > 0.5) {
			if(z < 0.5) {
				if(integer_x == world_datapoint_count - 1) {
					if(integer_z == 0) return blint(world_datapoints[integer_x][world_datapoint_count - 1],
						world_datapoints[0][world_datapoint_count - 1], world_datapoints[integer_x][0], world_datapoints[0][0], x, z + 0.5);

					else return blint(world_datapoints[integer_x][integer_z - 1], world_datapoints[0][integer_z - 1],
						world_datapoints[integer_x][integer_z], world_datapoints[0][integer_z], x, z + 0.5);
				}

				else {
					if(integer_z == 0) return blint(world_datapoints[integer_x][world_datapoint_count - 1],
						world_datapoints[integer_x + 1][world_datapoint_count - 1], world_datapoints[integer_x][0],
						world_datapoints[integer_x + 1][0], x, z + 0.5);

					else return blint(world_datapoints[integer_x][integer_z - 1], world_datapoints[integer_x + 1][integer_z - 1],
						world_datapoints[integer_x][integer_z], world_datapoints[integer_x + 1][integer_z], x, z + 0.5);
				}
			}

			else if(z > 0.5) {
				if(integer_x == world_datapoint_count - 1) {
					if(integer_z == world_datapoint_count - 1) return blint(world_datapoints[integer_x][integer_z],
						world_datapoints[0][integer_z], world_datapoints[integer_x][0], world_datapoints[0][0], x, z);

					else return blint(world_datapoints[integer_x][integer_z], world_datapoints[0][integer_z],
						world_datapoints[integer_x][integer_z + 1], world_datapoints[0][integer_z + 1], x, z);
				}

				else {
					if(integer_z == world_datapoint_count - 1) return blint(world_datapoints[integer_x][integer_z],
						world_datapoints[0][integer_z], world_datapoints[integer_x][0], world_datapoints[0][0], x, z);

					else return blint(world_datapoints[integer_x][integer_z], world_datapoints[0][integer_z],
						world_datapoints[integer_x][integer_z + 1], world_datapoints[0][integer_z + 1], x, z);
				}
			}

			else {
				if(integer_x == world_datapoint_count - 1) return lint(world_datapoints[integer_x][integer_z], world_datapoints[0][integer_z], x);

				else return lint(world_datapoints[integer_x][integer_z], world_datapoints[integer_x + 1][integer_z], x);
			}
		}

		else {
			if(z < 0.5) {
				if(integer_z == 0) return lint(world_datapoints[integer_x][world_datapoint_count - 1], world_datapoints[integer_x][0], z + 0.5);

				else return lint(world_datapoints[integer_x][integer_z - 1], world_datapoints[integer_x][integer_z], z + 0.5);
			}

			else if(z > 0.5) {
				if(integer_z == world_datapoint_count - 1) return lint(world_datapoints[integer_x][integer_z], world_datapoints[integer_x][0], z);

				else return lint(world_datapoints[integer_x][integer_z], world_datapoints[integer_x][integer_z + 1], z);
			}

			else return world_datapoints[integer_x][integer_z];
		}
	}

	else return 0;
}
