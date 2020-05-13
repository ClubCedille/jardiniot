// Copyright (C) 2020   Vincent Perrier
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

#ifndef DUMMY_H
#define DUMMY_H

#include <GPIOstrategy.hpp>
class dummy : GPIOstrategy {
  public:
    dummy( );
    ~dummy( );

    virtual bool initialize( );
    virtual bool read( int gpio );
    virtual int read_analog( int gpio );
    virtual bool write( int gpio, bool state );
    virtual bool write_analog( int gpio, int state );

  private:
};

#endif