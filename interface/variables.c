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
#include <interface/variables.h>

/* External Resources */
#include <pthread.h>
#include <stdbool.h>

/* Variable Definitions */
pthread_t graphics_thread = 0;
pthread_t physics_thread = 0;
pthread_t world_thread = 0;

bool exit_flag = false;
bool paused_flag = false;

double aileron_input = 0.0;
double aileron_offset = 0.0;
double elevator_input = 0.0;
double elevator_offset = 0.0;
double rudder_input = 0.0;
double rudder_offset = 0.0;
double throttle_input = 0.0;

char *interface_file = 0;

char aileron_input_left_char = 0;
char aileron_input_right_char = 0;
char aileron_offset_left_char = 0;
char aileron_offset_right_char = 0;
char elevator_input_back_char = 0;
char elevator_input_forwards_char = 0;
char elevator_offset_back_char = 0;
char elevator_offset_forwards_char = 0;
char rudder_input_left_char = 0;
char rudder_input_right_char = 0;
char rudder_offset_left_char = 0;
char rudder_offset_right_char = 0;
char throttle_input_up_char = 0;
char throttle_input_down_char = 0;

char pause_char = 0;
char exit_char = 0;
char input_char = 0;

double input_half_life = 0.0;
double input_delta = 0.0;
