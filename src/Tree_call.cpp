#include <cstdlib>
#include <ostream>
#include <fstream>

//#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Cluster.h"
//#include "Condition.h"
//#include "Node.h"
//#include "GetCluster.h"
//#include "Distribution.h"
//#include "DRTree.h"
//#include "MFAAlgo.h"
//#include "mfa1List.h"
//#include "mfaTree.h"
//#include "Solver.h"

int main(int argc, char** argv)
{
  Vertex vertex;
  std::cout << vertex << std::endl;
  Edge edge;
  std::cout << edge << std::endl;
  //Graph graph;
  //std::cout << graph << std::endl;
  Cluster cluster;
  std::cout << cluster << std::endl;
  //Condition condition;
  //condition.disp_Cond();
  //Node node;
  //node.showTree();
  //std::cout << checkSpecialExtensionCase (graph, std::cout, 1) << std::endl;
  ////std::cout << specialPushCase(graph, cluster) << std::endl;
  ////std::cout << getClusterType(graph, cluster) << std::endl;

  //List<Cluster> DRTrees;
  //std::ofstream file1, file2;
  //mfaAlgo (graph, DRTrees, file1, file2, 0, 0, 0);
  ////std::cout << specialPushCase (graph, cluster) << std::endl;
  //the_Tree tree;

  //int glo_flag=0;                      // Flag used for indicating end of search
  //int search_flag=0;                   // Global flag to know which type of search
  //int withHeldCluster;              //theCluster whose values are carried over in solving
  //List<std::string> vars;           //holds the list of variable strings
  //int nextEdgeName=1, nextVerName=1, singleVertex=1;
  //List<Edge> theImags;              //theImaginary Constraints
  //List<Cluster> roots;              //roots of the DRDAG
  //List<Cluster>* toSolverTrees;		  //points to SolverTrees
  //std::string varsToZero="";		  	//list of all the zeroed variables in a set
  //int aOverlap;                     //an example constraint between two clusters
  //int equationCount;                //the number of equations generated for a cluster
  //int startI;                       //starting point for int array read  
  //int startF;                       //starting point for float array read
  //int currPosI;				              //current location in inputInts
  //int currPosF;				              //current location in inputFloats
  //int* inputInts;				            //global pointer to the int array
  //int treeFlag;
  //int* bifurAnswers;			          //answers to the current bifurs
  //int graphDimen;				            //dimension of the graph
  //float* inputFloats;               //global pointer to the float array
  //char* inputChars;			            //global pointer to char array
  //bool first;                       //true if this is the first message to the sketcher
  //bool autoSolve;                   //automatically searches solution set if true
  //bool usingArrays;                 //true if the current data came from arrays
  //bool usedBifurs;			            //true if the bifurs have been placed
  //bool resolve;
  //
  //Graph gGraph1;				            //globalized graph1
  //solveCluster (graph, cluster, resolve, tree, vars, equationCount, 
  //              withHeldCluster, aOverlap, singleVertex, nextVerName, 
  //              nextEdgeName, glo_flag, search_flag, inputFloats, currPosF, 
  //              inputInts, currPosI, bifurAnswers, toSolverTrees, usedBifurs,
  //              roots, first, autoSolve, usingArrays, treeFlag, startF, startI,
  //              graphDimen, gGraph1, inputChars, varsToZero, theImags);
  //Tree.build_Tree(1);
  //Tree.display_Tree();
  //Tree.search_Tree();
  return EXIT_SUCCESS;
}
