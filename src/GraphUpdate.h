#ifndef INCLUDE_GRAPHUPDATE_H
#define INCLUDE_GRAPHUPDATE_H

#include <fstream>

#include "Graph.h"
#include "Cluster.h"
#include "mfa1List.h"
#include "Vertex.h"
#include "Utility.h"

//Graph Update Functions
void rotate(Cluster &theCluster, Vertex &v0);
void setValueInCluster (Graph &graph0, Cluster &theCluster, Vertex &theVertex, 
                        int location);
void setValueInCluster(Graph &graph0, Cluster &theCluster, Vertex &theVertex);
void populateCluster(Graph &graph0, Cluster &theCluster);
void populateForest(Graph &graph0, List<Cluster> &SolverTrees);
void populateGraph(Graph &graph0, List<Cluster> &SolverTrees);
void updateGraph(Graph &graph0, Cluster &theCluster);

#endif // INCLUDE_GRAPHUPDATE_H
