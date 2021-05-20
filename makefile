# Simple Flight (C) 2019-2021 Jyothiraditya Nellakra
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <https://www.gnu.org/licenses/>.

objs = $(patsubst %.c,%.o,$(wildcard src/*.c))

current_objs = $(wildcard src/*.o)
current_progs = $(wildcard simple-flight)

CLEAN = $(foreach obj,$(current_objs),rm $(obj);)
CLEAN += $(foreach prog,$(current_progs),rm $(prog);)

CC ?= gcc
CFLAGS += -std=c99
CPPFLAGS += -Wall -Wextra -Werror -O3

LIBS += -pthread -lm

$(objs) : %.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

simple-flight : $(objs)
	$(CC) $(CFLAGS) $(objs) -o $@ $(LIBS)

.DEFAULT_GOAL = all
.PHONY : all clean run

all : simple-flight

clean :
	$(CLEAN)

run : simple-flight
	./simple-flight