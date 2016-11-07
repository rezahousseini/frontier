#include "DegValues.h"

DegValues::DegValues () 
{
  int i;
  for(i=0;i<9;i++) degValues[i]=0;
}


DegValues& 
DegValues::operator= (const DegValues &deg)
{
  int i;

  if( this != &deg)
    {
      for(i=0;i<9;i++)
        degValues[i]=deg.degValues[i];
    }
  return *this;
}


std::ostream& 
operator<< (std::ostream& os, const DegValues& deg)
{
	for(int i=0;i<9;i++)
	  os << deg.degValues[i] << "    ";
	os << std::endl;
	return os;
}
