#include "GraphUpdate.h"


//! rotates the object stored in v0, and rotates using the rotation matrix 
//! stored in theCluster
void 
rotate (Cluster &theCluster, Vertex &v0)
{
  Vertex::Type type;
  float x, y, z, m, x2, y2, x2New, y2New, xNew, yNew, zNew, mNew;
  float sin, cos, p, q, f, siny, cosy, sinz, cosz;

	std::ofstream outf;
//	outf.open("rotate.out", std::ios::app);
	outf << " The beginning..." << std::endl;
	outf << "The cluster is: " << std::endl;
	outf << theCluster << std::endl;
	outf << "The vertex is: " << v0 << std::endl;
	
  type=v0.returnType();
  int v0Name=v0.returnName();

  if (theCluster.returnType() == Vertex::Ray and type==Vertex::Point3D)
    {
	    if (type == Vertex::Point3D)
	      {
	        if(theCluster.left.hasElem(v0Name))
	          {
		          v0.setValues(0,theCluster.returnValue(0));
		          v0.setValues(1,theCluster.returnValue(1));
              v0.setValues(2,theCluster.returnValue(2));
		          return;
	          }		
	        if(theCluster.right.hasElem(v0Name))
	          {
		          v0.setValues(0,theCluster.returnValue(3));
              v0.setValues(1,theCluster.returnValue(4));
              v0.setValues(2,theCluster.returnValue(5));
		          return;
	          }
	      }
    }

    if (theCluster.returnType() == Vertex::Arc and 
        (type == Vertex::Point or type == Vertex::LineSeg))
      {
	      if (type == Vertex::Point)
	        {
	          if (theCluster.left.hasElem(v0Name))
	            {
		            v0.setValues(0,theCluster.returnValue(0));
		            v0.setValues(1,theCluster.returnValue(1));
		            return;
	            }		
	          if(theCluster.right.hasElem(v0Name))
	            {
		            v0.setValues(0,theCluster.returnValue(3));
                v0.setValues(1,theCluster.returnValue(4));
		            return;
	            }
	        }
	      if (type == Vertex::LineSeg)
	        {
		        v0.setValues(0,theCluster.returnValue(0));
            v0.setValues(1,theCluster.returnValue(1));
		        v0.setValues(2,theCluster.returnValue(3));
            v0.setValues(3,theCluster.returnValue(4));
		        return;
	        }
      }

    switch(type)
    {
      case Vertex::Point:
      case Vertex::Circle:   x=v0.returnDegValueByName(0);
                    y=v0.returnDegValueByName(1);
                    p=theCluster.returnValue(0);
                    q=theCluster.returnValue(1);
                    cos=theCluster.returnValue(3);
                    sin=theCluster.returnValue(4);
                    xNew=(x*cos)-(y*sin)+p;
                    yNew=(y*cos)+(x*sin)+q;
                    v0.setValues(0,xNew);
                    v0.setValues(1,yNew);
                    break;
      case Vertex::Line:   x=v0.returnDegValueByName(0);
                    y=v0.returnDegValueByName(1);
                    m=v0.returnDegValueByName(4);
                    x2=x+1.0;
                    y2=y+m;
                    p=theCluster.returnValue(0);
                    q=theCluster.returnValue(1);
                    cos=theCluster.returnValue(3);
                    sin=theCluster.returnValue(4);
                    xNew=(x*cos)-(y*sin)+p;
                    yNew=(y*cos)+(x*sin)+q;
                    x2New=(x2*cos)-(y2*sin)+p;
                    y2New=(y2*cos)+(x2*sin)+q;
                    mNew=(y2New-yNew)/(x2New-xNew);
                    v0.setValues(0,xNew);
                    v0.setValues(1,yNew);
                    v0.setValues(4,mNew);
                    break;
      case Vertex::Ray:
      case Vertex::LineSeg:   x=v0.returnDegValueByName(0);
                    y=v0.returnDegValueByName(1);
	            x2=v0.returnDegValueByName(2);
                    y2=v0.returnDegValueByName(3);
		    p=theCluster.returnValue(0);
                    q=theCluster.returnValue(1);
                    cos=theCluster.returnValue(3);
                    sin=theCluster.returnValue(4);
 		    xNew=(x*cos)-(y*sin)+p;
                    yNew=(y*cos)+(x*sin)+q;
                    x2New=(x2*cos)-(y2*sin)+p;
                    y2New=(y2*cos)+(x2*sin)+q;
		    v0.setValues(0,xNew);
                    v0.setValues(1,yNew);
		    v0.setValues(2,x2New);
                    v0.setValues(3,y2New);
		    break;
      case Vertex::Point3D:   x=v0.returnDegValueByName(0); 
                    y=v0.returnDegValueByName(1);
		    z=v0.returnDegValueByName(2);
		    p=theCluster.returnValue(0);
                    q=theCluster.returnValue(1);
                    f=theCluster.returnValue(2);
                    cos=theCluster.returnValue(3);
                    sin=theCluster.returnValue(4);
                    cosy=theCluster.returnValue(5);
                    siny=theCluster.returnValue(6);
                    cosz=theCluster.returnValue(7);
                    sinz=theCluster.returnValue(8);
		    xNew=(cosy*cosz*x)+(cosy*sinz*y)-(siny*z)+p;
                    yNew=((sin*siny*cosz-cos*sinz)*x)+((cos*cosz+sin*siny*sinz)*y)+(sin*cosy*z)+q;
                    zNew=((sin*sinz+cos*siny*cosz)*x)+((cos*siny*sinz-sin*cosz)*y)+(cos*cosy*z)+f;
    //wrong equations....
//		    xNew=(cosy*cosz*x)-(cosy*sinz*y)+(siny*z)+p;
//                    yNew=((sin*siny*cosz+cos*sinz)*x)+((cos*cosz-sin*siny*sinz)*y)-(sin*cosy*z)+q;
//                    zNew=((sin*sinz-cos*siny*cosz)*x)+((cos*siny*sinz+sin*cosz)*y)+(cos*cosy*z)+f;
     		    outf << "x, y, z = " << x << ", " << y << ", " << z << std::endl;
     		    outf << "p, q, f, cos, sin, cosy, siny, cosz, sinz = " << p << ", " << q << ", " << f << ", " ;
     		    outf << cos <<  ", " << sin << ", " << cosy << ", " << siny << ", " << cosz << ", " << sinz <<
std::endl;  
     		    outf << "xnew, ynew, znew = " << xNew << ", " << yNew << ", " << zNew << std::endl;
                    v0.setValues(0,xNew);
                    v0.setValues(1,yNew);
                    v0.setValues(2,zNew);
		    break; 
      case Vertex::NoClue:
      case Vertex::Cluster: 
      case Vertex::Arc: break;
    }
}


//! recursively determines the position of any object in the given cluster,
//! by rotating it through all the past rotations up from the children
void 
setValueInCluster (Graph &graph0, Cluster &theCluster, Vertex &theVertex, 
                   int location)
{
   int i; 
   int childIndex;

	std::ofstream outf;
//	outf.open("setValueIncluster.out", std::ios::app);
	outf << "location is: " << location << std::endl;
	outf << "The cluster is: " << std::endl;
	outf << theCluster << std::endl;
	outf << "thevertex is: " << theVertex << std::endl;

   if(theCluster.returnName()==theVertex.returnName())
   {
     theVertex=graph0.returnVertByName(theVertex.returnName());
	outf << "in if" << std::endl;
     for(i=0;i<9;i++)
        theVertex.setValues(i,theCluster.returnValue(i));

   }
   else
   {
	outf << "in else" << std::endl;
     childIndex=getChildIndexByName(theCluster, getChildNameWithVertex(theCluster, theVertex.returnName()));
	outf << "childIndex is: " << childIndex << std::endl;
     //theCluster.children.retrieve(childIndex).setToCluster(theCluster);
     setValueInCluster(graph0, theCluster.children.retrieve(childIndex), theVertex, location+1);
	outf  << "after setvalue of location++" << std::endl;
     if(location!=1) rotate(theCluster, theVertex);
	outf  << "after rotate" << std::endl;
   }
	outf << "The END" << std::endl;
}


//! the setValueInCluster method is interpreted to set the value given vertex in the currnet cluster
//! this second method prevents the recursive method from rotating the vertex through the cluster
//! in which its called
void setValueInCluster(Graph &graph0, Cluster &theCluster, Vertex &theVertex)
{
    setValueInCluster(graph0, theCluster, theVertex, 1);
}


//! if the cluster is singleton, sets the values in the corresponding vertex in graph0
//! to the values stored in theCluster, otherwise recursively calls itself on every one 
//! of its children with populateForest
void populateCluster(Graph &graph0, Cluster &theCluster)
{
   int length=theCluster.children.returnLen();
   int name;
   int i;

   if(theCluster.returnOrig().returnLen()==1)
   {
      name=theCluster.returnName();
      for(i=0;i<9;i++)
         setValue(graph0.returnVertByName(name),i,theCluster.returnValue(i));
   }
   if(length>0) populateForest(graph0, theCluster.children);
}


//! calls populate cluster for every cluster in SolverTrees
void populateForest(Graph &graph0, List<Cluster> &SolverTrees)
{
    int i, numTrees;

    numTrees=SolverTrees.returnLen();
    for(i=1; i<=numTrees; i++)
       populateCluster(graph0, SolverTrees.retrieve(i));
}


//! begins the recursion completed in populateForest and PopulateCluster
void populateGraph(Graph &graph0, List<Cluster> &SolverTrees)
{
   populateForest(graph0, SolverTrees);
}


//! updates the graph to contain the degree values stored in the children of
//! theCluster, also performs all necessary rotations to bring the the vertex to
//! the coordinate system of theCluster
void updateGraph(Graph &graph0, Cluster &theCluster)
{
    int i, j, length=theCluster.returnOrigLen();
    int vName, cName;
    float aValue;

	std::ofstream outf;
//	outf.open("updateGraph.out", std::ios::app);
    	outf <<"The beginning, the cluster Being Updating: "<<theCluster.returnName()<<std::endl;
	outf << theCluster << std::endl;

    for(i=1;i<=length;i++)
    {
       vName=theCluster.returnOrigV(i);
	outf << "i = " << i << std::endl;
	outf << "vName = " << vName << std::endl;
       cName=getChildNameWithVertex(theCluster, vName);
	outf << "cName = " << cName << std::endl;
       if(vName==cName)
         for(j=0; j<9; j++)
         {
            aValue=theCluster.children.retrieve(getChildIndexByName(theCluster,cName)).returnValue(j);
		outf << "j = " << j << "aValue = " << aValue << std::endl;
            setValue(graph0.returnVertByName(vName),j,aValue);
		outf << " After setValue" << std::endl;
         }
       else setValueInCluster(graph0, theCluster, graph0.returnVertByName(vName));
	outf << "after setValueInCluster" << std::endl;
    }
}
