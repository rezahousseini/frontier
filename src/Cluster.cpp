#include "Cluster.h"

Cluster::Cluster()
{
  DegValues first;

  first.setValue(3,1.0);
	first.setValue(5,1.0);
	first.setValue(8,1.0);
  group=0;
	type=0;
  constrain=0;
  currBifur=-1;
  numBifurs=0;
  solved=false;
  currDeg=1;
  values.push_back(first);
	currAlias=-1;
	left.clear();
	right.clear();
	lines.clear();
}


Cluster::Cluster(const Cluster &clu)
{
  core=clu.core;
  group=clu.group;
	type=clu.type;
  frontiers=clu.frontiers;
  innerE=clu.innerE;
  outerE=clu.outerE;
  originalV=clu.originalV;
  children=clu.children;
  bifurs=clu.bifurs;
  currBifur=clu.currBifur;
  numBifurs=clu.numBifurs;
  constrain=clu.constrain;
  solved=clu.solved;
  values=clu.values;
	currAlias=clu.currAlias;
	left=clu.left;
	right=clu.right;
	lines=clu.lines;
}


void 
Cluster::addFrot (int v) 
{ 
  if (std::find(frontiers.begin(), frontiers.end(), v) == frontiers.end())
    frontiers.push_back (v);
}


void 
Cluster::deleteFrot (int ver) 
{
  auto it = std::remove(frontiers.begin(), frontiers.end(), ver);
  frontiers.erase (it, frontiers.end());
}


void
Cluster::setBifurs (std::vector<std::string>& theBifurs)
{ 
  bifurs=theBifurs; 
  numBifurs=theBifurs.size(); 
}


void 
Cluster::addOrig (int v) 
{ 
  if (std::find(originalV.begin(), originalV.end(), v) == originalV.end())
    originalV.push_back (v);
}


void 
Cluster::deleteOrig (int ver) 
{ 
  auto it = std::remove(originalV.begin(), originalV.end(), ver);
  frontiers.erase (it, originalV.end());
}


void 
Cluster::setToCluster(Cluster &theCluster)
{
  int length, name;
  DegValues theNew;

  length=values.size();
  name=theCluster.returnName();

  if(length==1 && values.at(1).returnValue(7)==0)
    {
      currDeg=1;
      values.at(currDeg).setValue(7,name);
    }
  else
    {
      for (auto it = values.begin(); it != values.end(); ++it)
        {
          if (it->returnValue(7)==name)
            currDeg=1;
          else
            {
              theNew.setValue(3,1.0);
              theNew.setValue(5,1.0);
              theNew.setValue(7,1.0);
              values.push_back(theNew);
              currDeg=length+1;
              values.at(currDeg).setValue(7,name);
            }
        }
    }
}


void 
Cluster::makeEmpty()
{
  DegValues first;

  core.setName(0);
  group=0;
  type=0;
  frontiers.clear();
  innerE.clear();
  outerE.clear();
  originalV.clear();
  children.clear();
  bifurs.clear();
  currBifur=-1;
  numBifurs=0;
  constrain=0;
  solved=false;
  values.clear();
  currDeg=1;
  first.setValue(3,1.0);
  first.setValue(5,1.0);
  first.setValue(7,1.0);
  values.push_back(first);
  currAlias=-1;
  left.clear();
  right.clear();
  lines.clear();
}


bool 
Cluster::empty() 
{
  if(core.returnName()==0&&group==0&&children.empty())
    return true;
  else return false;
}


void 
Cluster::formCl (Vertex &c, std::vector<int> &fV, std::vector<Edge> &iE, 
                 std::vector<Edge> &oE, std::vector<int> &o)
{
  core=c;
  frontiers=fV;
  innerE=iE;
  outerE=oE;
  originalV=o;
}


Cluster& 
Cluster::operator = (const Cluster &clu)
{
  if (this != &clu)
    {
      core=clu.core;
      group=clu.group;
	    type=clu.type;
      frontiers=clu.frontiers;
      innerE=clu.innerE;
      outerE=clu.outerE;
      originalV=clu.originalV;
      children=clu.children;
      bifurs=clu.bifurs;
      currBifur=clu.currBifur;
      numBifurs=clu.numBifurs;
      constrain=clu.constrain;
      solved=clu.solved;
      values=clu.values;
	    currAlias=clu.currAlias;
	    left=clu.left;
	    right=clu.right;
	    lines=clu.lines;
    }
  return *this;
}


std::ostream& 
operator<< (std::ostream& os, const Cluster& clu)
{
  int child;
  os<<"Cluster(core):"<<clu.core.returnName()
    <<", depth="<<clu.core.returnDepth()<<", type="<<clu.type;
  if(clu.constrain==1) os<<", well constrained";
  if(clu.constrain>1) os<<", over constrained";
  if(clu.constrain<1) os<<", under constrained";
  os<<std::endl<<"Frontiers: ";
  for (auto it = clu.frontiers.begin(); it != clu.frontiers.end(); ++it)
    os << *it << ' ';
  os << std::endl;

  os<<std::endl<<"Previous clusters: ";
  for (auto it = clu.children.begin(); it != clu.children.end(); ++it)
    {
      child = it->returnCore().returnName();
      if (child!=0)
        os << child << ' ';
      else
        os << "Grp" << it->returnGroup() << ' ';
    }
  os << std::endl;

  os<<std::endl<<"Original Vertices: ";
  for (auto it = clu.originalV.begin(); it != clu.originalV.end(); ++it)
    os << *it << ' ';
  os << std::endl;

  os<<std::endl<<"Inner Edge: ";
  for (auto it = clu.innerE.begin(); it != clu.innerE.end(); ++it)
    os << it->returnName() << '('
       << it->returnWeight() << ','
       << it->returnEnd1() << '-'
       << it->returnEnd2() << ") ";
  os << std::endl;
    
  os<<std::endl<<"Onter Edge: ";
  for (auto it = clu.outerE.begin(); it != clu.outerE.end(); ++it)
    os << it->returnName() << '('
       << it->returnWeight() << ','
       << it->returnEnd1() << '-'
       << it->returnEnd2() << ") ";
  os << std::endl;

  os<<std::endl<<"Bifurcations (Current Selection: ";
  if(clu.currBifur<1) os<<"None):"<<std::endl;
  else os<<clu.currBifur<<"):"<<std::endl;
  for (auto it = clu.bifurs.begin(); it != clu.bifurs.end(); ++it)
    os <<"    " <<  *it << std::endl;
  os << std::endl;

	os << "The Degs are " << std::endl;
  for (auto it = clu.values.begin(); it != clu.values.end(); ++it)
	  os << *it;
  os << std::endl;

  return os;
}
