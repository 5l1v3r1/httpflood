# HTTPFlood
Tool for flooding HTTP servers under [Linux](http://www.linux.org/).

## Build

1. Clone:
	
		git clone https://github.com/TheFox/httpflood.git

2. In `httpflood` directory, make:
	
		mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make && make test

3. Done.

## License
Copyright (C) 2010 Christian Mayer <http://fox21.at>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
