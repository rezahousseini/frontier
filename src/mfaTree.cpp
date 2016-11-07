#include "mfaTree.h"


//! Constructor
//! \param select Informs if the Tree has to be intialized all over again.
//!               Value 0 indicates usage from the old Tree, value 1 
//!               indicates reconstuction with new constraints
the_Tree::the_Tree (int select, int glo_flag, char *file_String)
{
  node_count = 0;
  glo_flag = 0;
  strcpy(file_String, "");
}


//! This gets the choice of the user as to whether he/she would like to use 
//! a previously constructed tree or create a new one and save it for 
//! future use.
//! \param select Informs if the Tree has to be intialized all over again.
//!               Value 0 indicates usage from the old Tree, value 1 
//!               indicates reconstuction with new constraints 
void 
the_Tree::build_Tree(int select, char *file_String, int search_flag)
{
  int mode = 0; 

  if (select==1)
    search_flag=1;
  else
    search_flag=2;

  std::cout << "1. Find mode\n" << "2. Input Mode\n"  << "Enter selection:";
  mode=1;

  std::cout << std::endl;	

  // Create Root node irrespective of mode of operation
  // Root node is a dummy node with no equation attached to it
  node_count++;  
  Block.resize(node_count);
  Cases.resize(node_count);
  Block[node_count-1]=new Node; 
  Cases[node_count-1]=new Condition;
  Block[node_count-1]->Set_parent(Block[0]);
  char *rootname = new char[5];
  strcpy(rootname,"Root");
  Block[0]->Set_label(rootname);
  
  // If user inputs a number other than 1 or 2, default mode is 1
  if (mode!=2)
    if (mode!=1)
      {
        std::cout << "Entered an invalid mode. So, default mode is " 
                  << "Find mode" << std::endl;
        mode=1;
      }

  // Find mode, i.e., User can use already existing Tree structures to 
  // design his Tree
  if (mode==1)     
    {
      const int maxSize = 200;
      int count=node_count;
      
      char* buffer0 = new char[maxSize];
      char* buffer1 = new char[maxSize];  
      char* buffer2 = new char[maxSize];  
      char* buffer3 = new char[maxSize];  
      char* buffer4 = new char[maxSize];  
      
      
      // create a temperory file called orig_path for storing the current 
      // directory
      system("pwd > orig_path");
      std::ifstream inp_file("orig_path");
      inp_file.getline(buffer0,maxSize);	        
      
      char* dir_name = new char[maxSize];
      chdir("../../datafiles/");
      strcpy(dir_name,"");
        
      std::cout << "The available data files directories are:\n";
      system("ls");
         
      std::cout << "Give name of the required data files directory : ";

      strcpy(dir_name,"original");
       
      // assign default 
      if (strcmp(dir_name,"")==0)
        strcpy(dir_name,"original");
      
      chdir(dir_name);
      system("pwd");
      
      // Groups.txt is a file that contains information regarding the Tree
      // such as Parent-child relationships and also contains the 
      // information of the equation associated with each node
      std::ifstream gpFile("Groups.txt");
      
      while (gpFile)
        {
          gpFile.getline(buffer1, maxSize);  // Gets the label of each node
          gpFile.getline(buffer2, maxSize);  // Gets the equation to be put 
                                             // in each node
          gpFile.getline(buffer3, maxSize);  // Gets the label of the parent
                                             // node of current node
      
          int index = 0, flag = 0, parent=0;
          // Search for the Parent node in the list of nodes
          while ((flag==0) && (index<node_count))            
            {
      	      if (strcmp(Block[index]->Ret_label(),buffer3)==0)   
      	        {
      	          flag=1;
      	          parent=index; //identifies the parent id
      	          break;
      	        }
      	      index++;
            }
      
          node_count++;
          Block.resize(node_count);  
          Cases.resize(node_count);
      
          // creation of a new Node for the current node in Tree
          Block[count]=new Node;
          Cases[count]=new Condition;
          Block[count]->Set_parent(Block[parent]);  // Sets the parent
      
          // Sets the label of the current node
          Block[count]->Set_label(buffer1); 
          // Sets the equation of the current node
          Block[count]->Set_Eqn(buffer2);   
          // Sets the node as a child of its parent
          Block[parent]->Set_child(Block[parent]->Get_child_count(), 
                                   Block[count], Cases[count], buffer4, 
                                   buffer1, mode); 
          count++;
          gpFile.getline(buffer3, maxSize);
      
        }
        
      std::cout << "In req. dir";
      system("pwd");
        
      chdir(buffer0);
      system("rm orig_path");
        
        
      delete buffer0;
      delete buffer1;
      delete buffer2;
      delete buffer3;	
      delete dir_name;
      delete buffer4;
    }


  // Input mode, i.e., user would have to input the Tree and save it if 
  // necessary for later use
  if (mode==2)    
    {
      char more='y';
      while ((more=='y') || (more=='Y'))
        {
          std::cout << "More nodes? (Y/N): ";
          std::cin >> more;  
          std::cout << std::endl;

          if ((more=='y') || (more=='Y'))
            {
              char* str1 = new char[400];
              char* str2 = new char[400];
  
              // Get Equation for new node
              std::cout << "Give Equation: ";   
              std::cin >> str1;

              // Attach to which parent node?
              std::cout << "\nWhat is the Parent of new Node :";
              std::cin >> str2;
              std::cout << std::endl;
                  	
              int i = 0; 
              int flag = 0;
              int par=0;

              // Search for the Parent node in the list of nodes
              while ((flag==0) && (i<node_count))            
                {
                  if (strcmp(Block[i]->Ret_label(),str2)==0)   
                    {
              	flag=1;
              	par=i;
                    }
                  i++;
                }
              
              if (flag==0)
                {
                  std::cout << "Sorry! No such node found to be parent.\n";
                  more='y';
                }
              else
                {
                  char* str3 = new char[200];	
                  node_count++; 
                  Block.resize(node_count);
                  Cases.resize(node_count);
                  Block[node_count-1]=new Node;
                  Cases[node_count-1]=new Condition;
                  Block[node_count-1]->Set_Eqn(str1);
                  std::cout << "Give label for node :";
                  std::cin >> str3; 
                  std::cout << std::endl;
                  Block[node_count-1]->Set_label(str3);
                  Block[node_count-1]->Set_parent(Block[par]);
                  Block[par]->Set_child(Block[par]->Get_child_count(),
                                        Block[node_count-1], 
                                        Cases[node_count-1], str1);
                  delete str3;
                }
              delete str1;
              delete str2;
            }
          else
            more='n';
        }

      // Save the Tree structure and data into files so that they can be 
      // read abd used later
      std::cout << "The Tree structure and constraints can be saved in "
                << "a directory." << std::endl;
      std::cout << "Save (Y/N)? ";
      char save_info;
      std::cin >> save_info;
      if ((save_info=='y') || (save_info=='Y'))
        {
          // Get the name of the directory from the user
          char* dir_name = new char[100];
          std::cout << "\nGive name of new directory :";
          std::cin >> dir_name;
          
          // make a sub-directory under the current directory and give 
          // permission 755
          char* cmd2 = new char[200];
          chdir("datafiles");
          system("pwd");
          mkdir(dir_name, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
          strcpy(cmd2,"chmod ");
          strcat(cmd2,"755 ");	    
          strcat(cmd2, dir_name);
          system(cmd2); 
          
          // go into the newly created directory
          chdir(dir_name);
          system("pwd");

          // make new files in the directory
          std::ofstream out_file("Groups.txt");
          Block[0]->write_Tree(file_String);
          out_file << file_String;
          
          delete dir_name;
          delete cmd2;
        }
    }
}
  

void 
the_Tree::copyTreeIntoArray(int *array, char *strArray)
{
  char* name[10000]; 

  for (int i=0; i<10000; i++)
    name[i]=0;

  std::vector <Node *> Q;
  std::vector <int> suppQ;

  Node *nd = NULL;

  std::cout << "Starting location for data: " << array[0] << std::endl; 

  int index=array[0];

  //int strStore = index+1;  //Old
  int strStore = index++; //New
  int strIndex = 0;
  array[strStore]=0;

  int parIndex=0, nodeNo=0;
  int count=1; 
  
  /*  Old  */  
  array[index++]=nodeNo;
  array[index++]=nodeNo;
  array[index++]=Block[0]->Get_child_count();

  /* New 
  array[index+1]=nodeNo;
  array[index+2]=nodeNo;
  array[index+3]=Block[0]->Get_child_count();
  index+=4;
  */    

  array[0]=index;

  for (int i=0; i<Block[0]->Get_child_count(); i++)
    {
      Block[0]->cond[i]->copyCondIntoArray(array);
      index = array[0];
      //std::cout << "SPSPSPSIndex & Array[0]= " << index << " " << array[0] << std::endl;
    }
  nodeNo++;

  nd=Block[0];
  suppQ.push_back(nd->Get_child_count());
  while (count <= nd->Get_child_count())
    {
      Q.push_back(nd->ptr[count-1]);
      count++;
    }
  
  while (!Q.empty())
    {
      nd = popQ(Q);
      array[index++]=nodeNo;
      array[index++]=parIndex;
      
      strIndex = array[strStore];
      std::cout << "index Here : " << index << " " << strIndex << std::endl;
      array[index++]=strIndex;
      
      strcpy((strArray+strIndex),nd->Get_Eqn());
      strIndex = strIndex + strlen(nd->Get_Eqn())+1;
      array[strStore] = strIndex;
      
      name[index-3]= new char[strlen(nd->Ret_label())+1];
      strcpy(name[index-3],nd->Ret_label());
      
      if (nd->parent !=NULL)
        {
          name[index-2]= new char[strlen(nd->parent->Ret_label())+1];
          strcpy(name[index-2],nd->parent->Ret_label());
        }
      
      array[index++]=nd->Get_child_count();
      array[0]=index;
      for (int i=0; i<(nd->Get_child_count()); i++)
        {
          nd->cond[i]->copyCondIntoArray(array);
          index = array[0];
          //std::cout << "HHHHHHHHHIndex & Array[0]= " << index << " " <<array[0] << std::endl;
        }
      
      count=1;
      suppQ.push_back(nd->Get_child_count());
      while (count <= nd->Get_child_count())
        {
          Q.push_back(nd->ptr[count-1]);
          count++;
        }
      
      if (suppQ[0]==0)
        {
          if (suppQ.size()!=0)
            {
              popfunc(suppQ);
              parIndex++;
            }
        }
      else
        {
          suppQ[0]-=1;
          if (suppQ[0]==0)
            {
      	      if (suppQ.size()!=0)
      	        {
      	          popfunc(suppQ);
      	          parIndex++;
      	        }
      	      while (suppQ[0]==0)
      	        {
      	          if (suppQ.size()!=0)
      	            {
      		            popfunc(suppQ);
      		            parIndex++;
      	            }
      	          else
      	            break;
      	        }
            }
        }
      nodeNo++;
    }

  array[index++]=-1;
  std::cout << "Max for Tree : " << index-1 <<std::endl;
  std::cout << "Value at max index = " << array[index-1] << std::endl; 
  array[0]=index;

  std::cout << "\nThe arrays\n";
  for (int i=0; i<100; i++)
    {
      /*
      int a;
      if (i%1000==0)
        std::cin >> a;
      */
      if (array[i]!=-2)
        {
          std::cout << "index=" << i << " " << array[i] << std::endl; 
        } 
      else
        break;
    }
  
  for (int i=0; i<100; i++)
    {
      if (strArray[i]!='\n')
        {
          std::cout << strArray[i] ;
          if (strArray[i]=='\0')
            std::cout << std::endl;
        }
    }
  std::cout << "The arrays\n";
}


//! pops the first element out of the vector
void 
the_Tree::popfunc(std::vector <int> &A)
{
  int check=0;
  int size=A.size();
  while (check<size-1)
    {
      A[check]=A[check+1];
      check++;
    }
  A.pop_back();
}


//! pops the first element out of the vector of Nodes
Node*
the_Tree::popQ(std::vector <Node *> &A)
{
  Node *temp = A[0];
  int check=0;
  int size=A.size();
  while (check<size-1)
    {
      A[check]=A[check+1];
      check++;
    }
  A.pop_back();
  return temp;
}


//! Changes the data in array to Tree form 
void 
the_Tree::copyArrayIntoTree(int &startI, int *&array, char *&strArray)
{
  int index=startI;
  
  //std::cout << "INDEX = " << index;
  //int ll;
  //std::cin >> ll;

  int strIndex = 0;

  //clears the old Tree
  Block.clear();
  node_count=0;
  
  node_count++;  
  Block.resize(node_count);
  Cases.resize(node_count);
  Block[node_count-1]=new Node; 
  Cases[node_count-1]=new Condition;
  Block[node_count-1]->Set_parent(Block[0]);
  char *rootname = new char[5];
  strcpy(rootname,"Root");
  Block[0]->Set_label(rootname);   
  

  index+=3;
  startI=index;

  int nodeIndex = 0;
  int parIndex = 0;
  int no_of_children = array[index++];
  //std::cout << "No. of children = " << no_of_children << std::endl;

  startI=index;
  
  while (array[index]!=-1)   //until all nodes are retrieved 
    {
      for (int i=0; i<no_of_children; i++)  // set all conditions for child nodes
        {
          Block[nodeIndex]->cond.resize(i+1);
          Block[nodeIndex]->cond[i] = new Condition;
          Block[nodeIndex]->cond[i]->copyArrayIntoCond(startI,array);
          index = startI;
        }
      
      if (array[index]!=-1)
        {
          //std::cout << "index = " << index << " " << ;
          
          nodeIndex = array[index++];  //get Node no.
          parIndex = array[index++];   //get node no. of parent
          
          node_count++;  
          Block.resize(node_count);
          Cases.resize(node_count);
          Block[node_count-1]=new Node; 
          Cases[node_count-1]=new Condition;
          Block[node_count-1]->child_count=0;
      
          Block[node_count-1]->Set_parent(Block[parIndex]); //set parent node of current node
      
          std::string nodeName = "Node:";
          nodeName += std::to_string(nodeIndex);
          Block[nodeIndex]->Set_label(&nodeName[0]);   //set label to current node
          
          Block[parIndex]->child_count++; //increase no. of children of its parent
          Block[parIndex]->ptr.resize(Block[parIndex]->child_count);
          // set current node as child for its parent
          Block[parIndex]->ptr[Block[parIndex]->child_count-1]=Block[nodeIndex];
      
          strIndex = array[index++];
          // sets equation of the current node
          Block[nodeIndex]->Set_Eqn(strArray+strIndex);  
              
          no_of_children = array[index++];
          startI=index;
          //startI = index;
        }
    }

  startI++;
}


//! converts a valid integer into a string
char* 
the_Tree::itoa(int n, char s[])
{
  int i, sign;
  if ((sign = n ) < 0)
    n = -n;
  i=0;
  do 
    {
      s[i++] = n%10 + '0';
    } 
  while ((n/=10)>0);
  if (sign < 0)
    s[i++]= '-';
  s[i]='\0';
  std::reverse(s, s + strlen(s));
  return s;
}


//! Display the Tree so far constructed
void 
the_Tree::display_Tree()
{
  std::cout << "\nThe Tree:\n\n"; 
  std::cout << "Root" << std::endl;
  Block[0]->showTree();
  std::cout << std::endl;
}


//! Searches the Tree for a single constraint in automated search mode
char* 
the_Tree::search_Tree(int a, int b, int c, int d, int e)
{  
  return(Block[0]->Find_Eqn_def_mode(a,b,c,d,e));    
}


//! Searches the Tree for a set of constraints but in a one-by-one basis rather 
//! than en-bloc
std::string 
the_Tree::search_Tree(Graph &graph0, Cluster &theCluster, 
                      std::ostream &inputFile, int flag, int withHeldCluster,
                      int graphDimen, int glo_flag, List<std::string>& vars)
{
  ClustData test;
  
  test=summCluster(graph0, theCluster);
 
  std::cout<<"FIRST SOLVE TYPE"<<std::endl;

  int length=test.length;
  std::string newString, outputString;	 
  Vertex vEnd1, vEnd2;
  int end1C, end2C;
  
  //set correct output style in maple
  outputString+="interface(prettyprint=0);\n";
  
  //ten second solution time limit set
  outputString+="timelimit(10,solve({";
  
  // Tree.search_Tree();
  

  //outputString+=search_Tree(test, graph0, theCluster, inputFile);
  
  
  for(int i=0; i<length; i++)
    {
      int a,b,c,d,e;
      float value;
      
      a=test.e1Type[i];
      b=test.e1Part[i];
      c=test.e2Type[i];
      d=test.e2Part[i];
      e=test.edgeType[i];
      value=test.values[i];
      
      int end1ID=test.e1ID[i];
      int end2ID=test.e2ID[i];
      
      std::string str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, 
                  str11, str12, str13;
      std::string rep_1, rep_2, rep_3, rep_4, rep_5, rep_6, rep_7, rep_8, 
                  rep_9, rep_10, rep_11, rep_12, rep_13;
      
      std::cout << "Search :" << a << b << c << d << e << ": "; 
      newString=search_Tree(a,b,c,d,e);
      std::cout << newString << std::endl;
      
      
      //search_Tree(a,b,c,d,e)      - Searches tree for a single constraint
      //search_Tree()               - Searches tree in User-input-Search mode
      
      if (e==4)
        value = (tan((value/180)*M_PI))*(tan((value/180)*M_PI)); 	
      //value = (tan((value/180)*PI));
      if (e==8)
        value = cos((value/180)*M_PI);
      
      //newString=replaceAll(newString,"1",toString(end1ID));
      //newString=replaceAll(newString,"2",toString(end2ID));
      newString=replaceAll(newString,"value","("+toString(value)+")");
      //      newString=replaceAll(newString,",","\n");
      
      int j=0, k=0;
      for (int round=1;round<=2; round++) 
        {		
          if (round==1) 
            {  
      	      j=end1ID;
      	      k=a;     
            } 
          else
            {
      	      j=end2ID;
      	      k=c;    
            }
          //	  std::cout << "j=" << j << ",k=" << k << std::endl;
          switch(k)
            {
              case 0:		
      	        str1="?"+toString(j);
      	        str1="x"+str1;
      	        str2="?"+toString(j); 
      	        str2="y"+str2;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        break;
              case 1:
      	        str1="?"+toString(j);
      	        str1="x"+str1;
      	        str2="?"+toString(j);
      	        str2="y"+str2;
      	        str3="?"+toString(j);
      	        str3="m"+str3;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_3="m"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_3,str3);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str3="m"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str3)) vars.append(str3);
      	        break;
              case 2:
      	        str1="?"+toString(j);
      	        str1="x"+str1;
      	        str2="?"+toString(j);
      	        str2="y"+str2;
      	        str4="?"+toString(j);
      	        str4="w"+str4;
      	        str5="?"+toString(j);
      	        str5="v"+str5;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_4="w"+toString(round);
      	        rep_5="v"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_4,str4);
      	        newString=replaceAll(newString,rep_5,str5);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str4="w"+toString(j);
      	        str5="v"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str4)) vars.append(str4);
      	        if(!vars.hasElem(str5)) vars.append(str5);
      	        break;
              case 3:
      	        str1="?"+toString(j);
      	        str1="x"+str1;
      	        str2="?"+toString(j);
      	        str2="y"+str2;
      	        str6="?"+toString(j);
      	        str6="c"+str6;
      	        str7="?"+toString(j);
      	        str7="d"+str7;
      	        str3="?"+toString(j);
      	        str3="m"+str3;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_6="c"+toString(round);
      	        rep_7="d"+toString(round);
      	        rep_3="m"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_6,str6);
      	        newString=replaceAll(newString,rep_7,str7);
      	        newString=replaceAll(newString,rep_3,str3);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str6="c"+toString(j);
      	        str7="d"+toString(j);
      	        str3="m"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str6)) vars.append(str6);
      	        if(!vars.hasElem(str7)) vars.append(str7);
      	        if(!vars.hasElem(str3)) vars.append(str3);
      	        break;
              case 4:
      	        str1="?"+toString(j); 
      	        str1="x"+str1;
      	        str2="?"+toString(j);
      	        str2="y"+str2;
      	        str8="?"+toString(j);     
      	        str8="r"+str8;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_8="r"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_8,str8);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str8="r"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str8)) vars.append(str8);
      	        break;
              case 5:
      	        str1="?"+toString(j);      
      	        str1="x"+str1;
      	        str2="?"+toString(j); 
      	        str2="y"+str2;
      	        str8="?"+toString(j); 
      	        str8="r"+str8;
      	        str11="?"+toString(j);
      	        str11="a"+str11;
      	        str12="?"+toString(j);
      	        str12="b"+str12;
      	        str5="?"+toString(j);
      	        str5="v"+str5;
      	        str4="?"+toString(j);
      	        str4="w"+str4;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_8="r"+toString(round);
      	        rep_11="a"+toString(round);
      	        rep_12="b"+toString(round);      
      	        rep_4="w"+toString(round);
      	        rep_5="v"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_8,str8);
      	        newString=replaceAll(newString,rep_11,str11);
      	        newString=replaceAll(newString,rep_12,str12);
      	        newString=replaceAll(newString,rep_4,str4);
      	        newString=replaceAll(newString,rep_5,str5);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str8="r"+toString(j);
      	        str11="a"+toString(j);
      	        str12="b"+toString(j);
      	        str4="w"+toString(j);
      	        str5="v"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str8)) vars.append(str8);
      	        if(!vars.hasElem(str11)) vars.append(str11);	
      	        if(!vars.hasElem(str12)) vars.append(str12);
      	        if(!vars.hasElem(str4)) vars.append(str4);
      	        if(!vars.hasElem(str5)) vars.append(str5);
      	        break;
              case 6:		
      	        str1="?"+toString(j);
      	        str1="x"+str1;
      	        str2="?"+toString(j); 
      	        str2="y"+str2;
      	        str13="?"+toString(j);
      	        str13="z"+str13;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_13="z"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_13,str13);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str13="z"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str13)) vars.append(str13);
      	        break;
              case 7:
      	        str1="?"+toString(j);
      	        str1="x"+str1;
      	        str2="?"+toString(j);
      	        str2="y"+str2;
      	        str3="?"+toString(j);
      	        str3="z"+str3;
      	        str6="?"+toString(j);
      	        str6="c"+str6;
      	        str7="?"+toString(j);
      	        str7="d"+str7;
      	        str8="?"+toString(j);
      	        str8="e"+str8;
      	        rep_1="x"+toString(round);
      	        rep_2="y"+toString(round);
      	        rep_3="z"+toString(round);
      	        rep_6="c"+toString(round);
      	        rep_7="d"+toString(round);
      	        rep_8="e"+toString(round);
      	        newString=replaceAll(newString,rep_1,str1);
      	        newString=replaceAll(newString,rep_2,str2);
      	        newString=replaceAll(newString,rep_3,str3);
      	        newString=replaceAll(newString,rep_6,str6);
      	        newString=replaceAll(newString,rep_7,str7);
      	        newString=replaceAll(newString,rep_8,str8);
      	        str1="x"+toString(j);
      	        str2="y"+toString(j);
      	        str3="z"+toString(j);
      	        str6="c"+toString(j);
      	        str7="d"+toString(j);
      	        str8="e"+toString(j);
      	        if(!vars.hasElem(str1)) vars.append(str1);
      	        if(!vars.hasElem(str2)) vars.append(str2);
      	        if(!vars.hasElem(str6)) vars.append(str6);
      	        if(!vars.hasElem(str7)) vars.append(str7);
      	        if(!vars.hasElem(str3)) vars.append(str3);
      	        if(!vars.hasElem(str8)) vars.append(str8);
      	        break;
            }
        }
      
      newString=replaceAll(newString,"?","");
      
      vEnd1=graph0.returnVertByName(end1ID);
      vEnd2=graph0.returnVertByName(end2ID);
          
      end1C=getChildNameWithVertex(theCluster, end1ID);
      end2C=getChildNameWithVertex(theCluster, end2ID);
      
      int ind1=getChildIndexByName(theCluster, end1C);
      int ind2=getChildIndexByName(theCluster, end2C);
      
      /*	if(theCluster.children.retrieve(ind1).returnType()==2 ||
      	   theCluster.children.retrieve(ind2).returnType()==2)
      	{	
      		outputString+=newString;
      		if(i<(length-1)) outputString+=",";
      		continue;
      	}
      */	

	    setValueInCluster(graph0,theCluster.children.retrieve(ind1), vEnd1);
	    setValueInCluster(graph0,theCluster.children.retrieve(ind2), vEnd2);

	    if (end1C==-1 || end2C==-1) return "";
	    if (end1C!=end1ID) 
	      {
	        newString=switchString(vEnd1, Vertex::Type(a), end1ID, end1C, 
                                 newString, end1C!=withHeldCluster, vars,
                                 graphDimen);
	        if(end1C!=withHeldCluster)
	          newString=switchString(vEnd1, Vertex::Type(a), end1ID, end1C, 
                                   newString, false, vars, graphDimen);
	      }
	    if (end2C!=end2ID)
	      {
	        newString=switchString(vEnd2, Vertex::Type(c), end2ID, end2C, 
                                 newString, end2C!=withHeldCluster, vars, 
                                 graphDimen);
	        if(end2C!=withHeldCluster)
	          newString=switchString(vEnd2, Vertex::Type(c), end2ID, end2C, 
                                   newString, false, vars, graphDimen);
	      }
	    outputString+=newString;
	    if(i<(length-1)) outputString+=",";         
    }
  return outputString;
}
  

//! Searches the Tree in En-Bloc fashion for the constraints
std::string 
the_Tree::search_Tree (Graph &graph0, Cluster &theCluster, 
                       std::ostream &inputFile, int withHeldCluster, 
                       int graphDimen, int glo_flag, List<std::string>& vars)
{
  ClustData test;
  test=summCluster(graph0, theCluster);
 
  std::ofstream outf("search_Tree.out", std::ios::app);
  outf<<"SECOND SOLVE TYPE"<<std::endl;

  int no_of_searches=0;        // No. of searches to be done 
  std::vector <Ord_Set *> Searches; // The dynamic list for Search operation 
  std::vector <char *> t_str;
  
  int t_par[500];
  int flag_arr[500];
  char contin = 'y';

  int length=test.length;
  outf << "Length : " << length << std::endl;
  outf << "vars are: " << getVarString(vars) << std::endl;
  std::string tempString, newString, outputString;
  std::string stringArray[500];
  Vertex vEnd1, vEnd2;
  int end1C, end2C;    


  //set correct output style in maple
  outputString+="interface(prettyprint=0);\n";
            
  //ten second solution time limit set
  outputString+="timelimit(10,solve({";

  for (int i=0; i<length; i++)
    {
      int a=test.e1Type[i];
      int b=test.e1Part[i];
      int c=test.e2Type[i];
      int d=test.e2Part[i];
      int e=test.edgeType[i];
          	
      no_of_searches++;
      Searches.resize(no_of_searches);
      t_str.resize(no_of_searches);
      Searches[no_of_searches-1]=new Ord_Set;
      Searches[no_of_searches-1]->Set_Val(a,b,c,d,e);
      t_str[no_of_searches-1] = new char[200];
      t_par[no_of_searches-1] = 0;
      flag_arr[no_of_searches-1] = 0;
    }
  
  outf << "No_of_Searches : " << no_of_searches << std::endl;

  while (contin=='y')
    {	
      outf<<"While Loop"<<std::endl;
      for (int j=0; j<no_of_searches; j++) // Search the Tree
        {
          outf<<"For Loop j="<<j<<std::endl;
          int a,b,c,d,e;
          int end1ID=test.e1ID[j];
          int end2ID=test.e2ID[j];
          float value=test.values[j];
      
          outf<<"Before searches"<<std::endl;
          
          a=Searches[j]->ret_1();
          b=Searches[j]->ret_2();
          c=Searches[j]->ret_3();
          d=Searches[j]->ret_4();
          e=Searches[j]->ret_5();
          outf << "Search No." << j+1 << ": (" <<a<< "," <<b<< "," <<c<< "," 
               <<d<< "," <<e<<  "): ";
          //strcpy(t_str[j],Block[t_par[j]]->Find_Eqn(a,b,c,d,e)) ;
          strcpy(t_str[j],Block[t_par[j]]->Find_Eqn(a,b,c,d,e)) ;
      
          if (e==4)
            value = (tan((value/180)*M_PI))*(tan((value/180)*M_PI));
          //value = (tan((value/180)*PI));
          if (e==8)
            value = cos((value/180)*M_PI);
          
          tempString=t_str[j];
          tempString=replaceAll(tempString,"value","("+toString(value)+")");
          outf << "tempString is: " << std::endl << tempString << std::endl;
      	  outf << "vars are: " << getVarString(vars) << std::endl;	    
          std::string str1, str2, str3, str4, str5, str6, str7, str8, str9, 
                      str10, str11, str12, str13;
          std::string rep_1, rep_2, rep_3, rep_4, rep_5, rep_6, rep_7, rep_8, 
                      rep_9, rep_10, rep_11, rep_12, rep_13;
      
          
          int ind=0, k=0;
      
          
          for (int round=1;round<=2; round++) 
            {		
      	      if (round==1) 
      	        {  
      	          ind=end1ID;
      	          k=a;     
      	        } 
      	      else
      	        {
      	          ind=end2ID;
      	          k=c;    
      	        }
          
      
      
      	      switch(k)
      	        {
      	          case 0:		
      	            str1="?"+toString(ind);
      	            str1="x"+str1;
      	            str2="?"+toString(ind); 
      	            str2="y"+str2;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            break;
      	          case 1:
      	            str1="?"+toString(ind);
      	            str1="x"+str1;
      	            str2="?"+toString(ind);
      	            str2="y"+str2;
      	            str3="?"+toString(ind);
      	            str3="m"+str3;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_3="m"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_3,str3);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str3="m"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str3)) vars.append(str3);
      	            break;
      	          case 2:
      	            str1="?"+toString(ind);
      	            str1="x"+str1;
      	            str2="?"+toString(ind);
      	            str2="y"+str2;
      	            str4="?"+toString(ind);
      	            str4="w"+str4;
      	            str5="?"+toString(ind);
      	            str5="v"+str5;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_4="w"+toString(round);
      	            rep_5="v"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_4,str4);
      	            tempString=replaceAll(tempString,rep_5,str5);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str4="w"+toString(ind);
      	            str5="v"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str4)) vars.append(str4);
      	            if(!vars.hasElem(str5)) vars.append(str5);
      	            break;
      	          case 3:
      	            str1="?"+toString(ind);
      	            str1="x"+str1;
      	            str2="?"+toString(ind);
      	            str2="y"+str2;
      	            str6="?"+toString(ind);
      	            str6="c"+str6;
      	            str7="?"+toString(ind);
      	            str7="d"+str7;
      	            str3="?"+toString(ind);
      	            str3="m"+str3;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_6="c"+toString(round);
      	            rep_7="d"+toString(round);
      	            rep_3="m"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_6,str6);
      	            tempString=replaceAll(tempString,rep_7,str7);
      	            tempString=replaceAll(tempString,rep_3,str3);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str6="c"+toString(ind);
      	            str7="d"+toString(ind);
      	            str3="m"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str6)) vars.append(str6);
      	            if(!vars.hasElem(str7)) vars.append(str7);
      	            if(!vars.hasElem(str3)) vars.append(str3);
      	            break;
      	          case 4:
      	            str1="?"+toString(ind); 
      	            str1="x"+str1;
      	            str2="?"+toString(ind);
      	            str2="y"+str2;
      	            str8="?"+toString(ind);     
      	            str8="r"+str8;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_8="r"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_8,str8);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str8="r"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str8)) vars.append(str8);
      	            break;
      	          case 5:
      	            str1="?"+toString(ind);      
      	            str1="x"+str1;
      	            str2="?"+toString(ind); 
      	            str2="y"+str2;
      	            str8="?"+toString(ind); 
      	            str8="r"+str8;
      	            str11="?"+toString(ind);
      	            str11="a"+str11;
      	            str12="?"+toString(ind);
      	            str12="b"+str12;
      	            str5="?"+toString(ind);
      	            str5="v"+str5;
      	            str4="?"+toString(ind);
      	            str4="w"+str4;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_8="r"+toString(round);
      	            rep_11="a"+toString(round);
      	            rep_12="b"+toString(round);      
      	            rep_4="w"+toString(round);
      	            rep_5="v"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_8,str8);
      	            tempString=replaceAll(tempString,rep_11,str11);
      	            tempString=replaceAll(tempString,rep_12,str12);
      	            tempString=replaceAll(tempString,rep_4,str4);
      	            tempString=replaceAll(tempString,rep_5,str5);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str8="r"+toString(ind);
      	            str11="a"+toString(ind);
      	            str12="b"+toString(ind);
      	            str4="w"+toString(ind);
      	            str5="v"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str8)) vars.append(str8);
      	            if(!vars.hasElem(str11)) vars.append(str11);	
      	            if(!vars.hasElem(str12)) vars.append(str12);
      	            if(!vars.hasElem(str4)) vars.append(str4);
      	            if(!vars.hasElem(str5)) vars.append(str5);
      	            break;
      	          case 6:		
      	            str1="?"+toString(ind);
      	            str1="x"+str1;
      	            str2="?"+toString(ind); 
      	            str2="y"+str2;
      	            str13="?"+toString(ind);
      	            str13="z"+str13;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_13="z"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_13,str13);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str13="z"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str13)) vars.append(str13);
      	            break;
      	          case 7:
      	            str1="?"+toString(ind);
      	            str1="x"+str1;
      	            str2="?"+toString(ind);
      	            str2="y"+str2;
      	            str3="?"+toString(ind);
      	            str3="z"+str3;
      	            str6="?"+toString(ind);
      	            str6="c"+str6;
      	            str7="?"+toString(ind);
      	            str7="d"+str7;
      	            str8="?"+toString(ind);
      	            str8="e"+str8;
      	            rep_1="x"+toString(round);
      	            rep_2="y"+toString(round);
      	            rep_3="z"+toString(round);
      	            rep_6="c"+toString(round);
      	            rep_7="d"+toString(round);
      	            rep_8="e"+toString(round);
      	            tempString=replaceAll(tempString,rep_1,str1);
      	            tempString=replaceAll(tempString,rep_2,str2);
      	            tempString=replaceAll(tempString,rep_3,str3);
      	            tempString=replaceAll(tempString,rep_6,str6);
      	            tempString=replaceAll(tempString,rep_7,str7);
      	            tempString=replaceAll(tempString,rep_8,str8);
      	            str1="x"+toString(ind);
      	            str2="y"+toString(ind);
      	            str3="z"+toString(ind);
      	            str6="c"+toString(ind);
      	            str7="d"+toString(ind);
      	            str8="e"+toString(ind);
      	            if(!vars.hasElem(str1)) vars.append(str1);
      	            if(!vars.hasElem(str2)) vars.append(str2);
      	            if(!vars.hasElem(str6)) vars.append(str6);
      	            if(!vars.hasElem(str7)) vars.append(str7);
      	            if(!vars.hasElem(str3)) vars.append(str3);
      	            if(!vars.hasElem(str8)) vars.append(str8);
      	            break;
	              }
            }
          outf << "vars are: " << getVarString(vars) << std::endl;	    
          tempString=replaceAll(tempString,"?","");
    
          stringArray[j]=tempString;
          
          //outf << "tempString: " << tempString << std::endl;
          outf << stringArray[j] << std::endl;
          	    
          int u = 0; 
          int flag = 0;
          while ((flag==0) && (u<node_count))            
            {
	            if (strcmp(Block[u]->Get_Eqn(),t_str[j])==0)   
	              {
	                flag=1;
	                t_par[j]=u;
	              }
	            u++;
            }
  
          if (glo_flag==1)
            {
	            flag_arr[j]=0;
	            outf << "  Search ends\n";
            }
          else
            {
	            flag_arr[j]=1;
	            outf << "  Search can continue\n";
            }
        }
      outf << "vars are: " << getVarString(vars) << std::endl;

    	outf << "After the xyz replacement, the tempstring is: " << std::endl 
           << tempString << std::endl;
      int sig_flag=0; 
      for (int ind=0; ind<no_of_searches; ind++)
        {
          if (flag_arr[ind]==1)
            { 
	            sig_flag=1; 
	            continue;
            }
        }
    	outf << "vars are: " << getVarString(vars) << std::endl;

      if (sig_flag==1)
        {
          outf << "Continue? (y/n)" ;
          contin='y';
          //std::cin >> contin; outf << std::endl;
          if ((contin=='y') || (contin=='Y'))
            contin = 'y';
          else
            contin = 'n';
        }
      else contin = 'n';
    }	  

  for (int i=0; i<no_of_searches; i++)
    {
      int a=Searches[i]->ret_1();
      int c=Searches[i]->ret_3();
      
      Edge theEdge=graph0.returnEdgeByName(test.edgeID[i]);
          
      int end1ID=theEdge.returnEnd1();
      int end2ID=theEdge.returnEnd2();
      newString=stringArray[i];
      vEnd1=graph0.returnVertByName(end1ID);
      vEnd2=graph0.returnVertByName(end2ID);
          
      end1C=getChildNameWithVertex(theCluster, end1ID);
      end2C=getChildNameWithVertex(theCluster, end2ID);
      
      int ind1=getChildIndexByName(theCluster, end1C);
      int ind2=getChildIndexByName(theCluster, end2C);
      
      setValueInCluster(graph0,theCluster.children.retrieve(ind1), vEnd1);
      setValueInCluster(graph0,theCluster.children.retrieve(ind2), vEnd2);
      
      if (end1C==-1 || end2C==-1) return "";
      if (end1C!=end1ID && theCluster.children.retrieve(ind1).returnType()!=2 
          && theCluster.children.retrieve(ind1).returnType()!=5) 
        {
          newString=switchString(vEnd1, Vertex::Type(a), end1ID, end1C, newString, 
                                 end1C!=withHeldCluster, vars, graphDimen);
          if(end1C!=withHeldCluster)
            newString=switchString(vEnd1, Vertex::Type(a), end1ID, end1C, newString,
                                   false, vars, graphDimen);
        }
      if (end2C!=end2ID && theCluster.children.retrieve(ind2).returnType()!=2
          && theCluster.children.retrieve(ind1).returnType()!=5) 
        {
          newString=switchString(vEnd2, Vertex::Type(c), end2ID, end2C, newString, 
                                 end2C!=withHeldCluster, vars, graphDimen);
          if(end2C!=withHeldCluster)
            newString=switchString(vEnd2, Vertex::Type(c), end2ID, end2C, newString,
                                   false, vars, graphDimen);
        }
      	outputString+=newString;
      	if(i<(length-1)) outputString+=",";
    }
	outf << "vars are: " << getVarString(vars) << std::endl;	
  outf<<"outputString="<<outputString<<std::endl;
  return outputString;
}


//! Searches the Tree En-Block in user search mode
void 
the_Tree::search_Tree(int glo_flag)
{      
  int no_of_searches=0;        // No. of searches to be done 
  std::vector <Ord_Set *> Searches; // The dynamic list for Search operation 
  std::vector <char *> t_str;
  
  int t_par[500];
  int flag_arr[500];
  char contin = 'y';
  
  while ((contin=='y') || (contin=='Y'))  // What should be searched?? Get the inputs
    {
      int a,b,c,d,e;
      no_of_searches++;
      std::cout << "Give conditions for search : " ;
      std::cin >> a >> b >> c >> d >> e;
      std::cout << "Search No." << no_of_searches << ": " <<a<< "," <<b<< "," 
                <<c<< "," <<d<< "," <<e;
      Searches.resize(no_of_searches);
      t_str.resize(no_of_searches);
      Searches[no_of_searches-1]=new Ord_Set;
      Searches[no_of_searches-1]->Set_Val(a,b,c,d,e);
      t_str[no_of_searches-1] = new char[200];
      t_par[no_of_searches-1] = 0;
      flag_arr[no_of_searches-1] = 0;
      std::cout << "\nContinue (Y/N): ";
      std::cin >> contin;
    }
  
  contin='y';
  glo_flag=0;
  while (contin=='y')
    {	
      for (int x=0; x<no_of_searches; x++) // Search the Tree
        {
          int a,b,c,d,e;
          a=Searches[x]->ret_1();
          b=Searches[x]->ret_2();
          c=Searches[x]->ret_3();
          d=Searches[x]->ret_4();
          e=Searches[x]->ret_5();
          std::cout << "Search No." << x+1 << ": (" <<a<< "," <<b<< "," 
                    <<c<< "," <<d<< "," <<e<<  "): ";
          std::cout << "Parent: " << t_par[x] << " " 
                    << Block[t_par[x]]->Ret_label() << std::endl;
          //std::cout << "\nGlobal: " << glo_flag;
          strcpy(t_str[x],Block[t_par[x]]->Find_Eqn(a,b,c,d,e)) ;
          std::cout << t_str[x] ; 
          int i = 0; 
          int flag = 0;
          while ((flag==0) && (i<node_count))            
            {
      	      if (strcmp(Block[i]->Get_Eqn(),t_str[x])==0)   
      	        {
      	          /*
      	            std::cout << "\nBlidsfdsf : " << Block[i]->Get_Eqn();
      	            std::cout << "\nt_str: " << t_str[x] << std::endl;
      	          */
      	          flag=1;
      	          t_par[x]=i;
      	          //std::cout << "Parent: " << t_par[x];
      	        }
      	      i++;
            }
          if (glo_flag==1)
            {
      	      flag_arr[x]=0;
      	      std::cout << "  Search ends\n";
            }
          else
            {
      	      flag_arr[x]=1;
      	      std::cout << "  Search can continue\n";
            }
        }

      int sig_flag=0; 
      for (int x=0; x<no_of_searches; x++)
        {
          if (flag_arr[x]==1)
            { 
	            sig_flag=1; 
	            //continue;
            }
        }
      if (sig_flag==1)
        {
          std::cout << "Continue? (y/n)" ;
          std::cin >> contin; std::cout << std::endl;
          if ((contin=='y') || (contin=='Y'))
            contin = 'y';
          else
            contin = 'n';
        }
      else contin = 'n';
    }
  return;
}
