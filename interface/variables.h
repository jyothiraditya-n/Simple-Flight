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

#ifndef INTERFACE_VARIABLES_HEADER
#define INTERFACE_VARIABLES_HEADER

/* External Resources */
#include <pthread.h>
#include <stdbool.h>

/* Variable Declarations */
pthread_t graphics_thread;
pthread_t physics_thread;
pthread_t world_thread;

bool exit_flag;
bool paused_flag;

double aileron_input;
double aileron_offset;
double elevator_input;
double elevator_offset;
double rudder_input;
double rudder_offset;
double throttle_input;

char *interface_file;

char aileron_input_left_char, aileron_input_right_char;
char aileron_offset_left_char, aileron_offset_right_char;
char elevator_input_back_char, elevator_input_forwards_char;
char elevator_offset_back_char, elevator_offset_forwards_char;
char rudder_input_left_char, rudder_input_right_char;
char rudder_offset_left_char, rudder_offset_right_char;
char throttle_input_up_char, throttle_input_down_char;

char pause_char, exit_char;
char input_char;

double input_half_life, input_delta;

#endif
