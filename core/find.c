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
#include <core/find.h>

/* External Resources */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Definitions */
char find_char(char *filename, char *identifier) {
	char buffer[4096] = {0};
	FILE *file = fopen(filename, "r");
	char character = 0;
	int ret = 0;

	if(file) {
		while(fscanf(file, "%s", buffer) != EOF) {
			if(!strcmp(identifier, buffer)) {
				ret = fscanf(file, " %c", &character);
				break;
			}

			else {
				ret = fscanf(file, "%s", buffer);
				if(ret != 1) break;
			}
		}

		fclose(file);
	}

	return character;
}

size_t find_size(char *filename, char *identifier) {
	char buffer[4096] = {0};
	FILE *file = fopen(filename, "r");
	size_t size = 0;
	int ret = 0;

	if(file) {
		while(fscanf(file, "%s", buffer) != EOF) {
			if(!strcmp(identifier, buffer)) {
				ret = fscanf(file, "%zu", &size);
				break;
			}

			else {
				ret = fscanf(file, "%s", buffer);
				if(ret != 1) break;
			}
		}

		fclose(file);
	}

	return size;
}

double find_value(char *filename, char *identifier) {
	char buffer[4096] = {0};
	FILE *file = fopen(filename, "r");
	double value = 0.0;
	int ret = 0;

	if(file) {
		while(fscanf(file, "%s", buffer) != EOF) {
			if(!strcmp(identifier, buffer)) {
				ret = fscanf(file, "%lf", &value);
				break;
			}

			else {
				ret = fscanf(file, "%s", buffer);
				if(ret != 1) break;
			}
		}

		fclose(file);
	}

	return value;
}
