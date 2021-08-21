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
#include <graphics/backend.h>

/* External Resources */
#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <core/vectors.h>
#include <graphics/variables.h>

/* Function Declarations */
void _graphics_draw(intmax_t start_x, intmax_t start_y, intmax_t end_x, intmax_t end_y);
void __graphics_draw(size_t x, size_t y, char character);

/* Function Definitions */
void graphics_initialise() {
	if(screen) free(screen);
	screen = calloc((screen_width + 1) * screen_height, sizeof(char));

	if((screen_width != 0) && (screen_height != 0)) {
		for(size_t y = 0; y < (screen_height - 1); ++y) {
			for(size_t x = 0; x < screen_width; ++x) screen[((screen_width + 1) * y) + x] = ' ';
			screen[((screen_width + 1) * y) + screen_width] = '\n';
		}

		for(size_t i = 0; i < screen_width; ++i) screen[((screen_width + 1) * (screen_height - 1)) + i] = ' ';
		screen[((screen_width + 1) * screen_height) - 1] = 0;
	}

	return;
}

void graphics_clean() {
	if(screen) for(size_t x = 0; x < screen_width; ++x) for(size_t y = 0; y < screen_height; ++y) screen[((screen_width + 1) * y) + x] = ' ';
	return;
}

void graphics_draw(vector_t start, vector_t end) {
	intmax_t integer_start_x, integer_start_y;
	intmax_t integer_end_x, integer_end_y;

	start.x /= display_scale.x; end.x /= display_scale.x;
	start.y /= display_scale.y; end.y /= display_scale.y;
	start.z /= display_scale.z; end.z /= display_scale.z;

	if((start.x >= 1.0) && (end.x >= 1.0)) {
		start.y /= -start.x;
		start.z /= start.x;
		end.y /= -end.x;
		end.z /= end.x;

		integer_start_x = (intmax_t) start.z;
		integer_start_y = (intmax_t) start.y;
		integer_end_x = (intmax_t) end.z;
		integer_end_y = (intmax_t) end.y;

		_graphics_draw(integer_start_x, integer_start_y, integer_end_x, integer_end_y);
		return;
	}
}

void _graphics_draw(intmax_t start_x, intmax_t start_y, intmax_t end_x, intmax_t end_y) {
	intmax_t x, y;
	size_t position_x, position_y;
	char character;

	intmax_t dx;
	intmax_t dy;
	intmax_t d;

	if(start_x > end_x) {
		if(start_y > end_y) {
			dx = start_x - end_x;
			dy = start_y - end_y;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = end_y;

				character = '_';

				for(x = end_x; x <= start_x; ++x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						++y;
						d -= 2 * dx;

						character = '\\';
					}
					else character = '_';

					d += 2 * dy;
				}
			}

			else if(dx < dy) {
				d = (2 * dx) - dy;
				x = start_x;

				character = '|';

				for(y = start_y; y >= end_y; --y) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						--x;
						d -= 2 * dy;

						character = '\\';
					}
					else character = '|';

					d += 2 * dx;
				}
			}

			else {
				y = end_y;
				character = '\\';

				for(x = end_x; x <= start_x; ++x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);
					++y;
				}
			}
		}

		else if(start_y < end_y) {
			dx = start_x - end_x;
			dy = end_y - start_y;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = start_y;

				character = '_';

				for(x = start_x; x >= end_x; --x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						++y;
						d -= 2 * dx;

						character = '/';
					}
					else character = '_';

					d += 2 * dy;
				}
			}

			else if(dx < dy) {
				d = (2 * dx) - dy;
				x = start_x;

				character = '|';

				for(y = start_y; y <= end_y; ++y) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						--x;
						d -= 2 * dy;

						character = '/';
					}
					else character = '|';

					d += 2 * dx;
				}
			}

			else {
				y = end_y;
				character = '/';

				for(x = end_x; x <= start_x; ++x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);
					--y;
				}
			}
		}

		else {
			y = start_y;
			character = '_';

			for(x = end_x; x <= start_x; ++x) {
				if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
				else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
				if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
				else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

				__graphics_draw(position_x, position_y, character);
			}
		}
	}

	else if(start_x < end_x) {
		if(start_y > end_y) {
			dx = end_x - start_x;
			dy = start_y - end_y;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = end_y;

				character = '_';

				for(x = end_x; x >= start_x; --x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						++y;
						d -= 2 * dx;

						character = '/';
					}
					else character = '_';

					d += 2 * dy;
				}
			}

			else if(dx < dy) {
				d = (2 * dx) - dy;
				x = end_x;

				character = '|';

				for(y = end_y; y <= start_y; ++y) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						--x;
						d -= 2 * dy;

						character = '/';
					}
					else character = '|';

					d += 2 * dx;
				}
			}

			else {
				y = start_y;
				character = '/';

				for(x = start_x; x <= end_x; ++x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);
					--y;
				}
			}
		}

		else if(start_y < end_y) {
			dx = end_x - start_x;
			dy = end_y - start_y;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = start_y;

				character = '_';

				for(x = start_x; x <= end_x; ++x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						++y;
						d -= 2 * dx;

						character = '\\';
					}
					else character = '_';

					d += 2 * dy;
				}
			}

			else if(dx < dy) {
				d = (2 * dx) - dy;
				x = end_x;

				character = '|';

				for(y = end_y; y >= start_y; --y) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					if(d > 0) {
						--x;
						d -= 2 * dy;

						character = '\\';
					}
					else character = '|';

					d += 2 * dx;
				}
			}

			else {
				y = start_y;
				character = '\\';

				for(x = start_x; x <= end_x; ++x) {
					if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
					else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
					if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
					else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

					__graphics_draw(position_x, position_y, character);

					++y;
				}
			}
		}

		else {
			y = start_y;
			character = '_';

			for(x = start_x; x <= end_x; ++x) {
				if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
				else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
				if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
				else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

				__graphics_draw(position_x, position_y, character);
			}
		}
	}

	else {
		if(start_y > end_y) {
			x = start_x;
			character = '|';

			for(y = end_y; y <= start_y; ++y) {
				if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
				else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
				if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
				else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

				__graphics_draw(position_x, position_y, character);
			}
		}

		else if(start_y < end_y) {
			x = start_x;
			character = '|';

			for(y = start_y; y <= end_y; ++y) {
				if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
				else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
				if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
				else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

				__graphics_draw(position_x, position_y, character);
			}
		}

		else {
			x = start_x;
			y = start_y;
			character = '+';

			if(x >= 0) position_x = (screen_width / 2) + ((size_t) imaxabs(x));
			else position_x = (screen_width / 2) - ((size_t) imaxabs(x));
			if(y >= 0) position_y = (screen_height / 2) + ((size_t) imaxabs(y));
			else position_y = (screen_height / 2) - ((size_t) imaxabs(y));

			__graphics_draw(position_x, position_y, character);
		}
	}

	return;
}

void __graphics_draw(size_t x, size_t y, char character) {
	if(screen) if((x < screen_width) && (y < screen_height))
		screen[((screen_width + 1) * y) + x] = character;
	return;
}

void graphics_render() {
	printf("\x1b[2J");
	if(screen) printf("%s", screen);
	return;
}
