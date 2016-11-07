/*Copyright (C) June 22, 2001 Meera Sitharam

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
http://www.gnu.org/copyleft/gpl.html

You should have received a copy of the GNU General Public License
in the documentation index in the documentation
folder of the FRONTIER-gnu directory; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//! \file mfa3Prnt.cpp
//! \brief These methods allow for the recursive output of DR_Trees to the given ostream

#include "Print.h"

void printTree(Cluster &DR_Tree, std::ostream &os, int indent)
{
   int i, numKids, kidName;
   List<Cluster> kids;

   kids = DR_Tree.children;
   numKids = kids.returnLen();

	

   for(i=0;i<indent;i++) os<<"**";
   os<<"Core: "<<DR_Tree.returnCore().returnName()
     <<",  Grp="<<DR_Tree.returnGroup();
   os<<",  Type="<<DR_Tree.returnType();
   os<<", CBifur="<<DR_Tree.returnCurrBifur();
   os<<", Solved="<<(DR_Tree.isSolved() ? "true" : "false");
   os<<", Value=";
   for(i=0;i<8;i++)  os<<DR_Tree.returnValue(i)<<" ";

   if(numKids>0)
   {
      os<<"   Children: ";
      for(i=1;i<=numKids;i++)
      {
         kidName=kids.retrieve(i).returnCore().returnName();
         if(kidName==0)
           os<<"Grp"<<kids.retrieve(i).returnGroup()<<' ';
         else
           os<<kidName<<' ';
      }
      os<<std::endl;
	

//     DR_Tree.output(os);
     printForest(kids, os, indent);
   }
   os<<std::endl;
}

void printForest(List<Cluster> &DR_Trees, std::ostream &os, int indent)
{
   int i, len;
   Cluster oneTree;

   indent=indent+1;
   len=DR_Trees.returnLen();
   for(i=1;i<=len;i++)
   {
      oneTree = DR_Trees.retrieve(i);
      printTree(oneTree, os, indent);
   }
   return;
}


//! prints the a cluster and all its children starting with a single cluster
void 
print (Graph &graph0, Cluster &theCluster)
{
  std::cout << theCluster << std::endl;

  int i, length;

  length=theCluster.children.returnLen();

  if(theCluster.returnName()==0) return;

  for(i=1;i<=length;i++)
    print(graph0, theCluster.children.retrieve(i));
}


//! for every cluster in SolverTrees, this method prints contents of the cluster
//! and all its children
void 
print (Graph &graph0, List<Cluster> &SolverTrees)
{
   int i, numTrees;
   numTrees=SolverTrees.returnLen();

   std::cout<<std::endl<<numTrees<<" Solver Input Trees"<<std::endl;
   for(i=1;i<=numTrees;i++)
   {
      std::cout<<"---------"<<std::endl;
      std::cout<<"Tree "<<i<<std::endl;
      printTree(SolverTrees.retrieve(i), std::cout, 1);
   }
}


//! prints the string corresponding to the bifurcations of theCluster
void 
printBifurcations (Cluster &theCluster, std::ofstream &outf)
{
   int i, length;
   List<std::string> theList;

   theList=theCluster.returnBifurs();

   length=theCluster.returnNumBifurs();

   for(i=1;i<=length;i++)
      outf<<"       "<<theList.retrieve(i)<<std::endl;
}
