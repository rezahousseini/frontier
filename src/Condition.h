#ifndef INCLUDE_CONDITION_H
#define INCLUDE_CONDITION_H

#include <vector>

#include "Ord_Set.h"

//! An object of this class contains a list of the conditions that should be 
//! satisfied to enter a particular subtree, it is a dynamic array of pointers 
//! to objects of class Ord_Set 
class Condition
{
  protected:

    std::vector <Ord_Set *> list;  // the dynamic list of conditions
    int cond_count;                // no. of conditions
  
  public:
 
    //! Constructor
    Condition();
    
    //! Add a condition to the existing list of conditions 
    void add_Cond(int a, int b, int c, int d, int e); 

    //! Display the list of conditions 
    void disp_Cond(); 

    //! Returns the list of conditions for writing in file
    char* write_Cond(); 

    //! Returns the no. of conditions
    int ret_Cond();
    
    //! Useful during FIND operation, checks if any of the conditions are present
    int Check_Cond(int a,int b, int c, int d, int e);
    
    //! Stores information of conditions into Array
    void copyCondIntoArray(int* array); // , int *index);

    //! Stores information of conditions from Array
    void copyArrayIntoCond(int &startI, int* array);
};

#endif // INCLUDE_CONDITION_H
