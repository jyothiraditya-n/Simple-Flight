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

#include "main.h"

#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"
#include "gfx.h"
#include "plane.h"
#include "tui.h"
#include "world.h"

char *SF_name = "simple-flight";

static bool flag_is_valid(char *flag);

static void print_flag_error();
static void print_help();
static void print_minihelp();

static void read_flags();

static bool do_gfx = true;

static bool set_do_gfx = false;
static bool set_gfx_height = false;
static bool set_gfx_width = false;

static bool set_gfx_char_height = false;
static bool set_gfx_char_width = false;
static bool set_gfx_fov_scale = false;

static bool set_tui_file = false;
static bool set_plane_file = false;
static bool set_world_file = false;

static bool flag_is_valid(char *flag) {
	if(!strcmp(flag, "-")) return true;

	if(!strcmp(flag, "-gfx")) return true;
	if(!strcmp(flag, "-no-gfx")) return true;
	if(!strcmp(flag, "-help")) return true;

	if(!strcmp(flag, "-gfx-height")) return true;
	if(!strcmp(flag, "-gfx-width")) return true;

	if(!strcmp(flag, "-keybinds")) return true;
	if(!strcmp(flag, "-plane")) return true;
	if(!strcmp(flag, "-world")) return true;

	return false;
}

static void print_flag_error(char *flag, char *invalid_compl) {
	fprintf(stderr, "%s: Error: '%s' is an invalid argument for '%s'.\n\n",
		SF_name, invalid_compl, flag);

	print_minihelp();
}

static void print_help() {
	printf("Simple Flight Copyright (C) 2019-2021 Jyothiraditya Nellakra\n\n");

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

	printf("Usage: %s [OPTIONS]\n\n", SF_name);

	printf("-gfx: Enable command-line ANSI graphics (default).\n");
	printf("-no-gfx: Disable command-line ANSI graphics.");
	printf("-help: Display this help dialogue.\n");

	printf("-gfx-height HEIGHT: Set the ANSI graphics display height to HEIGHT.\n");
	printf("-gfx-width WIDTH: Set the ANSI graphics display width to WIDTH.\n\n");

	printf("-gfx-char-height HEIGHT: Set the character height multiplier to HEIGHT.\n");
	printf("-gfx-char-width WIDTH: Set the character width multiplier to WIDTH.\n");
	printf("-gfx-fov-multiplier VALUE: Set the fov multiplier to VALUE.\n\n");

	printf("-keybinds KEYBINDS: Read the TUI key bindings from the file KEYBINDS.\n");
	printf("-plane PLANE: Read plane details from the file PLANE.\n");
	printf("-world WORLD: Read world details from the file WORLD.\n\n");

	printf("NOTE: Disabling the ANSI graphics replaces the TUI with a CLI.\n");

	exit(0);
}

static void print_minihelp() {
	printf("Usage: %s [OPTIONS]\n\n", SF_name);

	printf("-gfx: Enable command-line ANSI graphics (default).\n");
	printf("-no-gfx: Disable command-line ANSI graphics.");
	printf("-help: Display this help dialogue.\n");

	printf("-gfx-height HEIGHT: Set the ANSI graphics display height to HEIGHT.\n");
	printf("-gfx-width WIDTH: Set the ANSI graphics display width to WIDTH.\n\n");

	printf("-gfx-char-height HEIGHT: Set the character height multiplier to HEIGHT.\n");
	printf("-gfx-char-width WIDTH: Set the character width multiplier to WIDTH.\n");
	printf("-gfx-fov-scale SCALE: Set the fov multiplier to SCALE.\n\n");

	printf("-keybinds KEYBINDS: Read the TUI key bindings from the file KEYBINDS.\n");
	printf("-plane PLANE: Read plane details from the file PLANE.\n");
	printf("-world WORLD: Read world details from the file WORLD.\n\n");

	exit(1);
}

static void read_flags(int argc, char **argv) {
	for(int i = 1; i < argc; i++) {
		if(!flag_is_valid(argv[i])) {
			fprintf(stderr, "%s: Error: '%s' is not a valid "
				"argument.\n\n", SF_name, argv[i]);

			print_minihelp();
		}

		// single-string arguments
		if(!strcmp(argv[i], "-gfx")) {
			if(set_do_gfx) {
				fprintf(stderr, "%s: Error: Graphics enabled "
					"or disabled multiple times.\n\n",
					SF_name);

				print_minihelp();
			}

			do_gfx = true;
			set_do_gfx = true;
		}

		else if(!strcmp(argv[i], "-no-gfx")) {
			if(set_do_gfx) {
				fprintf(stderr, "%s: Error: Graphics enabled "
					"or disabled multiple times.\n\n",
					SF_name);

				print_minihelp();
			}

			do_gfx = false;
			set_do_gfx = true;
		}

		else if(!strcmp(argv[i], "-help")) print_help();

		else if(!strcmp(argv[i], "--")) return;

		// double-string arguments
		else if(argc - i <= 1) {
			fprintf(stderr, "%s: Error: '%s' requires a "
				"value.\n\n", SF_name, argv[i]);

			print_minihelp();
		}

		else if(argv[i + 1][0] == '-') {
			fprintf(stderr, "%s: Error: '%s' requires a "
				"value.\n\n", SF_name, argv[i]);

			print_minihelp();
		}

		else if(!strcmp(argv[i], "-gfx-height")) {
			if(set_gfx_height) {
				fprintf(stderr, "%s: Error: Graphics display "
					"height set multiple times.\n\n",
					SF_name);

				print_minihelp();
			}

			int ret = sscanf(argv[i + 1], "%zu", &SFg_height);

			if(ret != 1) {
				print_flag_error("-gfx-height", argv[i + 1]);
			}

			set_gfx_height = true;
			i++;
		}

		else if(!strcmp(argv[i], "-gfx-width")) {
			if(set_gfx_width) {
				fprintf(stderr, "%s: Error: Graphics display "
					"width set multiple times.\n\n",
					SF_name);

				print_minihelp();
			}

			int ret = sscanf(argv[i + 1], "%zu", &SFg_width);

			if(ret != 1) {
				print_flag_error("-gfx-width", argv[i + 1]);
			}

			set_gfx_width = true;
			i++;
		}

		else if(!strcmp(argv[i], "-gfx-char-height")) {
			if(set_gfx_char_height) {
				fprintf(stderr, "%s: Error: Graphics display "
					"character height set multiple "
					"times.\n\n", SF_name);

				print_minihelp();
			}

			int ret = sscanf(argv[i + 1], "%lf", &SFg_char_height);

			if(ret != 1) {
				print_flag_error("-gfx-char-height",
					argv[i + 1]);
			}

			set_gfx_char_height = true;
			i++;
		}

		else if(!strcmp(argv[i], "-gfx-char-width")) {
			if(set_gfx_char_width) {
				fprintf(stderr, "%s: Error: Graphics display "
					"character width set multiple "
					"times.\n\n", SF_name);

				print_minihelp();
			}

			int ret = sscanf(argv[i + 1], "%lf", &SFg_char_height);

			if(ret != 1) {
				print_flag_error("-gfx-width", argv[i + 1]);
			}

			set_gfx_char_width = true;
			i++;
		}

		else if(!strcmp(argv[i], "-gfx-fov-scale")) {
			if(set_gfx_fov_scale) {
				fprintf(stderr, "%s: Error: Graphics display "
					"fov multiplier set multiple "
					"times.\n\n", SF_name);

				print_minihelp();
			}

			int ret = sscanf(argv[i + 1], "%lf", &SFg_fov_scale);

			if(ret != 1) {
				print_flag_error("-gfx-fov-scale",
					argv[i + 1]);
			}

			set_gfx_fov_scale = true;
			i++;
		}

		else if(!strcmp(argv[i], "-keybinds")) {
			if(set_tui_file) {
				fprintf(stderr, "%s: Error: TUI key bindings "
					"file set multiple times.\n\n",
					SF_name);

				print_minihelp();
			}

			SFt_file = argv[i + 1];

			if(strcmp(SFt_file, "builtin")
				&& access(SFt_file, R_OK) != 0)
			{
				fprintf(stderr, "%s: Error: Cannot open file "
					"'%s' for reading.\n", SF_name,
					SFt_file);

				print_flag_error("-keybinds", SFt_file);
			}

			set_tui_file = true;
			i++;
		}

		else if(!strcmp(argv[i], "-plane")) {
			if(set_plane_file) {
				fprintf(stderr, "%s: Error: plane file set "
					"multiple times.\n\n", SF_name);

				print_minihelp();
			}

			SFp_file = argv[i + 1];

			if(strcmp(SFp_file, "builtin")
				&& access(SFp_file, R_OK) != 0)
			{
				fprintf(stderr, "%s: Error: Cannot open file "
					"'%s' for reading.\n", SF_name,
					SFp_file);

				print_flag_error("-plane", SFp_file);
			}

			set_plane_file = true;
			i++;
		}

		else if(!strcmp(argv[i], "-world")) {
			if(set_world_file) {
				fprintf(stderr, "%s: Error: world file set "
					"multiple times.\n\n", SF_name);

				print_minihelp();
			}

			SFw_file = argv[i + 1];

			if(strcmp(SFw_file, "builtin")
				&& access(SFw_file, R_OK) != 0)
			{
				fprintf(stderr, "%s: Error: Cannot open file "
					"'%s' for reading.\n", SF_name,
					SFw_file);

				print_flag_error("-world", SFw_file);
			}

			set_world_file = true;
			i++;
		}
	}
	
	return;
}

int main(int argc, char **argv) {
	if(argc >= 1) SF_name = argv[0];
	read_flags(argc, argv);

	SFg_init();
	SFp_init();
	SFw_init();

	if(do_gfx) SFt_main();
	else SFc_main();

	exit(0);
}