#include "Condition.h"

//! Constructor
Condition::Condition()
{
  cond_count=0;          
}


//! Add a condition to the existing list of conditions 
void 
Condition::add_Cond(int a, int b, int c, int d, int e)
{ 
  cond_count++;
  list.resize(cond_count);
  list[cond_count-1]= new Ord_Set;
  list[cond_count-1]->Set_Val(a,b,c,d,e);    
}


//! Display the list of conditions 
void 
Condition::disp_Cond()
{
  if (cond_count!=0)
    for (int x=0; x<cond_count; x++)
      list[x]->Display_Val();
}


//! Returns the list of conditions for writing in file
char* 
Condition::write_Cond()
{
  //std::cout << "Am i here??"; 
  char* str = new char[500];
  strcpy(str,"");
  if (cond_count!=0)
    for (int x=0; x<cond_count; x++)
      strcat(str,list[x]->Disp_Val());
  return str;
}


//! Returns the no. of conditions
int 
Condition::ret_Cond()
{
  return cond_count;
}


//! Useful during FIND operation, checks if any of the conditions are present
int 
Condition::Check_Cond (int a, int b, int c, int d, int e)
{
  int j=1;
  int count=1;
  while ((count<=cond_count) && (j==1))
    {
      int i=0;
      i=(list[count-1]->Check_List(a,b,c,d,e));
      //std::cout<<"Cond_Count="<<cond_count<<std::endl;
      //std::cout<<"In CHECK CONDITION i = "<<i<<std::endl;
      if (i==1)
	      {
	        return 1;
	        j=0;
	      }
      else count++;
    }
  if (j==1) return 0;
  return 0;
}


void 
Condition::copyCondIntoArray (int* array)
{
  int index = array[0];
  array[index++]=cond_count;
  array[0]=index;
  for (int i=0; i<cond_count; i++)
    {
      list[i]->copyOrdSetIntoArray(array);
    }
  //array[0]=index;
  //std::cout << "Index in Condition : " << index << "\n";
  //return *index;
}


void 
Condition::copyArrayIntoCond(int &startI, int* array)
{
  int index = startI;
  int count = array[index++];
  startI=index;
  for (int i=0; i<count; i++)
    {
      list.resize(i+1);
      list[i]= new Ord_Set;
      list[i]->copyArrayIntoOrdSet(startI,array);
      index = startI;
    }
  cond_count = count;
}
