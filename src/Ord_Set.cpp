#include "Ord_Set.h"


Ord_Set::Ord_Set()
{
  type1=type2=part1=part2=const_type=0;
}


//! Initializes values
void 
Ord_Set::Set_Val(int a, int b, int c, int d, int e)
{
  type1 = a;
  part1 = b;
  type2 = c;
  part2 = d;
  const_type = e;
}


//! Displays values as an ordered set
void 
Ord_Set::Display_Val()
{
  std::cout << "(" << type1 << "," << part1 << "," << type2 ;
  std::cout << "," << part2 << "," << const_type << ")\n";
}


//! Returns values as a concatenated string
char* 
Ord_Set::Disp_Val()
{
  std::string str = std::to_string(type1);
  str += ",";
  str += std::to_string(part1);
  str += ",";
  str += std::to_string(type2);
  str += ",";
  str += std::to_string(part2);
  str += ",";
  str += std::to_string(const_type);
  str += "\n";
  return &str[0];
}


//! returns the id of first entity
int 
Ord_Set::ret_1()
{
  return type1;
}


//! returns the part id of first entity
int 
Ord_Set::ret_2()
{
  return part1;
}


//! returns the id of second entity
int 
Ord_Set::ret_3()
{
  return type2;
}


//! returns the part id of second entity  
int 
Ord_Set::ret_4()
{
  return part2;
}


//! returns the id of the constraint between the two end entities
int 
Ord_Set::ret_5()
{
  return const_type;
}


//! Useful during FIND operation, checks if entities, parts and constraints 
//! match
int 
Ord_Set::Check_List (int a, int b, int c, int d, int e)
{
  if ((type1==a) && (part1==b) && (type2==c) && (part2==d) && (const_type==e))
    return 1;
  else
    return 0;
}


void 
Ord_Set::copyOrdSetIntoArray (int* array)
{
  int index = array[0];
  array[index++]=ret_1();
  array[index++]=ret_2();
  array[index++]=ret_3();
  array[index++]=ret_4();
  array[index++]=ret_5();
  array[0]=index;
} 


void 
Ord_Set::copyArrayIntoOrdSet (int &startI, int* array)
{
  int index = startI;
  int a = array[index++];
  int b = array[index++];
  int c = array[index++];
  int d = array[index++];
  int e = array[index++];
  Set_Val(a,b,c,d,e);
  startI = index;
}
