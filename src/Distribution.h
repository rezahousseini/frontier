#ifndef INCLUDE_DISTRIBUTION_H
#define INCLUDE_DISTRIBUTION_H

#include <fstream>

#include "Graph.h"
#include "Cluster.h"
#include "Edge.h"
#include "GetCluster.h"

bool specialPushCase (Graph &graph0, Cluster &C);
void copyLabel (Graph &g0, Graph &g1);
void delInnerVer (Graph &F, Graph &graph0);
int distributEdge (Edge &edge, Graph &F, std::ostream &file2);
int removeFlow (Cluster &C, Graph &F, Graph &graph0);
int pushOutside (Cluster &C, Graph &F, Graph &graph0, std::ostream &file1, 
                 std::ostream &file2, int nextVerName);
int pushOutside0 (Graph &F, std::ostream &file2, int nextVerName);
Cluster* distributeVert (Vertex &v1, Graph &F, Graph &graph0, 
                         std::ostream &file1, std::ostream &file2, 
                         int singleVertex, int nextVerName, int nextEdgeName);
Cluster& distributeCl (Cluster &C, Graph &F, Graph &graph0, 
                       std::ostream &file1, std::ostream &file2, 
                       int singleVertex, int nextVerName, int nextEdgeName);

#endif // INCLUDE_DISTRIBUTION_H
