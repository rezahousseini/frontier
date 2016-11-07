#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <fstream>

#include "Condition.h"

//! An object of this class is a node in the intended tree. It contains the 
//! equation that needs to be output.  
class Node
{
  public:
  
    char* label;               //Label for the node
    char* eqn;                 //Equation at that node
    int child_count;           //no. of children nodes for this node
    std::vector <Node *> ptr;       //pointers to children
    std::vector <Condition *> cond; //conditions for the children nodes 
    Node *parent;
    int glo_flag=0;                      // Flag used for indicating end of search
  
  public:
  
    //! Constructor
    Node();
    
    //! Sets the label for the node
    void Set_label(char* s);
     
    //! Prints the label of a node
    void Get_label();
    
    //! Returns the label of a node
    char* Ret_label();
    
    //! Sets the parent for a node
    void Set_parent(Node *i);
    
    //! Returns the label of the parent of any given node
    char* Get_Parent();
    
    //! Sets the children nodes after taking in the conditions for that node
    //! Called during Input mode only
    void Set_child(int i, Node* j, Condition* k, char* str);
    
    //! Sets the children nodes by taking the conditions for that node from a 
    //! file f_name. Called during Find mode only
    void Set_child(int i, Node* j, Condition* k, char* path_name, char* f_name, 
                   int a);
    
    //! Sets the equation in the node
    void Set_Eqn(char* s);
    
    //! Returns the equation in the node
    char* Get_Eqn();
    
    //! Displays the equation in the node
    void disp_Eqn();
      
    //! Returns the no. of children a node has in the tree
    int Get_child_count();
     
    //! Displays the tree in Pre-order form
    void showTree();
    
    //! Writes the tree into a file
    void write_Tree(char* file_String);
    
    //! Useful in FIND operation. Finds the equation given the end entities and 
    //! the constraints 
    char* Find_Eqn(int a,int b, int c, int d, int e);
    char* Find_Eqn_def_mode(int a,int b, int c, int d, int e);
};

#endif // INCLUDE_NODE_H
