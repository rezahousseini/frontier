#ifndef INCLUDE_GRAPH_H
#define INCLUDE_GRAPH_H

#include <ostream>
#include <iostream>
#include <random>
#include <algorithm>

#include "Edge.h"
#include "Vertex.h"


class Graph
{
  private:
    int dimension;  		// dimension=2 or 3
    int NumVert;   	 	// # of vertices
    int NumEdge;    		// # of edges 
    int depth;      		// depth of the largest cluster in the graph
    List<Vertex> vertices;	// list of the vertices in the graph
    List<Edge> edges;		// list of the edges in the graph

    //see separate pseudocode and paper documentation of explanation
    void augment(Vertex *, Edge *);

  public:

    //! constructor
    Graph();

    void setDimen(int dimen) { dimension=dimen; }
    void setDepth(int d) { depth=d; }
    void setVlist(List<Vertex> &vl);
    void setElist(List<Edge> &el);
    
    //! merge multi-edges and remove zero-weight edges
    void simplify();

    //! freeze all vertices
    void freeze();

    //! defrost vertices if any of them are frozen
    void defrostGraph();

    //! freeze the vertex with ID vName forever (set frozen to 2) 
    void freezeVertForever(int vName);
    
    //! defrost the vertex with ID vName
    void defrostOneVert(int vName);


    void appendVertex(Vertex &ver);
    void appendEdge(Edge &edg);

    void delAllVer();
    void delAllEdg();
    void makeEmpty();
    void delVer(Vertex &v);
    void delEdg(Edge &e);
 
    //! find vertex by ID and remover from vertex list
    void delVerByName(int vName);
    //! find edge by ID and remover from edge list
    void delEdgeByName(int eName);

    //! true if the graph has a vertex with the given name
    bool hasEdge(int eName);
    //! true if the graph has an edge with the given name
    bool hasVert(int vName);


    int returnDimen() { return dimension; }
    int returnNumVer() { return NumVert; }
    int returnNumEdg() { return NumEdge; }
    int returnDepth() { return depth; }

    //! returns the number of labeled edges in the graph
    int numLabeled();

    List<Vertex> & returnVlist() { return vertices; }
    List<Edge>   & returnElist() { return edges; }

    Vertex & returnVertByIndex(int i) { return vertices.retrieve(i); }
    Edge   & returnEdgeByIndex(int i) { return edges.retrieve(i); }
    Vertex & returnVertByName(int vName);
    Edge   & returnEdgeByName(int eName);
    Edge   & returnEdgeByEnds(int v1, int v2);


    //! returns a vertex with the given ID
    Vertex * VertAddr(int vName);
    //! returns an edge with the given ID
    Edge   * EdgeAddr(int eName);

    // reads data from the arrays sent by the sketcher
    // from sketch to graph 
    //int sketchInput(int &idx, jint *inputData, int &indxDbl, jdouble *dbleData); 

    //! used for testing generates a random graph
    void randomGraph();

    //! stream output
    friend std::ostream& operator <<(std::ostream&, const Graph&);

    //! set all of the labels in both the edges and the vertices to the 
    //! unlabeled state, 0
    void removeLabels();

    //! returns the flow on an edge back to undistributed flow on vertices
    void restoreFlow(Edge *edgep);

    //! see the attached paper for complete documentation
    int distribute0(Edge &edge, std::ostream &file2);
    
    //! returns the difference between the total weight of the edges and the 
    //! weight of the vertices less the number of degrees of freedom of a rigid 
    //! object in space, 2D = 3, 3D = 6
    int constrainDegree();
};

#endif // INCLUDE_GRAPH_H
