#ifndef INCLUDE_EQUATION_H
#define INCLUDE_EQUATION_H

#include <string>
#include <fstream>

#include "Vertex.h"
#include "Edge.h"
#include "Cluster.h"
#include "Graph.h"
#include "GraphUpdate.h"
#include "StringFunction.h"
#include "Utility.h"
#include "Print.h"
#include "MFAAlgo.h"

struct VUsed
{
  int vName;
  List<int> usedChild;
};

//Equation Generators
std::string getDistanceEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                           std::string theDist, List<std::string>& vars);
std::string getTangencyEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                           List<std::string>& vars);
std::string getIncidenceEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                            List<std::string>& vars);
std::string getAngleEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                        List<std::string>& vars);
std::string getAngle3DEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                          List<std::string>& vars);
std::string getParallelEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                           List<std::string>& vars);
std::string getPerpendicularEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                                List<std::string>& vars);
std::string getDistance3DEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                             std::string theDist, List<std::string>& vars);
int getEdgeCode (Edge &theEdge, Cluster &theCluster);
int getEdgeCode (Edge &theEdge, Cluster &theCluster, int ch1, int ch2);
int getEdgeCodeDRPlanner (Edge &theEdge, Cluster &theCluster);
std::string switchString (Vertex &theVertex, Vertex::Type type, int shapeName, 
                          int clusterName, std::string toReplace, 
                          bool solveOrValue, List<std::string>& vars,
                          int graphDimen);
std::string getEquationBetweenClusters (Graph& graph0, Edge &theEdge, 
                                        Cluster &theCluster, 
                                        List<std::string>& vars,
                                        List<Edge>& theImags,
                                        int withHeldCluster,
                                        int graphDimen);
std::string getEquationInCluster (Graph& graph0, Edge &theEdge, 
                                  Cluster &theCluster, List<std::string>& vars,
                                  List<Edge>& theImags);
std::string getEquation (Graph &graph0, Edge &theEdge, Cluster &theCluster, 
                         List<std::string>& vars, List<Edge> theImags,
                         int withHeldCluster, int graphDimen);
std::string getSinCosConstraint (List<std::string>& vars);
std::string getOverlapConstraint (Graph &graph0, Cluster &theCluster, 
                                  int totalExtra, List<std::string>& vars, 
                                  int equationCount, int withHeldCluster,
                                  int aOverlap, int singleVertex,
                                  int nextVerName, int nextEdgeName);
std::string getLineConstraint (Graph &graph0, List<Cluster> &theChildren, 
                               List<std::string>& vars, int equationCount);
std::string getOriginEquations (Edge &theEdge, Edge &theEdge2, Graph &graph0, 
                                int clusterName, int clusterType, 
                                std::string varsToZero);
std::string getRotationEquations (Cluster &theCluster, List<std::string>& vars, 
                                  int equationCount, int withHeldCluster);
void minusString (std::string & str, int ID1, int ID2);
int isValidSecond (Graph& graph0, int ID1, int ID2, std::string outputString, 
                   int& temp);
void verifyOrigsets (Graph &graph0, int &n1, int &n2, int &n3);
void setPartDof (int needEqNum, int numEqPair, Cluster &theCluster, 
                 int PartMaxDof[], int extraNum[]);
int getExtraNum (Graph &graph0, Cluster &theCluster, List<int> &overlappedList, 
                 int ch1, int ch2);
std::string getPartOverEquation (Graph &graph0, Cluster &theCluster, 
                                 List<VUsed> &vUsedList, int child1, int child2,
                                 int totalDof, List<std::string>& vars, 
                                 int equationCount, int withHeldCluster,
                                 int aOverlap, int singleVertex,
                                 int nextVerName, int nextEdgeName);
void addUsedChildren (int vName, int child1, int child2, 
                      List<VUsed> &vUsedList);
std::string getSpecialCaseEquations (Graph &graph0, Cluster &theCluster, 
                                     int caseInt, std::string &outputString);
int countEdges (Graph &graph0, Cluster &theCluster);
ClustData& summCluster (Graph &graph0, Cluster &theCluster);
Cluster createSP2Cluster(Graph &newGraph);
Cluster createSPCluster(Graph &newGraph);
bool isImaginary(Graph &graph0, Edge &theEdge);

#endif // INCLUDE_EQUATION_H
