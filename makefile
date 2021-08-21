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

# Include the header file.
include headerfile.mk

# External Resources
include core/headerfile.mk
include graphics/headerfile.mk
include interface/headerfile.mk
include physics/headerfile.mk
include world/headerfile.mk

include core/makefile.mk
include graphics/makefile.mk
include interface/makefile.mk
include physics/makefile.mk
include world/makefile.mk

# Folders
build/:
	mkdir -p build/

# Files
build/main: $(objects)
	$(CC) $(CFLAGS) $(objects) -o build/main $(LD_LIBS)

# Commands
all: build/main

test: build/main
	build/main $(FLAGS) --plane $(TEST_PLACE) --world $(TEST_WORLD)

run: build/main
	build/main $(FLAGS)

clean: build/
	rm -r build/
