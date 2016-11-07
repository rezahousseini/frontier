#ifndef INCLUDE_MFATREE_H
#define INCLUDE_MFATREE_H

#include <string>
#include <vector>
//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
//#include <ctype.h>
#include <fstream>
//#include <iomanip>
////#include <sys/ddi.h>
////#include <thread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <jni.h>
#include <cmath>
#include <algorithm>

#include "Cluster.h"
#include "Graph.h"
#include "Node.h"
#include "Condition.h"
#include "Utility.h"
#include "ClustData.h"
#include "Equation.h"
#include "GraphUpdate.h"
#include "StringFunction.h"


// Global variables
//int glo_flag=0;                      // Flag used for indicating end of search
//char* file_String = new char[10000]; // Global string used for writing into files
//int search_flag=0;                   // Global flag to know which type of search
//Node *rootOfTree;
//int withHeldCluster;              //theCluster whose values are carried over in solving
//List<std::string> vars;           //holds the list of variable strings

//! An object of this class is the Tree for conversion from constraints to 
//! mathematical equations
class the_Tree
{
  private:

    int node_count;                  // Number of nodes in the tree
    std::vector <Node *> Block;      // The dynamic list of nodes of the tree 
                                     // to be created   
    std::vector <Condition *> Cases; // The dynamic list of condition for nodes 
                                     // of the tree to be created


  public:

    //! Empty constructor
    the_Tree () {}
  
    //! Constructor
    //! \param select Informs if the Tree has to be intialized all over again.
    //!               Value 0 indicates usage from the old Tree, value 1 
    //!               indicates reconstuction with new constraints
    the_Tree (int select, int glo_flag, char *file_String); 
 
    //! This gets the choice of the user as to whether he/she would like to use 
    //! a previously constructed tree or create a new one and save it for 
    //! future use.
    //! \param select Informs if the Tree has to be intialized all over again.
    //!               Value 0 indicates usage from the old Tree, value 1 
    //!               indicates reconstuction with new constraints 
    void build_Tree(int select, char *file_String, int search_flag);
    
    void copyTreeIntoArray(int *array, char *strArray);
    

    //! pops the first element out of the vector
    void popfunc(std::vector <int> &A); 

    //! pops the first element out of the vector of Nodes
    Node *popQ(std::vector <Node *> &A);
  
    // Changes the data in array to Tree form 
    void copyArrayIntoTree(int &startI, int *&array, char *&strArray);
     
    //! converts a valid integer into a string
    char* itoa(int n, char s[]);
    
    //! Display the Tree so far constructed
    void display_Tree(); 

    //! Searches the Tree for a single constraint in automated search mode
    char* search_Tree(int a, int b, int c, int d, int e);
  
    //! Searches the Tree for a set of constraints but in a one-by-one basis 
    //! rather than en-bloc
    std::string search_Tree(Graph &graph0, Cluster &theCluster, 
                            std::ostream &inputFile, int flag, 
                            int withHeldCluster, int graphDimen,
                            int glo_flag, List<std::string>& vars);
  
    //! Searches the Tree in En-Bloc fashion for the constraints
    std::string search_Tree(Graph &graph0, Cluster &theCluster, 
                            std::ostream &inputFile, int withHeldCluster, 
                            int graphDimen, int glo_flag, 
                            List<std::string>& vars);
  
    //! Searches the Tree En-Block in user search mode
    void search_Tree(int glo_flag);
};

#endif // INCLUDE_MFATREE_H
