//! \file Utility.cpp

#include "Utility.h"

//! returns the distance between (x1,y1) and (x2,y2)
float 
getDistance(float x1, float y1, float x2, float y2)
{
  return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}


//! returns the angle from (x1,y1) to (x2,y2)
float
getAngle (float x1, float y1, float x2, float y2)
{
  float cos1, sin1;

  sin1=(y2-y1)/getDistance(x1,y1,x2,y2);
  cos1=(x2-x1)/getDistance(x1,y1,x2,y2);

  if((sin1>=0 && cos1>=0) || (sin1>=0 && cos1<0)) return acos(cos1);
  if(sin1<0 && cos1<=0) return 2*M_PI-acos(cos1);
  return 2*M_PI+asin(sin1);
}


//! returns the angle that correspones to a given sine and cosine value
float
getAngle (float theCos, float theSin)
{
  if((theSin>=0 && theCos>=0) || (theSin>=0 && theCos<0)) return acos(theCos);
  if(theSin<0 && theCos<=0) return 2*M_PI-acos(theCos);
  return 2*M_PI+asin(theSin);
}


//! for the given cluster, returns the index of its first child with the name vName,
//! it no such child exists returns -1
int 
getChildIndexByName (Cluster &theCluster, int vName)
{
  int i, length;

  length=theCluster.children.returnLen();
  for(i=1;i<=length;i++)
    if(theCluster.children.retrieve(i).returnName()==vName) return i;

  return -1;
}


//! returns the ID of the first immediate child of theCluster to contain the 
//! given original vertex ID theV
int 
getChildNameWithVertex (Cluster &theCluster, int theV)
{
  int length, i;
  List<int> theOrig;

  length=theCluster.children.returnLen();

  for(i=1;i<=length;i++)
    {
      if(inOriginalV(theV,theCluster.children.retrieve(i)))
        return theCluster.children.retrieve(i).returnName();

    }
  return -1;
}


//! returns true if Name is a clild of theCluster
bool 
inOriginalV (int Name, Cluster &theCluster)
{
  List<int> theOrig;

  theOrig=theCluster.returnOrig();

  if (theOrig.hasElem(Name)) return true;

  return false;
}


//! assigns a given value to a freedeg in Vertex
void 
setValue (Vertex &theVertex, int index, float theValue)
{
  theVertex.setValues(index, theValue);
}


//! returns in theList, the names of all the children in theCluster that contain
//! vName as an original Vertex
void 
getContainedChildList (Cluster &theCluster, int vName, List<int> &theList)
{
  List<int> output;
  int i, length;

  theList.makeEmpty();
  length=theCluster.children.returnLen();
  for(i=1; i<=length; i++)
    if(inOriginalV(vName, theCluster.children.retrieve(i)))
      theList.append(theCluster.children.retrieve(i).returnName());
}


//! within the child of theCluster named ID, sets the indexth solved value to 
//! setValue
void 
setValue (Cluster &theCluster, int ID, float theValue, int index)
{
  int i=1;

  while(theCluster.children.retrieve(i).returnName()!=ID) i++;

  theCluster.children.retrieve(i).setValue(index, theValue);

  std::cout<<"Set Value in Cluster "<<ID<<std::endl;
  std::cout<<"with value "<<theValue<<" at index "<<index<<std::endl;
}


//! given the letter in a variable name returns the index of the freedom value
//! it corresponds to (a given type of value is always stored in the same index,
//! see chart in mfa2Clas.h
int 
getFreeDegIndex (char keyChar, Vertex &theVertex)
{
  int out;

  if(theVertex.returnType() == Vertex::Point3D)
  	switch(keyChar)
      {
        case 'p':
        case 'x': out=0;
                  break;
        case 'q':
        case 'y': out=1;
                  break;
        case 'r':
        case 'f':
        case 'z': out=2;
                  break;
        case 'c':
        case 'g':
        case 't': out=3;
                  break;
        case 'v':
        case 'm':
        case 's':
        case 'd': out=4;
                  break;
	      case 'e':
        case 'w':
        case 'l':
        case 'h': out=5;
                  break;
        case 'a':
        case 'j': out=6;
                  break;
        case 'b':
        case 'k': out=7;
                  break;
        case 'n': out=8;
                  break;
      }
  else
    switch(keyChar)
      {
	 	    case 'p':
	      case 'x': out=0;
            	    break;
        case 'q':
	      case 'y': out=1;
                  break;
	      case 'c':
        case 'r': 
	      case 'f': out=2;
            	    break;
	      case 'd':
        case 'g':
		    case 't': out=3;
             	    break;
	      case 'v':
	      case 'm': 
        case 's': out=4;
                  break;
	      case 'w':
        case 'l': 
		    case 'h': out=5;
                  break;
	      case 'a': 
		    case 'j': out=6;
            	    break;
	      case 'b':
        case 'k': out=7;
             	    break;
	      case 'n': out=8;
			            break;
      }
          
  return out;
}


//! resets the fin state of all of the cluster in the DRTree above theCluster
bool
resetFinByClusterName (Cluster &theCluster, int name)
{
  int i, length;
  bool anyChild=theCluster.isSolved();

  if(theCluster.returnName()==name)
    {
	    theCluster.setSolved(false);
	    return false;
    }

  length=theCluster.children.returnLen();

  for(i=1;i<=length;i++)
	  anyChild=resetFinByClusterName(theCluster.children.retrieve(i),name) && anyChild;

  theCluster.setSolved(anyChild);
  return anyChild;
}


//! resets the DRTrees datastructure to contain only the original vertices in 
//! the graph this method is used right before calling the DRPlanner to force 
//! it to recalculate the entire tree
void 
resetTrees (Graph &graph0, List<Cluster> &SolverTrees)
{
  int i, length;
  Cluster newCluster;
  List<Edge> innerE, outerE;
  List<int> frontiers, originalV;
  Vertex core;
  int coreName;

  SolverTrees.makeEmpty();

  length=graph0.returnNumVer();
  
  for(i=1;i<=length;i++)
    {
      core=graph0.returnVertByIndex(i);
      coreName=core.returnName();
      core.defrost();
      graph0.defrostOneVert(coreName);
      frontiers.append(coreName);
      originalV.append(coreName);
      newCluster.formCl(core, frontiers, innerE, outerE, originalV);
      SolverTrees.append(newCluster);
      frontiers.makeEmpty();
      originalV.makeEmpty();
    }

  //singleVertex=length+4; //??
}


//! sets the longest distance constraint in the cluster to .000001 less than 
//! before, this tricks maple to returning some numerical solutions that it 
//! otherwise would not with exact values
void 
setValueReduction (Graph &graph0, Cluster &theCluster)
{
  int i, length=graph0.returnNumEdg();
  int end1, end2, type;
  Edge* tempEdge;
  int longestDistIndex=-1;
  float longestDist=-1.0, value;
  bool in1, in2;

  for(i=1;i<=length;i++)
    {
      if(!graph0.hasEdge(i)) continue;
      tempEdge=graph0.EdgeAddr(i);
      end1=tempEdge->returnEnd1();
      end2=tempEdge->returnEnd2();    
      type=tempEdge->returnType();
      value=tempEdge->returnValue();
      in1=inOriginalV(end1, theCluster);
      in2=inOriginalV(end2, theCluster);
      std::cout<<"end1: "<<end1<<" end2: "<<end2<<" type: "<<type<<" in1: "
          <<in1<<" in2: "<<in2<<" value: "<<value<<std::endl;
      if(in1 && in2 && (type==0 || type==6) && value>longestDist)
        {
          longestDistIndex=i;
          longestDist=value;
        }
    }
  std::cout<<"longestIndex: "<<longestDistIndex<<std::endl;
  if(longestDistIndex>0)
    {
      tempEdge=graph0.EdgeAddr(longestDistIndex);
      tempEdge->setValue(longestDist-0.000001);
    }
}


//! as fixTrees but for clusters
void
fixCluster (Cluster &theCluster)
{
  Vertex theCore;
  int i, length, coreName;

  theCore=theCluster.returnCore();
  coreName=theCore.returnName();

  if(coreName==0) return;

  if(theCore.returnDepth()==0)
    {
      length=theCluster.returnOrigLen();
      for(i=1;i<=length;i++)
        if(theCluster.returnOrigV(i)!=coreName)
          theCluster.deleteOrig(theCluster.returnOrigV(i));
    }
  else fixTree(theCluster.children);
}


//! eliminates extra vertex in frontiers latent after DRPlanner
void
fixTree (List<Cluster> &SolverTrees)
{
  int i, length;

  length=SolverTrees.returnLen();

  for(i=1;i<=length;i++)
    fixCluster(SolverTrees.retrieve(i));
}


////! formats the input string so that it can be taken as an input M-file in 
////! Matlab
//std::string
//processMatlab (std::string input)
//{
//  input=input.erase(0,46);
//	input=input.erase(input.find("}"));
//	input=replaceAll(input, ",", ";\n");
//	input=replaceAll(input, "=", "-");
//	input=input+";";
//
//	std::string temp="";
//	std::string backup=varsToZero;
//
//	bool everFull=false;
//
//	while(varsToZero!="")
//	  {
//		  everFull=true;
//		  temp=varsToZero.substr(0,2);
//		  varsToZero=varsToZero.erase(0,2);
//		  input=replaceAll(input, temp, "0");
//		  vars.deleteElem(temp);
//	  }
//
//	varsToZero=backup;
//	
//	int i, len;
//	len=vars.returnLen();
//	for(i=1;i<=len;i++)
//	  {
//		  temp="X("+toString(i)+")";
//		  input=replaceAll(input, vars.retrieve(i),temp);
//	  }
//
//	input=replaceAll(input,"\n0-0;","");
//	
//	int length=input.size();
//	input=input.insert(0,"F(#)=");
//	int count=0;
//	input=replaceAll(input,";\n",";\nF(#)=");
//	
//	int pos=0;
//	count=1;
//	pos=input.find("#");
//	while(pos>=0)
//	  {
//		  input.insert(pos,toString(count));
//		  count++;
//		  input.erase(pos+1,1);
//		  pos=input.find("#");
//	  }
//
//	input="F=zeros("+toString(vars.returnLen())+",1);\n"+input;
//	input="function F = dplanFun(X)\n\n"+input;
//
//  return input;
//}
//
////! Post process function after calling processMatlab
//void
//postProcessMatlab ()
//{
//	std::ifstream input;
//	std::ofstream output;
//	
//	input.open("data.out");
//	output.open("output.txt");
//
//	output<<">>>>>{";
//	
//	int i, length=vars.returnLen();
//	float indata;
//
//	for(i=0;i<length;i++)
//	  {
//		  input>>indata;
//		  if(i!=0) output<<", ";
//		  output<<vars.retrieve(i)<<" = "<<indata;
//	  } 
//
//	std::string temp;
//
//	while(varsToZero!="")
//    {
//      temp=varsToZero.substr(0,2);
//      varsToZero=varsToZero.erase(0,2);
//		  output<<", "<<temp<<" = 0.0";
//    }	
//
//	output<<"}q";
//	
//	input.close();
//	output.close();
//}


float
findDist (Graph &graph0, Cluster &theCluster)
{
	int i, length=graph0.returnNumEdg();
	Edge tempEdge;

	for(i=1;i<=length;i++)
	  {
		  tempEdge=graph0.returnEdgeByIndex(i);
		  if(!inOriginalV(tempEdge.returnEnd1(),theCluster)
         || !inOriginalV(tempEdge.returnEnd2(),theCluster))
			  continue;

		  if(tempEdge.returnType()==6 || tempEdge.returnType()==0)
			  return tempEdge.returnValue();
	  }

	return 0;
}


void 
getOverlapList (Graph graph0, Cluster &theCluster, List<int> &outputList, 
                int child1, int child2)
{
  List<int> containedList;

  int i,currOrig;

  outputList.makeEmpty();

  for(i=1;i<=theCluster.returnOrigLen();i++)
    {
	    containedList.makeEmpty();
  	  currOrig=theCluster.returnOrigV(i);
  	  getContainedChildList(theCluster,currOrig,containedList);
	    if(containedList.returnLen()>=2)
	      {
		      if(child1==0 && child2==0)
			      outputList.append(currOrig);		 
		      else 
		        {
			        int child1Name = theCluster.children.retrieve(child1).returnName();
			        int child2Name = theCluster.children.retrieve(child2).returnName();
			        if(containedList.hasElem(child1Name) && 
                 containedList.hasElem(child2Name))
				        outputList.append(currOrig);
		        }
	      }
    }
  //check the incident part
  for(i=1; i<=theCluster.returnOrigLen(); i++)
    {
	    int v1 = theCluster.returnOrig().retrieve(i);
      if(!outputList.hasElem(v1))
	      {
		      for(int j=1; j<=outputList.returnLen(); j++)
		        {
			        int v2 = outputList.retrieve(j);
			        std::cout << "LLOOOO" << graph0.returnEdgeByEnds(v1, v2) 
                        << std::endl;
			        if(graph0.returnEdgeByEnds(v1, v2).returnType()==1)
				        outputList.append(v1);
		        }
	      }
    }
}


int
buildGraphFromList (Graph &newGraph, Graph &graph0, List<int> &vertList)
{
	newGraph.makeEmpty();
	int weight = 0;
	int i;
	Vertex v;
	
  std::cout << graph0 << std::endl;

	for(i=1;i<=vertList.returnLen();i++)
	  {
		  v = graph0.returnVertByName(vertList.retrieve(i));
		  newGraph.appendVertex(v);
		  weight += v.returnWeight();
	  }

	Edge tempEdge;
	int end1, end2;

	for(i=1;i<=graph0.returnNumEdg();i++)
	  {
		  tempEdge=graph0.returnEdgeByIndex(i);
		  end1=tempEdge.returnEnd1();
		  end2=tempEdge.returnEnd2();

		  if(!vertList.hasElem(end1)) continue;
		  if(!vertList.hasElem(end2)) continue; 

		  newGraph.appendEdge(tempEdge);
		  weight -= tempEdge.returnWeight();
	  }

  std::cout << newGraph << std::endl;
	return weight;
}


void
parseForExternalOverCons (Graph &graph0, List<Cluster> *SolverTrees)
{
	int i, length;
	Cluster currClust;

	length=SolverTrees->returnLen();

	for(i=length;i>=1;i--)
	  {
		  currClust=SolverTrees->retrieve(i);
		  if(currClust.returnType()==Vertex::Ray)
		    {
		  	  Vertex* theLS;
		  	  int origName;

		  	  for(int j=1;j<=currClust.children.returnLen();j++)
		  	    {
		  	  	  theLS=graph0.VertAddr(currClust.children.retrieve(j).returnName());
		  	    }


		  	  for(int j=currClust.children.returnLen();j>=1;j--)
		  	    {
		  	  	  origName=currClust.children.retrieve(j).returnOrigV(1);
		  	  	  Vertex tempVert=graph0.returnVertByName(origName);

		  	  	  if(tempVert.returnType()==Vertex::Point3D);
		  	  	    {
		  	  		    Edge tempEdge=graph0.returnEdgeByEnds(theLS->returnName(),origName);
		  	  		    if(tempEdge.returnName()==0) continue;
		  	  		    if(tempEdge.returnEnd1()==theLS->returnName())
		  	  	        {
		  	  			      std::cout<<"LS is end1"<<std::endl;
		  	  			      if(tempEdge.returnPart1()==1)
		  	  			        {
		  	  				        std::cout<<"Part 1 is 1"<<std::endl;
		  	  				        SolverTrees->addrByIndex(i)->setValue(6,origName);
		  	  			        }
		  	  			      else	
		  	  			        {
		  	  				        std::cout<<"Part 1 is 2"<<std::endl;
		  	  				        SolverTrees->addrByIndex(i)->setValue(7,origName);
		  	  			        }
		  	  		      }
		  	  		    else
		  	  		      {
		  	  			      std::cout<<"LS is end2"<<std::endl;
		  	  			      if(tempEdge.returnPart2()==1)
		  	  			        {
		  	  				        std::cout<<"Part 2 is 1"<<std::endl;
		  	  				        SolverTrees->addrByIndex(i)->setValue(6,origName);
		  	  			        }
                      else
		  	  			        {	
		  	  				        std::cout<<"Part 2 is 2"<<std::endl;
		  	  				        SolverTrees->addrByIndex(i)->setValue(7,origName);
		  	  			        }
		  	  		      }
		  	  	    }
            }
		    }
		  else 
        parseForExternalOverCons(graph0, &(SolverTrees->retrieve(i).children));
	  }
}
