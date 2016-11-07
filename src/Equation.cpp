#include "Equation.h"


/*  All of the following methods generate the equation strings used to solve the equations in 
    Maple.  For each constraint type, distance, incidence, tangent, parallel, angle and
    perpendicular, there is a corresponding method of the form getDistanceEQ etc.  Each method
    simply a long case statement that considers the type of object at each endpoint of the edge
    and generates the appropriate equation.  In addition, whenever a constraint is generated
    any variables used are added to the global list of variables, vars, and are used later to
    generate a list of variables required as input for Maple.
*/
std::string 
getDistanceEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
               std::string theDist, List<std::string>& vars)
{
    std::string x1,x2,y1,y2,coeff,m,v,w,output, firstVal;
    int v1Name, v2Name;
    Vertex::Type type1, type2;
    float value;

    value=theEdge.returnValue();
    if(value<0) value=-value;
    if (theDist=="") firstVal=toString(sqrt(value));
    else firstVal=theDist;

    type1=vEnd1.returnType();
    type2=vEnd2.returnType();

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    x1="x"+toString(v1Name);
    y1="y"+toString(v1Name);
    x2="x"+toString(v2Name);
    y2="y"+toString(v2Name);

    if ((type1 == Vertex::Point   and type2 == Vertex::Ray)     or
        (type1 == Vertex::Line    and type2 == Vertex::Ray)     or
        (type1 == Vertex::Ray     and type2 == Vertex::Point)   or
        (type1 == Vertex::Ray     and type2 == Vertex::Line)    or
        (type1 == Vertex::Ray     and type2 == Vertex::Ray)     or
        (type1 == Vertex::Ray     and type2 == Vertex::LineSeg) or
        (type1 == Vertex::Ray     and type2 == Vertex::Circle)  or
        (type1 == Vertex::Ray     and type2 == Vertex::Arc)     or
        (type1 == Vertex::LineSeg and type2 == Vertex::Ray)     or
        (type1 == Vertex::Circle  and type2 == Vertex::Ray)     or
        (type1 == Vertex::Arc     and type2 == Vertex::Ray))
      {
        if (type1 == Vertex::Ray)
        {
          v="v"+toString(v1Name);
          w="w"+toString(v1Name);
          m="("+w+"/"+v+")";
          output="("+firstVal+")^2=(("+y1+"+"+y2+"-"+m+"*("+x1+"-"+x2+"))/(1+"+m+"^2))";
        }
        else
        {
          v="v"+toString(v2Name);
          w="w"+toString(v2Name);
          m="("+w+"/"+v+")";
          output="("+firstVal+")^2=(("+y2+"+"+y1+"-"+m+"*("+x2+"-"+x1+"))/(1+"+m+"^2))";
        }
        if(!vars.hasElem(v)) vars.append(v);
        if(!vars.hasElem(w)) vars.append(w);
        if(!vars.hasElem(x1)) vars.append(x1);
        if(!vars.hasElem(y1)) vars.append(y1);
        if(!vars.hasElem(x2)) vars.append(x2);
        if(!vars.hasElem(y2)) vars.append(y2);
      }
    else if ((type1 == Vertex::Point   and type2 == Vertex::Line)    or
             (type1 == Vertex::Point   and type2 == Vertex::LineSeg) or
             (type1 == Vertex::Line    and type2 == Vertex::Point)   or
             (type1 == Vertex::Line    and type2 == Vertex::Line)    or
             (type1 == Vertex::Line    and type2 == Vertex::LineSeg) or
             (type1 == Vertex::Line    and type2 == Vertex::Circle)  or
             (type1 == Vertex::Line    and type2 == Vertex::Arc)     or
             (type1 == Vertex::LineSeg and type2 == Vertex::Point)   or
             (type1 == Vertex::LineSeg and type2 == Vertex::Line)    or
             (type1 == Vertex::LineSeg and type2 == Vertex::LineSeg) or
             (type1 == Vertex::LineSeg and type2 == Vertex::Circle)  or
             (type1 == Vertex::LineSeg and type2 == Vertex::Arc)     or
             (type1 == Vertex::Circle  and type2 == Vertex::Line)    or
             (type1 == Vertex::Circle  and type2 == Vertex::LineSeg) or
             (type1 == Vertex::Arc     and type2 == Vertex::Line)    or
             (type1 == Vertex::Arc     and type2 == Vertex::LineSeg))
      {
        if(type1 == Vertex::Line or type1 == Vertex::LineSeg)
        {
          m="m"+toString(v1Name);
          output="("+firstVal+")^2=(("+y1+"+"+y2+"-"+m+"*("+x1+"-"+x2+"))/(1+"+m+"^2))";
        }
        else
        {
          m="m"+toString(v2Name);
          output="("+firstVal+")^2=(("+y2+"+"+y1+"-"+m+"*("+x2+"-"+x1+"))/(1+"+m+"^2))";
        }
        if(!vars.hasElem(m)) vars.append(m);
        if(!vars.hasElem(x1)) vars.append(x1);
        if(!vars.hasElem(y1)) vars.append(y1);
        if(!vars.hasElem(x2)) vars.append(x2);
        if(!vars.hasElem(y2)) vars.append(y2);
      }
    else
      {
        if(theDist=="") firstVal=toString(value);
		    else firstVal=theDist;
		    output="("+firstVal+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
        if(!vars.hasElem(x1)) vars.append(x1);
        if(!vars.hasElem(y1)) vars.append(y1);
        if(!vars.hasElem(x2)) vars.append(x2);
        if(!vars.hasElem(y2)) vars.append(y2);
      }
    return output;
}

std::string 
getDistance3DEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                 std::string theDist, List<std::string>& vars)
{
    std::string x1,x2,y1,y2,z1,z2,output,firstVal;
    int v1Name, v2Name;
    float value;

    value=theEdge.returnValue();
    if(value<0) value=-value;
    if (theDist=="") firstVal=toString(sqrt(value));
    else firstVal=theDist;

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    x1="x"+toString(v1Name);
    y1="y"+toString(v1Name);
    z1="z"+toString(v1Name);
    x2="x"+toString(v2Name);
    y2="y"+toString(v2Name);
    z2="z"+toString(v2Name);


    if(theDist=="") firstVal=toString(value);
    else firstVal=theDist;
		output="("+firstVal+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2+("+z1+"-"+z2+")^2)";
    if(!vars.hasElem(x1)) vars.append(x1);
    if(!vars.hasElem(y1)) vars.append(y1);
    if(!vars.hasElem(z1)) vars.append(z1);       
    if(!vars.hasElem(x2)) vars.append(x2);
    if(!vars.hasElem(y2)) vars.append(y2);
    if(!vars.hasElem(z2)) vars.append(z2);       

    return output;
}


std::string 
getAngle3DEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
              List<std::string>& vars) //, std::string theDist)
{
    std::string x1,x2,y1,y2,z1,z2,output,firstVal,c1,c2,d1,d2,e1,e2;
    int v1Name, v2Name;
    float value;

    value=theEdge.returnValue();
    if(value<0) value=-value;
    value=value*M_PI/180.0;
    firstVal=toString(cos(value));

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    x1="x"+toString(v1Name);
    y1="y"+toString(v1Name);
    z1="z"+toString(v1Name);
    x2="x"+toString(v2Name);
    y2="y"+toString(v2Name);
    z2="z"+toString(v2Name);
    c1="c"+toString(v1Name);
    d1="d"+toString(v1Name);
    e1="e"+toString(v1Name);
    c2="c"+toString(v2Name);
    d2="d"+toString(v2Name);
    e2="e"+toString(v2Name);

    output=firstVal+"=("+x1+"-"+c1+")*("+x2+"-"+c2+")+";
		output+="("+y1+"-"+d1+")*("+y2+"-"+d2+")+";
    output+="("+z1+"-"+e1+")*("+z2+"-"+e2+")";

    if(!vars.hasElem(x1)) vars.append(x1);
    if(!vars.hasElem(y1)) vars.append(y1);
    if(!vars.hasElem(z1)) vars.append(z1);       
    if(!vars.hasElem(x2)) vars.append(x2);
    if(!vars.hasElem(y2)) vars.append(y2);
    if(!vars.hasElem(z2)) vars.append(z2);
    
    return output;
}

//! returns an equation for a tangency constraint
std::string 
getTangencyEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
               List<std::string>& vars)
{
    int v1Name, v2Name;
    Vertex::Type type1, type2;
    std::string output="", dist="", r1, r2;

    type1=vEnd1.returnType();
    type2=vEnd2.returnType();

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();


    if ((type1 == Vertex::Line or type1 == Vertex::Ray or type1 == Vertex::LineSeg) and
        (type2 == Vertex::Circle or type2 == Vertex::Arc))
      {
        dist="r"+toString(v2Name);
        if(!vars.hasElem(dist)) vars.append(dist);
      }
    else if ((type2 == Vertex::Line or type2 == Vertex::Ray or type2 == Vertex::LineSeg) and
             (type1 == Vertex::Circle or type1 == Vertex::Arc))
      {
        dist="r"+toString(v1Name);
        if(!vars.hasElem(dist)) vars.append(dist);
      }
    else if ((type1 == Vertex::Circle and type2 == Vertex::Circle) or
             (type1 == Vertex::Arc and type2 == Vertex::Arc))
      {
        dist="r"+toString(v1Name)+"+r"+toString(v2Name);
        r1="r"+toString(v1Name);
        r2="r"+toString(v2Name);
        if(!vars.hasElem(r1)) vars.append(r1);
        if(!vars.hasElem(r2)) vars.append(r2);
      }
    if(dist!="") output=getDistanceEQ(vEnd1, vEnd2, theEdge, dist, vars);
    return output;
}

//! returns an equation corresponding to an incidence constraint
std::string 
getIncidenceEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
                List<std::string>& vars)
{
    int v1Name, v2Name, part1, part2;;
    Vertex::Type type1, type2;
    std::string output="", dist;
    std::string x1, y1, a1, b1, c1, d1, e1, zz1, g1, l1, m1, r1, v1, w1;
    std::string x2, y2, a2, b2, c2, d2, e2, zz2, g2, l2, m2, r2, v2, w2;
    std::string z1, z2;


    type1=vEnd1.returnType();
    type2=vEnd2.returnType();
    part1=theEdge.returnPart1();
    part2=theEdge.returnPart2();

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    z1=toString(v1Name);
    z2=toString(v2Name);
    x1="x"+z1;
    y1="y"+z1;
    zz1="z"+z1;
    a1="a"+z1;
    b1="b"+z1;
    c1="c"+z1;
    d1="d"+z1; 
    e1="e"+z1;
    g1="g"+z1;
    l1="l"+z1;
    m1="m"+z1;
    r1="r"+z1;
    v1="v"+z1;
    w1="w"+z1;
    x2="x"+z2;
    y2="y"+z2;
    zz2="z"+z2;
    a2="a"+z2;
    b2="b"+z2;
    c2="c"+z2;
    d2="d"+z2;
    e2="e"+z2;
    g2="g"+z2;
    l2="l"+z2;
    m2="m"+z2;
    r2="r"+z2;
    v2="v"+z2;
    w2="w"+z2;
    /*  Key to above lettering:

        (x,y) - base point for all shapes
        (c,d) - second point
        (p,q) - translation point for clusters
        (v,w) - first angle
        (a,b) - second angle
        (t,s) - translation angle for clusters
          r   - radius
          g   - separtion angle
          l   - length
    */

    if (type1 == Vertex::Point and type2 == Vertex::Point)
      {
        output=x1+"="+x2+","+y1+"="+y2;
        if(!vars.hasElem(x1)) vars.append(x1);
        if(!vars.hasElem(y1)) vars.append(y1);
        if(!vars.hasElem(x2)) vars.append(x2);
        if(!vars.hasElem(y2)) vars.append(y2);
      }
    else if (type1 == Vertex::Point and type2 == Vertex::Line)
      {
        output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(x1)) vars.append(x1);
        if(!vars.hasElem(y1)) vars.append(y1);
        if(!vars.hasElem(x2)) vars.append(x2);
        if(!vars.hasElem(y2)) vars.append(y2);
      }
    else if (type1 == Vertex::Line and type2 == Vertex::Point)
      {
        output="("+y2+"-"+y1+")="+m1+"*("+x2+"-"+x1+")";
        if(!vars.hasElem(m1)) vars.append(m1);
        if(!vars.hasElem(x1)) vars.append(x1);
        if(!vars.hasElem(y1)) vars.append(y1);
        if(!vars.hasElem(x2)) vars.append(x2);
        if(!vars.hasElem(y2)) vars.append(y2);
      }
    else if (type1 == Vertex::Point and type2 == Vertex::Ray)
      {
        if(part2==0)
        {
          output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
          if(!vars.hasElem(m2)) vars.append(m2);
          if(!vars.hasElem(x1)) vars.append(x1);
          if(!vars.hasElem(y1)) vars.append(y1);
          if(!vars.hasElem(x2)) vars.append(x2);
          if(!vars.hasElem(y2)) vars.append(y2);
        }
        else
        {
           output=x1+"="+x2+","+y1+"="+y2;
           if(!vars.hasElem(x1)) vars.append(x1);
           if(!vars.hasElem(y1)) vars.append(y1);
           if(!vars.hasElem(x2)) vars.append(x2);
           if(!vars.hasElem(y2)) vars.append(y2);
        }
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Point)
      {
        if(part1==0)
        {
          output="("+y2+"-"+y1+")="+"("+w1+"/"+v1+")"+"*("+x2+"-"+x1+")";
          if(!vars.hasElem(v1)) vars.append(v1);
          if(!vars.hasElem(w1)) vars.append(w1);
          if(!vars.hasElem(x1)) vars.append(x1);
          if(!vars.hasElem(y1)) vars.append(y1);
          if(!vars.hasElem(x2)) vars.append(x2);
          if(!vars.hasElem(y2)) vars.append(y2);
        }
        else
        {
           output=x1+"="+x2+","+y1+"="+y2;
           if(!vars.hasElem(x1)) vars.append(x1);
           if(!vars.hasElem(y1)) vars.append(y1);
           if(!vars.hasElem(x2)) vars.append(x2);
           if(!vars.hasElem(y2)) vars.append(y2);
        }
      }
    else if (type1 == Vertex::Point and type2 == Vertex::LineSeg)
      {
        switch (part1*10+part2)
        {
               case 10: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 12: output=x1+"="+c2+","+y1+"="+d2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
        }
      }
    else if (type1 == Vertex::LineSeg and type2 == Vertex::Point)
      {
        switch (part1*10+part2)
        {
               case 1:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 21: output=c1+"="+x2+","+d1+"="+y2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Point and type2 == Vertex::Circle)
      {
        switch (part1*10+part2)
        {
               case 10: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r2, vars);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 13: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Circle and type2 == Vertex::Point)
      {
        switch (part1*10+part2)
        {
               case 1:  output=getDistanceEQ(vEnd1,vEnd2,theEdge,r1, vars);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 31: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Point and type2 == Vertex::Arc)
      {
        switch (part1*10+part2)
        {
               case 10: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r2, vars);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 11: output=x1+"="+x2+"+"+v2+"*"+r2+","+y1+"="+y2+"+"+w2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(y2)) vars.append(r2);
                        break;
               case 12: output=x1+"="+x2+"+"+a2+"*"+r2+","+y1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 13: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Point)
      {
        switch (part1*10+part2)
        {
               case 1: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r1, vars);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 11: output=x2+"="+x1+"+"+v1+"*"+r1+","+y2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(x2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 21: output=x2+"="+x1+"+"+a1+"*"+r1+","+y2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(x2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 31: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Line and type2 == Vertex::Line)
      {
        output="";
      }
    else if (type1 == Vertex::Line and type2 == Vertex::Ray)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Line)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 10: output="("+y2+"-"+y1+")="+m2+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Line and type2 == Vertex::LineSeg)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 2:  output="("+y1+"-"+d2+")="+m1+"*("+x1+"-"+c2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
        }
      }
    else if (type1 == Vertex::LineSeg and type2 == Vertex::Line)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 10: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 20: output="("+d1+"-"+y2+")="+m2+"*("+c1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Line and type2 == Vertex::Circle)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 3:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Circle and type2 == Vertex::Line)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 30: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Line and type2 == Vertex::Arc)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y1+"-"+"("+y2+"+"+r2+"*"+w2+")"+")="+m1+"*("+x1+"-"+"("+x2+"+"+r2+"*"+v2+")"+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        break;
               case 2:  output="("+y1+"-"+"("+y2+"+"+r2+"*"+b2+")"+")="+m1+"*("+x1+"-"+"("+x2+"+"+r2+"*"+a2+")"+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        break;
               case 3:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Line)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 10: output="("+y2+"-"+"("+y1+"+"+r1+"*"+w1+")"+")="+m2+"*("+x2+"-"+"("+x1+"+"+r1+"*"+v1+")"+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        break;
               case 20: output="("+y2+"-"+"("+y1+"+"+r1+"*"+b1+")"+")="+m2+"*("+x2+"-"+"("+x1+"+"+r1+"*"+a1+")"+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        break;
               case 30: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Ray)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y2+"-"+y1+")="+"("+w1+"/"+v1+")"+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+y1+"-"+y2+")="+"("+w2+"/"+v2+")"+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 11: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::LineSeg)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y2+"-"+y1+")="+"("+w1+"/"+v1+")"+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 2:  output="("+d2+"-"+y1+")="+"("+w1+"/"+v1+")"+"*("+c2+"-"+x1+")";
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
               case 10: output="("+y2+"-"+y1+")="+m2+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 12: output=x1+"="+c2+","+y1+"="+d2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
        }
      }
    else if (type1 == Vertex::LineSeg and type2 == Vertex::Ray)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y2+"-"+y1+")="+m1+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+y1+"-"+y2+")="+"("+w2+"/"+v2+")"+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 20: output="("+d1+"-"+y2+")="+"("+w2+"/"+v2+")"+"*("+c1+"-"+x2+")";
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        break;
               case 11: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 21: output=x2+"="+c1+","+y2+"="+d1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        break;
        }
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Circle)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 3:  output="("+y2+"-"+y1+")="+"("+w1+"/"+v1+")"+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+r2+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 13: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Circle and type2 == Vertex::Ray)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 30: output="("+y1+"-"+y2+")="+"("+w2+"/"+v2+")"+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 1:  output="("+r1+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 31: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Arc)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y1+"-"+"("+y2+"+"+r2+"*"+w2+")"+")="+"("+w1+"/"+v1+")"+"*("+x1+"-"+"("+x2+"+"+r2+"*"+v2+")"+")";
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        break;
               case 2:  output="("+y1+"-"+"("+y2+"+"+r2+"*"+b2+")"+")="+"("+w1+"/"+v1+")"+"*("+x1+"-"+"("+x2+"+"+r2+"*"+a2+")"+")";
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        break;
               case 3:  output="("+y2+"-"+y1+")="+"("+w1+"/"+v1+")"+"*("+x2+"-"+x1+")";
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+r2+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x1+"="+x2+"+"+v2+"*"+r2+","+y1+"="+y2+"+"+w2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(y2)) vars.append(r2);
                        break;
               case 12: output=x1+"="+x2+"+"+a2+"*"+r2+","+y1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 13: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Ray)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+r1+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+y2+"-"+"("+y1+"+"+r1+"*"+w1+")"+")="+"("+w2+"/"+v2+")"+"*("+x2+"-"+"("+x1+"+"+r1+"*"+v1+")"+")";
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        break;
               case 20: output="("+y2+"-"+"("+y1+"+"+r1+"*"+b1+")"+")="+"("+w2+"/"+v2+")"+"*("+x2+"-"+"("+x1+"+"+r1+"*"+a1+")"+")";
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        break;
               case 30: output="("+y1+"-"+y2+")="+"("+w2+"/"+v2+")"+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 11: output=x2+"="+x1+"+"+v1+"*"+r1+","+y2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(y1)) vars.append(r1);
                        break;
               case 21: output=x2+"="+x1+"+"+a1+"*"+r1+","+y2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 31: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::LineSeg and type2 == Vertex::LineSeg)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 2:  output="("+y1+"-"+d2+")="+m1+"*("+x1+"-"+c2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
               case 10: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 20: output="("+y1+"-"+d2+")="+m2+"*("+x1+"-"+c2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 12: output=x1+"="+c2+","+y1+"="+d2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
               case 21: output=c1+"="+x2+","+d1+"="+y2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 22: output=c1+"="+c2+","+d1+"="+d2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        break;
        }
      }
    else if (type1 == Vertex::LineSeg and type2 == Vertex::Circle)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 3:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+r2+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 13: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 20: output="("+r2+")^2=(("+c1+"-"+x2+")^2+("+d1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 23: output=c1+"="+x2+","+d1+"="+y2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Circle and type2 == Vertex::LineSeg)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 30: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 1:  output="("+r1+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 2:  output="("+r1+")^2=(("+c2+"-"+x1+")^2+("+d2+"-"+y1+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 31: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 32: output=c2+"="+x1+","+d2+"="+y1;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::LineSeg and type2 == Vertex::Arc)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+y1+"-"+"("+y2+"+"+r2+"*"+w2+")"+")="+m1+"*("+x1+"-"+"("+x2+"+"+r2+"*"+v2+")"+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        break;
               case 2:  output="("+y1+"-"+"("+y2+"+"+r2+"*"+b2+")"+")="+m1+"*("+x1+"-"+"("+x2+"+"+r2+"*"+a2+")"+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        break;
               case 3:  output="("+y1+"-"+y2+")="+m1+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m1)) vars.append(m1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 10: output="("+r2+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 20: output="("+r2+")^2=(("+c1+"-"+x2+")^2+("+d1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x1+"="+x2+"+"+v2+"*"+r2+","+y1+"="+y2+"+"+w2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(y2)) vars.append(r2);
                        break;
               case 12: output=x1+"="+x2+"+"+a2+"*"+r2+","+y1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 13: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 21: output=c1+"="+x2+"+"+v2+"*"+r2+","+d1+"="+y2+"+"+w2+"*"+r2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(y2)) vars.append(r2);
                        break;
               case 22: output=c1+"="+x2+"+"+a2+"*"+r2+","+d1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 23: output=c1+"="+x2+","+d1+"="+y2;
                        if(!vars.hasElem(c1)) vars.append(c1);
                        if(!vars.hasElem(d1)) vars.append(d1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::LineSeg)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+r1+")^2=(("+x1+"-"+x2+")^2+("+y1+"-"+y2+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 2:  output="("+r1+")^2=(("+c2+"-"+x1+")^2+("+d2+"-"+y1+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 10: output="("+y2+"-"+"("+y1+"+"+r1+"*"+w1+")"+")="+m2+"*("+x2+"-"+"("+x1+"+"+r1+"*"+v1+")"+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        break;
               case 20: output="("+y2+"-"+"("+y1+"+"+r1+"*"+b1+")"+")="+m2+"*("+x2+"-"+"("+x1+"+"+r1+"*"+a1+")"+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        break;
               case 30: output="("+y1+"-"+y2+")="+m2+"*("+x1+"-"+x2+")";
                        if(!vars.hasElem(m2)) vars.append(m2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 11: output=x2+"="+x1+"+"+v1+"*"+r1+","+y2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(x2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 21: output=x2+"="+x1+"+"+a1+"*"+r1+","+y2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(x2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 31: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 12: output=c2+"="+x1+"+"+v1+"*"+r1+","+d2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(y1)) vars.append(r1);
                        break;
               case 22: output=c2+"="+x1+"+"+a1+"*"+r1+","+d2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 32: output=c2+"="+x1+","+d2+"="+y1;
                        if(!vars.hasElem(c2)) vars.append(c2);
                        if(!vars.hasElem(d2)) vars.append(d2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
        }
      }
    else if (type1 == Vertex::Circle and type2 == Vertex::Circle)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 3:  output=getDistanceEQ(vEnd1,vEnd2,theEdge,r1, vars);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 30: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r2, vars);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 33: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Circle and type2 == Vertex::Arc)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 30: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r2, vars);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 1:  output="("+r1+")^2=(("+x2+"+"+v2+"*"+r2+"-"+x1+")^2+("+y2+"+"+w2+"*"+r2+"-"+y1+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 2:  output="("+r1+")^2=(("+x2+"+"+a2+"*"+r2+"-"+x1+")^2+("+y2+"+"+b2+"*"+r2+"-"+y1+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 3:  output=getDistanceEQ(vEnd1,vEnd2,theEdge,r1, vars);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 31: output=x1+"="+x2+"+"+v2+"*"+r2+","+y1+"="+y2+"+"+w2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(y2)) vars.append(r2);
                        break;
               case 32: output=x1+"="+x2+"+"+a2+"*"+r2+","+y1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 33: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Circle)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 3:  output=getDistanceEQ(vEnd1,vEnd2,theEdge,r1, vars);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 10: output="("+r2+")^2=(("+x1+"+"+v1+"*"+r1+"-"+x2+")^2+("+y1+"+"+w1+"*"+r1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 20: output="("+r2+")^2=(("+x1+"+"+a1+"*"+r1+"-"+x2+")^2+("+y1+"+"+b1+"*"+r1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 30: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r2, vars);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 13: output=x2+"="+x1+"+"+v1+"*"+r1+","+y2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(y1)) vars.append(r1);
                        break;
               case 23: output=x2+"="+x1+"+"+a1+"*"+r1+","+y2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 33: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Arc)
      {
        switch (part1*10+part2)
        {
               case 0:  output="";
                        break;
               case 1:  output="("+r1+")^2=(("+x2+"+"+v2+"*"+r2+"-"+x1+")^2+("+y2+"+"+w2+"*"+r2+"-"+y1+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 2:  output="("+r1+")^2=(("+x2+"+"+a2+"*"+r2+"-"+x1+")^2+("+y2+"+"+b2+"*"+r2+"-"+y1+")^2)";
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        break;
               case 3:  output=getDistanceEQ(vEnd1,vEnd2,theEdge,r1, vars);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 10: output="("+r2+")^2=(("+x1+"+"+v1+"*"+r1+"-"+x2+")^2+("+y1+"+"+w1+"*"+r1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 20: output="("+r2+")^2=(("+x1+"+"+a1+"*"+r1+"-"+x2+")^2+("+y1+"+"+b1+"*"+r1+"-"+y2+")^2)";
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
               case 30: output=getDistanceEQ(vEnd1,vEnd2,theEdge,r2, vars);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 11: output=x2+"+"+v2+"*"+r2+"="+x1+"+"+v1+"*"+r1+","+y2+"+"+w2+"*"+r2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 21: output=x2+"+"+v2+"*"+r2+"="+x1+"+"+a1+"*"+r1+","+y2+"+"+w2+"*"+r2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 31: output=x1+"="+x2+"+"+v2+"*"+r2+","+y1+"="+y2+"+"+w2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(v2)) vars.append(v2);
                        if(!vars.hasElem(w2)) vars.append(w2);
                        if(!vars.hasElem(y2)) vars.append(r2);
                        break;
               case 12: output=x1+"+"+v1+"*"+r1+"="+x2+"+"+a2+"*"+r2+","+y1+"+"+w1+"*"+r1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 22: output=x1+"+"+a1+"*"+r1+"="+x2+"+"+a2+"*"+r2+","+y1+"+"+b1+"*"+r1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 32: output=x1+"="+x2+"+"+a2+"*"+r2+","+y1+"="+y2+"+"+b2+"*"+r2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(a2)) vars.append(a2);
                        if(!vars.hasElem(b2)) vars.append(b2);
                        if(!vars.hasElem(r2)) vars.append(r2);
                        break;
               case 13: output=x2+"="+x1+"+"+v1+"*"+r1+","+y2+"="+y1+"+"+w1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(v1)) vars.append(v1);
                        if(!vars.hasElem(w1)) vars.append(w1);
                        if(!vars.hasElem(y1)) vars.append(r1);
                        break;
               case 23: output=x2+"="+x1+"+"+a1+"*"+r1+","+y2+"="+y1+"+"+b1+"*"+r1;
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(a1)) vars.append(a1);
                        if(!vars.hasElem(b1)) vars.append(b1);
                        if(!vars.hasElem(r1)) vars.append(r1);
                        break;
               case 33: output=x1+"="+x2+","+y1+"="+y2;
                        if(!vars.hasElem(x1)) vars.append(x1);
                        if(!vars.hasElem(y1)) vars.append(y1);
                        if(!vars.hasElem(x2)) vars.append(x2);
                        if(!vars.hasElem(y2)) vars.append(y2);
                        break;
        }
      }

    return output;
}

//! returns an equation corresponding to a angle constraint
std::string 
getAngleEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
            List<std::string>& vars)
{
    int v1Name, v2Name;
    Vertex::Type type1, type2;
    std::string output="", tanAngleStr, m1, m2, mA, mB, v1, v2, w1, w2, a1, a2, b1, b2;
    std::string n1, n2;
    float tanAngle;


    type1=vEnd1.returnType();
    type2=vEnd2.returnType();

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    n1=toString(v1Name);
    n2=toString(v2Name);

    m1="m"+n1;
    v1="v"+n1;
    w1="w"+n1;
    a1="a"+n1;
    b1="b"+n1;
    m2="m"+n2;
    v2="v"+n2;
    w2="w"+n2;
    a2="a"+n2;
    b2="b"+n2;

    tanAngle=tan(theEdge.returnValue()*M_PI/180.0);
    tanAngle=tanAngle*tanAngle*10000;
    tanAngle=floor(tanAngle);
    tanAngle=tanAngle/10000;
    tanAngleStr=toString(tanAngle);

    if ((type1 == Vertex::Line or type1 == Vertex::LineSeg) and
        (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA=m1;
        mB=m2;
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(m1)) vars.append(m1);
      }
    else if (type1 == Vertex::Ray and
             (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA="("+w1+"/"+v1+")";
        mB=m2;
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Ray)
      {
        mA="("+w1+"/"+v1+")";
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
      }
    else if (type2 == Vertex::Ray and
             (type1 == Vertex::Line or type1 == Vertex::LineSeg))
      {
        mA=m1;
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(m1)) vars.append(m1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
      }
    else if (type1 == Vertex::Arc and
             (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA="((1-"+v1+"*"+a1+"+"+w1+"*"+b1+")/("+w1+"*"+a1+"+"+v1+"*"+b1+"))";
        mB=m2;
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(a1)) vars.append(a1);
        if(!vars.hasElem(b1)) vars.append(b1);
        if(!vars.hasElem(m2)) vars.append(m2);
      }
    else if (type2 == Vertex::Arc and
             (type1 == Vertex::Line or type1 == Vertex::LineSeg))
      {
        mA=m1;
        mB="((1-"+v2+"*"+a2+"+"+w2+"*"+b2+")/("+w2+"*"+a2+"+"+v2+"*"+b2+"))";
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
        if(!vars.hasElem(a2)) vars.append(a2);
        if(!vars.hasElem(b2)) vars.append(b2);
        if(!vars.hasElem(m1)) vars.append(m1);
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Ray)
      {
        mA="((1-"+v1+"*"+a1+"+"+w1+"*"+b1+")/("+w1+"*"+a1+"+"+v1+"*"+b1+"))";
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(a1)) vars.append(a1);
        if(!vars.hasElem(b1)) vars.append(b1);
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Arc)
      {
        mA="("+w1+"/"+v1+")";
        mB="((1-"+v2+"*"+a2+"+"+w2+"*"+b2+")/("+w2+"*"+a2+"+"+v2+"*"+b2+"))";
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
        if(!vars.hasElem(a2)) vars.append(a2);
        if(!vars.hasElem(b2)) vars.append(b2);
      }
    else if (type1 == Vertex::Arc and type2 == Vertex::Arc)
      {
        mA="((1-"+v1+"*"+a1+"+"+w1+"*"+b1+")/("+w1+"*"+a1+"+"+v1+"*"+b1+"))";
        mB="((1-"+v2+"*"+a2+"+"+w2+"*"+b2+")/("+w2+"*"+a2+"+"+v2+"*"+b2+"))";
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(a1)) vars.append(a1);
        if(!vars.hasElem(b1)) vars.append(b1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
        if(!vars.hasElem(a2)) vars.append(a2);
        if(!vars.hasElem(b2)) vars.append(b2);
      }

    if(mA!="" || mB!="") output="("+tanAngleStr+")=(("+mA+"-"+mB+")/(1+"+mA+"*"+mB+"))^2";
    else output="";
    return output;
}

//! returns an equation for a parallel constraint
std::string 
getParallelEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, 
               List<std::string>& vars)
{
    int v1Name, v2Name;
    Vertex::Type type1, type2;
    std::string output="",mB,mA,m1,v1,w1,m2,v2,w2,n1,n2;

    type1=vEnd1.returnType();
    type2=vEnd2.returnType();

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    n1=toString(v1Name);
    n2=toString(v2Name);

    m1="m"+n1;
    v1="v"+n1;
    w1="w"+n1;
    m2="m"+n2;
    v2="v"+n2;
    w2="w"+n2;
 
    if ((type1 == Vertex::Line or type1 == Vertex::LineSeg) and
        (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA=m1;
        mB=m2;
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(m1)) vars.append(m1);
      }
    else if (type1 == Vertex::Ray and
             (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA="("+w1+"/"+v1+")";
        mB=m2;
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Ray)
      {
        mA="("+w1+"/"+v1+")";
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
      }
    else if (type2 == Vertex::Ray and
             (type1 == Vertex::Line or type1 == Vertex::LineSeg))
      {
        mA=m1;
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(m1)) vars.append(m1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
      }
    output="";
    if(mA!="" || mB!="") output=mA+"="+mB;
    return output;
}

//! returns an equation corresponding to a perpendicularity constraint
std::string 
getPerpendicularEQ (Vertex &vEnd1, Vertex &vEnd2, Edge &theEdge, List<std::string>& vars)
{
    int v1Name, v2Name;
    Vertex::Type type1, type2;
    std::string output="",mB,mA,m1,v1,w1,m2,v2,w2,n1,n2;

    type1=vEnd1.returnType();
    type2=vEnd2.returnType();

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    n1=toString(v1Name);
    n2=toString(v2Name);

    m1="m"+n1;
    v1="v"+n1;
    w1="w"+n1;
    m2="m"+n2;
    v2="v"+n2;
    w2="w"+n2;

    
    if ((type1 == Vertex::Line or type1 == Vertex::LineSeg) and 
        (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA=m1;
        mB=m2;
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(m1)) vars.append(m1);
      }
    else if (type1 == Vertex::Ray and 
             (type2 == Vertex::Line or type2 == Vertex::LineSeg))
      {
        mA="("+w1+"/"+v1+")";
        mB=m2;
        if(!vars.hasElem(m2)) vars.append(m2);
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
      }
    else if (type1 == Vertex::Ray and type2 == Vertex::Ray)
      {
        mA="("+w1+"/"+v1+")";
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(v1)) vars.append(v1);
        if(!vars.hasElem(w1)) vars.append(w1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
      }
    else if (type2 == Vertex::Ray and 
             (type1 == Vertex::Line or type1 == Vertex::LineSeg))
      {
        mA=m1;
        mB="("+w2+"/"+v2+")";
        if(!vars.hasElem(m1)) vars.append(m1);
        if(!vars.hasElem(v2)) vars.append(v2);
        if(!vars.hasElem(w2)) vars.append(w2);
      }
 
    output="";
    if(mA!="" || mB!="") output="(-1)="+mA+"*"+mB;
    return output;}

//! returns -1 if the edge is not in the cluster
//! returns  0 if the edge is in the cluster, DOES in a subcluster)
//! returns  1 if the edge is between two clusters or between a cluster and original V
int getEdgeCode(Edge &theEdge, Cluster &theCluster)
{
    int i, length, childLength, origLength;
    bool isEnd;
    List<int> childrenWithEnd1, childrenWithEnd2;

    childrenWithEnd1.makeEmpty();
    childrenWithEnd2.makeEmpty();

    childLength=(theCluster.children).returnLen();
    origLength=theCluster.returnOrigLen();

    isEnd=(childLength==origLength);

    length=(theCluster.children).returnLen();

    if(length==0)
	 return -1;

    bool inOrig1,inOrig2;

    inOrig1=inOriginalV(theEdge.returnEnd1(),theCluster);
    inOrig2=inOriginalV(theEdge.returnEnd2(),theCluster);

    if((!inOrig1) || (!inOrig2))
    {
      	return -1;
    }

    if(isEnd) return 0;

    for(i=1;i<=length;i++)
    {
       if(inOriginalV(theEdge.returnEnd1(), (theCluster.children).retrieve(i)))
         childrenWithEnd1.append(i);
       if(inOriginalV(theEdge.returnEnd2(), (theCluster.children).retrieve(i)))
         childrenWithEnd2.append(i);
    }
 
    std::cout<<std::endl;
    std::cout<<"Before End1 List: ";
    for(i=1;i<=childrenWithEnd1.returnLen();i++)
	std::cout<<childrenWithEnd1.retrieve(i);

    std::cout<<std::endl;
    std::cout<<"Before End2 List: ";
    for(i=1;i<=childrenWithEnd2.returnLen();i++)
        std::cout<<childrenWithEnd2.retrieve(i);
    std::cout<<std::endl;

/*
    for(i=1;i<=childrenWithEnd1.returnLen();i++)
       if(childrenWithEnd2.hasElem(childrenWithEnd1.retrieve(i))) return -1;
*/

    for(i=1;i<=childLength;i++)
	if(childrenWithEnd1.hasElem(i) && childrenWithEnd2.hasElem(i))
	{
		childrenWithEnd1.deleteElem(i);
		childrenWithEnd2.deleteElem(i);
		return 0;
	}

    return 1;

}

//! returns -1 if the edge is not in the cluster
//! returns  0 if the edge is in the cluster, DOES in one subcluster)
//! returns  1 if the edge is between two clusters ch1 and ch2
int getEdgeCode(Edge &theEdge, Cluster &theCluster, int ch1, int ch2)
{
    int i, length, childLength, origLength;
    bool isEnd;
    List<int> childrenWithEnd1, childrenWithEnd2;

	std::ofstream outf;
//    outf.open("getEdgeCode.out", std::ios::app);
	outf << "The beginning+++++++++++++" << std::endl;
	outf << "The edge is: " << theEdge << std::endl;
	outf << "The cluster is: " << std::endl;
	outf << theCluster << std::endl;
	
    childrenWithEnd1.makeEmpty();
    childrenWithEnd2.makeEmpty();

    childLength=(theCluster.children).returnLen();
    origLength=theCluster.returnOrigLen();
   
   	outf << "childLenth = " << childLength << std::endl;
 	outf << "origLength = " << origLength << std::endl;
 	
    isEnd=(childLength==origLength);

    length=(theCluster.children).returnLen();

    if(length==0)
	 return -1;

    bool inOrig1,inOrig2;

    inOrig1=inOriginalV(theEdge.returnEnd1(),theCluster);
    inOrig2=inOriginalV(theEdge.returnEnd2(),theCluster);

    if((!inOrig1) || (!inOrig2))
    {
      	return -1;
    }

    if(isEnd) return 0;

    for(i=1;i<=length;i++)
    {
       if(inOriginalV(theEdge.returnEnd1(), (theCluster.children).retrieve(i)))
         childrenWithEnd1.append(i);
       if(inOriginalV(theEdge.returnEnd2(), (theCluster.children).retrieve(i)))
         childrenWithEnd2.append(i);
    }
 
    outf <<std::endl;
    outf<<"Before End1 List: ";
    for(i=1;i<=childrenWithEnd1.returnLen();i++)
	outf<<childrenWithEnd1.retrieve(i);

    outf<<std::endl;
    outf<<"Before End2 List: ";
    for(i=1;i<=childrenWithEnd2.returnLen();i++)
        outf<<childrenWithEnd2.retrieve(i);
    outf<<std::endl;

    for(i=1;i<=childLength;i++)
    {
    	//the edge is contained in one child cluster, return 0
	if(childrenWithEnd1.hasElem(i) && childrenWithEnd2.hasElem(i))
	{
		childrenWithEnd1.deleteElem(i);
		childrenWithEnd2.deleteElem(i);
		outf << "the common child cluster index is: " << i << std::endl;
		
			return 0;	
	}
    }
    //The edge is between ch1 and ch2
    if((childrenWithEnd1.hasElem(ch1) && childrenWithEnd2.hasElem(ch2))
	|| (childrenWithEnd1.hasElem(ch2) && childrenWithEnd2.hasElem(ch1)))
	return 1;

    return 2;

}


//! When the DR-Planner needs to know whether an edge is between or in a cluster, the case
//! where it is in must take precedence over the case where it is between.  Of course,
//! the solver needs the opposite, thus two methods.
int getEdgeCodeDRPlanner(Edge &theEdge, Cluster &theCluster)
{
    int i, length, childLength, origLength;
    bool isEnd;
    List<int> childrenWithEnd1, childrenWithEnd2;
    
    std::ofstream outf;
//    outf.open("getEdgeCodeDRPlanner.out", std::ios::app);
    outf << "The beginning:" << std::endl;
    outf << "The edge is:" << theEdge << std::endl;   
    outf << "The cluster is:" << std::endl;
    outf << theCluster << std::endl;
      
    childrenWithEnd1.makeEmpty();
    childrenWithEnd2.makeEmpty();
    
    childLength=(theCluster.children).returnLen();
    origLength=theCluster.returnOrigLen();
        
    isEnd=(childLength==origLength);
    
    length=(theCluster.children).returnLen();
    outf << "length = " << length << std::endl;
    if(length==0)
         return -1;
                    
    bool inOrig1,inOrig2;
    
    inOrig1=inOriginalV(theEdge.returnEnd1(),theCluster);
    inOrig2=inOriginalV(theEdge.returnEnd2(),theCluster);
	outf << "inorig1 = " << inOrig1 << "    inOrig2 = " << inOrig2 << std::endl;

    if((!inOrig1) || (!inOrig2))
    {
        return -1;
    }

    if(isEnd) return 0;
          
    for(i=1;i<=length;i++)
    {
       if(inOriginalV(theEdge.returnEnd1(), (theCluster.children).retrieve(i)))
         childrenWithEnd1.append(i);
       if(inOriginalV(theEdge.returnEnd2(), (theCluster.children).retrieve(i)))
         childrenWithEnd2.append(i);
    }
                    
    std::cout<<std::endl;
    std::cout<<"End1 List: ";
    for(i=1;i<=childrenWithEnd1.returnLen();i++)
        std::cout<<childrenWithEnd1.retrieve(i);
          
    std::cout<<std::endl;
    std::cout<<"End2 List: ";
    for(i=1;i<=childrenWithEnd2.returnLen();i++)
        std::cout<<childrenWithEnd2.retrieve(i);
    std::cout<<std::endl;
                    
/*   
    for(i=1;i<=childrenWithEnd1.returnLen();i++)
       if(childrenWithEnd2.hasElem(childrenWithEnd1.retrieve(i))) return -1;
*/

    for(i=1;i<=childLength;i++)
        if(childrenWithEnd1.hasElem(i) && childrenWithEnd2.hasElem(i))
        {
                childrenWithEnd1.deleteElem(i);
                childrenWithEnd2.deleteElem(i);
        }
    
    if(childrenWithEnd1.returnLen()!=0 && childrenWithEnd2.returnLen()!=0) return 1;
    else return 0;
    
}


//! switchString takes an string as input then replaces all of the variables 
//! from a given cluster with an expression for that variable times the 2D 
//! rotation matrix. The boolean allows the method to also replace the variables
//! with strings representing there real solved positions.
std::string 
switchString (Vertex &theVertex, Vertex::Type type, int shapeName, 
              int clusterName, std::string toReplace, bool solveOrValue, 
              List<std::string>& vars, int graphDimen)
{
    std::string repStr1, repStr2, repStr3, repStr4, repStr5, repStr6;
    std::string repStrb1, repStrb2, repStrb3, repStrb4, repStrb5, repStrb6;
    std::string newStr1, newStr2, newStr3, newStr4, newStr5, newStr6;
    std::string clusterV1, clusterV2, clusterV3, clusterV4;
    std::string clusterV5, clusterV6, clusterV7, clusterV8, clusterV9;
    std::string output;
	
    std::ofstream outf;
//	outf.open("switchString.out", std::ios::app);
    outf<<"IN SWITCHSTRING"<<std::endl;

    outf<<"clusterName="<<clusterName<<std::endl;
    outf<<"toReplace="<<toReplace<<std::endl;

    if(solveOrValue)
    {
      clusterV1="p"+toString(clusterName);
      clusterV2="q"+toString(clusterName);
      clusterV3="t"+toString(clusterName);
      clusterV4="s"+toString(clusterName);

      if(graphDimen==3)
      {	
        clusterV5="f"+toString(clusterName);
        clusterV6="h"+toString(clusterName);
        clusterV7="j"+toString(clusterName);
        clusterV8="k"+toString(clusterName);
        clusterV9="n"+toString(clusterName);
	if(!vars.hasElem(clusterV5)) vars.append(clusterV5);
        if(!vars.hasElem(clusterV6)) vars.append(clusterV6);
        if(!vars.hasElem(clusterV7)) vars.append(clusterV7);
        if(!vars.hasElem(clusterV8)) vars.append(clusterV8);
        if(!vars.hasElem(clusterV9)) vars.append(clusterV9);
      }

      if(!vars.hasElem(clusterV1)) vars.append(clusterV1);
      if(!vars.hasElem(clusterV2)) vars.append(clusterV2);
      if(!vars.hasElem(clusterV3)) vars.append(clusterV3);
      if(!vars.hasElem(clusterV4)) vars.append(clusterV4);
    }

    output=toReplace;


    switch(type)
    {
      case Vertex::Circle:  
      case Vertex::Point:  repStr1="x"+toString(shapeName);
                   repStr2="y"+toString(shapeName);
                   if(solveOrValue)
                   {
                     repStrb1=repStr1;
                     repStrb2=repStr2;
                     repStrb1.insert(1,"?");
                     repStrb2.insert(1,"?");
                     newStr1="("+repStrb1+"*"+clusterV3+"-"+repStrb2+"*"+clusterV4+"+"+clusterV1+")";
                     newStr2="("+repStrb2+"*"+clusterV3+"+"+repStrb1+"*"+clusterV4+"+"+clusterV2+")";
                   }
                   else
                   {
                     newStr1="("+toString(theVertex.returnDegValueByName(0))+")";
                     newStr2="("+toString(theVertex.returnDegValueByName(1))+")";
                     vars.deleteElem(repStr1);
                     vars.deleteElem(repStr2);
		     if(type==Vertex::Circle)
	             {
			newStr3="("+toString(theVertex.returnDegValueByName(3))+")";
			repStr3="r"+toString(shapeName);
			vars.deleteElem(repStr3);
		     }
                   }
                   output=replaceAll(output, repStr1, newStr1, true);
                   output=replaceAll(output, repStr2, newStr2, true);
                   break;
      case Vertex::Line:  repStr1="x"+toString(shapeName);
                   repStr2="y"+toString(shapeName);
                   repStr3="m"+toString(shapeName);
                   if(solveOrValue)
                   {
                     repStrb1=repStr1;
                     repStrb2=repStr2;
                     repStrb3=repStr3;
                     repStrb1.insert(1,"?");
                     repStrb2.insert(1,"?");
                     repStrb3.insert(1,"?");
                     newStr1="("+repStrb1+"*"+clusterV3+"-"+repStrb2+"*"+clusterV4+"+"+clusterV1+")";
                     newStr2="("+repStrb2+"*"+clusterV3+"+"+repStrb1+"*"+clusterV4+"+"+clusterV2+")";
                     newStr3="(("+repStrb3+"*"+clusterV3+"+"+clusterV4+")/("+repStrb3+"*"+clusterV4+"+"+clusterV3+"))";
                   }
                   else
                   {
                     newStr1="("+toString(theVertex.returnDegValueByName(0))+")";
                     newStr2="("+toString(theVertex.returnDegValueByName(1))+")";
                     newStr3="("+toString(theVertex.returnDegValueByName(4))+")";
                     vars.deleteElem(repStr1);
                     vars.deleteElem(repStr2);
                     vars.deleteElem(repStr3);
                   }
                   output=replaceAll(output, repStr1, newStr1, true);
                   output=replaceAll(output, repStr2, newStr2, true);
                   output=replaceAll(output, repStr3, newStr3, true);
                   break;
      case Vertex::Ray:  repStr1="x"+toString(shapeName);
                   repStr2="y"+toString(shapeName);
                   repStr3="v"+toString(shapeName);
                   repStr4="w"+toString(shapeName);
                   if(solveOrValue)
                   {
                     repStrb1=repStr1;
                     repStrb2=repStr2;
                     repStrb3=repStr3;
                     repStrb4=repStr4;
                     repStrb1.insert(1,"?");
                     repStrb2.insert(1,"?");
                     repStrb3.insert(1,"?");
                     repStrb4.insert(1,"?");
                     newStr1="("+repStrb1+"*"+clusterV3+"-"+repStrb2+"*"+clusterV4+"+"+clusterV1+")";
                     newStr2="("+repStrb2+"*"+clusterV3+"+"+repStrb1+"*"+clusterV4+"+"+clusterV2+")";
                     newStr3="("+repStrb3+"*"+clusterV3+"-"+repStrb4+"*"+clusterV4+")";
                     newStr4="("+repStrb4+"*"+clusterV3+"+"+repStrb3+"*"+clusterV4+")";
                   }
                   else
                   {
                     newStr1="("+toString(theVertex.returnDegValueByName(0))+")";
                     newStr2="("+toString(theVertex.returnDegValueByName(1))+")";
                     newStr3="("+toString(theVertex.returnDegValueByName(4))+")";
                     newStr4="("+toString(theVertex.returnDegValueByName(5))+")";
                     vars.deleteElem(repStr1);
                     vars.deleteElem(repStr2);
                     vars.deleteElem(repStr3);
                     vars.deleteElem(repStr4);
                   }
                   output=replaceAll(output, repStr1, newStr1, true);
                   output=replaceAll(output, repStr2, newStr2, true);
                   output=replaceAll(output, repStr3, newStr3, true);
                   output=replaceAll(output, repStr4, newStr4, true);
                   break;
      case Vertex::LineSeg:  repStr1="x"+toString(shapeName);
                   repStr2="y"+toString(shapeName);
                   repStr3="c"+toString(shapeName);
                   repStr4="d"+toString(shapeName);
                   repStr5="m"+toString(shapeName);
                   if(solveOrValue)
                   {
                     repStrb1=repStr1;
                     repStrb2=repStr2;
                     repStrb3=repStr3;
                     repStrb4=repStr4;
                     repStrb5=repStr5;
                     repStrb1.insert(1,"?");
                     repStrb2.insert(1,"?");
                     repStrb3.insert(1,"?");
                     repStrb4.insert(1,"?");
                     repStrb5.insert(1,"?");
                     newStr1="("+repStrb1+"*"+clusterV3+"-"+repStrb2+"*"+clusterV4+"+"+clusterV1+")";
                     newStr2="("+repStrb2+"*"+clusterV3+"+"+repStrb1+"*"+clusterV4+"+"+clusterV2+")";
                     newStr3="("+repStrb3+"*"+clusterV3+"-"+repStrb4+"*"+clusterV4+"+"+clusterV1+")";
                     newStr4="("+repStrb4+"*"+clusterV3+"+"+repStrb3+"*"+clusterV4+"+"+clusterV2+")";
                     newStr5="(("+repStrb5+"*"+clusterV3+"+"+clusterV4+")/("+repStrb5+"*"+clusterV4+"+"+clusterV3+"))";
                   }
                   else
                   {
                     newStr1="("+toString(theVertex.returnDegValueByName(0))+")";
                     newStr2="("+toString(theVertex.returnDegValueByName(1))+")";
                     newStr3="("+toString(theVertex.returnDegValueByName(2))+")";
                     newStr4="("+toString(theVertex.returnDegValueByName(3))+")";
                     newStr5="("+toString(theVertex.returnDegValueByName(4))+")";
                     vars.deleteElem(repStr1);
                     vars.deleteElem(repStr2);
                     vars.deleteElem(repStr3);
                     vars.deleteElem(repStr4);
                     vars.deleteElem(repStr5);
                   }
                   output=replaceAll(output, repStr1, newStr1, true);
                   output=replaceAll(output, repStr2, newStr2, true);
                   output=replaceAll(output, repStr3, newStr3, true);
                   output=replaceAll(output, repStr4, newStr4, true);
                   output=replaceAll(output, repStr5, newStr5, true);
                   break;
      case Vertex::Arc:  repStr1="x"+toString(shapeName);
                   repStr2="y"+toString(shapeName);
                   repStr3="v"+toString(shapeName);
                   repStr4="w"+toString(shapeName);
                   repStr5="a"+toString(shapeName);
                   repStr6="b"+toString(shapeName);
                   if(solveOrValue)
                   {
                     repStrb1=repStr1;
                     repStrb2=repStr2;
                     repStrb3=repStr3;
                     repStrb4=repStr4;
                     repStrb5=repStr5;
                     repStrb6=repStr6;
                     repStrb1.insert(1,"?");
                     repStrb2.insert(1,"?");
                     repStrb3.insert(1,"?");
                     repStrb4.insert(1,"?");
                     repStrb5.insert(1,"?");
                     repStrb6.insert(1,"?");
                     newStr1="("+repStrb1+"*"+clusterV3+"-"+repStrb2+"*"+clusterV4+"+"+clusterV1+")";
                     newStr2="("+repStrb2+"*"+clusterV3+"+"+repStrb1+"*"+clusterV4+"+"+clusterV2+")";
                     newStr3="("+repStrb3+"*"+clusterV3+"-"+repStrb4+"*"+clusterV4+")";
                     newStr4="("+repStrb4+"*"+clusterV3+"+"+repStrb3+"*"+clusterV4+")";
                     newStr5="("+repStrb5+"*"+clusterV3+"-"+repStrb6+"*"+clusterV4+")";
                     newStr6="("+repStrb6+"*"+clusterV3+"+"+repStrb5+"*"+clusterV4+")";
                   }
                   else
                   {
                     newStr1="("+toString(theVertex.returnDegValueByName(0))+")";
                     newStr2="("+toString(theVertex.returnDegValueByName(1))+")";
                     newStr3="("+toString(theVertex.returnDegValueByName(4))+")";
                     newStr4="("+toString(theVertex.returnDegValueByName(5))+")";
                     newStr5="("+toString(theVertex.returnDegValueByName(6))+")";
                     newStr6="("+toString(theVertex.returnDegValueByName(7))+")";
                     vars.deleteElem(repStr1);
                     vars.deleteElem(repStr2);
                     vars.deleteElem(repStr3);
                     vars.deleteElem(repStr4);
                     vars.deleteElem(repStr5);
                     vars.deleteElem(repStr6);
                   }
                   output=replaceAll(output, repStr1, newStr1, true);
                   output=replaceAll(output, repStr2, newStr2, true);
                   output=replaceAll(output, repStr3, newStr3, true);
                   output=replaceAll(output, repStr4, newStr4, true);
                   output=replaceAll(output, repStr5, newStr5, true);
                   output=replaceAll(output, repStr6, newStr6, true);
                   break;
      case Vertex::Point3D:  repStr1="x"+toString(shapeName);
                   repStr2="y"+toString(shapeName);
                   repStr3="z"+toString(shapeName);
                   if(solveOrValue)
                   {
                     repStrb1=repStr1;
                     repStrb2=repStr2;
                     repStrb3=repStr3;
                     repStrb1.insert(1,"?");
                     repStrb2.insert(1,"?");
                     repStrb3.insert(1,"?");
			
                     
                     newStr1="(("+repStrb1+"*"+clusterV6+"*"+clusterV8+")+";
                     newStr1+="("+repStrb2+"*"+clusterV6+"*"+clusterV9+")-";
                     newStr1+="("+repStrb3+"*"+clusterV7+")+"+clusterV1+")";
                     
                     newStr2="(("+repStrb1+"*("+clusterV4+"*"+clusterV7+"*"+clusterV8+"-"+clusterV3+"*"+clusterV9+"))+";
                     newStr2+="("+repStrb2+"*("+clusterV3+"*"+clusterV8+"+"+clusterV4+"*"+clusterV7+"*"+clusterV9+"))+";
                     newStr2+="("+repStrb3+"*"+clusterV4+"*"+clusterV6+")+"+clusterV2+")";
                     newStr3="(("+repStrb1+"*("+clusterV4+"*"+clusterV9+"+"+clusterV3+"*"+clusterV7+"*"+clusterV8+"))+";
                     newStr3+="("+repStrb2+"*(-"+clusterV4+"*"+clusterV8+"+"+clusterV3+"*"+clusterV7+"*"+clusterV9+"))+";
                     newStr3+="("+repStrb3+"*"+clusterV3+"*"+clusterV6+")+"+clusterV5+")"; 
		   }
                   else
                   {
                     newStr1="("+toString(theVertex.returnDegValueByName(0))+")";
                     newStr2="("+toString(theVertex.returnDegValueByName(1))+")";
                     newStr3="("+toString(theVertex.returnDegValueByName(2))+")";
                     vars.deleteElem(repStr1);
                     vars.deleteElem(repStr2);
                     vars.deleteElem(repStr3);
                   }
outf << "The newstr1 = " << newStr1 << std::endl;
outf << "The newstr2 = " << newStr2 << std::endl;
outf << "The newstr3 = " << newStr3 << std::endl;

                   output=replaceAll(output, repStr1, newStr1, true);
                   output=replaceAll(output, repStr2, newStr2, true);
                   output=replaceAll(output, repStr3, newStr3, true);
outf << "After replaceall, the output is: " << output << std::endl;
		   break; 

      case Vertex::NoClue: 
      case Vertex::Cluster: break;
    }
    output=replaceAll(output, "?", "");

    return output;
}

//! Generates an equation for a constraint between two vertices in different 
//! clusters.It gets an equation as if the vertices were in one cluster, then 
//! replaces all of the variables for each cluste; either with the 2D arbitrary 
//! rotation or with the previously solved values of that vertex if its parent 
//! cluster will not be rotated.
std::string 
getEquationBetweenClusters (Graph& graph0, Edge &theEdge, Cluster &theCluster, 
                            List<std::string>& vars, List<Edge>& theImags,
                            int withHeldCluster, int graphDimen)
{
    std::string outString;
    Vertex vEnd1, vEnd2;
    int v1Name, v2Name;
    int end1C, end2C;

    outString="";

    if(isImaginary(graph0, theEdge)) theImags.append(theEdge);

    vEnd1=graph0.returnVertByName(theEdge.returnEnd1());
    vEnd2=graph0.returnVertByName(theEdge.returnEnd2());

    v1Name=vEnd1.returnName();
    v2Name=vEnd2.returnName();

    switch(theEdge.returnType()) {

          case 0: outString=getDistanceEQ(vEnd1,vEnd2,theEdge, "", vars);
                  break;
          case 1: outString=getIncidenceEQ(vEnd1,vEnd2,theEdge, vars);
                  break;
          case 4: outString=getAngleEQ(vEnd1,vEnd2,theEdge, vars);
                  break;
          case 3: outString=getParallelEQ(vEnd1,vEnd2,theEdge, vars);
                  break;
          case 2: outString=getPerpendicularEQ(vEnd1,vEnd2,theEdge, vars);
                  break;
          case 5: outString=getTangencyEQ(vEnd1,vEnd2,theEdge, vars);
                  break;
	  case 6: outString=getDistance3DEQ(vEnd1, vEnd2, theEdge, "", vars);
		  break;
          case 8: outString=getAngle3DEQ(vEnd1,vEnd2,theEdge, vars);
	          break;    
    }
    end1C=getChildNameWithVertex(theCluster, v1Name);
    end2C=getChildNameWithVertex(theCluster, v2Name);
    setValueInCluster(graph0,theCluster.children.retrieve(getChildIndexByName(theCluster, end1C)), vEnd1);
    setValueInCluster(graph0,theCluster.children.retrieve(getChildIndexByName(theCluster, end2C)), vEnd2);
    if (end1C==-1 || end2C==-1) return "";
    if (end1C!=v1Name) 
    {
       outString=switchString(vEnd1, vEnd1.returnType(), v1Name, end1C, 
                              outString, end1C!=withHeldCluster, vars, 
                              graphDimen);
       if(end1C!=withHeldCluster)
          outString=switchString(vEnd1, vEnd1.returnType(), v1Name, end1C, 
                                 outString, false, vars, graphDimen);
    }
    if (end2C!=v2Name)
    {
       outString=switchString(vEnd2, vEnd2.returnType(), v2Name, end2C, 
                              outString, end2C!=withHeldCluster, vars, 
                              graphDimen);
       if(end2C!=withHeldCluster)
          outString=switchString(vEnd2, vEnd2.returnType(), v2Name, end2C, 
                                 outString, false, vars, graphDimen);
    }
    return(outString);
}

//! gets a equation for a edge where both endpoints fall in the same cluster, it simply calls the
//! corresponding getEquation method above for each particular edge type.
std::string 
getEquationInCluster (Graph& graph0, Edge &theEdge, Cluster &theCluster, 
                      List<std::string>& vars, List<Edge>& theImags)
{
  std::string outString;
  Vertex vEnd1, vEnd2;

  outString="";

  if(isImaginary(graph0, theEdge)) theImags.append(theEdge);

  
  vEnd1=graph0.returnVertByName(theEdge.returnEnd1());
  vEnd2=graph0.returnVertByName(theEdge.returnEnd2());
  switch(theEdge.returnType()) 
    {
      case 0: outString=getDistanceEQ(vEnd1,vEnd2,theEdge, "", vars);
              break;
      case 1: outString=getIncidenceEQ(vEnd1,vEnd2,theEdge, vars);
              break;
      case 4: outString=getAngleEQ(vEnd1,vEnd2,theEdge, vars);
              break;
      case 3: outString=getParallelEQ(vEnd1,vEnd2,theEdge, vars);
              break;
      case 2: outString=getPerpendicularEQ(vEnd1,vEnd2,theEdge, vars);
              break;
      case 5: outString=getTangencyEQ(vEnd1,vEnd2,theEdge, vars);
              break;
      case 6: outString=getDistance3DEQ(vEnd1,vEnd2,theEdge,"", vars);
	            break;
      case 8: outString=getAngle3DEQ(vEnd1,vEnd2,theEdge, vars);
              break;	  
    }
  return(outString);
}


//! Ray objects use the sine and cosine of the angle of the ray compared to the 
//! positive x axis as degrees of freedom in there equation sets.  This method 
//! generates additional equations that insure that the squares of these sine 
//! and cosine values alway sum to 1
std::string getSinCosConstraint(List<std::string>& vars)
{
    int i, length;
    std::string temp, temp2, clust;
    std::string output="";

    length=vars.returnLen();

    for(i=1;i<=length;i++)
    {
       temp=vars.retrieve(i);
       temp2=temp;
       clust=temp2.erase(0,1);
       if(temp[0]=='w') output+=",1=(w"+clust+"^2+v"+clust+"^2)";
       if(temp[0]=='a') output+=",1=(a"+clust+"^2+b"+clust+"^2)";
    }
    return output;
}


bool childrenUsed(int vName, int child1, int child2, List<VUsed> vUsedList)
{
	VUsed temp;
	for(int i=1; i<=vUsedList.returnLen(); i++)
	{
		temp = vUsedList.retrieve(i);
		if(temp.vName == vName && temp.usedChild.hasElem(child1)
		   && temp.usedChild.hasElem(child2))
			return true;
	}
	return false;
}


//! Within the DRTree used by this solver, original vertices in more than one 
//! cluster have duplicate datastructures in each of the clusters that contain 
//! them.  At the time of solution, the implied constaint that each of these 
//! duplicated objects, must actually be the same, must be resolved.  To assure
//! this, additional equations are added, stating that for each of these 
//! overlaps, some rotation and translation of one cluster must bring all these
//! duplicate points into the correct positions.
std::string 
getOverlapConstraint (Graph &graph0, Cluster &theCluster, int totalExtra, 
                      List<std::string>& vars, int equationCount, 
                      int withHeldCluster, int aOverlap, int singleVertex,
                      int nextVerName, int nextEdgeName)
{
	std::string output="";
	
	if(theCluster.returnOrig().returnLen()==theCluster.children.returnLen()) return "";
	std::ofstream outf;
	outf.open("getOverlapConstraint.out", std::ios::app);

	outf<<"The beginning+++++++++++ The cluster is:" <<std::endl;
	outf << theCluster << std::endl;


	int childLen = theCluster.children.returnLen();
	//return "" if the cluster only has leaf children
	if(theCluster.children.returnLen()==theCluster.returnOrigLen())
		return output;



    	std::string stringPart;
	List<VUsed> vUsedList;
	int PartMaxDof[200], extraNum[200];
	int index = 0;
    	for(int i=1; i<childLen; i++)
    	{
		for(int j=i+1; j<=childLen; j++)
		{
   			List<int> overlappedList;

    			getOverlapList(graph0, theCluster, overlappedList, i, j);
			outf << "child1:" << i << "    child2: " << j << std::endl;
		        outf<<"Overlapped Vertices: ";
    			for(int k=1;k<=overlappedList.returnLen();k++)
				outf<<overlappedList.retrieve(k)<<" ";
    			outf<<std::endl;

   			Graph newGraph;
    			//get the max possbile equation numbers for each pair
    			PartMaxDof[index] = buildGraphFromList(newGraph,graph0,overlappedList);
    			outf << "The max dof of current pair is: " << PartMaxDof[index] << std::endl;
       			extraNum[index] = getExtraNum(graph0, theCluster, overlappedList, i, j);
       			outf << "extranum is: " << extraNum[index];
//       			outf << " The new Graph is: " << std::endl;
//    			newGraph.output(outf);
			index++;
    		}
    	}

	//get the total equations we need for the cluster.
	int numEqPair = ((graph0.returnDimen()==2)? 3 : 6);
	int needEqNum = (theCluster.children.returnLen() - 1)*numEqPair;
	outf << "The needed equation number of the cluster is: " << needEqNum << std::endl;
//	for(int i=0; i< index; i++)
//		needEqNum -= extraNum[i];
	needEqNum -= totalExtra;
	outf << "after minus extra number, the total equation number is: " << needEqNum << std::endl;

	//assign the dof for each pair
	setPartDof(needEqNum, numEqPair, theCluster, PartMaxDof, extraNum);
	outf << "the equation number of each pair is: " << std::endl;
	for(int i=0; i<index; i++)
		outf << PartMaxDof[i];

	outf << std::endl;
	index = 0;
    	for(int i=1; i<childLen; i++)
    	{
		for(int j=i+1; j<=childLen; j++)
		{
			outf << "child1:" << i << "    child2: " << j << " the dof is:" << PartMaxDof[index] <<  std::endl;
			stringPart = getPartOverEquation(graph0, theCluster, vUsedList, i, j, 
                                       PartMaxDof[index++], vars, equationCount,
                                       withHeldCluster, aOverlap, singleVertex,
                                       nextVerName, nextEdgeName);
			outf << "the stringPart is" << stringPart << std::endl;
			output += stringPart;
		}
	}

	return output;
}

//! the line object, has only two degrees of freedom, its y axis intercept and 
//! its slope; however, the equations generated for the line object use three 
//! degrees of freedom a point and a slope. in order to eliminate this 
//! additional added degree of freedom, this method generates simple equations
//! setting the x coordinate of any line to zero
std::string 
getLineConstraint (Graph &graph0, List<Cluster> &theChildren, 
                   List<std::string>& vars, int equationCount)
{
    std::string outString;
    Cluster theCluster;
    Vertex theVert;
    int i, length;
    std::string name;
    std::string intName;
    std::string slopeVar;

    outString="";

    length=theChildren.returnLen();

    for(i=1;i<=length;i++)
    {
       theCluster=theChildren.retrieve(i);
       name="x"+toString(theCluster.returnName());
       if(graph0.hasVert(theCluster.returnName()))
       {
         theVert=graph0.returnVertByName(theCluster.returnName());
         if(theVert.returnType()>0 && theVert.returnType()<3 && vars.hasElem(name))
         {
	   outString+=",x"+toString(theCluster.returnName())+"=0";
	   equationCount++;       
	 }

         if(theVert.returnType()==3)
         {
	   std::cout<<getVarString(vars)<<std::endl;
           intName=toString(theCluster.returnName());
	   slopeVar="m"+intName;
	   if(!vars.hasElem(slopeVar)) return outString;
           outString+=",(y"+intName+"-d"+intName+")=m"+intName+"*(x"+intName+"-c"+intName+")";
           if(!vars.hasElem(slopeVar)) vars.append(slopeVar);
         }
       }
    }
    return outString;
}

//! Each solved cluster has three remaining degrees of freedom, two 
//! translational degrees and one rotation, this program expresses these degrees
//! of freedom in four variables, x translation, y translation, sine of rotation
//! angle, and cosine of rotation angle. To insure that when the equations are 
//! solved, the relationship between the sine and cosine is maintained, this 
//! method generated additional equations stating that the sum of the squares of
//! the sine and cosine must be 1
std::string 
getRotationEquations (Cluster &theCluster, List<std::string>& vars, 
                      int equationCount, int withHeldCluster)
{
    std::string outString, temp, temp2;
    int i, length, childName;

    outString="";

    if(theCluster.children.returnLen()==0) return outString;
    if(theCluster.children.returnLen()==theCluster.returnOrigLen()) return outString;

    length=theCluster.children.returnLen();

    for(i=1;i<=length;i++)
    {
       childName=theCluster.children.retrieve(i).returnName();
       if(theCluster.children.retrieve(i).children.returnLen()!=0 && childName!=withHeldCluster &&
	  theCluster.children.retrieve(i).returnType()!=2 
	  && theCluster.children.retrieve(i).returnType()!=5)
       {
         temp=toString(childName);
	 temp2="f"+temp;
         if(vars.hasElem(temp2))
         {   
	   outString+=",s"+temp+"^2+t"+temp+"^2=1,h"+temp+"^2+j"+temp+"^2=1,k"+temp+"^2+n"+temp+"^2=1";        
           equationCount+=3;
	 }
	 else
         { 
	   outString+=",s"+temp+"^2+t"+temp+"^2=1";
	   equationCount++;
         }
       }
    }

    return outString;
}


//! after all of the equations for a cluster have been generated, if the cluster
//! is rigid, exactly three degrees of freedom will still remain.  This method 
//! generates simple equations which fix those degrees of freedom, so Maple will
//! generate exact answers
std::string 
getOriginEquations (Edge &theEdge, Edge &theEdge2, Graph &graph0, 
                    int clusterName, int clusterType, std::string varsToZero)
{
	std::string outString, tempString, secondName;
	Vertex vEnd1, vEnd2, vEnd3, vEnd4;
	int v1Name, v2Name, v3Name, v4Name, thirdName;
  Vertex::Type type1, type2;
	
	std::ofstream outf;
	outf.open("getOriginEquations.out", std::ios::app);
	outf << "The beginning************" << std::endl;
	
	outString="";
	
	if(theEdge2.returnName()==0) theEdge2=theEdge;
	
	if(clusterName>0)
	{
		tempString=toString(clusterName);
		outString="p"+tempString+"=0,q"+tempString+"=0,t"+tempString+"=0";
		return outString;
	}
	outf << " TheEdge: " << theEdge << std::endl;
	outf << " TheEdge2: " << theEdge2 << std::endl;
	outf << graph0 << std::endl;
	
	vEnd1=graph0.returnVertByName(theEdge.returnEnd1());
	vEnd2=graph0.returnVertByName(theEdge.returnEnd2());
	vEnd3=graph0.returnVertByName(theEdge2.returnEnd1());
	vEnd4=graph0.returnVertByName(theEdge2.returnEnd2());
	
	v1Name=vEnd1.returnName();
	v2Name=vEnd2.returnName();
	v3Name=vEnd3.returnName();
	v4Name=vEnd4.returnName();
	outf << "the vName 1-4 are:" << v1Name << ", " << v2Name << ", " << v3Name << ", " << v4Name << std::endl;
	if(v1Name==v3Name || v2Name==v3Name)
		thirdName=v4Name;
	else thirdName=v3Name;
	
	type1=vEnd1.returnType();
	type2=vEnd2.returnType();
	
	if(type2==Vertex::Ray || type2==Vertex::Line)
		secondName="y";
	else secondName="x";
	
	outf<<"in getOrigin after getting all data"<<std::endl;
	verifyOrigsets(graph0, v1Name, v2Name, thirdName);
	
	switch(type1)
	{
    case Vertex::Arc:
    case Vertex::Circle:
    case Vertex::Point: if(type2==Vertex::Ray || type2==Vertex::Line)
			  secondName="m";
		        else secondName="y";
			outString="x"+toString(v1Name)+"=0,y"+toString(v1Name)+"=0,"+secondName+toString(v2Name)+"=0";
			break;
    case Vertex::LineSeg: outString="x"+toString(v1Name)+"=0,y"+toString(v1Name)+"=0,d"+toString(v1Name)+"=0.0001";
		        break;
    case Vertex::Line: outString="y"+toString(v1Name)+"=0,m"+toString(v1Name)+"=0,"+secondName+toString(v2Name)+"=0";
			break;
    case Vertex::Ray: outString="y"+toString(v1Name)+"=0,w"+toString(v1Name)+"=0,"+secondName+toString(v2Name)+"=0";
			break;		
    case Vertex::Point3D: if(clusterType!=2)
			{
			  outString="x"+toString(v1Name)+"=0,y"+toString(v1Name)+"=0,z"+toString(v1Name)+"=0";
		          outString+=",x"+toString(v2Name)+"=0,z"+toString(v2Name)+"=0,z"+toString(thirdName)+"=0";
			}
			else
			{
			  outString="x"+toString(v1Name)+"=0,y"+toString(v1Name)+"=0,z"+toString(v1Name)+"=0";
		          outString+=",x"+toString(v2Name)+"=0,z"+toString(v2Name)+"=0";
			}
		        break;
    case Vertex::NoClue: 
    case Vertex::Cluster: break;
	}
	outf << "after switch, the outstring is: " << std::endl << outString << std::endl;
	varsToZero=outString;
	varsToZero=replaceAll(varsToZero,"=0","");
	varsToZero=replaceAll(varsToZero,",","");	
	
	outf << "Origin Output: "<<outString<<std::endl;
	
	return(outString);
}


//! check whether the overlapped point of two lines have same x or c;
//! if not, minus the cos(theta);
void minusString(std::string & str, int ID1, int ID2)
{
	std::string name1;
	std::string name3;

	std::ofstream outf;
	outf.open("minusString.out", std::ios::app);

	name1="x"+toString(ID1);
	name3="c"+toString(ID2);

	std::string test1, test2;

	test1=name1+"="+name3;
	test2=name3+"="+name1;

	size_t badFind=str.size();
	outf << ".....................The beginning..............." << std::endl;
	outf << "The string is: " << std::endl << str << std::endl;

	bool needMinus=false;
	//check x==c?
	if(str.find(test1)<badFind || str.find(test2)<badFind)
		needMinus = true;

	outf << "test 1 is: " << test1 << "   test2 is: " << test2 << std::endl;

	name1="c"+toString(ID1);
 	name3="x"+toString(ID2);

	test1=name1+"="+name3;
	test2=name3+"="+name1;

	outf << "test 1 is: " << test1 << "   test2 is: " << test2 << std::endl;

	if(str.find(test1)<badFind || str.find(test2)<badFind)
		needMinus = true;

	outf << "Do we need minus? " << needMinus << std::endl;

	if(!needMinus)
		return;
	size_t pos = str.find("sqrt");
	outf << "pos(sqrt) = " << pos << std::endl;

	//can't find sqrt
	if(pos>=badFind)
		return;

	pos = str.rfind("=", pos);
	outf << "pos (=) = " << pos << std::endl;
	str.insert(pos+1, "-");

	outf << "The result is: " << std::endl << str << std::endl;
}


int 
isValidSecond (Graph& graph0, int ID1, int ID2, std::string outputString, 
               int& temp)
{
	if(graph0.hasVert(ID2))
		return 0;
	int rst = 0;

	std::string name1;
	std::string name2;
	std::string name3;

	name1="x"+toString(ID1);
	name2="c"+toString(ID1);
	name3="c"+toString(ID2);

	std::string test1, test2, test3, test4;

	test1=name1+"="+name3;
	test2=name3+"="+name1;
	test3=name2+"="+name3;
  test4=name3+"="+name2;

	size_t badFind=outputString.size();
	//check c==c?
	if(outputString.find(test3)<badFind || outputString.find(test4)<badFind)
		temp = 1;

	if(outputString.find(test1)>=badFind &&
	   outputString.find(test2)>=badFind &&
           outputString.find(test3)>=badFind &&
           outputString.find(test4)>=badFind)
		 rst = -1;

	else
	{
		name3="x"+toString(ID2);

		test1=name1+"="+name3;
		test2=name3+"="+name1;
		test3=name2+"="+name3;
		test4=name3+"="+name2;

		if(outputString.find(test3)<badFind || outputString.find(test4)<badFind)
			temp = 1;
		if(outputString.find(test1)>=badFind &&
		outputString.find(test2)>=badFind &&
		outputString.find(test3)>=badFind &&
		outputString.find(test4)>=badFind)
			rst = 1;
	}

	return rst;

}


//! for every edge in graph0 in theCluster, gets a corresponding equation string
std::string 
getEquation (Graph &graph0, Edge &theEdge, Cluster &theCluster, 
             List<std::string>& vars, List<Edge>& theImags, int withHeldCluster,
             int graphDimen)
{
  int temp;
  std::string output;

  temp = getEdgeCode(theEdge, theCluster);

  if(temp==1) output+=getEquationBetweenClusters(graph0, theEdge, theCluster, 
                                                 vars, theImags, withHeldCluster,
                                                 graphDimen);
  if(temp==0) output+=getEquationInCluster(graph0, theEdge, theCluster, vars, 
                                           theImags);
  return output;
}


void 
verifyOrigsets (Graph &graph0, int &n1, int &n2, int &n3)
{
	//for image
	if (graph0.returnNumVer() == 4 && graph0.returnNumEdg() == 8
      && graph0.returnDimen() == 2)
		return;
	int v1, v2, v3;
	v1 = graph0.returnVertByName(n1).numIncid();
	v2 = graph0.returnVertByName(n2).numIncid();
	v3 = graph0.returnVertByName(n3).numIncid();
	
	int swap;
	if(v1>v2)
	{
		swap = n2;
		n2 = n1;
		n1 = swap;
		v1=v2;
	}
	if(v1>v3)
	{
		swap = n3;
		n3 = n1;
		n1 = swap;
	}
}


//! assign the dof of each pair to the array
void 
setPartDof (int needEqNum, int numEqPair, Cluster &theCluster, int PartMaxDof[],
            int extraNum[])
{
	int index=0;
	int childLen = theCluster.children.returnLen();
    	for(int i=1; i<childLen; i++)
    	{
		for(int j=i+1; j<=childLen; j++)
		{
			//child1 overlaps with child2
			if(PartMaxDof[index] != 0 && extraNum[index] + PartMaxDof[index] > numEqPair)
				PartMaxDof[index] = numEqPair - extraNum[index];

			needEqNum -= PartMaxDof[index];
			if(needEqNum<=0)
			{
				PartMaxDof[index]+=needEqNum;
				needEqNum=0;
			}
			index++;
		}//for child2
	}//for child1
}


//! get the number of the extra constraints between these 2 children
int 
getExtraNum (Graph &graph0, Cluster &theCluster, List<int> &overlappedList, 
             int ch1, int ch2)
{
	int extraCon = 0;
	Cluster child1, child2;
	int v1, v2;
	child1 = theCluster.children.retrieve(ch1);
	child2 = theCluster.children.retrieve(ch2);
	std::ofstream outf;
	//outf.open("getExtraNum.out", std::ios::app);
	outf << "child1 is" << std::endl;
	outf << child1 << std::endl;
	outf << "child2 is" << std::endl;
	outf << child2 << std::endl;
	for(int i=1; i<=child1.returnOrigLen(); i++)
	{
		v1 = child1.returnOrigV(i);
		if(!overlappedList.hasElem(v1))
		{
			for(int j=1; j<=child2.returnOrigLen(); j++)
			{
			v2 = child2.returnOrigV(j);
			Edge e;
			e =  graph0.returnEdgeByEnds(v1, v2);
			outf << "v1 = " << v1 << "      v2 = " << v2 << std::endl;
			outf << "e is: " << e << std::endl;
			outf << "the edge code is: " << getEdgeCode(e, theCluster, ch1, ch2) << std::endl;
			if(!overlappedList.hasElem(v2) && graph0.hasEdge(e.returnName())
			   && getEdgeCode(e, theCluster, ch1, ch2)==1)
				extraCon++;
			}//for child2
		}//if
	}//for child1

	return extraCon;
}


std::string 
getPartOverEquation (Graph &graph0, Cluster &theCluster, List<VUsed> &vUsedList,
                     int child1, int child2, int totalDof, 
                     List<std::string>& vars, int equationCount, 
                     int withHeldCluster, int aOverlap, int singleVertex,
                     int nextVerName, int nextEdgeName)
{
    int i, j, k, length, type, currOrig;
    int clustint1, clustint2;
    std::string cluster1, cluster2, origStr, nameStr;
    std::string newStr1a, newStr2a, newStr3a, newStr1b, newStr2b, newStr3b;
    std::string clusterV1, clusterV2, clusterV3, clusterV4;
    std::string clusterV5, clusterV6, clusterV7, clusterV8, clusterV9;
    std::string repStrb1, repStrb2, repStrb3;
    List<int> theOrig, in, theClust;
    Cluster tempCluster1, tempCluster2;
    Vertex tempVertex1, tempVertex2;
    std::string output="";
    std::string temp="", valueName="";

    std::ofstream outf;
    outf.open("getParOverEqution.out", std::ios::app);

    outf<<"The beginning+++++++++++ " <<std::endl;
    outf << "child 1 is: ";
    outf << theCluster.children.retrieve(child1) << std::endl;
	  outf << "Its children are: " << std::endl;
	Cluster tempcc1 = theCluster.children.retrieve(child1);
	for(i=1; i<= tempcc1.children.returnLen(); i++)
		outf << tempcc1.children.retrieve(i) << std::endl;

    outf << "child 2 is: ";
    outf << theCluster.children.retrieve(child2) << std::endl;
    outf << "Its children are: " << std::endl;
    tempcc1 = theCluster.children.retrieve(child2);
    for(i=1; i<= tempcc1.children.returnLen(); i++)
      outf << tempcc1.children.retrieve(i) << std::endl;


    List<int> overlappedList;

    getOverlapList(graph0, theCluster, overlappedList, child1, child2);
    outf<<"Overlapped Vertices: ";
    for(i=1;i<=overlappedList.returnLen();i++)
	outf<<overlappedList.retrieve(i)<<" ";
    outf<<std::endl;

    std::ofstream testFile1, testFile2;

    testFile1.open("testFile1.txt");
    testFile2.open("testFile2.txt");

    Graph newGraph;

    List<Cluster> test_DR_Trees;
    List<Cluster> testSolverTrees;

    buildGraphFromList(newGraph,graph0,overlappedList);

    resetTrees(newGraph,test_DR_Trees);

    outf << " The new Graph is: " << std::endl;
    outf << newGraph << std::endl;
    outf << "totalDof is: " << totalDof << std::endl;

    if(newGraph.returnNumVer()==0)
	return output;
	outf << "before call mfaAlgo" << std::endl;

	outf << "num ver is: " << newGraph.returnNumVer() << " and edge num is: " << newGraph.returnNumEdg() << std::endl;
    bool check2=false;
    //check whether need to create the second special cluster by hand
    if(newGraph.returnNumVer()==3 && newGraph.returnNumEdg()==3 && graph0.returnDimen()==3)
    {
    	int type6=0;
	int type7=0;
	for(int i=1; i<=3; i++)
 	{	if(newGraph.returnVertByIndex(i).returnType()==6)
			type6++;
		else if(newGraph.returnVertByIndex(i).returnType()==7)
			type7++;
	}
	if(type6==2 && type7==1)
		check2=true;
    }

    Cluster clSpecial;
    if(newGraph.returnNumVer()==2 && newGraph.returnNumEdg()==1 && graph0.returnDimen()==3)
    {
    	outf << "We are createing the special cluster" << std::endl;
	clSpecial = createSPCluster(newGraph);
	testSolverTrees.append(clSpecial);
    }
    else if(check2)
    {
    	outf << "We are createing the second special cluster" << std::endl;
	clSpecial = createSP2Cluster(newGraph);
	testSolverTrees.append(clSpecial);
    }
    else
	testSolverTrees = mfaAlgo(newGraph, test_DR_Trees, testFile1, testFile2, 
                            singleVertex, nextVerName, nextEdgeName);
    outf << "After call mfaAlgo" << std::endl;
    if(testSolverTrees.returnLen()==1 && totalDof==6
	&&testSolverTrees.retrieve(1).returnType()==2)
	totalDof--;

    outf << "The TOTAL DOF is: :: " << totalDof;

    int numTrees = testSolverTrees.returnLen();
    int maxOverArray[10];
    int flagTrees[10];

    for(int j=1; j<10; j++)
    {
    	maxOverArray[j] = 0;
    	flagTrees[j] = 1;
    }

    //decide the max equations numbers of each cluster.
    int odd = totalDof % numTrees;
    int base = totalDof / numTrees;
    outf << "odd is: " << odd << "\t base is: " << base << std::endl;

    for(int j=1; j<=numTrees; j++)
    {
    	maxOverArray[j] = base;
    	if(j<=odd)
    	{
    		if(base>5 && testSolverTrees.retrieve(j).returnType() == 2)
    			odd++;
    		else
    			maxOverArray[j]++;
    	}
    }

    outf << "the maxOver array is: ";
    for(int j=1; j<10; j++)
    	 outf << "\t" << maxOverArray[j] << std::endl;

    outf << "The testsolverTrees are:" << std::endl;
    for(int ii=1; ii <= testSolverTrees.returnLen(); ii++)
    {
	outf << " tree:::::" << std::endl;
        printTree(testSolverTrees.retrieve(ii), outf, 1);
    }
    print(newGraph, testSolverTrees);

    testFile1.close();
    testFile2.close();

    for(i=1;i<=testSolverTrees.returnLen();i++)
  	testSolverTrees.retrieve(i).currAlias=0;

    if(theCluster.returnOrig().returnLen()==theCluster.children.returnLen()) return "";

    theOrig=overlappedList;

    outf<<"Vars before getOverlap"<<std::endl;
    outf<<getVarString(vars)<<std::endl;

    length=theOrig.returnLen();
    for(i=1; i<=length; i++)
    {
        currOrig=theOrig.retrieve(i);
        getContainedChildList(theCluster,currOrig,in);
 	int treeIndex=1;
	//find the index of the tree which contains the vertex
	while(!inOriginalV(currOrig,testSolverTrees.retrieve(treeIndex))
              && treeIndex<testSolverTrees.returnLen())
       		treeIndex++;
	if(in.returnLen()>=3 && graph0.returnDimen()==3)
		testSolverTrees.retrieve(treeIndex).currAlias+=3;
    }

    for(i=1; i<=length; i++)
    {
       outf<<"Start Get Over Loop"<<std::endl;
       currOrig=theOrig.retrieve(i);
       outf<<"CurrOrig: "<<currOrig<<std::endl;
       //skip the line object
       if(graph0.returnVertByName(currOrig).returnType()==7)
       {	outf<<"SKIP IT...." << std::endl;
       		continue;}

       getContainedChildList(theCluster,currOrig,in);
       if(in.returnLen()<2) continue;

       type=graph0.returnVertByName(currOrig).returnType();

       int overLapClusterIndex=1;
       int availOver=-1, neededOver=0, currOver=0, maxOver;

       while(!inOriginalV(currOrig,testSolverTrees.retrieve(overLapClusterIndex))
              && overLapClusterIndex<testSolverTrees.returnLen())
       		outf<<overLapClusterIndex++<<std::endl;

       outf<<"overLapClusterIndex: "<<overLapClusterIndex<<std::endl;

       if(overLapClusterIndex<=testSolverTrees.returnLen() && graph0.returnDimen()>=2)
       {
             if((testSolverTrees.retrieve(overLapClusterIndex).currAlias==6 &&
                testSolverTrees.retrieve(overLapClusterIndex).returnType()!=2) ||
                (testSolverTrees.retrieve(overLapClusterIndex).currAlias==5 &&
                testSolverTrees.retrieve(overLapClusterIndex).returnType()==2))
	     {
		     outf<<"Skipping..."<<std::endl;
                     continue;
	     }
             else
             {
		     switch(type)
                     {

//                             case 6:neededOver=3;
//				     break;
			     case 6:
			     case 4:
			     case 0: neededOver=2;
                                     break;

                             case 1:
                             case 2: neededOver=3;
                                     break;
                             case 3: neededOver=4;
                                     break;
                             case 5: neededOver=5;
                                     break;
                             case 7: neededOver=6;
                                     break;
                     }


                     outf << "The current overlapped sub_cluster is: " << std::endl;
                     outf << testSolverTrees.retrieve(overLapClusterIndex) << std::endl;

		     maxOver = maxOverArray[overLapClusterIndex];

		     //for single vertex
		     if(testSolverTrees.retrieve(overLapClusterIndex).returnOrigLen()==1
			&& graph0.returnDimen()==3)
				neededOver = 3;
                     currOver=testSolverTrees.retrieve(overLapClusterIndex).currAlias;
                     availOver=maxOver-currOver;

                     if(type==6 && availOver>=3
                        && testSolverTrees.retrieve(overLapClusterIndex).returnType()==2)
                     	neededOver = 3;

      		     outf<<"maxOver:    "<<maxOver<<std::endl;
		     outf<<"neededOver: "<<neededOver<<std::endl;
		     outf<<"currOver:   "<<currOver<<std::endl;
		     outf<<"availOver:  "<<availOver<<std::endl;

                     if(neededOver<=availOver)
                     {
                             testSolverTrees.retrieve(overLapClusterIndex).currAlias+=neededOver;
                     }
                     else
                     {
                             testSolverTrees.retrieve(overLapClusterIndex).currAlias+=availOver;
                     }
             }//else
       }//if(overLapClusterIndex<=testSolverTrees.returnLen() && graph0.returnDimen()>2)

       outf<<"currOrig: "<<currOrig<<std::endl;
       outf<<"type:     "<<type<<std::endl;
       for(k=1;k<=testSolverTrees.returnLen();k++)
             outf<<"CurrAlias "<<k<<": "<<testSolverTrees.retrieve(k).currAlias<<std::endl;

       for(j=1; j<in.returnLen();j++)
       {
          outf<<"Start of inner for loop"<<std::endl;
	  clustint1=in.retrieve(j);
          clustint2=in.retrieve(j+1);
	  if(child1!=getChildIndexByName(theCluster, clustint1)||
	      child2!=getChildIndexByName(theCluster, clustint2))
	      continue;
          if(clustint1!=withHeldCluster) if(!theClust.hasElem(clustint1)) theClust.append(clustint1);
          if(clustint2!=withHeldCluster) if(!theClust.hasElem(clustint2)) theClust.append(clustint2);
          tempCluster1=theCluster.children.retrieve(getChildIndexByName(theCluster, clustint1));
          tempCluster2=theCluster.children.retrieve(getChildIndexByName(theCluster, clustint2));
          tempVertex1.setName(currOrig);
          tempVertex2.setName(currOrig);
	  outf<<"Right before set value"<<std::endl;
          setValueInCluster(graph0, tempCluster1, tempVertex1);
          setValueInCluster(graph0, tempCluster2, tempVertex2);
	  outf<<"Right after set value"<<std::endl;
          if(aOverlap==0 && clustint1!=withHeldCluster) aOverlap=clustint1;
          else if(aOverlap==0) aOverlap=clustint2;
          cluster1=toString(clustint1);
          cluster2=toString(clustint2);
          origStr=toString(currOrig);
          clusterV1="p"+cluster1;
          clusterV2="q"+cluster1;
          clusterV3="t"+cluster1;
          clusterV4="s"+cluster1;
          clusterV5="f"+cluster1;
          clusterV6="h"+cluster1;
          clusterV7="j"+cluster1;
          clusterV8="k"+cluster1;
          clusterV9="n"+cluster1;

	  outf<<"THIS IS IN OVERLAP"<<std::endl;
	  outf<<tempVertex1<<std::endl;
	  outf<<tempVertex2<<std::endl;

	  bool end1Over=(tempCluster1.returnType()==2 || tempCluster1.returnType()==5);
	  bool end2Over=(tempCluster2.returnType()==2 || tempCluster2.returnType()==5);

	  if(end1Over)
	  {
	    valueName=toString(tempVertex1.returnName()*1000+tempCluster1.returnName());
	    newStr1a="x"+valueName;
	    newStr2a="y"+valueName;
	    newStr3a="z"+valueName;           
	  }

          if(clustint1==withHeldCluster && !end1Over)
          {
            newStr1a="("+toString(tempVertex1.returnDegValueByName(0))+")";
            newStr2a="("+toString(tempVertex1.returnDegValueByName(1))+")";
            newStr3a="("+toString(tempVertex1.returnDegValueByName(2))+")";
          }

	  if(clustint1!=withHeldCluster && !end1Over)
          {
            if(type<6)
            {
              if(!vars.hasElem(clusterV1)) vars.append(clusterV1);
              if(!vars.hasElem(clusterV2)) vars.append(clusterV2);
              if(!vars.hasElem(clusterV3)) vars.append(clusterV3);
              if(!vars.hasElem(clusterV4)) vars.append(clusterV4);
              newStr1a="(("+toString(tempVertex1.returnDegValueByName(0))+")*"+clusterV3+"-("+toString(tempVertex1.returnDegValueByName(1))+")*"+clusterV4+"+"+clusterV1+")";
              newStr2a="(("+toString(tempVertex1.returnDegValueByName(1))+")*"+clusterV3+"+("+toString(tempVertex1.returnDegValueByName(0))+")*"+clusterV4+"+"+clusterV2+")";
              newStr3a="((("+toString(tempVertex1.returnDegValueByName(2))+")*"+clusterV3+"+"+clusterV4+")/(("+toString(tempVertex1.returnDegValueByName(2))+")*"+clusterV4+"+"+clusterV3+"))";
            }
            else
            {
              if(!vars.hasElem(clusterV1)) vars.append(clusterV1);
              if(!vars.hasElem(clusterV2)) vars.append(clusterV2);
              if(!vars.hasElem(clusterV3)) vars.append(clusterV3);
              if(!vars.hasElem(clusterV4)) vars.append(clusterV4);
              if(!vars.hasElem(clusterV5)) vars.append(clusterV5);
              if(!vars.hasElem(clusterV6)) vars.append(clusterV6);
              if(!vars.hasElem(clusterV7)) vars.append(clusterV7);
              if(!vars.hasElem(clusterV8)) vars.append(clusterV8);
              if(!vars.hasElem(clusterV9)) vars.append(clusterV9);
              repStrb1=toString(tempVertex1.returnDegValueByName(0));
              repStrb2=toString(tempVertex1.returnDegValueByName(1));
              repStrb3=toString(tempVertex1.returnDegValueByName(2));
              newStr1a="(("+repStrb1+"*"+clusterV6+"*"+clusterV8+")+";
              newStr1a+="("+repStrb2+"*"+clusterV6+"*"+clusterV9+")-";
              newStr1a+="("+repStrb3+"*"+clusterV7+")+"+clusterV1+")";
              newStr2a="(("+repStrb1+"*("+clusterV4+"*"+clusterV7+"*"+clusterV8+"-"+clusterV3+"*"+clusterV9+"))+";
              newStr2a+="("+repStrb2+"*("+clusterV3+"*"+clusterV8+"+"+clusterV4+"*"+clusterV7+"*"+clusterV9+"))+";
              newStr2a+="("+repStrb3+"*"+clusterV4+"*"+clusterV6+")+"+clusterV2+")";
              newStr3a="(("+repStrb1+"*("+clusterV4+"*"+clusterV9+"+"+clusterV3+"*"+clusterV7+"*"+clusterV8+"))+";
              newStr3a+="("+repStrb2+"*(-("+clusterV4+"*"+clusterV8+")+"+clusterV3+"*"+clusterV7+"*"+clusterV9+"))+";
              newStr3a+="("+repStrb3+"*"+clusterV3+"*"+clusterV6+")+"+clusterV5+")";              
            }
          }//if(clustint1!=withHeldCluster && !end1Over)

	  outf<<"Between end1 and end2"<<std::endl;

          clusterV1="p"+cluster2;
          clusterV2="q"+cluster2;
          clusterV3="t"+cluster2;
          clusterV4="s"+cluster2;
          clusterV5="f"+cluster2;
          clusterV6="h"+cluster2;
          clusterV7="j"+cluster2;
          clusterV8="k"+cluster2;
          clusterV9="n"+cluster2;

          if(end2Over)
          {
	    valueName=toString(tempVertex2.returnName()*1000+tempCluster2.returnName());
            newStr1b="x"+valueName;
            newStr2b="y"+valueName;
            newStr3b="z"+valueName;
          }	  

          if(clustint2==withHeldCluster && !end2Over)
          {
            newStr1b="("+toString(tempVertex2.returnDegValueByName(0))+")";
            newStr2b="("+toString(tempVertex2.returnDegValueByName(1))+")";
            newStr3b="("+toString(tempVertex2.returnDegValueByName(2))+")";
          }
	  if(clustint2!=withHeldCluster && !end2Over)
          {
            if(type<6)
            {
              if(!vars.hasElem(clusterV1)) vars.append(clusterV1);
              if(!vars.hasElem(clusterV2)) vars.append(clusterV2);
              if(!vars.hasElem(clusterV3)) vars.append(clusterV3);
              if(!vars.hasElem(clusterV4)) vars.append(clusterV4);
              newStr1b="(("+toString(tempVertex2.returnDegValueByName(0))+")*"+clusterV3+"-("+toString(tempVertex2.returnDegValueByName(1))+")*"+clusterV4+"+"+clusterV1+")";
              newStr2b="(("+toString(tempVertex2.returnDegValueByName(1))+")*"+clusterV3+"+("+toString(tempVertex2.returnDegValueByName(0))+")*"+clusterV4+"+"+clusterV2+")";
              newStr3b="((("+toString(tempVertex2.returnDegValueByName(2))+")*"+clusterV3+"+"+clusterV4+")/(("+toString(tempVertex2.returnDegValueByName(2))+")*"+clusterV4+"+"+clusterV3+"))";
            }   
            else
            {
              if(!vars.hasElem(clusterV1)) vars.append(clusterV1);
              if(!vars.hasElem(clusterV2)) vars.append(clusterV2);
              if(!vars.hasElem(clusterV3)) vars.append(clusterV3);
              if(!vars.hasElem(clusterV4)) vars.append(clusterV4);
              if(!vars.hasElem(clusterV5)) vars.append(clusterV5);
              if(!vars.hasElem(clusterV6)) vars.append(clusterV6);
              if(!vars.hasElem(clusterV7)) vars.append(clusterV7);
              if(!vars.hasElem(clusterV8)) vars.append(clusterV8);
              if(!vars.hasElem(clusterV9)) vars.append(clusterV9);
              repStrb1=toString(tempVertex2.returnDegValueByName(0));
              repStrb2=toString(tempVertex2.returnDegValueByName(1));
              repStrb3=toString(tempVertex2.returnDegValueByName(2));
              newStr1b="(("+repStrb1+"*"+clusterV6+"*"+clusterV8+")+";
              newStr1b+="("+repStrb2+"*"+clusterV6+"*"+clusterV9+")-";
              newStr1b+="("+repStrb3+"*"+clusterV7+")+"+clusterV1+")";
              newStr2b="(("+repStrb1+"*("+clusterV4+"*"+clusterV7+"*"+clusterV8+"-"+clusterV3+"*"+clusterV9+"))+";
              newStr2b+="("+repStrb2+"*("+clusterV3+"*"+clusterV8+"+"+clusterV4+"*"+clusterV7+"*"+clusterV9+"))+";
              newStr2b+="("+repStrb3+"*"+clusterV4+"*"+clusterV6+")+"+clusterV2+")";
              newStr3b="(("+repStrb1+"*("+clusterV4+"*"+clusterV9+"+"+clusterV3+"*"+clusterV7+"*"+clusterV8+"))+";
              newStr3b+="("+repStrb2+"*(-("+clusterV4+"*"+clusterV8+")+"+clusterV3+"*"+clusterV7+"*"+clusterV9+"))+";
              newStr3b+="("+repStrb3+"*"+clusterV3+"*"+clusterV6+")+"+clusterV5+")";
            }//else
          }//if(clustint2!=withHeldCluster && !end2Over)

	  outf<<"Before closing switch"<<std::endl;
	  List<int> tempList;     
          switch(type)
          {
                case 4:
                case 0:  if(availOver>=1) 
			 {
				temp+=newStr1a+"="+newStr1b;
				equationCount++;
			 }
			 if(availOver>=2)
                         {
				temp+=","+newStr2a+"="+newStr2b;
                                equationCount++;
                         }
                         break;
                case 1:  if(availOver>=1)
                         {
                                temp+=newStr1a+"="+newStr1b;
                                equationCount++;
                         }
                         if(availOver>=2)
                         {
			        temp+=","+newStr2a+"="+newStr2b;
                                equationCount++;
                         }
			 if(availOver>=3)
                         {
                                temp+=","+newStr3a+"="+newStr3b;
                                equationCount++;
                         }
                         break;
               case 6:  

			getContainedChildList(theCluster, currOrig, tempList);
			if(tempList.returnLen()>2)
			{
				if(!childrenUsed(currOrig, child1, child2, vUsedList))
				{
					temp+=newStr1a+"="+newStr1b;
					equationCount++;
					temp+=","+newStr2a+"="+newStr2b;
			                equationCount++;			
					temp+=","+newStr3a+"="+newStr3b;
		  	                equationCount++;
					addUsedChildren(currOrig, child1, child2, vUsedList);
				}
			}
			else 
		 	{
			   switch(flagTrees[overLapClusterIndex])
		 	   {
		 		case 1:                	 
		                	 if(availOver>=1) 
					 {
		
						temp+=newStr1a+"="+newStr1b;
						equationCount++;
					 }
					 if(availOver>=2)
		                         {
						temp+=","+newStr2a+"="+newStr2b;
		                                equationCount++;
		                         }
					 if((testSolverTrees.retrieve(overLapClusterIndex).returnType()==2
					    || testSolverTrees.retrieve(overLapClusterIndex).returnOrigLen()==1)
					    && availOver>=3)
		                         {
						temp+=","+newStr3a+"="+newStr3b;
		                                equationCount++;
		                         }		                         
		                         break;
		 		case 2: 
					 if(testSolverTrees.retrieve(overLapClusterIndex).returnType()==2)
		                         {
			                	 if(availOver>=1) 
						 {
							temp+=newStr1a+"="+newStr1b;
							equationCount++;
						 }
						 if(availOver>=2)
			                         {
							temp+=","+newStr2a+"="+newStr2b;
			                                equationCount++;
			                         }
		                         }	
		                         else
		                         {               	 
			                	 if(availOver>=1) 
						 {
			
							temp+=newStr2a+"="+newStr2b;
							equationCount++;
						 }
						 if(availOver>=2)
			                         {
							temp+=","+newStr3a+"="+newStr3b;
			                                equationCount++;
			                         }
			                 }
		                         break;
		 		case 3:                	 
		                	 if(availOver>=1) 
					 {
						temp+=newStr3a+"="+newStr3b;
						equationCount++;
					 }
					 if(availOver>=2)
		                         {
						temp+=","+newStr1a+"="+newStr1b;
		                                equationCount++;
		                         }
		                         break;
		            }//switch
		            flagTrees[overLapClusterIndex]++;
                	    if(flagTrees[overLapClusterIndex]==3)
                	 	flagTrees[overLapClusterIndex] = 1;
			 }//else for type 6
                         break;	
                default: temp="";
                         break;
          }//switch(type)
	  outf<<"after switch"<<std::endl;
	  if(temp.length() != 0)
                output+=","+temp;
          temp="";
	  outf<<"output at end of inner loop: "<<output<<std::endl;
       }//for(j=1; j<in.returnLen();j++)
       outf<<"clearing in"<<std::endl;
       in.makeEmpty();
       outf<<"End of Get Over loop"<<std::endl;
    }//for(i=1; i<=length; i++)

    if(equationCount==0) output.erase(0,1);

    return output;
}


void 
addUsedChildren (int vName, int child1, int child2, List<VUsed> &vUsedList)
{
	VUsed temp;
	bool added = false;
	for(int i=1; i<=vUsedList.returnLen(); i++)
	{
		temp = vUsedList.retrieve(i);
		if(temp.vName == vName)
		{
			if(!temp.usedChild.hasElem(child1))
			{
				temp.usedChild.append(child1);
				added = true;
			}
			if(!temp.usedChild.hasElem(child2))
			{
				temp.usedChild.append(child2);
				added = true;
			}
			break;
		}
	}
	if(!added)
	{
		VUsed * t = new VUsed;
		t->vName = vName;
		t->usedChild.append(child1);
		t->usedChild.append(child2);
		vUsedList.append(*t);
	}
}


std::string
getSpecialCaseEquations (Graph &graph0, Cluster &theCluster, int caseInt, 
                         std::string &outputString)
{
	std::string output="";

	std::ofstream outf;
	outf.open("getSpecialCase.out", std::ios::app);
	outf << "The beginning...." << std::endl;
	outf << theCluster << std::endl;

	switch(caseInt)
	  {
		  case 1:	
        int ID1=theCluster.children.retrieve(1).returnName();
			  std::string id1Name=toString(ID1);

			  int i=2;
			  int flag = 0;
			  int ID2=theCluster.children.retrieve(i).returnName();
			  int value=isValidSecond(graph0,ID1, ID2, outputString, flag);
			  outf <<"i="<<i<<"ID2="<<ID2<<" value="<<value<<std::endl;

			  while(ID2>0 && value==0)
			    {
				    i++;
				    ID2=theCluster.children.retrieve(i).returnName();
				    value=isValidSecond(graph0,ID1, ID2, outputString, flag);
				    outf<<"i="<<"    ID2="<<ID2<<"    value="<<value << "   flag=" 
                << flag<<std::endl;
			    }
			  outf << "after while, the values are: " << std::endl;
			  outf<<"i="<<"    ID2="<<ID2<<"    value="<<value << "   flag=" << flag
            <<std::endl;
			  std::string id2Name=toString(ID2);

			  output+="x"+id1Name+"=1/rand(),";
        output+="y"+id1Name+"=1/rand(),";
        if(graph0.returnDimen()==3)
	        {
            if(flag==1) output+="z"+id1Name+"=1/rand(),";
	          else	output+="e"+id1Name+"=1/rand(),";
	        }
        output+="c"+id1Name+"=1/rand(),";
        output+="d"+id1Name+"=1/rand(),";
			  switch(value)
			    {
				    case 1: output+="x"+id2Name+"=1/rand()";
					          break;
				    case -1: output+="c"+id2Name+"=1/rand()";
                     break;
				    default: exit(-1);
			    }
			  minusString(outputString, ID1, ID2);
			  break;
	  }

	return output;
}


ClustData& 
summCluster (Graph &graph0, Cluster &theCluster)
{
	int len;

	len=countEdges(graph0, theCluster);

	std::cout<<"CountEdges="<<len<<std::endl;

	ClustData *temp = new ClustData(len);

	int i, count=0, eCode;
	Edge edge;

  std::cout<<"BEGIN SUMM CLUSTER"<<std::endl;
  std::cout<<"Depth="<<theCluster.returnCore().returnDepth()<<std::endl;

	len=graph0.returnNumEdg();
	std::cout<<"graph Edge Lenght="<<len<<std::endl;
	for(i=1; i<=len; i++)
	  {
		  int end1Name;
		  int end2Name;

		  edge=graph0.returnEdgeByIndex(i);
		  eCode=getEdgeCode(edge, theCluster);
		  std::cout<<"eCode="<<eCode<<" Edge="<<edge<<std::endl;
		  
		  end1Name=edge.returnEnd1();
                  end2Name=edge.returnEnd2();

		  if(eCode!=1 && theCluster.returnCore().returnDepth()!=1) continue;

		  if(true) //edge.returnType()==1)
		    {
		  	  int j;
		  	  bool skip=false;

		  	  for(j=1;j<=theCluster.children.returnLen();j++)
		  	    {
		  	  	  int k;

		  	  	  Cluster currChild=theCluster.children.retrieve(j);
		  	  	  bool end1Value, end2Value;

		  	  	  std::cout<<"Alias  : "<<currChild.currAlias<<std::endl;
	            std::cout<<"Left   : ";
              for(k=1;k<=currChild.left.returnLen();k++)
                std::cout<<currChild.left.retrieve(k);
              std::cout<<std::endl;
              
	            std::cout<<"Right  : ";
              for(k=1;k<=currChild.right.returnLen();k++)
                std::cout<<currChild.right.retrieve(k);
              std::cout<<std::endl;  
              
	            std::cout<<"Lines  : ";
              for(k=1;k<=currChild.lines.returnLen();k++)
                std::cout<<currChild.lines.retrieve(k);
              std::cout<<std::endl;


		  	  	  end1Value=(currChild.currAlias==end1Name 	|| 
		  	  	             currChild.left.hasElem(end1Name)	||
		  	  	             currChild.right.hasElem(end1Name)	||
		  	  	             currChild.lines.hasElem(end1Name));
		  
              end2Value=(currChild.currAlias==end2Name         ||
                         currChild.left.hasElem(end2Name)     ||
                         currChild.right.hasElem(end2Name)    ||
                         currChild.lines.hasElem(end2Name));

		  	  	  std::cout<<"end1Value="<<(end1Value ? "true" : "false")<<std::endl;
		  	  	  std::cout<<"end2Value="<<(end2Value ? "true" : "false")<<std::endl;

		  	  	  if(end1Value && end2Value) skip=true;
		  	    }

		  	  if(skip)
		  	    {
		  	      std::cout<<"Skipping..."<<std::endl;
		  	      temp->length--;
		  	      continue;
		  	    }
		    }
	
		  if(eCode==1)
		    {
			    int j;
			    int countSet=0;
			    
			    for(j=1;j<=theCluster.children.returnLen();j++)
			      {
			    	  std::cout<<"Current Item: "<<j<<std::endl;
			    	  if(theCluster.children.retrieve(j).returnType()==Vertex::Ray
			    		   || theCluster.children.retrieve(j).returnType()==Vertex::Arc)
			    	    {
			    	      if(inOriginalV(end1Name,theCluster.children.retrieve(j)))
			    		      {	
			    			      countSet++;
			    			      end1Name=end1Name*1000+theCluster.children.retrieve(j).returnName();
			    		      }
 			    		    if(inOriginalV(end2Name,theCluster.children.retrieve(j)))
                    {       
                      countSet++;
			    			      end2Name=end2Name*1000+theCluster.children.retrieve(j).returnName();
			    		      }
			    	    }
			      }
			    std::cout<<"Count Set="<<countSet<<std::endl;
			    if(countSet>1) eCode=0;
		    }

		  if(eCode!=-1)
		    {
			    temp->inOrBetween[count]=true;//(eCode==1);
			    temp->edgeID[count]=edge.returnName();
			    temp->edgeType[count]=edge.returnType();
			    temp->e1ID[count]=end1Name;
			    temp->e2ID[count]=end2Name;
          temp->e1Type[count]=graph0.returnVertByName(edge.returnEnd1()).returnType();
			    temp->e2Type[count]=graph0.returnVertByName(edge.returnEnd2()).returnType();
			    temp->e1Part[count]=edge.returnPart1();
			    temp->e2Part[count]=edge.returnPart2();
			    temp->values[count]=edge.returnValue();

			    std::cout<<edge<<std::endl;
			    std::cout<<temp->inOrBetween[count]<<std::endl;
			    std::cout<<temp->edgeID[count]<<std::endl;
          std::cout<<temp->edgeType[count]<<std::endl;
          std::cout<<temp->e1ID[count]<<std::endl;
          std::cout<<temp->e2ID[count]<<std::endl;
          std::cout<<temp->e1Type[count]<<std::endl;
          std::cout<<temp->e2Type[count]<<std::endl;
          std::cout<<temp->e1Part[count]<<std::endl;
          std::cout<<temp->e2Part[count]<<std::endl;
          std::cout<<temp->values[count]<<std::endl;

			    count++;
		    }
	  }

	std::cout<<"Displaying Temp"<<std::endl;
	std::cout<<"Temp Length="<<temp->length<<std::endl;

	std::cout<<*temp<<std::endl;

  std::cout<<"END SUMM CLUSTER"<<std::endl;

	return *temp;
}


//! get the number of the edges which are in the cluster, but not in its 
//! subcluster.	
int 
countEdges (Graph &graph0, Cluster &theCluster)
{
	int i, length;
	int temp, count=0;
	Edge edge;

	length=graph0.returnNumEdg();
	for(i=1; i<=length; i++)
	  {
		  edge=graph0.returnEdgeByIndex(i);
		  temp=getEdgeCode(edge, theCluster);
		  std::cout<<"CountEdge Depth: "<<theCluster.returnCore().returnDepth()<<std::endl;
		  if(theCluster.returnCore().returnDepth()==1)
		    {
			    std::cout<<"Neg 1"<<std::endl;
			    if(temp!=-1)
				    count++;
		    }
		  else
		    {
			    std::cout<<"One"<<std::endl;
			    if(temp==1)
				    count++;
		    }
	  }

	return count;
}


//! create another special cluster for the linesegment in the overlapped part
//! This cluster includes one more line segment in it
Cluster createSP2Cluster(Graph &newGraph)
{
	List<Edge> ie;
	List<Edge> oe;
        List<int> fro;
        List<int> ori;
        Vertex core;
        Cluster s1, s2, rst;
	int v1Name, v2Name;
	int index = 1;

	std::cout << "==============================bingo, SECOND SPECIAL CASE=================" <<std::endl;
	core = newGraph.returnVertByIndex(index++);
	if(core.returnType()!=6)
		core = newGraph.returnVertByIndex(index++);
	v1Name = core.returnName();
        fro.makeEmpty();
        ori.makeEmpty();
        fro.append(v1Name);
        ori.append(v1Name);
        s1.formCl(core, fro, ie, oe, ori);

	core = newGraph.returnVertByIndex(index++);
	if(core.returnType()!=6)
		core = newGraph.returnVertByIndex(index++);
	v2Name = core.returnName();
        fro.makeEmpty();
        ori.makeEmpty();
        fro.append(v2Name);
        ori.append(v2Name);
        s2.formCl(core, fro, ie, oe, ori);

	//lineSegment
        fro.makeEmpty();
        ori.makeEmpty();
        core.setName(11);
        core.setDepth(1);
        core.setType(Vertex::Ray);
                ori.append(v1Name);
                ori.append(v2Name);
                fro.append(v1Name);
                fro.append(v2Name);

        rst.formCl(core, fro, ie, oe, ori);
        rst.children.append(s1);
        rst.children.append(s2);
	std::cout << "What is the special one we created for overlapped part:" << std::endl;
	rst.setType(2);
  std::cout << rst << std::endl;
	return rst;
}


//! create special cluster for the linesegment in the overlapped part
Cluster createSPCluster(Graph &newGraph)
{
	List<Edge> ie;
	List<Edge> oe;
        List<int> fro;
        List<int> ori;
        Vertex core;
        Cluster s1, s2, rst;
	int v1Name, v2Name;

	std::cout << "==============================bingo,,,,=================" <<std::endl;
	core = newGraph.returnVertByIndex(1);
	v1Name = core.returnName();
        fro.makeEmpty();
        ori.makeEmpty();
        fro.append(v1Name);
        ori.append(v1Name);
        s1.formCl(core, fro, ie, oe, ori);

	core = newGraph.returnVertByIndex(2);
	v2Name = core.returnName();
        fro.makeEmpty();
        ori.makeEmpty();
        fro.append(v2Name);
        ori.append(v2Name);
        s2.formCl(core, fro, ie, oe, ori);

	//lineSegment
        fro.makeEmpty();
        ori.makeEmpty();
        core.setName(11);
        core.setDepth(1);
        core.setType(Vertex::Ray);
                ori.append(v1Name);
                ori.append(v2Name);
                fro.append(v1Name);
                fro.append(v2Name);

        rst.formCl(core, fro, ie, oe, ori);
        rst.children.append(s1);
        rst.children.append(s2);
	std::cout << "What is the special one we created for overlapped part:" << std::endl;
	rst.setType(2);
  std::cout << rst << std::endl;
	return rst;
}


//! returns true if the constraint theEdge, is imaginary and must be checked to 
//! see if it is satisfied
bool isImaginary(Graph &graph0, Edge &theEdge)
{
  Vertex::Type end1Type, end2Type;
  int part1, part2;

  if(theEdge.returnType()!=1) return false;

  end1Type=graph0.returnVertByName(theEdge.returnEnd1()).returnType();
  end2Type=graph0.returnVertByName(theEdge.returnEnd2()).returnType();
  
  part1=theEdge.returnPart1();
  part2=theEdge.returnPart2();

  if(part1!=0 && part2!=0) return false;

  if ((end1Type == Vertex::Point or end1Type == Vertex::Ray or
       end1Type == Vertex::LineSeg or end1Type == Vertex::Arc)
      and
      (end2Type == Vertex::Point or end2Type == Vertex::Ray or
       end2Type == Vertex::LineSeg or end2Type == Vertex::Arc))
    {
      return(part1==0 || part2==0);
    }
  else if ((end1Type == Vertex::Line and end2Type == Vertex::Arc) or
           (end1Type == Vertex::Circle and end2Type == Vertex::Ray) or
           (end1Type == Vertex::Circle and end2Type == Vertex::LineSeg) or
           (end1Type == Vertex::Circle and end2Type == Vertex::Arc))
    {
      return(part2==0);
    }
  else if ((end2Type == Vertex::Line and end1Type == Vertex::Arc) or
           (end2Type == Vertex::Circle and end1Type == Vertex::Ray) or
           (end2Type == Vertex::Circle and end1Type == Vertex::LineSeg) or
           (end2Type == Vertex::Circle and end1Type == Vertex::Arc))
    {
      return(part1==0);
    }
  else
    {
      return(part1==0 && part2==0);
    }
  return false;
}
