#ifndef INCLUDE_PRINT_H
#define INCLUDE_PRINT_H

#include <ostream>
#include <fstream>

#include "Cluster.h"
#include "mfa1List.h"
#include "Graph.h"

void printTree(Cluster &DR_Tree, std::ostream &os, int indent);
void printForest(List<Cluster> & DR_Trees, std::ostream &os, int indent);
void print(Graph &graph0, List<Cluster> &SolverTrees);
void print(Graph &graph0, Cluster &theCluster);
void printBifurcations(Cluster &theCluster, std::ofstream &outf);

#endif // INCLUDE_PRINT_H
