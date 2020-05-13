// Copyright (C) 2020      Vincent Perrier
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

#include <dummy.hpp>

dummy::dummy( ) {}

dummy::~dummy( ) {}

bool dummy::initialize( ) { return true; }

bool dummy::read( int gpio ) {
    (void) gpio;
    return true;
}

int dummy::read_analog( int gpio ) {
    (void) gpio;
    return 255;
}

bool dummy::write( int gpio, bool state ) {
    (void) gpio;
    (void) state;
    return true;
}

bool dummy::write_analog( int gpio, int state ) {
    (void) gpio;
    (void) state;
    return true;
}