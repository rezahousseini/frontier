#ifndef INCLUDE_CLUSTER_H
#define INCLUDE_CLUSTER_H

#include <list>
#include <algorithm>

#include "DegValues.h"
#include "Edge.h"
#include "Vertex.h"

class Cluster
{
  private:

    Vertex core;           // core vertex formed by the reduction of all the 
                           // interior vertices in the cluster
    int group;             // group ID is specified by user
    int type;		           // 0 - normal, 1 - external overconst, 2 - internal overconst
    std::vector<int> frontiers;   // list of the frontier edges in the cluster by ID
    std::vector<Edge> innerE;     // list of edges between core and frontiers
    std::vector<Edge> outerE;     // list of edges between frontiers
    std::vector<int> originalV;   // list of vertices corresponding to original graph
    std::vector<std::string> bifurs;   // list of the strings representing the 
                                // bifurcations of this cluster
    int constrain;         // 1--well constrained, 2,3,...--over constrained
    int numBifurs;         // lenght of the list bifurs
    int currBifur;         // the currently selected bifurcation, -1 means no selection
    bool solved;           // true if the cluster has been solved before
    int currDeg;           // the index of the currect set of DegValues;
    std::vector<DegValues> values;// same format and use as in Vertex

  public:

    std::vector<Cluster> children;    // list of children
    int currAlias;         // line segment this cluster is aliasing
    std::vector<int> left;        // list of points incident to the left endpt of alias
    std::vector<int> right;       //  "   "    "        "     "  "  right  "   "   "
    std::vector<int> lines;       // list of lines incident to the alias

    //! Default constructor sets all values to default, note that the default 
    //! value of the degValues[2] is 1 since a zero rotation has a cosine of 1
    Cluster();

    //intializes a cluster in group g
    Cluster(int g) { group=g; }

    //copy constructor
    Cluster(const Cluster &);
    
    void setDepth(int t) { core.setDepth(t);}
    void setType(int t) { type=t; }
    void setName(int n) { core.setName(n); }
    void setGroup(int g) { group=g; }
    void setBifurs(std::vector<std::string>& theBifurs);
    void setCurrBifur(int theNum) { currBifur=theNum; }
    void setCore(Vertex &c) { core=c; }
    void setConst(int c) { constrain=c; }
    void setValue(int index, float value) { values.at(currDeg).setValue(index,value); }
    void setSolved(bool sol) { solved=sol; }
    void setCurrDeg(int i) { currDeg=i; }
    void setDegValues(std::vector<DegValues> theValues) { values=theValues; }

    //! adds a new set of degvalues to this cluster in the case that this 
    //! cluster has multiple parents
    void setToCluster(Cluster &theCluster); 

    //creates a new cluster
    void formCl (Vertex &, std::vector<int> &, std::vector<Edge> &,
                 std::vector<Edge> &, std::vector<int>&);

    void addOrig(int v);
    void deleteOrig(int ver);
    void addFrot (int v);
    void deleteFrot (int ver);
    void makeEmpty(); 

    const Vertex& returnCore() const {  return core; }
    int returnDepth() const {return core.returnDepth();}	
    int returnType() const { return type; }
    int returnName() const {return core.returnName(); }
    int returnGroup() const { return group; }
    int returnConst() const { return constrain; }
    int returnCurrDeg() const { return currDeg; }
    int returnNumDeg() const { return values.size(); }
    int returnNumChildren() const {return children.size();}
    float returnValue(int index) const { return values.at(currDeg).returnValue(index); }
    int returnNumBifurs() const { return numBifurs; }
    int returnCurrBifur() const { return currBifur; }
    std::string        returnCurrBifurString() const { return bifurs.at(currBifur); }
    std::vector<std::string>& returnBifurs() { return bifurs; }
    std::vector<int>&    returnFrontiers() { return frontiers; }
    int           returnFronLen() const { return frontiers.size (); }
    int 	         returnFrontier(int index) const { return frontiers.at(index); }
    std::vector<Edge>&   returnInnerE() { return innerE; }
    int 	         returnInnerELen() const { return innerE.size(); }
    Edge& 	 returnInnerE(int index) { return innerE.at(index); }
    std::vector<Edge>&   returnOuterE() { return outerE; }
    int           returnOuterELen() const { return outerE.size(); }
    Edge&	 returnOuterE(int index) { return outerE.at(index); }
    std::vector<int>&    returnOrig() { return originalV; }
    int           returnOrigV(int index) const { return originalV.at(index); }
    int           returnOrigLen() const { return originalV.size(); }
    bool          isSolved() const { return solved; }

    
    bool empty();
    
    //clusters are equal if they have the same name and are in the same group
    inline bool operator == (const Cluster &clu)
    {
       if(core==clu.core && group==clu.group) return true;
       else return false;
    }

    // = operator
    Cluster& operator = (const Cluster &clu);

    //! stream output
    friend std::ostream& operator <<(std::ostream&, const Cluster&);
};

#endif // INCLUDE_CLUSTER_H
