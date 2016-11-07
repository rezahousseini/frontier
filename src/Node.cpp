#include "Node.h"

//! Constructor
Node::Node()
{
  child_count=0;
  // label = new char[100];
  //eqn  = new char[100];
  parent = NULL;
  eqn = new char[strlen("No equation")];
  strcpy(eqn,"No equation");
}


//! Sets the label for the node
void 
Node::Set_label(char* s)
{
  label = new char[strlen(s)+1];
  strcpy(label,s);
}


//! Prints the label of a node
void 
Node::Get_label()
{
  std::cout << label << "\n";
}


//! Returns the label of a node
char* 
Node::Ret_label()
{
  return(label);
}


//! Sets the parent for a node
void 
Node::Set_parent(Node *i)
{
  parent=i;
}


//! Returns the label of the parent of any given node
char* 
Node::Get_Parent()
{
  return parent->Ret_label();
}


//! Sets the children nodes after taking in the conditions for that node
//! Called during Input mode only
void 
Node::Set_child(int i, Node* j, Condition* k, char* str)
{ 
  child_count++;
  ptr.resize(child_count);
  cond.resize(child_count);
  ptr[child_count-1]=j;
  cond[child_count-1]=k;
  char x='y';
  while ((x=='y') || (x=='Y'))
    {
      int a,b,c,d,e;
      a=b=c=d=e=0;
      x='n';
      std::cout << "Give conditions :";
      std::cin >> a >> b >> c >> d >> e ; // >> f; 
      cond[child_count-1]->add_Cond(a,b,c,d,e);
      // cond[child_count-1]->disp_Cond();
      std::cout << "More conditions? : (Y/N)";
      std::cin >> x; 
    }
}


//! Sets the children nodes by taking the conditions for that node from a file f_name
//! Called during Find mode only
void 
Node::Set_child(int i, Node* j, Condition* k, char* path_name, char* f_name, int a)
{ 
   if (a==1)
    {
      child_count++;
      ptr.resize(child_count);
      cond.resize(child_count);
      ptr[child_count-1]=j;
      cond[child_count-1]=k;
      
      /*
      char* path_file = new char[200];
      strcpy(path_file, "/cise/research/constraints/ramesh/2dto3d/datafiles/");
      strcat(path_file, f_name);
      */
      
      path_name=(char *)"";
      
      char* link = new char[200];
      strcpy(link, path_name);
      //std::cout<<"IN SET_CHILD path name = "<<path_name<<" file name= "<<f_name<<std::endl;
      strcat(link, f_name);
      
      std::ifstream infile(link);
      //std::ifstream infile(path_file);
      char buffer[200];
      while (infile)
        {
          int buf[6];
          char* temp=new char[500];
          infile.getline(buffer, 500);
          
          if (strcmp(buffer,"")!=0)
            {  
      	      unsigned int e=0;
      	      int start=0;
      	      int cnt=0;
      	      while (cnt<=5)
      	        {
      	          strcpy(temp,"");
      	          while ((buffer[e]!=',') && (e!=(strlen(buffer)-1)))
      	            e++;
      	          if (e!=(strlen(buffer)-1))
      	            {
      	      	      for (unsigned int z=start; z<e; z++)
      	      	        strcat(temp,&buffer[z]);
      	            }
      	          else
      	            {
      	      	      strcat(temp,&buffer[start]);
      	            }
      	          strcat(temp,"\0");
      	          if (e!=strlen(buffer)-1)
      	            { 
      	      	      e++;
      	      	      start=e;
      	            }
      	          if (cnt<=5)
      	            {
      	      	      buf[cnt]=atoi(temp);
      	      	      cnt++;
      	            }
      	        }
      	      cond[child_count-1]->add_Cond(buf[0],buf[1],buf[2],buf[3],buf[4]);
            }
        }

      /* Do not delete..
         displays the equations
      
      std::cout << ptr[child_count-1]->label;
      std::cout << ptr[child_count-1]->Get_Eqn() << std::endl;
      */
      
      /* Do not delete..
         displays the conditions
      
      cond[child_count-1]->disp_Cond();
      */
    }
  else
    std::cout << "Error in mode\n";
}
  

//! Sets the equation in the node
void 
Node::Set_Eqn(char* s)
{
  eqn = new char[strlen(s)+1];
  strcpy(eqn,s);
}


//! Returns the equation in the node
char* 
Node::Get_Eqn()
{
  return eqn;
}


//! Displays the equation in the node
void 
Node::disp_Eqn()
{
  std::cout << eqn << "." << std::endl;
}


//! Returns the no. of children a node has in the tree
int 
Node::Get_child_count()
{
  return(child_count);
}  


//! Displays the tree in Pre-order form
void 
Node::showTree()
{
  if (child_count!=0)
    for (int j=1; j<=child_count; j++)
      {  
        //std::cout << space << ptr[j-1]->label << "\n";
        std::cout << ptr[j-1]->label << "\n";
        //std::cout << "Equation:" << ptr[j-1]->eqn << "\n";
        //std::cout << space; 
        cond[j-1]->disp_Cond();
        //char* newspace = new char[100];
        //strcpy(newspace,space);
        //strcat(newspace,"  ");
        	  //ptr[j-1]->showTree(newspace);
        ptr[j-1]->showTree();
      }
  //std::cout << "Child count " << child_count << std::endl; 
}


//! Writes the tree into a file
void 
Node::write_Tree(char* file_String)
{
  if (child_count!=0)
    for (int j=1; j<=child_count; j++)
      {  
        strcat(file_String,ptr[j-1]->label);
        strcat(file_String,"\n");
        strcat(file_String,ptr[j-1]->eqn);
        strcat(file_String,"\n");
        strcat(file_String,ptr[j-1]->Get_Parent());
        strcat(file_String,"\n\n");
        //std::cout << "Writable string : " << file_String << " !!! Ends" << std::endl;

        char* create_file = new char[100];
        char* file_name = new char[100];
        strcpy(create_file,"touch ");
        strcat(create_file,ptr[j-1]->label);
        system(create_file);
        strcpy(file_name, ptr[j-1]->label);
        std::ofstream outfile(file_name);
        outfile << cond[j-1]->write_Cond();
        ptr[j-1]->write_Tree(file_String);
        
        delete create_file, file_name;
      }
}


//! Useful in FIND operation. Finds the equation given the end entities and the 
//! constraints
char* 
Node::Find_Eqn_def_mode(int a, int b, int c, int d, int e)
{
  int j=1; 
  int count=1;
  while ((count<=child_count) && (j==1))
    {
      int i=0;
      i=(cond[count-1]->Check_Cond(a,b,c,d,e));  
      if (i==1)
	      {
	        return(ptr[count-1]->Find_Eqn(a,b,c,d,e));
	        j=0;
	      }
      else count++;
    }
  if (j==1) 
    return eqn;
  else return((char *)"No equation exists");
}


//! Useful in FIND operation. Finds the equation given the end entities and the 
//! constraints. This procedure helps in stepping through the Tree during Search
char* 
Node::Find_Eqn(int a, int b, int c, int d, int e)
{
  int j=1; 
  int count=1;
  while ((count<=child_count) && (j==1))
    {
      int i=0;
      i=(cond[count-1]->Check_Cond(a,b,c,d,e));  
      //std::cout<<"CHECK CONDITION i = "<<i<<std::endl;
      if (i==1)
	      {
	        glo_flag = 0;
	        return(ptr[count-1]->eqn);
	        j=0;
	      }
      else count++;
    }
  if (j==1) 
    {
      glo_flag = 1;
      return eqn;
    }
  else
    {
      glo_flag = 2;
      return((char *)"No equation exists");
    }
}
