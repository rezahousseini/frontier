#ifndef INCLUDE_GETCLUSTER_H
#define INCLUDE_GETCLUSTER_H

#include <ostream>
#include <fstream>

#include "Graph.h"
#include "Cluster.h"

int copyG (Graph &g0, Graph &g1);
bool checkSpecialExtensionCase (Graph &F, std::ostream &out, int nextVerName);
bool canExtend (Graph &F, Graph &graph0, List<Cluster> &DR_Trees, int groupID, 
                List<int> &groupV);
int extension (Graph &F, Graph &graph0, std::ostream &file1, 
               std::ostream &file2, int singleVertex, int nextVerName);
int extension (Graph &F, Graph &graph0, bool firstTime, int groupID,
               std::ostream &file1, std::ostream &file2,
               int singleVertex, int nextVerName);
Cluster* getCluster (Graph &F, Graph &graph0, int nextVerName, 
                     int nextEdgeName);

#endif // INCLUDE_GETCLUSTER_H
