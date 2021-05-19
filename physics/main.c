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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <core/constants.h>
#include <core/find.h>
#include <core/orientations.h>
#include <core/vectors.h>
#include <interface/variables.h>
#include <physics/bodies.h>
#include <physics/main.h>
#include <physics/variables.h>
#include <world/variables.h>

/* Function Definitions */
void *physics_main() {
	char buffer[4096] = {0};
	clock_t start, end;
	double time_difference;

	double mass = 0.0;
	vector_t moment_of_intertia = {0.0, 0.0, 0.0};

	orientation_t plane_angular_acceleration;
	vector_t plane_acceleration;

	orientation_t object_orientation;
	vector_t force, torque, velocity;

	plane_body_count = find_size(plane_file, "body_count");
	plane_bodies = (body_t *) calloc(plane_body_count, sizeof(body_t));

	plane_orientation.alpha = find_value(plane_file, "orientation.alpha");
	plane_orientation.beta = find_value(plane_file, "orientation.beta");
	plane_orientation.gamma = find_value(plane_file, "orientation.gamma");

	plane_position.x = find_value(plane_file, "position.x");
	plane_position.y = find_value(plane_file, "position.y");
	plane_position.z = find_value(plane_file, "position.z");

	plane_angular_velocity.alpha = find_value(plane_file, "angular_velocity.alpha");
	plane_angular_velocity.beta = find_value(plane_file, "angular_velocity.beta");
	plane_angular_velocity.gamma = find_value(plane_file, "angular_velocity.gamma");

	plane_velocity.x = find_value(plane_file, "velocity.x");
	plane_velocity.y = find_value(plane_file, "velocity.y");
	plane_velocity.z = find_value(plane_file, "velocity.z");

	for(size_t i = 0; i < plane_body_count; ++i) {
		sprintf(buffer, "%zu.position.x", i);
		plane_bodies[i].position.x = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.position.y", i);
		plane_bodies[i].position.y = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.position.z", i);
		plane_bodies[i].position.z = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.orientation.alpha", i);
		plane_bodies[i].orientation.alpha = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.orientation.beta", i);
		plane_bodies[i].orientation.beta = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.orientation.gamma", i);
		plane_bodies[i].orientation.gamma = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.aileron_delta.alpha", i);
		plane_bodies[i].aileron_delta.alpha = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.aileron_delta.beta", i);
		plane_bodies[i].aileron_delta.beta = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.aileron_delta.gamma", i);
		plane_bodies[i].aileron_delta.gamma = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.elevator_delta.alpha", i);
		plane_bodies[i].elevator_delta.alpha = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.elevator_delta.beta", i);
		plane_bodies[i].elevator_delta.beta = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.elevator_delta.gamma", i);
		plane_bodies[i].elevator_delta.gamma = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.rudder_delta.alpha", i);
		plane_bodies[i].rudder_delta.alpha = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.rudder_delta.beta", i);
		plane_bodies[i].rudder_delta.beta = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.rudder_delta.gamma", i);
		plane_bodies[i].rudder_delta.gamma = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.mass", i);
		plane_bodies[i].mass = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.drag.x", i);
		plane_bodies[i].drag.x = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.drag.y", i);
		plane_bodies[i].drag.y = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.drag.z", i);
		plane_bodies[i].drag.z = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.lift.x", i);
		plane_bodies[i].lift.x = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.lift.y", i);
		plane_bodies[i].lift.y = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.lift.z", i);
		plane_bodies[i].lift.z = find_value(plane_file, buffer);
		buffer[0] = 0;

		sprintf(buffer, "%zu.thrust.x", i);
		plane_bodies[i].thrust.x = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.thrust.y", i);
		plane_bodies[i].thrust.y = find_value(plane_file, buffer);
		buffer[0] = 0;
		sprintf(buffer, "%zu.thrust.z", i);
		plane_bodies[i].thrust.z = find_value(plane_file, buffer);
		buffer[0] = 0;

		mass += plane_bodies[i].mass;
		moment_of_intertia.x += plane_bodies[i].mass * (pow(plane_bodies[i].position.y, 2.0) + pow(plane_bodies[i].position.z, 2.0));
		moment_of_intertia.y += plane_bodies[i].mass * (pow(plane_bodies[i].position.x, 2.0) + pow(plane_bodies[i].position.z, 2.0));
		moment_of_intertia.z += plane_bodies[i].mass * (pow(plane_bodies[i].position.x, 2.0) + pow(plane_bodies[i].position.y, 2.0));
	}

	if((mass != 0.0) && (moment_of_intertia.x != 0.0) && (moment_of_intertia.y != 0.0) && (moment_of_intertia.z != 0.0)) {
		while(!exit_flag) if(!paused_flag) {
			start = clock();

			plane_acceleration.x = 0.0; plane_acceleration.y = -world_gravity; plane_acceleration.z = 0.0;
			plane_angular_acceleration.alpha = 0.0; plane_angular_acceleration.beta = 0.0; plane_angular_acceleration.gamma = 0.0;

			for(size_t i = 0; i < plane_body_count; ++i) {
				object_orientation = add_orientations(plane_bodies[i].orientation,
					add_orientations(scale_orientation(plane_bodies[i].aileron_delta, aileron_input + aileron_offset),
					add_orientations(scale_orientation(plane_bodies[i].elevator_delta, elevator_input + elevator_offset),
					scale_orientation(plane_bodies[i].rudder_delta, rudder_input + rudder_offset))));

				velocity = orient_vector(orient_vector(plane_velocity, reverse_orientation(plane_orientation)),
					reverse_orientation(object_orientation));

				force = scale_vector(plane_bodies[i].thrust, throttle_input);

				force.y += 0.5 * plane_bodies[i].lift.x * air_density * pow(velocity.x, 2.0);
				force.y += 0.5 * plane_bodies[i].lift.y * air_density * pow(velocity.y, 2.0);
				force.y += 0.5 * plane_bodies[i].lift.z * air_density * pow(velocity.z, 2.0);

				if(velocity.x < 0.0) force.x += 0.5 * plane_bodies[i].drag.x * air_density * pow(velocity.x, 2.0);
				else force.x -= 0.5 * plane_bodies[i].drag.x * air_density * pow(velocity.x, 2.0);

				if(velocity.y < 0.0) force.y += 0.5 * plane_bodies[i].drag.y * air_density * pow(velocity.y, 2.0);
				else force.y -= 0.5 * plane_bodies[i].drag.y * air_density * pow(velocity.y, 2.0);

				if(velocity.z < 0.0) force.z += 0.5 * plane_bodies[i].drag.z * air_density * pow(velocity.z, 2.0);
				else force.z -= 0.5 * plane_bodies[i].drag.z * air_density * pow(velocity.z, 2.0);

				force = orient_vector(force, object_orientation);
				torque = vector_product(plane_bodies[i].position, force);
				force = orient_vector(force, plane_orientation);

				plane_angular_acceleration.alpha += torque.x / moment_of_intertia.x;
				plane_angular_acceleration.beta += torque.y / moment_of_intertia.y;
				plane_angular_acceleration.gamma += torque.z / moment_of_intertia.z;

				plane_acceleration.x += force.x / mass;
				plane_acceleration.y += force.y / mass;
				plane_acceleration.z += force.z / mass;
			}

			end = clock();
			time_difference = (((double) end) - ((double) start)) / ((double) CLOCKS_PER_SEC);

			plane_velocity.x += plane_acceleration.x * time_difference;
			plane_velocity.y += plane_acceleration.y * time_difference;
			plane_velocity.z += plane_acceleration.z * time_difference;

			plane_angular_velocity.alpha += plane_angular_acceleration.alpha * time_difference;
			plane_angular_velocity.beta += plane_angular_acceleration.beta * time_difference;
			plane_angular_velocity.gamma += plane_angular_acceleration.gamma * time_difference;

			plane_position.x += plane_velocity.x * time_difference;
			plane_position.y += plane_velocity.y * time_difference;
			plane_position.z += plane_velocity.z * time_difference;

			plane_orientation.alpha += plane_angular_velocity.alpha * time_difference;
			plane_orientation.beta += plane_angular_velocity.beta * time_difference;
			plane_orientation.gamma += plane_angular_velocity.gamma * time_difference;
		}
	}
	return 0;
}
