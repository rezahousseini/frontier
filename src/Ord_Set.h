#ifndef INCLUDE_ORD_SET_H
#define INCLUDE_ORD_SET_H

#include <cstring>
#include <iostream>
#include <algorithm>

class Ord_Set
{
  protected:

    int type1, type2; // entity type
    int part1, part2; // part involved
    int const_type;   // constraint type
  
  public:
  
    //! Constructor
    Ord_Set();
    
    //! Initializes values
    void Set_Val(int a, int b, int c, int d, int e);
    
    //! Displays values as an ordered set
    void Display_Val();

    //! Returns values as a concatenated string
    char* Disp_Val();
     
    //! returns the id of first entity
    int ret_1(); 
    
    //! returns the part id of first entity
    int ret_2();
    
    //! returns the id of second entity
    int ret_3();
    
    //! returns the part id of second entity  
    int ret_4();
    
    //! returns the id of the constraint between the two end entities
    int ret_5();
    
    //! Useful during FIND operation, checks if entities, parts and constraints 
    //! match
    int Check_List(int a, int b, int c, int d, int e);

    //! Stores information of conditions into Array
    void copyOrdSetIntoArray(int* array); //, int *index);

    //! Stores information of conditions from Array
    void copyArrayIntoOrdSet(int &startI, int* array);
};

#endif // INCLUDE_ORD_SET_H
