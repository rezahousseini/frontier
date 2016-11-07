#include "utuHeader.h"

//! tc4.skr
void createTrees(Graph &graph1, List<Cluster> &solverTree)
{
	solverTree.makeEmpty();
	cout << "create my own trees" << std::endl;
	List<Edge> ie;
	List<Edge> oe;
	List<int> fro;
	List<int> ori;
	Vertex core;
	Cluster s1, s2, s3, s4, s5, s6, s7, s8;
	
	core = graph1.returnVertByName(1);
	fro.append(1);
	ori.append(1);
	s1.formCl(core, fro, ie, oe, ori);
	
	core = graph1.returnVertByName(2);
	fro.makeEmpty();
	ori.makeEmpty();
	fro.append(2);
	ori.append(2);
	s2.formCl(core, fro, ie, oe, ori);
	
	core = graph1.returnVertByName(3);
	fro.makeEmpty();
	ori.makeEmpty();
	fro.append(3);
	ori.append(3);
	s3.formCl(core, fro, ie, oe, ori);
	
	core = graph1.returnVertByName(4);
	fro.makeEmpty();
	ori.makeEmpty();
	fro.append(4);
	ori.append(4);
	s4.formCl(core, fro, ie, oe, ori);
	
	core = graph1.returnVertByName(5);
	fro.makeEmpty();
	ori.makeEmpty();
	fro.append(5);
	ori.append(5);
	s5.formCl(core, fro, ie, oe, ori);

	core = graph1.returnVertByName(6);
	fro.makeEmpty();
	ori.makeEmpty();
	fro.append(6);
	ori.append(6);
	s6.formCl(core, fro, ie, oe, ori);

	core = graph1.returnVertByName(7);
	fro.makeEmpty();
	ori.makeEmpty();
	fro.append(7);
	ori.append(7);
	s7.formCl(core, fro, ie, oe, ori);
	
	//triangle
	Cluster tri1;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(11);
	core.setDepth(1);
	core.setType(0);
		ori.append(1);
		ori.append(2);
		ori.append(3);
		fro.append(1);
		fro.append(2);
		fro.append(3);
	tri1.formCl(core, fro, ie, oe, ori);
	tri1.children.append(s1);
	tri1.children.append(s2);
	tri1.children.append(s3);
	//depth 2
	Cluster tetra1;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(14);
	core.setDepth(2);
	core.setType(0);
		ori.append(1);
		ori.append(2);
		ori.append(3);
		ori.append(7);
	fro.append(1);
	fro.append(3);
	fro.append(7);
	tetra1.formCl(core, fro, ie, oe, ori);
	tetra1.children.append(s7);
	tetra1.children.append(tri1);

	//triangle
	Cluster tri2;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(15);
	core.setDepth(1);
	core.setType(0);
		ori.append(1);
		ori.append(5);
		ori.append(6);
		fro.append(1);
		fro.append(5);
		fro.append(6);
	tri2.formCl(core, fro, ie, oe, ori);
	tri2.children.append(s1);
	tri2.children.append(s5);
	tri2.children.append(s6);
	//depth 2
	Cluster tetra2;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(16);
	core.setDepth(2);
	core.setType(0);
		ori.append(1);
		ori.append(5);
		ori.append(6);		
		ori.append(7);
	fro.append(1);
	fro.append(5);
	fro.append(7);
	tetra2.formCl(core, fro, ie, oe, ori);
	tetra2.children.append(s7);
	tetra2.children.append(tri2);

	//triangle
	Cluster tri3;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(17);
	core.setDepth(1);
	core.setType(0);
		ori.append(3);
		ori.append(5);
		ori.append(4);
		fro.append(3);
		fro.append(5);
		fro.append(4);
	tri3.formCl(core, fro, ie, oe, ori);
	tri3.children.append(s3);
	tri3.children.append(s5);
	tri3.children.append(s4);
	//depth 2
	Cluster tetra3;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(18);
	core.setDepth(2);
	core.setType(0);
		ori.append(3);
		ori.append(5);
		ori.append(4);
		ori.append(7);
		fro.append(3);
		fro.append(5);
		fro.append(7);
	tetra3.formCl(core, fro, ie, oe, ori);
	tetra3.children.append(s7);
	tetra3.children.append(tri3);
	//depth 3
	Cluster final;
	fro.makeEmpty();
	ori.makeEmpty();
	core.setName(19);
	core.setDepth(3);
	core.setType(0);
	for(int i = 1; i <=7; i++)
		ori.append(i);
	fro.append(1);
	fro.append(4);
	final.formCl(core, fro, ie, oe, ori);
	final.children.append(tetra1);
	final.children.append(tetra2);	
	final.children.append(tetra3);	
  
      solverTree.append(final);	

}

main()
{
  Graph graph1;
  List<Cluster> SolverTrees;
  createTrees(graph1, SolverTrees);
}
