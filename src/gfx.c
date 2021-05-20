/* Simple Flight (C) 2019-2021 Jyothiraditya Nellakra
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>. */

#include "gfx.h"

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "main.h"
#include "math.h"

size_t SFg_height = 24;
size_t SFg_width = 80;

double SFg_char_width = 1.0;
double SFg_char_height = 1.0;
double SFg_fov_scale = 1.0;


static void draw(intmax_t x1, intmax_t y1, intmax_t x2, intmax_t y2);
static void _draw(size_t x, size_t y, char character);

static char *screen = 0;

static void draw(intmax_t x1, intmax_t y1, intmax_t x2, intmax_t y2) {
	intmax_t x, y;
	size_t x_pos, y_pos;
	intmax_t dx, dy, d;
	char character;

	if(x1 > x2) {
		if(y1 > y2) {
			dx = x1 - x2;
			dy = y1 - y2;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = y2;

				character = '_';

				for(x = x2; x <= x1; ++x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				x = x1;

				character = '|';

				for(y = y1; y >= y2; --y) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				y = y2;
				character = '\\';

				for(x = x2; x <= x1; ++x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);
					++y;
				}
			}
		}

		else if(y1 < y2) {
			dx = x1 - x2;
			dy = y2 - y1;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = y1;

				character = '_';

				for(x = x1; x >= x2; --x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				x = x1;

				character = '|';

				for(y = y1; y <= y2; ++y) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				y = y2;
				character = '/';

				for(x = x2; x <= x1; ++x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);
					--y;
				}
			}
		}

		else {
			y = y1;
			character = '_';

			for(x = x2; x <= x1; ++x) {
				if(x >= 0) x_pos = (SFg_width / 2)
					+ ((size_t) imaxabs(x));

				else x_pos = (SFg_width / 2)
					- ((size_t) imaxabs(x));

				if(y >= 0) y_pos = (SFg_height / 2)
					+ ((size_t) imaxabs(y));

				else y_pos = (SFg_height / 2)
					- ((size_t) imaxabs(y));

				_draw(x_pos, y_pos, character);
			}
		}
	}

	else if(x1 < x2) {
		if(y1 > y2) {
			dx = x2 - x1;
			dy = y1 - y2;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = y2;

				character = '_';

				for(x = x2; x >= x1; --x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				x = x2;

				character = '|';

				for(y = y2; y <= y1; ++y) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				y = y1;
				character = '/';

				for(x = x1; x <= x2; ++x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);
					--y;
				}
			}
		}

		else if(y1 < y2) {
			dx = x2 - x1;
			dy = y2 - y1;

			if(dx > dy) {
				d = (2 * dy) - dx;
				y = y1;

				character = '_';

				for(x = x1; x <= x2; ++x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				x = x2;

				character = '|';

				for(y = y2; y >= y1; --y) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

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
				y = y1;
				character = '\\';

				for(x = x1; x <= x2; ++x) {
					if(x >= 0) x_pos = (SFg_width / 2)
						+ ((size_t) imaxabs(x));

					else x_pos = (SFg_width / 2)
						- ((size_t) imaxabs(x));

					if(y >= 0) y_pos = (SFg_height / 2)
						+ ((size_t) imaxabs(y));

					else y_pos = (SFg_height / 2)
						- ((size_t) imaxabs(y));

					_draw(x_pos, y_pos, character);

					++y;
				}
			}
		}

		else {
			y = y1;
			character = '_';

			for(x = x1; x <= x2; ++x) {
				if(x >= 0) x_pos = (SFg_width / 2)
					+ ((size_t) imaxabs(x));

				else x_pos = (SFg_width / 2)
					- ((size_t) imaxabs(x));

				if(y >= 0) y_pos = (SFg_height / 2)
					+ ((size_t) imaxabs(y));

				else y_pos = (SFg_height / 2)
					- ((size_t) imaxabs(y));

				_draw(x_pos, y_pos, character);
			}
		}
	}

	else {
		if(y1 > y2) {
			x = x1;
			character = '|';

			for(y = y2; y <= y1; ++y) {
				if(x >= 0) x_pos = (SFg_width / 2)
					+ ((size_t) imaxabs(x));

				else x_pos = (SFg_width / 2)
					- ((size_t) imaxabs(x));

				if(y >= 0) y_pos = (SFg_height / 2)
					+ ((size_t) imaxabs(y));

				else y_pos = (SFg_height / 2)
					- ((size_t) imaxabs(y));

				_draw(x_pos, y_pos, character);
			}
		}

		else if(y1 < y2) {
			x = x1;
			character = '|';

			for(y = y1; y <= y2; ++y) {
				if(x >= 0) x_pos = (SFg_width / 2)
					+ ((size_t) imaxabs(x));

				else x_pos = (SFg_width / 2)
					- ((size_t) imaxabs(x));

				if(y >= 0) y_pos = (SFg_height / 2)
					+ ((size_t) imaxabs(y));

				else y_pos = (SFg_height / 2)
					- ((size_t) imaxabs(y));

				_draw(x_pos, y_pos, character);
			}
		}

		else {
			x = x1;
			y = y1;
			character = '+';

			if(x >= 0) x_pos = (SFg_width / 2)
				+ ((size_t) imaxabs(x));

			else x_pos = (SFg_width / 2)
				- ((size_t) imaxabs(x));

			if(y >= 0) y_pos = (SFg_height / 2)
				+ ((size_t) imaxabs(y));

			else y_pos = (SFg_height / 2)
				- ((size_t) imaxabs(y));

			_draw(x_pos, y_pos, character);
		}
	}

	return;
}

static void _draw(size_t x, size_t y, char character) {
	if(screen && x < SFg_width && y < SFg_height) {
		screen[((SFg_width + 1) * y) + x] = character;
	}

	return;
}

void SFg_init() {
	if(screen) free(screen);

	screen = calloc((SFg_width + 1) * SFg_height, sizeof(char));

	if(!screen) {
		fprintf(stderr, "%s: Error: Cannot allocate screen memory.\n",
			SF_name);

		exit(1);
	}

	if(SFg_width != 0 && SFg_height != 0) {
		for(size_t y = 0; y < (SFg_height - 1); ++y) {
			for(size_t x = 0; x < SFg_width; ++x) {
				screen[((SFg_width + 1) * y) + x] = ' ';
			}

			screen[((SFg_width + 1) * y) + SFg_width] = '\n';
		}

		for(size_t i = 0; i < SFg_width; ++i) {
			screen[((SFg_width + 1) 
				* (SFg_height - 1)) + i] = ' ';
		}

		screen[((SFg_width + 1) * SFg_height) - 1] = 0;
	}

	return;
}

void SFg_clear() {
	if(screen) {
		for(size_t x = 0; x < SFg_width; ++x)
			for(size_t y = 0; y < SFg_height; ++y)
		{
			screen[((SFg_width + 1) * y) + x] = ' ';
		}
	}

	return;
}

void SFg_draw(SFv_t start, SFv_t end) {
	intmax_t start_x, start_y;
	intmax_t end_x, end_y;

	start.x /= SFg_char_width; end.x /= SFg_char_width;
	start.y /= SFg_char_height; end.y /= SFg_char_height;
	start.z /= SFg_fov_scale; end.z /= SFg_fov_scale;

	if((start.x >= 1.0) && (end.x >= 1.0)) {
		start.y /= -start.x;
		start.z /= start.x;
		end.y /= -end.x;
		end.z /= end.x;

		start_x = (intmax_t) start.z;
		start_y = (intmax_t) start.y;
		end_x = (intmax_t) end.z;
		end_y = (intmax_t) end.y;

		draw(start_x, start_y, end_x, end_y);
	}

	return;
}