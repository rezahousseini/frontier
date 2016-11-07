#ifndef INCLUDE_MFAALGO_H
#define INCLUDE_MFAALGO_H

#include <ostream>
#include <fstream>

#include "mfa1List.h"
#include "Cluster.h"
#include "Graph.h"
#include "Print.h"
#include "DRTree.h"

List<Cluster>& mfaAlgo (Graph &graph1, List<Cluster> &DRTrees, 
                        std::ostream &file1, std::ostream &file2,
                        int singleVertex, int nextVerName, int nextEdgeName);

#endif // INCLUDE_MFAALGO_H
