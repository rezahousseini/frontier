#ifndef INCLUDE_DRTREE_H
#define INCLUDE_DRTREE_H

#include <fstream>

#include "mfa1List.h"
#include "Cluster.h"
#include "Graph.h"
#include "Print.h"
#include "GetCluster.h"
#include "Distribution.h"
#include "Utility.h"
#include "Equation.h"

void defrostTree (Cluster &DR_Tree, Graph &F);
void defrostForest (List<Cluster> & DR_Trees, Graph &F);
Cluster &popMinDepth (List<Cluster> &DR_Trees, int nextVerName);
Cluster &popMaxDepth (List<Cluster> &DR_Trees);
Cluster& distributeTree (Cluster &aDRtree, Graph &F, Graph &graph0, 
                         std::ostream &file1, std::ostream &file2, 
                         int indentation, int singleVertex, int nextVerName,
                         int nextEdgeName);
void explicitChild (Cluster &newTree, List<int> &nameList, 
                    List<Cluster> &forest);
int getClusterType (Graph &graph0, Cluster &theCluster);
bool specialCluster (Graph &graph0, Cluster cl);
bool canCombine (Cluster &c, Cluster &cl0, Graph &F, Graph &graph0, 
                 int singleVertex, int nextVerName, int nextEdgeName);
void implicitChild (Cluster &newTree, List<int> &nameList, 
                    List<Cluster> &forest, Graph &F, Graph &graph0, 
                    int singleVertex, int nextVertName, int nextEdgeName);
void addChild (Cluster &newTree, List<Cluster> &popedTrees,
               List<Cluster> &DR_Trees, Graph &F, Graph &graph0,
               int singleVertex, int nextVerName, int nextEdgeName);
int checkClusterForBananas (Graph &graph0, Cluster &theCluster);
void setAlias (Graph &graph0, Cluster &theCluster);
bool isDense (Cluster &C1, Cluster &C2, Graph &graph0);
void pseudoAppendChild (Cluster &theCluster, Cluster &newCluster);
void pseudoMinDense (Cluster &theCluster, Graph &graph0);
bool canMerge (Graph &graph0, Cluster &child1, Cluster &child2, 
               int singleVertex, int nextVerName, int nextEdgeName);
void mergeCluster (Graph &graph0, int coreName, Cluster &parent, Cluster child1,
                   Cluster child2);
void changeDepth (Cluster &newC);
int modifyTree (Graph &graph0, Cluster &newC, int singelVertex, 
                int nextVerName, int nextEdgeName);
int setConstrain (Graph &G, Cluster &theCluster);
List<Cluster>& distributeForest (List<Cluster> &DR_Trees, Graph &F, 
                                 Graph &graph0, std::ostream &file1, 
                                 std::ostream &file2, int groupID, 
                                 int indentation, int singleVertex,
                                 int nextVerName, int nextEdgeName);
void getTrivial (List<Cluster> &DRTrees, Graph &graph0, int singleVertex, 
                 int nextVerName);

#endif // INCLUDE_DRTREE_H
