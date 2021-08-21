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
#include <interface/main.h>

/* External Resources */
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <core/find.h>
#include <core/orientations.h>
#include <core/vectors.h>
#include <graphics/main.h>
#include <graphics/variables.h>
#include <interface/variables.h>
#include <physics/main.h>
#include <physics/variables.h>
#include <world/main.h>
#include <world/variables.h>

/* Variable Definitions */
pthread_t interface_helper_thread = 0;

/* Function Definitions */
int main(int argc, char **argv) {
	bool headless_flag = false, help_flag = false;

	clock_t start, end;
	double time_difference;

	for(int i = 1; i < argc; ++i) {
		if(!strcmp(argv[i], "--headless")) headless_flag = true;
		else if(!strcmp(argv[i], "--help")) help_flag = true;

		else if(!strcmp(argv[i], "--height") && (i != argc - 1)) sscanf(argv[++i], "%zu", &screen_height);
		else if(!strcmp(argv[i], "--width") && (i != argc - 1)) sscanf(argv[++i], "%zu", &screen_width);

		else if(!strcmp(argv[i], "--graphics") && (i != argc - 1)) graphics_file = argv[++i];
		else if(!strcmp(argv[i], "--interface") && (i != argc - 1)) interface_file = argv[++i];
		else if(!strcmp(argv[i], "--plane") && (i != argc - 1)) plane_file = argv[++i];
		else if(!strcmp(argv[i], "--world") && (i != argc - 1)) world_file = argv[++i];
	}

	if(help_flag) {
		printf("Simple Flight Copyright (C) 2019 Jyothiraditya Nellakra (Der Linux König)\n\n");

		printf("  This program is free software: you can redistribute it and/or modify\n");
		printf("  it under the terms of the GNU General Public License as published by\n");
		printf("  the Free Software Foundation, either version 3 of the License, or\n");
		printf("  (at your option) any later version.\n\n");

		printf("  This program is distributed in the hope that it will be useful,\n");
		printf("  but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
		printf("  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n");
		printf("  GNU General Public License for more details.\n\n");

		printf("  You should have received a copy of the GNU General Public License\n");
		printf("  along with this program. If not, see <https://www.gnu.org/licenses/>.\n\n");

		printf("Usage: %s [OPTION]...\n\n", argv[0]);

		printf("--headless: Disable graphical functionality.\n");
		printf("--help: Display this help dialogue.\n");

		printf("--height HEIGHT: Set the interface display height to HEIGHT.\n");
		printf("--width WIDTH: Set the interface display width to WIDTH.\n\n");

		printf("--graphics GRAPHICS: Set the filename for the graphics to GRAPHICS.\n");
		printf("--interface INTERFACE: Set the filename for the interface to INTERFACE.\n");
		printf("--plane PLANE: Set the filename for the plane to PLANE.\n");
		printf("--world WORLD: Set the filename for the world to WORLD.\n\n");
	}

	else {
		while(!plane_file) {
			plane_file = (char *) calloc(4096, sizeof(char));

			printf("Enter the filename for the plane: ");
			scanf("%s", plane_file);
			printf("\n");
		}
		pthread_create(&physics_thread, NULL, physics_main, NULL);

		while(!world_file) {
			world_file = (char *) calloc(4096, sizeof(char));

			printf("Enter the filename for the world: ");
			scanf("%s", world_file);
			printf("\n");
		}
		pthread_create(&world_thread, NULL, world_main, NULL);

		if(headless_flag) {
			char buffer[4096] = {0};

			printf("Simple Flight Copyright (C) 2019 Jyothiraditya Nellakra (Der Linux König)\n\n");

			printf("  This program comes with ABSOLUTELY NO WARRANTY; for details type `about warranty'.\n");
			printf("  This is free software, and you are welcome to redistribute it\n");
			printf("  under certain conditions; type `about copying' for details.\n\n");

			while(true) {
				printf("> ");
				scanf("%s", buffer);
				printf("\n");

				if(!strcmp(buffer, "about")) {
					scanf("%s", buffer);

					if(!strcmp(buffer, "warranty")) {
						printf("Simple Flight Copyright (C) 2019 Jyothiraditya Nellakra (Der Linux König)\n\n");

						printf("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n");
						printf("APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n");
						printf("HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n");
						printf("OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n");
						printf("THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n");
						printf("PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n");
						printf("IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n");
						printf("ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\n");

					}

					else if(!strcmp(buffer, "copying")) {
						printf("Simple Flight Copyright (C) 2019 Jyothiraditya Nellakra (Der Linux König)\n\n");

						printf("You are not required to accept this License in order to receive or\n");
						printf("run a copy of the Program. Ancillary propagation of a covered work\n");
						printf("occurring solely as a consequence of using peer-to-peer transmission\n");
						printf("to receive a copy likewise does not require acceptance. However,\n");
						printf("nothing other than this License grants you permission to propagate or\n");
						printf("modify any covered work. These actions infringe copyright if you do\n");
						printf("not accept this License. Therefore, by modifying or propagating a\n");
						printf("covered work, you indicate your acceptance of this License to do so.\n\n");

					}
				}

				else if(!strcmp(buffer, "help")) {
					printf("Usage: > [COMMAND]\n\n");

					printf("[COMMANDS]\n");
					printf("about warranty: Display details about the warranty.\n");
					printf("about copying: Display detials about copying the code.\n");
					printf("help: Display this help dialogue.\n\n");

					printf("get [VARIABLE]: Display the value of [VARIABLE].\n");
					printf("set [VARIABLE] [VALUE]: Set the value of [VARIABLE] to [VALUE].\n\n");

					printf("exit: Stop the interactive shell.\n\n");

					printf("[VARIABLES]\n");
					printf("paused: A boolean for if the program is paused or not (true/false.)\n\n");

					printf("orientation.alpha: The alpha component of the orientation of the plane.\n");
					printf("orientation.beta: The beta component of the orientation of the plane.\n");
					printf("orientation.gamma: The gamma component of the orientation of the plane.\n\n");

					printf("angularvelocity.alpha: The alpha orientation of the angular velocity of the plane.\n");
					printf("angularvelocity.beta: The beta orientation of the angular velocity of the plane.\n");
					printf("angularvelocity.gamma: The gamma orientation of the angular velocity of the plane.\n\n");

					printf("position.x: The x component of the position vector of the plane.\n");
					printf("position.y: The y component of the position vector of the plane.\n");
					printf("position.z: The z component of the position vector of the plane.\n\n");

					printf("velocity.x: The x component of the velocity vector of the plane.\n");
					printf("velocity.y: The y component of the velocity vector of the plane.\n");
					printf("velocity.z: The z component of the velocity vector of the plane.\n\n");

					printf("aileron_input: The state of the aileron (-1 = max left, 1 = max right.)\n");
					printf("elevator_input: The state of the elevator (-1 = max up, 1 = max down.)\n");
					printf("rudder_input: The state of the rudder (-1 = max left, 1 = max right.)\n");
					printf("throttle_input: The state of the throttle (0 = min, 1 = max.)\n\n");

				}

				else if(!strcmp(buffer, "get")) {
					scanf("%s", buffer);
					if(!strcmp(buffer, "paused")) printf("%s\n\n", paused_flag ? "true" : "false");

					else if(!strcmp(buffer, "orientation.alpha")) printf("%lf\n\n", plane_orientation.alpha);
					else if(!strcmp(buffer, "orientation.beta")) printf("%lf\n\n", plane_orientation.beta);
					else if(!strcmp(buffer, "orientation.gamma")) printf("%lf\n\n", plane_orientation.gamma);

					else if(!strcmp(buffer, "angular_velocity.alpha")) printf("%lf\n\n", plane_angular_velocity.alpha);
					else if(!strcmp(buffer, "angular_velocity.beta")) printf("%lf\n\n", plane_angular_velocity.beta);
					else if(!strcmp(buffer, "angular_velocity.gamma")) printf("%lf\n\n", plane_angular_velocity.gamma);

					else if(!strcmp(buffer, "position.x")) printf("%lf\n\n", plane_position.x);
					else if(!strcmp(buffer, "position.y")) printf("%lf\n\n", plane_position.y);
					else if(!strcmp(buffer, "position.z")) printf("%lf\n\n", plane_position.z);

					else if(!strcmp(buffer, "velocity.x")) printf("%lf\n\n", plane_velocity.x);
					else if(!strcmp(buffer, "velocity.y")) printf("%lf\n\n", plane_velocity.y);
					else if(!strcmp(buffer, "velocity.z")) printf("%lf\n\n", plane_velocity.z);

					else if(!strcmp(buffer, "aileron_input")) printf("%lf\n\n", aileron_input);
					else if(!strcmp(buffer, "elevator_input")) printf("%lf\n\n", elevator_input);
					else if(!strcmp(buffer, "rudder_input")) printf("%lf\n\n", rudder_input);
					else if(!strcmp(buffer, "throttle_input")) printf("%lf\n\n", throttle_input);
				}

				else if(!strcmp(buffer, "set")) {
					scanf("%s", buffer);

					if(!strcmp(buffer, "paused")) {
						scanf("%s", buffer);
						if(!strcmp(buffer, "true")) paused_flag = true;
						else if(!strcmp(buffer, "false")) paused_flag = false;
					}

					else if(!strcmp(buffer, "orientation.alpha")) scanf("%lf", &plane_orientation.alpha);
					else if(!strcmp(buffer, "orientation.beta")) scanf("%lf", &plane_orientation.beta);
					else if(!strcmp(buffer, "orientation.gamma")) scanf("%lf", &plane_orientation.gamma);

					else if(!strcmp(buffer, "angular_velocity.alpha")) scanf("%lf", &plane_angular_velocity.alpha);
					else if(!strcmp(buffer, "angular_velocity.beta")) scanf("%lf", &plane_angular_velocity.beta);
					else if(!strcmp(buffer, "angular_velocity.gamma")) scanf("%lf", &plane_angular_velocity.gamma);

					else if(!strcmp(buffer, "velocity.x")) scanf("%lf", &plane_velocity.x);
					else if(!strcmp(buffer, "velocity.y")) scanf("%lf", &plane_velocity.y);
					else if(!strcmp(buffer, "velocity.z")) scanf("%lf", &plane_velocity.z);

					else if(!strcmp(buffer, "aileron_input")) scanf("%lf", &aileron_input);
					else if(!strcmp(buffer, "elevator_input")) scanf("%lf", &elevator_input);
					else if(!strcmp(buffer, "rudder_input")) scanf("%lf", &rudder_input);
					else if(!strcmp(buffer, "throttle_input")) scanf("%lf", &throttle_input);
				}

				else if(!strcmp(buffer, "exit")) {
					exit_flag = true;
					break;
				}
			}
		}

		else {
			while(!interface_file) {
				interface_file = (char *) calloc(4096, sizeof(char));

				printf("Enter the filename for the interface: ");
				scanf("%s", interface_file);
				printf("\n");
			}

			aileron_input_left_char = find_char(interface_file, "aileron_input_left_char");
			aileron_input_right_char = find_char(interface_file, "aileron_input_right_char");
			aileron_offset_left_char = find_char(interface_file, "aileron_offset_left_char");
			aileron_offset_right_char = find_char(interface_file, "aileron_offset_right_char");
			elevator_input_back_char = find_char(interface_file, "elevator_input_back_char");
			elevator_input_forwards_char = find_char(interface_file, "elevator_input_forwards_char");
			elevator_offset_back_char = find_char(interface_file, "elevator_offset_back_char");
			elevator_offset_forwards_char = find_char(interface_file, "elevator_offset_forwards_char");
			rudder_input_left_char = find_char(interface_file, "rudder_input_left_char");
			rudder_input_right_char = find_char(interface_file, "rudder_input_right_char");
			rudder_offset_left_char = find_char(interface_file, "rudder_offset_left_char");
			rudder_offset_right_char = find_char(interface_file, "rudder_offset_right_char");
			throttle_input_up_char = find_char(interface_file, "throttle_input_up_char");
			throttle_input_down_char = find_char(interface_file, "throttle_input_down_char");

			pause_char = find_char(interface_file, "pause_char");
			exit_char = find_char(interface_file, "exit_char");

			while(!aileron_input_left_char) {
				printf("Enter the character for moving the aileron input left: ");
				scanf(" %c", &aileron_input_left_char);
				printf("\n");
			}

			while(!aileron_input_right_char) {
				printf("Enter the character for moving the aileron input right: ");
				scanf(" %c", &aileron_input_right_char);
				printf("\n");
			}

			while(!aileron_offset_left_char) {
				printf("Enter the character for moving the aileron offset left: ");
				scanf(" %c", &aileron_offset_left_char);
				printf("\n");
			}

			while(!aileron_offset_right_char) {
				printf("Enter the character for moving the aileron offset right: ");
				scanf(" %c", &aileron_offset_right_char);
				printf("\n");
			}

			while(!elevator_input_back_char) {
				printf("Enter the character for moving the elevator input back: ");
				scanf(" %c", &elevator_input_back_char);
				printf("\n");
			}

			while(!elevator_input_forwards_char) {
				printf("Enter the character for moving the elevator input forwards: ");
				scanf(" %c", &elevator_input_forwards_char);
				printf("\n");
			}

			while(!elevator_offset_back_char) {
				printf("Enter the character for moving the elevator offset back: ");
				scanf(" %c", &elevator_offset_back_char);
				printf("\n");
			}

			while(!elevator_offset_forwards_char) {
				printf("Enter the character for moving the elevator offset forwards: ");
				scanf(" %c", &elevator_offset_forwards_char);
				printf("\n");
			}

			while(!rudder_input_left_char) {
				printf("Enter the character for moving the rudder input left: ");
				scanf(" %c", &rudder_input_left_char);
				printf("\n");
			}

			while(!rudder_input_right_char) {
				printf("Enter the character for moving the rudder input right: ");
				scanf(" %c", &rudder_input_right_char);
				printf("\n");
			}

			while(!rudder_offset_left_char) {
				printf("Enter the character for moving the rudder offset left: ");
				scanf(" %c", &rudder_offset_left_char);
				printf("\n");
			}

			while(!rudder_offset_right_char) {
				printf("Enter the character for moving the rudder offset right: ");
				scanf(" %c", &rudder_offset_right_char);
				printf("\n");
			}

			while(!throttle_input_up_char) {
				printf("Enter the character for moving the throttle input up: ");
				scanf(" %c", &throttle_input_up_char);
				printf("\n");
			}

			while(!throttle_input_down_char) {
				printf("Enter the character for moving the throttle input down: ");
				scanf(" %c", &throttle_input_down_char);
				printf("\n");
			}

			while(!pause_char) {
				printf("Enter the character for toggling the paused state of the program: ");
				scanf(" %c", &pause_char);
				printf("\n");
			}

			while(!exit_char) {
				printf("Enter the character for exiting the program: ");
				scanf(" %c", &exit_char);
				printf("\n");
			}

			while(input_half_life == 0) {
				printf("Enter the half-life period for the input: ");
				scanf("%lf", &input_half_life);
				printf("\n");
			}

			while(input_delta == 0) {
				printf("Enter the delta for the input: ");
				scanf("%lf", &input_delta);
				printf("\n");
			}

			while(!graphics_file) {
				graphics_file = (char *) calloc(4096, sizeof(char));

				printf("Enter the filename for the graphics: ");
				scanf("%s", graphics_file);
				printf("\n");
			}
			pthread_create(&graphics_thread, NULL, graphics_main, NULL);

			while(!graphics_ready);
			system("/bin/stty raw");
			pthread_create(&interface_helper_thread, NULL, interface_helper, NULL);

			while(!exit_flag) {
				start = clock();

				if(input_char == aileron_input_left_char) aileron_input -= input_delta;
				else if(input_char == aileron_input_right_char) aileron_input += input_delta;
				else if(input_char == aileron_offset_left_char) aileron_offset -= input_delta;
				else if(input_char == aileron_offset_right_char) aileron_offset += input_delta;
				else if(input_char == elevator_input_back_char) elevator_input -= input_delta;
				else if(input_char == elevator_input_back_char) elevator_input += input_delta;
				else if(input_char == elevator_offset_forwards_char) elevator_offset -= input_delta;
				else if(input_char == elevator_offset_forwards_char) elevator_offset += input_delta;
				else if(input_char == rudder_input_left_char) rudder_input -= input_delta;
				else if(input_char == rudder_input_right_char) rudder_input += input_delta;
				else if(input_char == rudder_offset_left_char) rudder_offset -= input_delta;
				else if(input_char == rudder_offset_right_char) rudder_offset += input_delta;
				else if(input_char == throttle_input_up_char) throttle_input -= input_delta;
				else if(input_char == throttle_input_down_char) throttle_input += input_delta;

				else if(input_char == pause_char) paused_flag = paused_flag ? false : true;
				else if(input_char == exit_char) exit_flag = true;

				end = clock();
				time_difference = (((double) end) - ((double) start)) / ((double) CLOCKS_PER_SEC);

				if(!paused_flag) {
					aileron_input *= pow(0.5, time_difference / input_half_life);
					elevator_input *= pow(0.5, time_difference / input_half_life);
					rudder_input *= pow(0.5, time_difference / input_half_life);
				}
				input_char = 0;
			}

			pthread_join(interface_helper_thread, NULL);
			pthread_join(graphics_thread, NULL);
			system("/bin/stty cooked");
		}

		pthread_join(physics_thread, NULL);
		pthread_join(world_thread, NULL);
		return 0;
	}
}

void *interface_helper() {
	while(!exit_flag) if(!input_char) input_char = getchar();
}
