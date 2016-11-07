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
as a file both in the FRONTIER-gnu directory, and 
in the documentation index in the documentation
folder of the FRONTIER-gnu directory; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//! \file Solver.h
//! \brief Header file for the equation solution manager (ESM)


#ifndef INCLUDE_SOLVER_H
#define INCLUDE_SOLVER_H

#include "mfaTree.h"
#include "Utility.h"
#include "Cluster.h"
#include "Print.h"
#include "Equation.h"
#include "MFAAlgo.h"

//Global variable declarations
//List<int> keys;                   //records the keys pressed by the user
//List<Edge> theImags;              //theImaginary Constraints
//
//List<Cluster> roots;              //roots of the DRDAG
//List<Cluster>* toSolverTrees;		  //points to SolverTrees
//List<Cluster> DAGBackup;		      //Backup of the DRDAG
//Graph graph0Backup;			          //Backup of graph0
//
//Vertex testVertex1, testVertex2;  //sample vertices used in testing
//
//std::string outFile="./Sketcher/testout.txt"; //path to output file
//std::string varsToZero="";		  	//list of all the zeroed variables in a set
//
//int aOverlap;                     //an example constraint between two clusters
//int equationCount;                //the number of equations generated for a cluster
//
//Vertex::Type type1, type2;        //used in the testEQ section
//int startI;                       //starting point for int array read  
//int startF;                       //starting point for float array read
//int currPosI;				              //current location in inputInts
//int currPosF;				              //current location in inputFloats
//int* inputInts;				            //global pointer to the int array
//int treeFlag;
//int* bifurAnswers;			          //answers to the current bifurs
//int graphDimen;				            //dimension of the graph
//
//float* inputFloats;               //global pointer to the float array
//
//char* inputChars;			            //global pointer to char array
//
//bool toSolve;                     //stores a command to solve or to halt
//bool first;                       //true if this is the first message to the sketcher
//bool autoSolve;                   //automatically searches solution set if true
//bool usingArrays;                 //true if the current data came from arrays
//bool usedBifurs;			            //true if the bifurs have been placed
//
//Graph gGraph1;				            //globalized graph1


// Function Headers
// For definitions and function documentation see the inidividual function 
// definitions in mfa9Solver.cpp

//Printing Functions
void generateOutput(Graph &graph0, Cluster &theCluster, std::ostream &outfile, bool printNum);
void updateGraph(Graph &graph0, Cluster &theCluster);
void outputDRDAG(List<Cluster> &theCluster, std::ostream &output, bool first);
void outputFinState(Cluster &theCluster, int &startI, int*& theInts, int &count);

//Intersection finders
void getIntersectionLineLine (Vertex &theVertex, float x1, float y1, float m1, 
                              float x2, float y2, float m2);
void getIntersectionLineCircle (List<Vertex> &thePoints, float x1, float y1, 
                                float m1, float x2, float y2, float r);
void getIntersectionCircleCircle (List<Vertex> &thePoints, float x1, float y1, 
                                  float r1, float x2, float y2, float r2);

//Imaginary Constraint recognition functions
bool isValidPointIncidence(Vertex &thePoint, Vertex &theOther, int part1, int part2);
bool isValidLineIncidence(Vertex &theLine, Vertex &theOther, int part1, int part2);
bool isValidRayIncidence(Vertex &theRay, Vertex &theOther, int part1, int part2);
bool isValidLSIncidence(Vertex &theLS, Vertex &theOther, int part1, int part2);
bool isValidCircleIncidence(Vertex &theCircle, Vertex &theOther, int part1, int part2);
bool isValidArcIncidence(Vertex &theArc, Vertex &theOther, int part1, int part2);

//Bifurcation functions
bool isValidConstraint(Graph &graph0, Edge &theEdge, Cluster &theCluster);
bool validBifur(std::string theString);
void setBifurs(std::string filename, Graph graph0, Cluster& theCluster, bool usingfSolve);
void parseBifurString(Graph &graph0, Cluster &theCluster);
bool getNextBifurcation(Graph &graph0, Cluster &theCluster);
int selectBifurcation(Graph &graph0, Cluster &theCluster, bool &useFile, 
                      float *inputFloats, int currPosF, int *inputInts, int currPosI);
void checkBifurs(Graph &graph0, Cluster &theCluster, List<Edge> &theImags);

//Solver Functions
void Solver (Graph &graph1, Graph &graph0, List<Cluster> &SolverTrees, 
             jint* inputTheInts, jdouble* inputDouble, jchar* inputChar, 
             the_Tree &Tree, List<std::string>& vars, int equationCount, 
             int withHeldCluster, int aOverlap, int singleVertex,
             int nextVerName, int nextEdgeName, int glo_flag, int search_flag,
             float *inputFloats, int currPosF, int *inputInts, int currPosI,
             int *bifurAnswers, List<Cluster> *toSolverTrees, bool usedBifurs,
             List<Cluster> &roots, bool first, bool autoSolve, bool usingArrays,
             int treeFlag, int startF, int startI, int graphDimen, 
             Graph &gGraph1, char *inputChars, std::string &varsToZero, 
             List<Edge> &theImags);
void shellMaple();
void setWithHeldCluster(Cluster &theCluster, int withHeldCluster);
int solveCluster (Graph &graph0, Cluster &theCluster, bool resolve, 
                  the_Tree &Tree, List<std::string>& vars, int equationCount, 
                  int withHeldCluster, int aOverlap, int singleVertex,
                  int nextVerName, int nextEdgeName, int glo_flag, 
                  int search_flag, float *inputFloats, int currPosF, 
                  int *inputInts, int currPosI, int *bifurAnswers, 
                  List<Cluster> *toSolverTrees, bool usedBifurs,
                  List<Cluster> &roots, bool first, bool autoSolve, 
                  bool usingArrays, int treeFlag, int startF, int startI, 
                  int graphDimen, Graph &gGraph1, char *inputChars,
                  std::string &varsToZero, List<Edge> &theImags);
int solveForest (Graph &graph0, List<Cluster> &theForest, the_Tree &Tree,
                 List<std::string>& vars, int equationCount, 
                 int withHeldCluster, int aOverlap, int singleVertex,
                 int nextVerName, int nextEdgeName, int glo_flag,
                 int search_flag, float *inputFloats, int currPosF, 
                 int *inputInts, int currPosI, int *bifurAnswers, 
                 List<Cluster> *toSolverTrees, bool usedBifurs,
                 List<Cluster> &roots, bool first, bool autoSolve, 
                 bool usingArrays, int treeFlag, int startF, int startI, 
                 int graphDimen, Graph &gGraph1, char *inputChars,
                 std::string &varsToZero, List<Edge> &theImags);

//Testing functions
void testEquations (Graph &graph0, List<std::string> &vars, List<Edge> &theImags,
                    Vertex::Type type1, Vertex::Type type2, Vertex testVertex1, 
                    Vertex testVertex2);
void getGraphFromFile(Graph &graph0, List<Cluster> &SolverTrees);

//Array IO Functions
void stringToArray(std::string theString, int*& theInts);
std::string readStringFromArray(int& start, int* theInts);
void vertexToArray(Vertex &theVertex, int*& theInts, float*& theFloats);
void readVertexFromArray (Vertex &vertex, int &startI, int* theInts, 
                          int& startF, float* theFloats);
void edgeToArray(Edge &theEdge, int*& theInts, float*& theFloats);
void readEdgeFromArray (Edge &edge, int &startI, int* theInts, 
                        int &startF, float* theFloats);
void graphToArray(Graph &graph0, int*& theInts, float*& theFloats);
void readGraphFromArray (Graph &graph, int &startI, int* theInts, 
                         int &startF, float* theFloats);
void clusterToArray(Cluster &theCluster, int*& theInts, float*& theFloats);
void readClusterFromArray (Cluster &theCluster, int &startI, int* theInts, 
                           int &startF, float* theFloats);
void outputArrays(int* theInts, float* theFloats);
void inputArrays(int*& theInts, float*& theFloats);
void saveState (Graph &graph0, List<Cluster>* toSolverTrees, int *inputInts,
                float *inputFloats, int treeFlag, Graph& gGraph1);
//void saveState (Graph &graph1, Graph &graph0, List<Cluster> &SolverTrees, 
//                jint*& thejInts, jdouble*& thejDoubles);
void loadState (Graph &graph1, Graph &graph0, List<Cluster> &SolverTrees, 
                int &startI, jint* thejInts, int &startF, jdouble* thejDoubles, jchar *thejChars);
void setArraysForOutput (jint*& theJInts, jdouble*& theJDoubles, 
                         int *inputInts, float *inputFloats);
void setArraysForInput(jint*& theJInts, jdouble*& theJDoubles, jchar*& theJChars,
                       char *inputChars, int *inputInts, float *inputFloats);
void outputDRDAGToArray(List<Cluster> &theCluster, int& index, int*& theInts, bool first);
void generateOutputToArray (Graph &graph0, Cluster &theCluster, bool printNum,
                            float *inputFloats, int currPosF, int *inputInts, 
                            int currPosI);
/*
void treeToArray(Node *Root, int*& theInts);
Node* readTreeFromArray(int*& start, int* theInts);
*/

std::string getEquation (Graph &graph0, Cluster &theCluster, 
                         std::ostream &inputFile, the_Tree &Tree, 
                         List<std::string>& vars, int equationCount, 
                         int withHeldCluster, int aOverlap, int singleVertex,
                         int nextVerName, int nextEdgeName, int glo_flag,
                         int search_flag, std::string &varsToZero,
                         int graphDimen);
bool isIdentical (Graph &graph0, Cluster &theCluster, List<int> &overlappedList,
                  int ID, float p, float q, float s, float t, float f, float h, 
                  float j, float k, float n, int withHeldCluster);
bool checkEdge (Edge &theEdge, Graph &graph0, List<Cluster> &SolverTrees, 
                List<std::string>& vars, int graphDimen, List<Edge> &theImags);
int verifyBifurs (Graph graph0, Cluster theCluster, List<std::string> &theList, 
                  int withHeldCluster);

#endif // INCLUDE_SOLVER_H
