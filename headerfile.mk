# Simple Flight Copyright (C) 2019 Jyothiraditya Nellakra

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

# Command Flags
.DEFAULT_GOAL = all

FLAGS += --height $(shell tput lines) --width $(shell tput cols)
FLAGS += --graphics files/graphics/$(shell hostname)

TEST_PLANE ?= files/planes/unit_cube
TEST_WORLD ?= files/worlds/flat_earth

CC ?= gcc
CFLAGS += -Wall -Wextra -Werror -std=c99 -O3 -I ./

LD ?= ld
LD_LIBS = -pthread -lm

# Command Declarations
.PHONY: all test run clean
