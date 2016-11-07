/*Copyright (C) June 22, 2001 Meera Sitharam

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
http://www.gnu.org/copyleft/gpl.html

You should have received a copy of the GNU General Public License
in the documentation index in the documentation
folder of the FRONTIER-gnu directory; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//! \file DegValues.h
//! \brief Header file that contains the interface for the data structures
//!        used by the UTU, ESM and DR-planner

#ifndef INCLUDE_DEGVALUES_H
#define INCLUDE_DEGVALUES_H

#include <iostream>


//class that stores one set of degvalues exactly as described in Class Vertex above
class DegValues
{
  private:
  
    float degValues[9];

  public:

    DegValues();
    void setValue(int i, float value) { degValues[i]=value; }
    float returnValue(int i) const { return degValues[i]; }
    DegValues & operator = (const DegValues &deg);
    //stream output
    friend std::ostream& operator <<(std::ostream&, const DegValues&);
};

#endif // INCLUDE_DEGVALUES_H
