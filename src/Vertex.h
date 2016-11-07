#ifndef INCLUDE_VERTEX_H
#define INCLUDE_VERTEX_H

#include <ostream>
#include <vector>
#include <algorithm>


class Vertex
{
  private:
    int name;           // unique object ID
    
    int weight;         // degree of freedom
    float degValues[9]; // solved values of this object
    int freeDegs[9];    // if freeDegs[i]=0, solver can change degValues[i]
                        // if freeDegs[i]=1, degValues[i] is changed by solver
                        // if freeDegs[i]=-1, degValues[i] is fixed by user
                        // if freeDegs[i]=-2, degValues[i] is NA(Not Applicable) or not defined
     

     //Table shows the different types of degrees of freedom used for each object type and
     //the degvalue location where it is stored
     /****************************************************************************\
     *              point line   Ray   LineSeg circle  arc      cluster  point3D  *
     *  degValue[0]   x    x1     x1     x1      x      x        x-sft      x     *
     *  degValue[1]   y    y1     y1     y1      y      y        y-sft      y     *
     *  degValue[2]   -    x2     x2     x2      r      r        z-sft      z     *
     *  degValue[3]   -    y2     y2     y2      -    angle    rotx-cos     -     *
     *  degValue[4]   -  slope   cos   slope     -  start_cos  rotx-sin     -     *
     *  degValue[5]   -          sin   length    -  start_sin  roty-cos     -     *
     *  degValue[6]   -    -      -      -       -   end_cos   roty-sin     -     *
     *  degValue[7]   -    -      -      -       -   end_sin   rotz-cos     -     *
     *  degValue[8]   -    -      -      -       -      -      rotz-sin     -     *
     \****************************************************************************/

    std::vector<int> incid;  // List of the ID's of the inicident edges
    int nIncid;       // number of incident edges
    int label;        // 0 or 1 used for augmenting path
    int scan;         // 0 or 1 used for augmenting path
    int frozen;       // If frozen=1, we don't distribute; If frozen=2, frozen forever
    int posFlow;      // possible flow that could be delivered to this vertex
    int existFlow;    // flow already absorbed by this vertex
    int predEdge;     // predecessor edge in the augmenting path
    int depth;        // depth==0 for original vertex
    bool ignore;      // when true vertex is ignored with output from solver

    //prevent automatic conversion for any other built-in types such as bool, int, etc
    template<typename T> operator T () const;

  public:

    enum Type
    {
      Cluster = -1,
      Point   =  0, 
      Line    =  1, 
      Ray     =  2, 
      LineSeg =  3, 
      Circle  =  4, 
      Arc     =  5, 
      Point3D =  6,
      NoClue  =  7
    };
    Type type;           // point=0,line=1,ray=2,LSeg=3,circle=4,arc=5,
                         // cluster=-1,point3D=6
    std::vector<int> leftEndIncid; //!< points with incidence constraints on the left 
                            //!< end of the line segment
    std::vector<int> rightEndIncid; //!< points with incidence constraints on the right
                             //!< end of the line segment

    //Constructors
    
    //! default initializes all values to zero
    Vertex();

    //! sets the ID of vertex to theName, and theType to theType
    Vertex(int theName, Type theType);

    //! copy constructor
    Vertex(const Vertex &);

    void setName(int nm) { name=nm; }
    void setType(Type tp) { type=tp; }
    void setWeight(int wt) { weight=wt; }
    void setPosFlow(int fl) { posFlow=fl; }
    void setEstFlow(int fl) { existFlow=fl; }
    void setPredEdg(int e) { predEdge=e; }
    void setDepth(int d) { depth=d; }
    void setIgnore(bool t) { ignore=t; }
    void notDefinedValue(int ix) { freeDegs[ix]=-2; }
    void initialValue(int ix, float value, int free);
    bool setValues(int ix, float value);
    void appendIncid(int edge_name);
    void setLabel(int lb) { label=lb; }
    void setScan(int sc) { scan=sc; }
    void freeze() { if(frozen==0) frozen=1; } // can be defrosted
    void freezeForever() { frozen=2; }        // can't be defrosted
    void incrsWt(int wt) { weight=weight+wt; }
    void incrsEstFlow(int fl) { existFlow=existFlow+fl; }
    void incrsPosFlow(int fl) { posFlow=posFlow+fl; }
    void delIncid(int e);
    void defrost() { if(frozen==1) frozen=0; }  // if frozen=2, it can't be defrosted
    void unFrozen() {frozen=0;}
    int returnName() const { return name; }
    Type returnType() const { return type; }
    int returnWeight() const { return weight; }
    bool returnIgnore() const { return ignore; }
    bool hasFreeDeg();
    int returnFreeDegs(int index) const { return freeDegs[index]; }
    float returnDegValueByName(int index) const { return degValues[index]; }
    int returnIncid(int index) const { return incid.at(index); }
    std::vector<int>& returnIncid() {return incid;}
    int numIncid() const { return nIncid; }
    bool hasIncid(int e);
    int returnLabel() const { return label; }
    int returnScan() const { return scan; }
    int isFrozen() const { return frozen; }
    int returnEstFlow() const { return existFlow; }
    int returnPosFlow() const { return posFlow; }
    int returnPredEdg() const { return predEdge; }
    int returnDepth() const { return depth; }
    
    //overridden = operator
    Vertex & operator = (const Vertex &ver);

    //! two vertices are equal if they have the same name and weight
    inline bool operator == (const Vertex &v) {
       if(name==v.name&&weight==v.weight) return true;
       else return false;
    }

    //! stream output
    friend std::ostream& operator <<(std::ostream&, const Vertex&);
};

#endif // INCLUDE_VERTEX_H
