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
#include <graphics/main.h>

/* External Resources */
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <core/find.h>
#include <core/rays.h>
#include <core/orientations.h>
#include <core/vectors.h>
#include <graphics/backend.h>
#include <graphics/variables.h>
#include <interface/variables.h>
#include <physics/variables.h>
#include <world/main.h>

/* Function Definitions */
void *graphics_main() {
	char buffer[4096] = {0};

	double height, width;
	ray_t ray_sight_top_left, ray_sight_top_right, ray_sight_bottom_left, ray_sight_bottom_right;
	vector_t render_region_top_left, render_region_top_right, render_region_bottom_left, render_region_bottom_right;
	vector_t absolute_viewport_position;

	double minimum_x, maximum_x, minimum_z, maximum_z;
	vector_t start, end;
	orientation_t object_orientation;

	viewport_orientation.alpha = find_value(graphics_file, "orientation.alpha");
	viewport_orientation.beta = find_value(graphics_file, "orientation.beta");
	viewport_orientation.gamma = find_value(graphics_file, "orientation.gamma");
	viewport_position.x = find_value(graphics_file, "position.x");
	viewport_position.y = find_value(graphics_file, "position.y");
	viewport_position.z = find_value(graphics_file, "position.z");

	display_scale.x = find_value(graphics_file, "distance_to_display");
	display_scale.y = find_value(graphics_file, "height_of_display");
	display_scale.z = find_value(graphics_file, "width_of_display");
	render_density = find_value(graphics_file, "render_density");
	render_distance = find_value(graphics_file, "render_distance");

	plane_body_count = find_size(plane_file, "body_count");
	plane_body_point_counts = calloc(plane_body_count, sizeof(size_t));
	plane_body_point_positions = calloc(plane_body_count, sizeof(vector_t *));

	viewport_orientation.alpha += find_value(plane_file, "viewport_orientation.alpha");
	viewport_orientation.beta += find_value(plane_file, "viewport_orientation.beta");
	viewport_orientation.gamma += find_value(plane_file, "viewport_orientation.gamma");
	viewport_position.x += find_value(plane_file, "viewport_position.x");
	viewport_position.y += find_value(plane_file, "viewport_position.y");
	viewport_position.z += find_value(plane_file, "viewport_position.z");

	for(size_t i1 = 0; i1 < plane_body_count; ++i1) {
		sprintf(buffer, "%zu.point_count", i1);
		plane_body_point_counts[i1] = find_size(plane_file, buffer);
		buffer[0] = 0;

		plane_body_point_positions[i1] = calloc(plane_body_point_counts[i1], sizeof(vector_t));
		for(size_t i2 = 0; i2 < plane_body_point_counts[i1]; ++i2) {
			sprintf(buffer, "%zu.%zu.x", i1, i2);
			plane_body_point_positions[i1][i2].x = find_value(plane_file, buffer);
			buffer[0] = 0;

			sprintf(buffer, "%zu.%zu.y", i1, i2);
			plane_body_point_positions[i1][i2].y = find_value(plane_file, buffer);
			buffer[0] = 0;

			sprintf(buffer, "%zu.%zu.z", i1, i2);
			plane_body_point_positions[i1][i2].z = find_value(plane_file, buffer);
			buffer[0] = 0;
		}
	}

	while(!screen_height) {
		printf("Enter the screen height: ");
		scanf("%zu", &screen_height);
		printf("\n");
	}

	while(!screen_width) {
		printf("Enter the screen width: ");
		scanf("%zu", &screen_width);
		printf("\n");
	}

	while(display_scale.x == 0.0) {
		printf("Enter the distance to the display: ");
		scanf("%lf", &display_scale.x);
		printf("\n");
	}

	while(display_scale.y == 0.0) {
		printf("Enter the height of the display: ");
		scanf("%lf", &display_scale.y);
		printf("\n");
	}

	while(display_scale.z == 0.0) {
		printf("Enter the width of the display: ");
		scanf("%lf", &display_scale.z);
		printf("\n");
	}

	while(render_density == 0.0) {
		printf("Enter the render density: ");
		scanf("%lf", &render_density);
		printf("\n");
	}

	while(render_distance == 0.0) {
		printf("Enter the render distance: ");
		scanf("%lf", &render_distance);
		printf("\n");
	}

	height = (double) screen_height;
	width = (double) screen_width;

	display_scale.y /= height / 2.0;
	display_scale.z /= width / 2.0;

	graphics_initialise();
	graphics_ready = true;

	while(!exit_flag) if(!paused_flag) {
		graphics_clean();

		absolute_viewport_position = add_vectors(orient_vector(viewport_position, plane_orientation), plane_position);
		ray_sight_top_left.a = absolute_viewport_position;
		ray_sight_top_right.a = ray_sight_top_left.a; ray_sight_bottom_left.a = ray_sight_top_left.a; ray_sight_bottom_right.a = ray_sight_top_left.a;

		ray_sight_top_left.b.x = display_scale.x; ray_sight_top_right.b.x = display_scale.x;
		ray_sight_bottom_left.b.x = display_scale.x; ray_sight_bottom_right.b.x = display_scale.x;
		ray_sight_top_left.b.y = 0.5 * -height * display_scale.x; ray_sight_top_right.b.y = 0.5 * -height * display_scale.x;
		ray_sight_bottom_left.b.y = 0.5 * height * display_scale.x; ray_sight_bottom_right.b.y = 0.5 * height * display_scale.x;
		ray_sight_top_left.b.z = 0.5 * -width * display_scale.x; ray_sight_top_right.b.z = 0.5 * width * display_scale.x;
		ray_sight_bottom_left.b.z = 0.5 * -width * display_scale.x; ray_sight_bottom_right.b.z = 0.5 * width * display_scale.x;

		ray_sight_top_left.b = orient_vector(orient_vector(ray_sight_top_left.b, viewport_orientation), plane_orientation);
		ray_sight_top_right.b = orient_vector(orient_vector(ray_sight_top_right.b, viewport_orientation), plane_orientation);
		ray_sight_bottom_left.b = orient_vector(orient_vector(ray_sight_bottom_left.b, viewport_orientation), plane_orientation);
		ray_sight_bottom_right.b = orient_vector(orient_vector(ray_sight_bottom_right.b, viewport_orientation), plane_orientation);

		render_region_top_left = complete_ray_position_xz(ray_sight_top_left, 0.0);
		render_region_top_right = complete_ray_position_xz(ray_sight_top_right, 0.0);
		render_region_bottom_left = complete_ray_position_xz(ray_sight_bottom_left, 0.0);
		render_region_bottom_right = complete_ray_position_xz(ray_sight_bottom_right, 0.0);

		if(scalar_length(add_vectors(render_region_top_left, reverse_vector(absolute_viewport_position))) > render_distance *
			fabs(absolute_viewport_position.y)) render_region_top_left = get_ray_position(ray_sight_top_left, (render_distance *
			fabs(absolute_viewport_position.y)) / scalar_length(ray_sight_top_left.b)); render_region_top_left.y = 0.0;
		if(scalar_length(add_vectors(render_region_top_right, reverse_vector(absolute_viewport_position))) > render_distance *
			fabs(absolute_viewport_position.y)) render_region_top_right = get_ray_position(ray_sight_top_right, (render_distance *
			fabs(absolute_viewport_position.y)) / scalar_length(ray_sight_top_left.b)); render_region_top_right.y = 0.0;
		if(scalar_length(add_vectors(render_region_bottom_left, reverse_vector(absolute_viewport_position))) > render_distance *
			fabs(absolute_viewport_position.y)) render_region_bottom_left = get_ray_position(ray_sight_bottom_left, (render_distance *
			fabs(absolute_viewport_position.y)) / scalar_length(ray_sight_top_left.b)); render_region_bottom_left.y = 0.0;
		if(scalar_length(add_vectors(render_region_bottom_right, reverse_vector(absolute_viewport_position))) > render_distance *
			fabs(absolute_viewport_position.y)) render_region_bottom_right = get_ray_position(ray_sight_bottom_right, (render_distance *
			fabs(absolute_viewport_position.y)) / scalar_length(ray_sight_top_left.b)); render_region_bottom_right.y = 0.0;

		minimum_x = render_region_top_left.x;
		if(render_region_top_right.x < minimum_x) minimum_x = render_region_top_right.x;
		if(render_region_bottom_left.x < minimum_x) minimum_x = render_region_bottom_left.x;
		if(render_region_bottom_right.x < minimum_x) minimum_x = render_region_bottom_right.x;
		maximum_x = render_region_top_left.x;
		if(render_region_top_right.x > maximum_x) maximum_x = render_region_top_right.x;
		if(render_region_bottom_left.x > maximum_x) maximum_x = render_region_bottom_left.x;
		if(render_region_bottom_right.x > maximum_x) maximum_x = render_region_bottom_right.x;
		minimum_z = render_region_top_left.z;
		if(render_region_top_right.z < minimum_z) minimum_z = render_region_top_right.z;
		if(render_region_bottom_left.z < minimum_z) minimum_z = render_region_bottom_left.z;
		if(render_region_bottom_right.z < minimum_z) minimum_z = render_region_bottom_right.z;
		maximum_z = render_region_top_left.z;
		if(render_region_top_right.z > maximum_z) maximum_z = render_region_top_right.z;
		if(render_region_bottom_left.z > maximum_z) maximum_z = render_region_bottom_left.z;
		if(render_region_bottom_right.z > maximum_z) maximum_z = render_region_bottom_right.z;

		for(double x = minimum_x; x <= maximum_x; x += (render_density * fabs(absolute_viewport_position.y))) {
			for(double z = minimum_z; z <= maximum_z; z += (render_density * fabs(absolute_viewport_position.y))) {
				start.x = x; start.z = z; start.y = world_height(start.x, start.z);
				start = orient_vector(orient_vector(add_vectors(start, reverse_vector(absolute_viewport_position)),
					reverse_orientation(plane_orientation)), reverse_orientation(viewport_orientation));
				end.x = x + (render_density * fabs(absolute_viewport_position.y)); end.z = z; end.y = world_height(end.x, end.z);
				end = orient_vector(orient_vector(add_vectors(end, reverse_vector(absolute_viewport_position)),
					reverse_orientation(plane_orientation)), reverse_orientation(viewport_orientation));
				graphics_draw(start, end);
				end.x = x; end.z = z + (render_density * fabs(absolute_viewport_position.y)); end.y = world_height(end.x, end.z);
				end = orient_vector(orient_vector(add_vectors(end, reverse_vector(absolute_viewport_position)),
					reverse_orientation(plane_orientation)), reverse_orientation(viewport_orientation));
				graphics_draw(start, end);
			}
		}

		for(size_t i1 = 0; i1 < plane_body_count; ++i1) {
			object_orientation = add_orientations(plane_bodies[i1].orientation,
				add_orientations(scale_orientation(plane_bodies[i1].aileron_delta, aileron_input + aileron_offset),
				add_orientations(scale_orientation(plane_bodies[i1].elevator_delta, elevator_input + elevator_offset),
				scale_orientation(plane_bodies[i1].rudder_delta, rudder_input + rudder_offset))));

			if(plane_body_point_counts[i1]) end = orient_vector(add_vectors(orient_vector(plane_body_point_positions[i1][plane_body_point_counts[i1]
			 - 1], object_orientation), reverse_vector(viewport_position)), reverse_orientation(viewport_orientation));

			for(size_t i2 = 0; i2 < plane_body_point_counts[i1]; ++i2) {
				if(i2 % 2 == 0) start = orient_vector(add_vectors(orient_vector(plane_body_point_positions[i1][i2], object_orientation),
					reverse_vector(viewport_position)), reverse_orientation(viewport_orientation));
				else end = orient_vector(add_vectors(orient_vector(plane_body_point_positions[i1][i2], object_orientation),
					reverse_vector(viewport_position)), reverse_orientation(viewport_orientation));
				graphics_draw(start, end);
			}
		}

		graphics_render();
	}
}
