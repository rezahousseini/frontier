//! \file Utility.h

#ifndef INCLUDE_UTILITY_H
#define INCLUDE_UTILITY_H

#include <cstdlib>
#include <fstream>
#include <cmath>

#include "Cluster.h"
#include "Vertex.h"
#include "Graph.h"
#include "mfa1List.h"
#include "ClustData.h"
//#include "Equation.h"
#include "StringFunction.h"


float getDistance (float x1, float y1, float x2, float y2);
float getAngle (float x1, float y1, float x2, float y2);
float getAngle (float theCos, float theSin);
int getChildIndexByName (Cluster &theCluster, int vName);
int getChildNameWithVertex (Cluster &theCluster, int theV);
bool inOriginalV (int Name, Cluster &theCluster);
void setValue (Vertex &theVertex, int index, float theValue);
void getContainedChildList (Cluster &theCluster, int vName, List<int> &theList);
void setValue (Cluster &theCluster, int ID, float theValue, int index);
int getFreeDegIndex (char keyChar, Vertex &theVertex);
bool resetFinByClusterName (Cluster &theCluster, int name);
void resetTrees (Graph &graph0, List<Cluster> &SolverTrees);
void setValueReduction (Graph &graph0, Cluster &theCluster);
void fixCluster (Cluster &theCluster);
void fixTree (List<Cluster> &SolverTrees);
//std::string processMatlab (std::string input);
//void postProcessMatlab ();
float findDist (Graph &graph0, Cluster &theCluster);
void getOverlapList (Graph graph0, Cluster &theCluster, List<int> &outputList, 
                     int child1, int child2);
int buildGraphFromList (Graph &newGraph, Graph &graph0, List<int> &vertList);
void parseForExternalOverCons (Graph &graph0, List<Cluster> *SolverTrees);

#endif // INCLUDE_UTILITY_H
