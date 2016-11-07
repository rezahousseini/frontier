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

//! \file mfa9Solver.cpp
//! \brief The entire equation and solution manager ESM


#define INTSIZE		16000
#define FLOATSIZE	4000
#define CHARSIZE	10000

#include "Solver.h"

//! returns in Vertex, the point of intersection between line1 and line2
void getIntersectionLineLine(Vertex &theVertex, float x1, float y1, float m1, 
                             float x2, float y2, float m2)
{
     float Xout, Yout;
     float Xnew, Ynew;

     Xnew=x2-x1;
     Ynew=y2-y1;

     Xout=(m2*Xnew+Ynew)/(m1-m2);
     Yout=Xout*m1;
     
     Xout+=x1;
     Yout+=y1;

     theVertex.setValues(0,Xout);
     theVertex.setValues(1,Yout);
     theVertex.setType(Vertex::Point);
}

//! returns in thePoints the two point of intersection between a line and a circle
void getIntersectionLineCircle(List<Vertex> &thePoints, float x1, float y1, 
                               float m1, float x2, float y2, float r)
{
    float Xout1, Yout1, Xout2, Yout2;
    float deter;

    deter=-y2-pow(m1,2)*pow(x1,2)+2*y1*m1*x1+pow(r,2)+pow(m1,2)*pow(r,2);

    if(deter<0) 
    {
      thePoints.retrieve(1).setType(Vertex::Cluster);
      return;
    }

    Xout1=pow(m1,2)*x1+y1*m1+sqrt(deter)+x1;
    Xout2=pow(m1,2)*x1+y1*m1-sqrt(deter)+x2;
    Yout1=m1*Xout1;
    Yout2=m1*Xout2;

    thePoints.retrieve(1).setType(Vertex::Point);
    thePoints.retrieve(1).setValues(0,Xout1);
    thePoints.retrieve(1).setValues(1,Yout1);
    thePoints.retrieve(2).setType(Vertex::Point);
    thePoints.retrieve(2).setValues(0,Xout2);
    thePoints.retrieve(2).setValues(1,Yout2);
}

//! returns a vertex list containing the two points of intersection between 2 circles
void getIntersectionCircleCircle(List<Vertex> &thePoints, float x1, float y1, 
                                 float r1, float x2, float y2, float r2)
{
    float Xout1, Yout1, Xout2, Yout2;
    float Xnew, Ynew;
    float deter, d, e, f;

    Xnew=x2-x1;
    Ynew=y2-y1;

    d=pow(Xnew,2)+pow(Ynew,2);
    e=pow(r1,2)-pow(r2,2);
    f=pow(r1,2)+pow(r2,2);

    deter=-pow(d,2)+2*d*f-pow(e,2);

    if(deter<0) 
    {
      thePoints.retrieve(1).setType(Vertex::Cluster);
      return;
    }

    Xout1=(Xnew*(e+d)-Ynew*sqrt(deter))/(2*d)+x1;
    Xout2=(Xnew*(e+d)+Ynew*sqrt(deter))/(2*d)+x1;
    Yout1=(Ynew*(e+d)-Xnew*sqrt(deter))/(2*d)+y1;
    Yout2=(Ynew*(e+d)-Xnew*sqrt(deter))/(2*d)+x1;

    thePoints.retrieve(1).setType(Vertex::Point);
    thePoints.retrieve(1).setValues(0,Xout1);
    thePoints.retrieve(1).setValues(1,Yout1);
    thePoints.retrieve(2).setType(Vertex::Point);
    thePoints.retrieve(2).setValues(0,Xout2);
    thePoints.retrieve(2).setValues(1,Yout2);
}    

//! given an point and another object, determines if the point has incidence with the object
bool isValidPointIncidence(Vertex &thePoint, Vertex &theOther, int part1, int part2)
{
  Vertex::Type type;
  float angle1a, angle1b, angle2a, angle2b, x1, y1, x2, y2, x3, y3;
  float pointAngle, length1, length2, length;

  if(part1!=1) return false;
  if(part2!=0) return true;   

  type=theOther.returnType();
  
  x1=thePoint.returnDegValueByName(0);
  y1=thePoint.returnDegValueByName(1);
  x2=theOther.returnDegValueByName(0);
  y2=theOther.returnDegValueByName(1);

  switch(type)
  {
    case Vertex::Ray:   angle1a=theOther.returnDegValueByName(4);
                  angle1b=theOther.returnDegValueByName(5);
                  return (getAngle(angle1a,angle1b)==getAngle(x2,y2,x1,y2));
                  break;
    case Vertex::LineSeg:   x3=theOther.returnDegValueByName(2);
  	            y3=theOther.returnDegValueByName(3);
                  length=getDistance(x2,y2,x3,y3);
                  length1=getDistance(x1,y1,x2,y2);
                  length2=getDistance(x1,y1,x3,y3);
                  if(length1<length && length2<length) return true;
                  else return false;
                  break;
    case Vertex::Arc:   pointAngle=getAngle(x2,y2,x1,y2);
                  angle1a=theOther.returnDegValueByName(4);
                  angle1b=theOther.returnDegValueByName(5);
                  angle2a=theOther.returnDegValueByName(6);
                  angle2b=theOther.returnDegValueByName(7);
                  if(pointAngle>=getAngle(angle1a,angle1b) && 
                     pointAngle<=getAngle(angle2a,angle2b)) 
                    return true;
                  else return false;
                  break;
        default:  return true;
	              break;
  }
}

//! given a line and another object, returns true if the object is incidence 
//! about the line
bool 
isValidLineIncidence (Vertex &theLine, Vertex &theOther, int part1, int part2)
{
  Vertex::Type type = theOther.returnType();
  float x1, y1, m1, x2, y2, m2, r2;
  Vertex theInter, Vert1, Vert2;
  List<Vertex> theInters;
  bool out1, out2;

  if(part1!=0) return false;
  if(part2!=0) return true;   

  x1=theLine.returnDegValueByName(0);
  y1=theLine.returnDegValueByName(1);
  m1=theLine.returnDegValueByName(4);
  x2=theOther.returnDegValueByName(0);
  y2=theOther.returnDegValueByName(1);

  switch(type)
  {
    case Vertex::Line:   m2=theOther.returnDegValueByName(4);
                  return(m1!=m2);
                  break;
    case Vertex::Ray:
    case Vertex::LineSeg:   if(type==Vertex::Ray) m2=(theOther.returnDegValueByName(5)/theOther.returnDegValueByName(4));
                  else m2=theOther.returnDegValueByName(4);
                  getIntersectionLineLine(theInter, x1, y1, m1, x2, y2, m2);
                  return(isValidPointIncidence(theInter, theOther,1,0));
                  break;
    case Vertex::Circle:   theInters.append(Vert1);
                  theInters.append(Vert2);
                  r2=theOther.returnDegValueByName(2);
                  getIntersectionLineCircle(theInters, x1, y1, m1, x2, y2, r2);
                  return(theInters.retrieve(1).returnType()!=Vertex::Cluster);
                  break;
    case Vertex::Arc:   theInters.append(Vert1);
                  theInters.append(Vert2);
                  r2=theOther.returnDegValueByName(2);
                  getIntersectionLineCircle(theInters, x1, y1, m1, x2, y2, r2);
                  if(theInters.retrieve(1).returnType()==Vertex::Cluster)  return false;
                  out1=isValidPointIncidence(theInters.retrieve(1), theOther,1,0);
                  out2=isValidPointIncidence(theInters.retrieve(2), theOther,1,0);
                  return(out1 || out2);
                  break;
        default:  return true;
  }
}

//! given a ray and another object, returns true if the object is incident upon the ray
bool isValidRayIncidence(Vertex &theRay, Vertex &theOther, int part1, int part2)
{
  Vertex::Type type = theOther.returnType();
  float x1, y1, x2, y2, x3, y3, m1, m2, r2;
  Vertex theInter, Vert1, Vert2;
  List<Vertex> theInters;
  bool out1, out2;

  x1=theRay.returnDegValueByName(0);
  y1=theRay.returnDegValueByName(1);
  m1=theRay.returnDegValueByName(5)/theRay.returnDegValueByName(4);
  x2=theOther.returnDegValueByName(0);
  y2=theOther.returnDegValueByName(1);

  switch(type)
  {
    case Vertex::Ray:   switch(part1*10+part2)
                  {
                        case 0:  m2=theOther.returnDegValueByName(5)/theOther.returnDegValueByName(4);
                                 getIntersectionLineLine(theInter, x1, y1, m1, x2, y2, m2);
                                 out1=isValidPointIncidence(theInter, theOther,1,0);
                                 out2=isValidPointIncidence(theInter, theRay,1,0);
                                 return(out1 && out2);
                                 break;
                        case 1:  Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x2);
                                 Vert1.setValues(1,y2);
                                 return(isValidPointIncidence(Vert1,theRay,1,0));
                                 break;
                        case 10: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1);
                                 Vert1.setValues(1,y1);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 11: return true;
                                 break;
                  }
                  break;
    case Vertex::LineSeg:   switch(part1*10+part2)
                  {
                        case 0:  m2=theOther.returnDegValueByName(4);
                                 getIntersectionLineLine(theInter, x1, y1, m1, x2, y2, m2);
                                 out1=isValidPointIncidence(theInter, theOther,1,0);
                                 out2=isValidPointIncidence(theInter, theRay,1,0);
                                 return(out1 && out2);
                                 break;
                        case 1:  Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x2);
                                 Vert1.setValues(1,y2);
                                 return(isValidPointIncidence(Vert1,theRay,1,0));
                                 break;
                        case 2:  x3=theOther.returnDegValueByName(2);
                                 y3=theOther.returnDegValueByName(3);
                                 Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x3);
                                 Vert1.setValues(1,y3);
                                 return(isValidPointIncidence(Vert1,theRay,1,0));
                                 break;
                        case 10: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1);
                                 Vert1.setValues(1,y1);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 11:
                        case 12: return true;
                                 break;
                  }
                  break;
    case Vertex::Circle:   switch(part1*10+part2)
                  {
                         case 0:  theInters.append(Vert1);
                                  theInters.append(Vert2);
                                  r2=theOther.returnDegValueByName(2);
                                  getIntersectionLineCircle(theInters, x1, y1, m1, x2, y2, r2);
                                  if(theInters.retrieve(1).returnType()==Vertex::Cluster)  return false;
                                  out1=isValidPointIncidence(theInters.retrieve(1), theRay,1,0);
                                  out2=isValidPointIncidence(theInters.retrieve(2), theRay,1,0);
                                  return(out1 || out2);
                         case 3:  Vert1.setType(Vertex::Point);
                                  Vert1.setValues(0,x2);
                                  Vert1.setValues(1,y2);
                                  return(isValidPointIncidence(Vert1,theRay,1,0));
                                  break;
                         case 10:
                         case 13: return true;
                                  break;
                  }
                  break;
    case Vertex::Arc:   switch(part1*10+part2)
                  {
                        case 0:  theInters.append(Vert1);
                                 theInters.append(Vert2);
                                 r2=theOther.returnDegValueByName(2);
                                 getIntersectionLineCircle(theInters, x1, y1, m1, x2, y2, r2);
                                 if(theInters.retrieve(1).returnType()==Vertex::Cluster)  return false;
                                 out1=isValidPointIncidence(theInters.retrieve(1), theOther,1,0);
                                 out1=(out1 && isValidPointIncidence(theInters.retrieve(1), theRay,1,0));
                                 out2=isValidPointIncidence(theInters.retrieve(2), theOther,1,0);
                                 out2=(out2 && isValidPointIncidence(theInters.retrieve(2), theRay,1,0));
                                 return(out1 || out2);
                                 break;
                        case 1:  r2=theOther.returnDegValueByName(2);
                                 x3=x2+r2*theOther.returnDegValueByName(4);
                                 y3=y2+r2*theOther.returnDegValueByName(5);
                                 Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x3);
                                 Vert1.setValues(1,y3);
                                 return(isValidPointIncidence(Vert1,theRay,1,0));
                                 break;
                        case 2:  r2=theOther.returnDegValueByName(2);
                                 x3=x2+r2*theOther.returnDegValueByName(6);
                                 y3=y2+r2*theOther.returnDegValueByName(7);
                                 Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x3);
                                 Vert1.setValues(1,y3);
                                 return(isValidPointIncidence(Vert1,theRay,1,0));
                                 break;
                        case 3:  Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x2);
                                 Vert1.setValues(1,y2);
                                 return(isValidPointIncidence(Vert1,theRay,1,0));
                                 break;
                        case 10: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1);
                                 Vert1.setValues(1,y1);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 11:
                        case 12:
                        case 13: return true;
                                 break;
                  }
        default:  return true;
  }
  return false;
}

//! given a line segment and another object, returns true if the object is 
//! incident with the line segment
bool isValidLSIncidence(Vertex &theLS, Vertex &theOther, int part1, int part2)
{
  Vertex::Type type = theOther.returnType();
  float x1a, y1a, x1b, y1b, x2, y2, x3, y3, m1, m2, r2;
  Vertex theInter, Vert1, Vert2;
  List<Vertex> theInters;
  bool out1, out2;

  x1a=theLS.returnDegValueByName(0);
  y1a=theLS.returnDegValueByName(1);
  x1b=theLS.returnDegValueByName(2);
  y1b=theLS.returnDegValueByName(3);
  m1=theLS.returnDegValueByName(4);
  x2=theOther.returnDegValueByName(0);
  y2=theOther.returnDegValueByName(1);

  switch(type)
  {
    case Vertex::LineSeg:   switch(part1*10+part2)
                  {
                        case 0:  m2=theOther.returnDegValueByName(4);
                                 getIntersectionLineLine(theInter, x1a, y1a, m1, x2, y2, m2);
                                 out1=isValidPointIncidence(theInter, theOther,1,0);
                                 out2=isValidPointIncidence(theInter, theLS,1,0);
                                 return(out1 && out2);
                                 break;
                        case 1:  Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x2);
                                 Vert1.setValues(1,y2);
                                 return(isValidPointIncidence(Vert1,theLS,1,0));
                                 break;
                        case 2:  x3=theOther.returnDegValueByName(2);
                                 y3=theOther.returnDegValueByName(3);
                                 Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x3);
                                 Vert1.setValues(1,y3);
                                 return(isValidPointIncidence(Vert1,theLS,1,0));
                                 break;
                        case 10: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1a);
                                 Vert1.setValues(1,y1a);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 20: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1b);
                                 Vert1.setValues(1,y1b);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 21:
                        case 11:
                        case 12: return true;
                                 break;
                  }
                  break;
    case Vertex::Circle:   switch(part1*10+part2)
                  {
                        case 0:  theInters.append(Vert1);
                                 theInters.append(Vert2);
                                 r2=theOther.returnDegValueByName(2);
                                 getIntersectionLineCircle(theInters, x1a, y1a, m1, x2, y2, r2);
                                 if(theInters.retrieve(1).returnType()==Vertex::Cluster)  return false;
                                 out1=isValidPointIncidence(theInters.retrieve(1), theLS,1,0);
                                 out2=isValidPointIncidence(theInters.retrieve(2), theLS,1,0);
                                 return(out1 || out2);
                        case 3:  Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x2);
                                 Vert1.setValues(1,y2);
                                 return(isValidPointIncidence(Vert1,theLS,1,0));
                                 break;
                        case 10:
                        case 20:
                        case 13:
                        case 23: return true;
                                 break;
                  }
                  break;
    case Vertex::Arc:   switch(part1*10+part2)
                  {
                        case 0:  theInters.append(Vert1);
                                 theInters.append(Vert2);
                                 r2=theOther.returnDegValueByName(2);
                                 getIntersectionLineCircle(theInters, x1a, y1a, m1, x2, y2, r2);
                                 if(theInters.retrieve(1).returnType()==Vertex::Cluster)  return false;
                                 out1=isValidPointIncidence(theInters.retrieve(1), theOther,1,0);
                                 out1=(out1 && isValidPointIncidence(theInters.retrieve(1), theLS,1,0));
                                 out2=isValidPointIncidence(theInters.retrieve(2), theOther,1,0);
                                 out2=(out2 && isValidPointIncidence(theInters.retrieve(2), theLS,1,0));
                                 return(out1 || out2);
                                 break;
                        case 1:  r2=theOther.returnDegValueByName(2);
                                 x3=x2+r2*theOther.returnDegValueByName(4);
                                 y3=y2+r2*theOther.returnDegValueByName(5);
                                 Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x3);
                                 Vert1.setValues(1,y3);
                                 return(isValidPointIncidence(Vert1,theLS,1,0));
                                 break;
                        case 2:  r2=theOther.returnDegValueByName(2);
                                 x3=x2+r2*theOther.returnDegValueByName(6);
                                 y3=y2+r2*theOther.returnDegValueByName(7);
                                 Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x3);
                                 Vert1.setValues(1,y3);
                                 return(isValidPointIncidence(Vert1,theLS,1,0));
                                 break;
                        case 3:  Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x2);
                                 Vert1.setValues(1,y2);
                                 return(isValidPointIncidence(Vert1,theLS,1,0));
                                 break;
                        case 10: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1a);
                                 Vert1.setValues(1,y1a);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 20: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1b);
                                 Vert1.setValues(1,y1b);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 11:
                        case 12:
                        case 13:
                        case 21:
                        case 22:
                        case 23: return true;
                                 break;
                  }
        default:  return true;
  }
  return false;
}

//! given a circle and another object, returns true if the object is incident upon the circle
bool isValidCircleIncidence(Vertex &theCircle, Vertex &theOther, int part1, int part2)
{
  Vertex::Type type = theOther.returnType();
  float x1, y1, r1, x2, y2, r2, sep;
  Vertex theInter, Vert1, Vert2;
  List<Vertex> theInters;
  bool out1, out2;

  x1=theCircle.returnDegValueByName(0);
  y1=theCircle.returnDegValueByName(1);
  r1=theCircle.returnDegValueByName(2);  
  x2=theOther.returnDegValueByName(0);
  y2=theOther.returnDegValueByName(1);
  r2=theOther.returnDegValueByName(2);
  
  switch(type)
  {
    case Vertex::Circle:   switch(part1*10+part2)
                  {
                        case 0:  sep=getDistance(x1,y1,x2,y2);
                                 if((sep+r1)<r2 || (sep+r2)<r1) return false;
                                 else return(getDistance(x1,y1,x2,y2)<=(r1+r2));
                                 break;
                        case 3:
                        case 10:
                        case 30: return true;
                                 break;
                  }
                  break;
    case Vertex::Arc:   switch(part1*10+part2)
                  {
                        case 0:  theInters.append(Vert1);
                                 theInters.append(Vert2);
                                 getIntersectionCircleCircle(theInters, x1, y1, r1, x2, y2, r2);
                                 if(theInters.retrieve(1).returnType()==Vertex::Cluster)  return false;
                                 out1=isValidPointIncidence(theInters.retrieve(1), theOther,1,0);
                                 out2=isValidPointIncidence(theInters.retrieve(2), theOther,1,0);
                                 return(out1 || out2);
                                 break;
                        case 30: Vert1.setType(Vertex::Point);
                                 Vert1.setValues(0,x1);
                                 Vert1.setValues(1,y1);
                                 return(isValidPointIncidence(Vert1,theOther,1,0));
                                 break;
                        case 1:
                        case 2:
                        case 3:
                        case 31:
                        case 32:
                        case 33: return true;
                                 break;
                  }
        default:  return true;
  }
  return false;
}

//! given an arc and another object, returns true if the object is incident on the arc
bool isValidArcIncidence(Vertex &theArc, Vertex &theOther, int part1, int part2)
{
  float x1, y1, r1, x2, y2, x3, y3, r2, sep;
  Vertex theInter, Vert1, Vert2;
  List<Vertex> theInters;
  bool out1, out2;

  x1=theArc.returnDegValueByName(0);
  y1=theArc.returnDegValueByName(1);
  r1=theArc.returnDegValueByName(2);  
  x2=theOther.returnDegValueByName(0);
  y2=theOther.returnDegValueByName(1);
  r2=theOther.returnDegValueByName(2);
  
  switch(part1*10+part2)
  {
        case 0:  sep=getDistance(x1,y1,x2,y2);
                 if((sep+r1)<r2 || (sep+r2)<r1) return false;
                 if(sep>(r1+r2)) return false;
                 theInters.append(Vert1);
                 theInters.append(Vert2);
                 getIntersectionCircleCircle(theInters, x1, y1, r1, x2, y2, r2);
                 if(theInters.retrieve(1).returnType()==-1)  return false;
                 out1=isValidPointIncidence(theInters.retrieve(1), theOther,1,0);
                 out1=out1 && isValidPointIncidence(theInters.retrieve(1), theArc,1,0);
                 out2=isValidPointIncidence(theInters.retrieve(2), theOther,1,0);
                 out2=out2 && isValidPointIncidence(theInters.retrieve(2), theArc,1,0);
                 return(out1 || out2);
                 break;
        case 1:  x3=x2+r2*theOther.returnDegValueByName(4);
                 y3=y2+r2*theOther.returnDegValueByName(5);
                 Vert1.setType(Vertex::Point);
                 Vert1.setValues(0,x3);
                 Vert1.setValues(1,y3);
                 return(isValidPointIncidence(Vert1,theArc,1,0));
                 break;
        case 2:  x3=x2+r2*theOther.returnDegValueByName(6);
                 y3=y2+r2*theOther.returnDegValueByName(7);
                 Vert1.setType(Vertex::Point);
                 Vert1.setValues(0,x3);
                 Vert1.setValues(1,y3);
                 return(isValidPointIncidence(Vert1,theArc,1,0));
                 break;
        case 3:  Vert1.setType(Vertex::Point);
                 Vert1.setValues(0,x2);
                 Vert1.setValues(1,y2);
                 return(isValidPointIncidence(Vert1,theArc,1,0));
                 break;
        case 10: x3=x1+r1*theOther.returnDegValueByName(4);
                 y3=y1+r1*theOther.returnDegValueByName(5);
                 Vert1.setType(Vertex::Point);
                 Vert1.setValues(0,x3);
                 Vert1.setValues(1,y3);
                 return(isValidPointIncidence(Vert1,theOther,1,0));
                 break;
        case 20: x3=x1+r1*theOther.returnDegValueByName(6);
                 y3=y1+r1*theOther.returnDegValueByName(7);
                 Vert1.setType(Vertex::Point);
                 Vert1.setValues(0,x3);
                 Vert1.setValues(1,y3);
                 return(isValidPointIncidence(Vert1,theOther,1,0));
                 break;
        case 30: Vert1.setType(Vertex::Point);
                 Vert1.setValues(0,x1);
                 Vert1.setValues(1,y1);
                 return(isValidPointIncidence(Vert1,theOther,1,0));
                 break;
        case 11:
        case 12:
        case 13:
        case 21:
        case 22:
        case 23:
        case 31:
        case 32:
        case 33: return true;
                 break;
  }
  return false;
}

//!  given the edge, if it is not imaginary returns true (if the constraint
//!  is not imaginary if must be satisfied after solution, otherwise the 
//!  method calls the correct isValidIncidence method from above and returns 
//!  true only if the incidence is met with the current values
bool isValidConstraint(Graph &graph0, Edge &theEdge, Cluster &theCluster)
{
  Vertex end1, end2;
  int v1, v2, part1, part2;
  Vertex::Type type1, type2;

  v1=theEdge.returnEnd1();
  v2=theEdge.returnEnd2();

  part1=theEdge.returnPart1();
  part2=theEdge.returnPart2();
  
  end1=graph0.returnVertByName(v1);
  end2=graph0.returnVertByName(v2);

  type1=end1.returnType();
  type2=end2.returnType();

  if(!isImaginary(graph0, theEdge)) return true;

  if (type1 == Vertex::Point and
      (type2 == Vertex::Point or type2 == Vertex::Line or 
       type2 == Vertex::Ray or type2 == Vertex::LineSeg or
       type2 == Vertex::Circle or type2 == Vertex::Arc))
    {
      return(isValidPointIncidence(end1,end2,part1,part2));
    }
  else if (type2 == Vertex::Point and
           (type1 == Vertex::Point or type1 == Vertex::Line or 
            type1 == Vertex::Ray or type1 == Vertex::LineSeg or
            type1 == Vertex::Circle or type1 == Vertex::Arc))
    {
      return(isValidPointIncidence(end2,end1,part2,part1));
    }
  else if (type1 == Vertex::Line and
           (type2 == Vertex::Line or 
            type2 == Vertex::Ray or type2 == Vertex::LineSeg or
            type2 == Vertex::Circle or type2 == Vertex::Arc))
    {
      return(isValidLineIncidence(end1,end2,part1,part2));
    }
  else if (type2 == Vertex::Line and
           (type1 == Vertex::Ray or type1 == Vertex::LineSeg or
            type1 == Vertex::Circle or type1 == Vertex::Arc))
    {
      return(isValidLineIncidence(end2,end1,part2,part1));
    }
  else if (type1 == Vertex::Ray and
           (type2 == Vertex::Ray or type2 == Vertex::LineSeg or
            type2 == Vertex::Circle or type2 == Vertex::Arc))
    {
      return(isValidRayIncidence(end1,end2,part1,part2));
    }
  else if (type2 == Vertex::Ray and
           (type1 == Vertex::LineSeg or
            type1 == Vertex::Circle or type1 == Vertex::Arc))
    {
      return(isValidRayIncidence(end2,end1,part2,part1));
    }
  else if (type1 == Vertex::LineSeg and
           (type2 == Vertex::LineSeg or
            type2 == Vertex::Circle or type2 == Vertex::Arc))
    {
      return(isValidLSIncidence(end1,end2,part1,part2));
    }
  else if (type2 == Vertex::LineSeg and
           (type1 == Vertex::Circle or type1 == Vertex::Arc))
    {
      return(isValidLSIncidence(end2,end1,part2,part1));
    }
  else if (type1 == Vertex::Circle and
           (type2 == Vertex::Circle or type2 == Vertex::Arc))
    {
      return(isValidCircleIncidence(end1,end2,part1,part2));
    }
  else if (type1 == Vertex::Arc and type2 == Vertex::Circle)
    {
      return(isValidCircleIncidence(end2,end1,part2,part1));
    }
  else if (type1 == Vertex::Arc and type2 == Vertex::Arc)
    {
      return(isValidArcIncidence(end1,end2,part1,part2));
    }
  else
    {
      return false;
    }
}


//! THIS METHOD HAS BEEN OUTDATED BY THE USE OF THE JAVA NATIVE INTERFACE
//! prints the graph data into a text file in a format that can be read by the sketcher
//! when printNum is true the ID of theCluster is printed first
void generateOutput(Graph &graph0, Cluster &theCluster, std::ostream &outfile, bool printNum)
{
   int i, length;
   Vertex currVert;
   float angle1;
   float x,y,tempValue, tempValue2;

   if(printNum) outfile<<theCluster.returnOrigLen()<<std::endl;
   length=graph0.returnNumVer();
   for(i=1;i<=length;i++)
   {

      currVert=graph0.returnVertByIndex(i);
      if(inOriginalV(currVert.returnName(),theCluster))
      {
        outfile<<currVert.returnName()<<std::endl;
        x=currVert.returnDegValueByName(0);
        y=currVert.returnDegValueByName(1);
        outfile<<x<<std::endl;
        outfile<<y<<std::endl;
        switch(currVert.returnType())
        {
          case Vertex::Point:   break;
          case Vertex::Line:   tempValue=currVert.returnDegValueByName(4);
                        outfile<<x+1<<std::endl;
			outfile<<y+tempValue<<std::endl;
                        break;
          case Vertex::Ray:   tempValue=currVert.returnDegValueByName(4);
			tempValue2=currVert.returnDegValueByName(5);
                        outfile<<x+tempValue<<std::endl;
			outfile<<y+tempValue2<<std::endl;
                        break;
          case Vertex::LineSeg:   outfile<<currVert.returnDegValueByName(2)<<std::endl;
                        outfile<<currVert.returnDegValueByName(3)<<std::endl;
                        break;
          case Vertex::Circle:   tempValue=currVert.returnDegValueByName(2);
 			if(tempValue<0) tempValue=-tempValue;
                        outfile<<tempValue<<std::endl;
                        break;
          case Vertex::Arc:   angle1=getAngle(currVert.returnDegValueByName(4),currVert.returnDegValueByName(5));
                        angle1=getAngle(currVert.returnDegValueByName(6),currVert.returnDegValueByName(7));
                        outfile<<currVert.returnDegValueByName(2)<<std::endl;
                        outfile<<currVert.returnDegValueByName(3)<<std::endl;
                        outfile<<angle1<<std::endl;
                        break;
          case Vertex::NoClue:
          case Vertex::Cluster: 
          case Vertex::Point3D: break;
        }
      }
   }
}

//! Same as above but places the output values in the transfer arrays, inputInts and 
//! inputFloats.  The format is as follows, if printnum, the ID of theCluster is output,
//! otherwise nothing.  Then for every original vertex in theCluster, the ID is printed,
//! then the following information, for every point the x then y coordinate, followed by
//! information depending on the type of the object:
//!
//!    points - nothing
//!    lines - second point on line
//!    rays - second point on ray
//!    line segment - second endpoint
//!    circle - radius
//!    arc - points of the start and end of the arc, x coordinates first
//!    point3D - z coord
//!
void 
generateOutputToArray (Graph &graph0, Cluster &theCluster, bool printNum,
                       float *inputFloats, int currPosF, int *inputInts, 
                       int currPosI)
{   
   int i, length;
   Vertex currVert;   
   float angle1, angle2;
   float x,y,tempValue, tempValue2,x2,y2;
   
   std::cout << graph0 << std::endl;

   int memPos=currPosI;
   int outCount=0;

   if(printNum) currPosI++;

   std::cout<<"Memory location of count="<<memPos<<std::endl;
   
//   if(printNum) inputInts[currPosI++]=theCluster.returnOrigLen();
   length=graph0.returnNumVer();
   for(i=1;i<=length;i++)
   {
    
      currVert=graph0.returnVertByIndex(i);
      if(currVert.returnIgnore())
 	std::cout<<"Ignore=true for vertex="<<currVert.returnName()<<std::endl;
      else std::cout<<"Ignore=false for vertex="<<currVert.returnName()<<std::endl;

      if(currVert.returnIgnore()) continue;
      if(inOriginalV(currVert.returnName(),theCluster))
      {
	outCount++;
        inputInts[currPosI++]=currVert.returnName();
        x=currVert.returnDegValueByName(0);
        y=currVert.returnDegValueByName(1);
	std::cout<<"Name: "<<currVert.returnName();
        inputFloats[currPosF++]=x;
        inputFloats[currPosF++]=y;
	std::cout<<", x="<<x;
	std::cout<<", y="<<y;
        switch(currVert.returnType())
        {
          case Vertex::Point:   break;
          case Vertex::Line:   tempValue=currVert.returnDegValueByName(4);
			x2=inputFloats[currPosF++]=x+1;
                        y2=inputFloats[currPosF++]=y+tempValue;
			std::cout<<", x2="<<x2;
			std::cout<<", y2="<<y2;
                        break;
          case Vertex::Ray:   tempValue=currVert.returnDegValueByName(4);
                        tempValue2=currVert.returnDegValueByName(5);
                        inputFloats[currPosF++]=x+tempValue;
                        inputFloats[currPosF++]=y+tempValue2;
                        break;
          case Vertex::LineSeg:   inputFloats[currPosF++]=currVert.returnDegValueByName(2);
                        inputFloats[currPosF++]=currVert.returnDegValueByName(3);
                        break;
          case Vertex::Circle:   tempValue=currVert.returnDegValueByName(2);
                        if(tempValue<0) tempValue=-tempValue;
                        inputFloats[currPosF++]=tempValue;
                        break;
          case Vertex::Arc:   angle1=getAngle(currVert.returnDegValueByName(4),currVert.returnDegValueByName(5));
                        angle2=getAngle(currVert.returnDegValueByName(6),currVert.returnDegValueByName(7));
                        inputFloats[currPosF++]=currVert.returnDegValueByName(2);
                        inputFloats[currPosF++]=currVert.returnDegValueByName(3);
	                inputFloats[currPosF++]=angle1;
                        inputFloats[currPosF++]=angle2;
                        break;
          case Vertex::Point3D:   inputFloats[currPosF++]=currVert.returnDegValueByName(2);
                        break; 
          case Vertex::Cluster: 
          case Vertex::NoClue: break;

        }
	std::cout<<std::endl;
      }  
   }

   std::cout<<"Count of bifurcations sent="<<outCount<<std::endl;

   if(printNum) inputInts[memPos]=outCount;
}


//! shells to maple and calls the solver
void shellMaple()
{
    std::string outputString;

    outputString="maple <input.txt> output.txt";
    remove("output.txt");
    system(outputString.c_str());   
}

/*
//shells to maple and calls the solver
void shellMaple()
{ 
    std::ofstream output;
    std::string outputString;
    
    output.open("startup.m");
    output<<"xStart=zeros("+toString(vars.returnLen())+",1);\n";
    output<<"fun=@dplanFun;\nx=fsolve(fun, xStart);\nsave data.out xStart -ascii;\nquit;";
    output.close();

    outputString="matlab -nojvm -nosplash";
    //remove("output.txt");
    system(outputString.c_str());
}
*/

//! checks that a given bifurcation string is valid by checking that it contains
//! only the valid characters below
bool validBifur(std::string theString)
{
    int i, length;
    bool output;

    output=true;

    length=theString.size();

    for(i=0;i<length;i++)
    {
       switch(theString[i])
       {
             case '0':
             case '1':
             case '2':
             case '3':
             case '4':
             case '5':
             case '6':
             case '7':
             case '8':
             case '9':
             case 'q':
             case 'p':
             case 's':
             case 't':
             case 'x':
             case 'y':
             case 'r':
             case 'm':
             case 'a':
             case 'b':
             case 'c':
             case 'd':
             case 'w':
             case 'v':
             case '.':
             case '=':
             case ',':
             case 'e':
	     case 'l':
	     case 'g':
             case 'f':
             case 'h':
             case 'j':
             case 'k':
             case 'n':
	     case 'z':
             case '-':  break;
             default:   output=false;
                        break;
       }
    }
    return output;
}

bool 
isIdentical (Graph &graph0, Cluster &theCluster, List<int> &overlappedList, 
             int ID, float p, float q, float s, float t, float f, float h, 
             float j, float k, float n, int withHeldCluster)
{
	int vName, clustint1, clustint2;
	Cluster tempCluster1, tempCluster2;
	Vertex tempVertex1, tempVertex2;
	float x1, y1, z1, x2, y2, z2, xold, yold, zold;
	
	int dimen = graph0.returnDimen();
	//don't check 3D
	if(graph0.returnDimen() ==3 ) return true;

	std::ofstream outf;
//	outf.open("isIdentical.out", std::ios::app);
	outf << "The cluster is: " << std::endl;
	outf << theCluster << std::endl;
	outf<< "  s: " << s << "  t: " << t  << "  p: " << p  << "  q: " << q << std::endl; 
	
	for(int i=1; i<=overlappedList.returnLen(); i++)
	{
		List<int> tempList;
		vName = overlappedList.retrieve(i);
		outf << " we are checking: " << vName << std::endl;
		
		getContainedChildList(theCluster, vName, tempList);
		if(tempList.returnLen()>2) continue;
		
		clustint1 = tempList.retrieve(1);
		clustint2 = tempList.retrieve(2);
		tempCluster1=theCluster.children.retrieve(getChildIndexByName(theCluster, clustint1));
		tempCluster2=theCluster.children.retrieve(getChildIndexByName(theCluster, clustint2));
		tempVertex1.setName(vName);
		tempVertex2.setName(vName);
		setValueInCluster(graph0, tempCluster1, tempVertex1);
		setValueInCluster(graph0, tempCluster2, tempVertex2);
		
		outf << "withHeldCluster: " << withHeldCluster << std::endl;
		outf << "clustint1: " << clustint1 << "    clustint2: " << clustint2 << std::endl;
		outf << "values of vertex1:"<< std::endl;
		outf << tempVertex1.returnDegValueByName(0) << std::endl;
		outf << tempVertex1.returnDegValueByName(1) << std::endl;
		outf << tempVertex1.returnDegValueByName(2) << std::endl;
		outf << "values of vertex2:"<< std::endl;
		outf << tempVertex2.returnDegValueByName(0) << std::endl;
		outf << tempVertex2.returnDegValueByName(1) << std::endl;
		outf << tempVertex2.returnDegValueByName(2) << std::endl;
		
		if(clustint1==withHeldCluster)
		{
			x1 = tempVertex1.returnDegValueByName(0);
			y1 = tempVertex1.returnDegValueByName(1);
			z1 = tempVertex1.returnDegValueByName(2);
			xold = tempVertex2.returnDegValueByName(0);
			yold = tempVertex2.returnDegValueByName(1);
			zold = tempVertex2.returnDegValueByName(2);
			if(dimen==2)
			{
				x2 = xold*t - yold*s + p;
				y2 = xold*s + yold*t + q;
			}
			else if(dimen==3)
			{
              			x2 = (xold*h*k)-(yold*h*n)+(zold*j)+p;
              			y2 = (xold*(s*j*k+t*n))+(yold*(t*k-s*j*n))-(zold*s*h)+q;
              			z2 = (xold*(s*n-t*j*k))+(yold*(s*k+t*j*n))+(zold*t*h)+f;
              		}
		}
		else
		{
			x2 = tempVertex2.returnDegValueByName(0);
			y2 = tempVertex2.returnDegValueByName(1);
			z2 = tempVertex2.returnDegValueByName(2);
			xold = tempVertex1.returnDegValueByName(0);
			yold = tempVertex1.returnDegValueByName(1);
			zold = tempVertex1.returnDegValueByName(2);
			if(dimen==2)
			{
				x1 = xold*t - yold*s + p;
				y1 = xold*s + yold*t + q;
			}
			else if(dimen==3)
			{
              			x1 = (xold*h*k)-(yold*h*n)+(zold*j)+p;
              			y1 = (xold*(s*j*k+t*n))+(yold*(t*k-s*j*n))-(zold*s*h)+q;
              			z1 = (xold*(s*n-t*j*k))+(yold*(s*k+t*j*n))+(zold*t*h)+f;
              		}
		}
		if(fabs(x1-x2)>1e-5) return false;
		if(fabs(y1-y2)>1e-5) return false;
		if(dimen==3 && fabs(z1-z2)>1e-5) return false;
	}//check each vertex
	return true;
}

//! check the bifurcations in the output.txt and delete the wrong ones
//! current method only works for the cluster with 2 children
int 
verifyBifurs (Graph graph0, Cluster theCluster, List<std::string> &theList, 
              int withHeldCluster)
{
	if(graph0.returnDimen()==3) return 1;
	if(theList.returnLen()<2) return 1;
	if(theCluster.children.returnLen()>2) return 1;

	List<int> overlappedList;
	getOverlapList(graph0, theCluster, overlappedList, 1, 2);
	
	if(overlappedList.returnLen()==0) return 1;
	std::ofstream outf;
//	outf.open("verifyBifurs.out", std::ios::app);
	outf << "The BEGINNING " << std::endl << " The cluster is: " << std::endl;
	outf << theCluster << std::endl;

	outf<< "the bifurs of the cluster are: " << std::endl;
	printBifurcations(theCluster, outf);
	outf << "finish printBifurs" << std::endl;	
	
	int length, inputLength;
	int pos=0, ID;
	float value, p, q, s, t, f, h, j, k, n;
	char varID, temp;
	std::string currParse, IDString, input;

	//parse the bifurcation
	for(int jj=1; jj<=theList.returnLen(); jj++)
	{
		input=theList.retrieve(jj);
		
		outf << "The input is: " << input << std::endl;
		length=0;
		pos = 0;
		inputLength=input.size();
		for(int i=0; i<inputLength; i++)
			if(input[i]=='=') length++;
		temp=input[pos];
		for(int i=0; i<length; i++)
		{
			currParse="";
			while(temp!=',' && pos<inputLength)
			{
				currParse=currParse+temp;
				pos++;
				temp=input[pos];
			}
			IDString="";
			if(currParse[currParse.size()-1]=='.') currParse.erase(currParse.size()-1);
			varID=currParse[0];
			currParse.erase(0,1);
			while(currParse[0]!='=')
			{
				IDString+=currParse[0];
				currParse.erase(0,1);
			}
			currParse.erase(0,1);
			value=atof(currParse.c_str());
			outf << "value is: " << value << std::endl;
			if(fabs(value)<1e-5) value=0;
			ID=atoi(IDString.c_str());
			setValue(theCluster,ID,value,getFreeDegIndex(varID,graph0.returnVertByName(ID)));
			outf << "after setValue" << std::endl;
			switch(varID) 
			{
				case 'p': p=value;
					break;
				case 'q': q=value;
					break;
				case 's': s=value;
					break;
				case 't': t=value;
					break;
				case 'f': f=value;
					break;
				case 'h': h=value;
					break;
				case 'j': j=value;
					break;
				case 'k': k=value;
					break;
				case 'n': n=value;
					break;
				default:
					return 1;
			}//switch varID

			pos++;
			if(pos<inputLength) temp=input[pos];
		}//for each equation
		//the bifurcation is wrong, remove it
		outf << "Before isIdentical" << std::endl;
		if(!isIdentical(graph0, theCluster, overlappedList, ID, p, q, s, t, f, h, j, k, n, withHeldCluster))
		{	
			theList.deleteIndex(jj);
			jj = 1;
		}	
		outf << "after one cycle, jj is	" << jj << std::endl;
	}//for each bifurc<< std::endl;utf << "The END" << std::endl;
  return 0; //??
}

//! reads the bifurcations from filename and sets them in theCluster, fsolve is used to
//! differentiate the two different cases.  When true the data is read as if the output comes
//! Maple's numeric solver, otherwise as if the symbolic solver was used.
void setBifurs(std::string filename, Graph graph0, Cluster& theCluster, bool usingfSolve)
{
    std::ifstream infile;
    int caretCount=0;
    std::string output="";
    char in;
    int tag=0;
    std::string temp;
    List<std::string> theList;

    theList.makeEmpty();

    infile.open(filename.c_str());

    if(usingfSolve)
    {
      while(caretCount!=3)
      {
            if(infile.get()=='>') caretCount++;
            if(infile.eof()) return;
      }
      while(infile.get()!=';') if(infile.eof()) return;
      
      infile>>in;
      while(in!='{')
      {
        if(infile.eof()) return;
        if(in=='f') return;
        infile>>in;
      }

      infile>>in;  
      while(tag==0)
      {
         while(in!='}')
         {
             temp="";  
             temp+=in; 
             temp+=" ";
             if(temp!="\\ ") output+=in;
             infile>>in;
             if(infile.eof()) return;
         }
         if(validBifur(output)) theList.append(output);
         output="";
         while(in!='{' && in!='q')
         {
             infile>>in;
             if(infile.eof()) return;
         }
         if(in=='q') tag=1;
         if(in=='{') infile>>in;
      }
      infile.close();
      //verifyBifurs(graph0, theCluster, theList);
      theCluster.setBifurs(theList);
      return;      
    }

    while(caretCount!=2)
    {
          if(infile.get()=='%') caretCount++;
          if(infile.eof()) return;
    }

    while(infile.get()!='{') if(infile.eof()) return;

    infile>>in;
    while(tag==0)
    {
       while(in!='}')
       {   
           temp="";
           temp+=in;
           temp+=" ";
           if(temp!="\\ ") output+=in;
           infile>>in;
	   if(infile.eof()) return;
       }
       if(validBifur(output)) theList.append(output);
       if(theList.returnLen()==5) break;
       output="";
       while(in!='{' && in!='q')
       {
           infile>>in;
           if(infile.eof()) return;
       }
       if(in=='q') tag=1;
       if(in=='{') infile>>in;
    }

    infile.close();
      //verifyBifurs(graph0, theCluster, theList);
      theCluster.setBifurs(theList);
}	
	
	
//! sets the degrees of freedom in theCluster to the values stored in the given
//! bifurcation string
void parseBifurString(Graph &graph0, Cluster &theCluster)
{
    int i, length, inputLength;
    int pos=0, ID;
    float value;
    char varID, temp;
    std::string currParse, IDString, input; 

    input=theCluster.returnCurrBifurString();
    length=0;
    inputLength=input.size();
    for(i=0; i<inputLength; i++)
       if(input[i]=='=') length++;
    temp=input[pos];
    for(i=0; i<length; i++)
    {
       currParse="";
       while(temp!=',' && pos<inputLength)
       {
          currParse=currParse+temp;
          pos++;
          temp=input[pos];
       }
       IDString="";
       if(currParse[currParse.size()-1]=='.') currParse.erase(currParse.size()-1);
       varID=currParse[0];
       currParse.erase(0,1);
       while(currParse[0]!='=')
       {
          IDString+=currParse[0];
          currParse.erase(0,1);
       }
       currParse.erase(0,1);
       value=atof(currParse.c_str());
       if(fabs(value)<1e-5) value=0;
       ID=atoi(IDString.c_str());
       setValue(theCluster,ID,value,getFreeDegIndex(varID,graph0.returnVertByName(ID)));
       pos++;
       if(pos<inputLength) temp=input[pos];
    }
}


//! NO LONGER USED SINCE THE IMPLEMENTATION OF THE JAVA NATIVE INTERFACE
//! outputs the DRDAG to a file
void outputDRDAG(List<Cluster> &theCluster, std::ostream &output, bool first)
{
    int j, length, lengthOrig, lengthChild;

    length=theCluster.returnLen();
    
    if(first)
    {
      output<<-2<<std::endl;
      output<<length<<std::endl;
    }

    for(int i=1;i<=length;i++)
    {
       output<<theCluster.retrieve(i).returnName()<<std::endl;
       lengthOrig=theCluster.retrieve(i).returnOrigLen();
       output<<lengthOrig<<std::endl;
       for(j=1;j<=lengthOrig;j++)
          output<<theCluster.retrieve(i).returnOrigV(j)<<std::endl;
       lengthChild=theCluster.retrieve(i).children.returnLen();
       output<<lengthChild<<std::endl;
       for(j=1;j<=lengthChild;j++)
	  output<<theCluster.retrieve(i).children.retrieve(j).returnName()<<std::endl;
       outputDRDAG(theCluster.retrieve(i).children,output,false);
    }
    if(first) output<<-1<<std::endl;
}

//! Ouputs the DRDag to an array, the following format is used:
//!
//! \li -2			-- signal to sketcher that the DRDag is coming
//! \li \<number of trees in the DAG\>
//!
//! then recursively, each node before its children the following is output:
//!
//! \li \<cluster ID\>
//! \li \<number of original vertices\>
//! \li \<list of original vertices\>
//! \li \<number of children\>
//! \li \<list of children\>
//! 
//! (Note that all values are always printed even if they are 0);
void outputDRDAGToArray(List<Cluster> &theCluster, int &index, int*& theInts, bool first)
{
    int j, length, lengthOrig, lengthChild, overConst;

    length=theCluster.returnLen();

    if(first)
    {
       theInts[index++]=-2;
       theInts[index++]=length;
    }

    for(int i=1;i<=length;i++)
    {
       theInts[index++]=theCluster.retrieve(i).returnName();
       if(theCluster.retrieve(i).returnType()>0 || theCluster.retrieve(i).returnConst()>1)
	  	overConst=1;
       else	overConst=0;
       theInts[index++]=overConst;
       lengthOrig=theCluster.retrieve(i).returnOrigLen();
       theInts[index++]=lengthOrig;
       for(j=1;j<=lengthOrig;j++)
          theInts[index++]=theCluster.retrieve(i).returnOrigV(j);
       lengthChild=theCluster.retrieve(i).children.returnLen();
       theInts[index++]=lengthChild;
       for(j=1;j<=lengthChild;j++)
          theInts[index++]=theCluster.retrieve(i).children.retrieve(j).returnName();
       outputDRDAGToArray(theCluster.retrieve(i).children, index, theInts, false);
    }
    if(first) theInts[index]=-1;
}

//! outputs the fin state of every cluster.  Fin flags are used to tell the solver which 
//! clusters have and have not been solved.  This method visits each node in the tree, and
//! at each visit outputs the clusters name, then fin start 0 for solved, 1 for not solved,
//! before recursively continuing for each of its children
void outputFinState(Cluster &theCluster, int &startI, int*& theInts, int &count)
{
    int i, length;

    count++;
    theInts[startI++]=theCluster.returnName();
    if(theCluster.isSolved()) theInts[startI++]=0;
    else theInts[startI++]=1;

    length=theCluster.children.returnLen();
    for(i=1;i<=length;i++)
       outputFinState(theCluster.children.retrieve(i), startI, theInts, count);
}

//! sets the children of theCluster to the next distinct set of bifurcations
bool getNextBifurcation(Graph &graph0, Cluster &theCluster)
{
    int i, childLength=theCluster.children.returnLen();

    if(theCluster.children.retrieve(1).returnCurrBifur()==-1)
    {
      for(i=1;i<=childLength;i++)
      {
         theCluster.children.retrieve(i).setCurrBifur(1);
         parseBifurString(graph0, theCluster.children.retrieve(i));
         updateGraph(graph0, theCluster.children.retrieve(i));
      }	     
      return(true);
    }

    int numBifur, currBifur;

    for(i=1;i<=childLength;i++)
    {
       numBifur=theCluster.children.retrieve(i).returnNumBifurs();
       currBifur=theCluster.children.retrieve(i).returnCurrBifur();
       if(numBifur==currBifur)
       {
         theCluster.children.retrieve(i).setCurrBifur(1);
         parseBifurString(graph0, theCluster.children.retrieve(i));
         updateGraph(graph0, theCluster.children.retrieve(i));
         continue;
       }
       theCluster.children.retrieve(i).setCurrBifur(currBifur+1);
       parseBifurString(graph0, theCluster.children.retrieve(i));
       updateGraph(graph0, theCluster.children.retrieve(i));
       return(true);
    }
    return(false);
}

//! Chooses the bifurcation for theCluster.  Two automatic methods are used first:
//! if there is only one bifurcation it is selected.
//! if the cluster contains only original vertices and the bifurcation only adjusts reflections
//!   in space, the first bifurcation is chosen.
//! In any other case, the method outputs the information about the clusters to the sketcher
//! which queries the user for the correct bifurcation.  The format for this output is:
//! <ID of the cluster whose bifurcations are being chosen>
//! <number of bifurcations>
//! for each bifurcation:
//! <output of the generateOutput method above called with theCluster set to the
//! correct bifur.>
int 
selectBifurcation (Graph &graph0, Cluster &theCluster, bool &useFile, 
                   float *inputFloats, int currPosF, int *inputInts, int currPosI)
{
    int i, answer=-1;
    int numBifurs=theCluster.returnNumBifurs();
    std::string answerString, bifurString;
    std::ofstream outfile;
    std::ifstream infile;
    bool validToSkip=true;

	std::ofstream outf;
//	outf.open("selectBifucation.out", std::ios::app);
	outf << "The beginning+++++++++++++++++" << std::endl;
	outf << "The cluster is: " << std::endl;
	outf << theCluster << std::endl;

    useFile=false;

    if(numBifurs==1) return 1;
    if(numBifurs==0) return 0;

    int childLength=0, totalSingle=0;

    childLength=theCluster.children.returnLen();

    bifurString=theCluster.returnCurrBifurString();
	outf << "The bifurstring is: " << bifurString << std::endl;

    if(strchr(bifurString.c_str(),'r')!=NULL) validToSkip=false;
//    if(strchr(bifurString.c_str(),'m')!=NULL) validToSkip=false;

    int type2count=0;

    for(i=1;i<=childLength;i++)
    {
       if(theCluster.children.retrieve(i).returnOrigLen()>1) totalSingle++;
       if(theCluster.children.retrieve(i).returnType()==2) type2count++;
    }

	outf << "type2count = " << type2count << " and totalSingle = " << totalSingle << std::endl;
    if(type2count==childLength) return 1;
    if(totalSingle==0 && validToSkip) return 1;

    useFile=true;
   
    int temp=currPosI;
 
    inputInts[currPosI++]=theCluster.returnName();
    inputInts[currPosI++]=numBifurs;
    for(i=1;i<=numBifurs;i++)   
    {  
       theCluster.setCurrBifur(i);
       parseBifurString(graph0, theCluster);
       updateGraph(graph0, theCluster);
       generateOutputToArray(graph0, theCluster, i==1, inputFloats, currPosF, 
                             inputInts, currPosI);
    }

    outf <<"Values sent to sketcher"<<std::endl;

    for(i=temp;i<currPosI;i++)
     	outf <<inputInts[i]<<std::endl;

    theCluster.setCurrBifur(-1);
    return (answer);

/*  REMOVE OLD SELECTION METHODS

    outfile.open("./Sketcher/testin.txt");
    outfile<<-1;
    outfile.close();

    outfile.open(outFile.c_str());

    if(first)
    {
       first=false;
       outfile<<-2<<std::endl;
       outfile<<roots.returnLen()<<std::endl;
       outputDRDAG(roots,outfile);
       outfile<<-1<<std::endl;
    }
    outfile<<theCluster.returnName()<<std::endl<<numBifurs<<std::endl;
    for(i=1;i<=numBifurs;i++)
    {
       theCluster.setCurrBifur(i);
       parseBifurString(graph0, theCluster);
       updateGraph(graph0, theCluster);
       generateOutput(graph0, theCluster, outfile, i==1);
    }
    outfile.close();

    while(answer<0)
    {
       infile.open("./Sketcher/testin.txt");
       infile>>answer;
       infile.close();
    }
    
    return answer+1; 

    answerString="";

    printBifurcations(theCluster);
    std::cout<<std::endl;

    while(answer<1 || answer>numBifurs)
    {
        if(tag==1) std::cout<<"   Incorrect selection, Please make another: ";
        if(tag==0) {std::cout<<"   Select a bifurcation to continue: "; tag=1; }
        std::cin>>answerString;
        answer=atoi(answerString.c_str());
    }
    std::cout<<std::endl;
    keys.append(answer);
    return (answer); 

END REMOVE OLD SELECTION METHODS */ 
 
}

//! chooses the largest child of theCluster and sets it to be withheld, meaning
//! when theCluster is reconciled, all of the other clusters will be rotated into
//! the coordinate system of this withheld cluster
void setWithHeldCluster(Cluster &theCluster, int withHeldCluster)
{
    int i, length=theCluster.children.returnLen();
    int temp=0;
    int currLen=0;
    int origLen;

    for(i=1;i<=length;i++)
    {
       origLen=theCluster.children.retrieve(i).returnOrigLen();
       if(origLen>1 && origLen>currLen)
       {
         temp=theCluster.children.retrieve(i).returnName();
         currLen=origLen;
       }
    }
    withHeldCluster=temp;
}

//! eliminates any clusters that do not satisfy all of the imaginary constraints
void checkBifurs(Graph &graph0, Cluster &theCluster, List<Edge> &theImags)
{
    int i,j,num,length;
    Edge temp;
    Vertex v1,v2;
    bool out;
    List<std::string> theList;

    num=theCluster.returnNumBifurs();
    length=theImags.returnLen();

    for(i=1;i<=num;i++)
    {
       out=true;
       theCluster.setCurrBifur(i);
       parseBifurString(graph0, theCluster);
       updateGraph(graph0, theCluster);
       for(j=1;j<=length;j++)
       {
          temp=theImags.retrieve(i);
          out=(out && isValidConstraint(graph0, temp, theCluster));
       }
       if(out) theList.append(theCluster.returnCurrBifurString());
    }
    theCluster.setBifurs(theList);
    theCluster.setCurrBifur(-1);
}





//! solves a given cluster
int
solveCluster (Graph &graph0, Cluster &theCluster, bool resolve, the_Tree &Tree,
              List<std::string>& vars, int equationCount, int withHeldCluster, 
              int aOverlap, int singleVertex, int nextVerName, int nextEdgeName,
              int glo_flag, int search_flag, float *inputFloats, int currPosF, 
              int *inputInts, int currPosI, int *bifurAnswers, 
              List<Cluster> *toSolverTrees, bool usedBifurs, 
              List<Cluster> &roots, bool first, bool autoSolve, 
              bool usingArrays, int treeFlag, int startF, int startI, 
              int graphDimen, Graph &gGraph1, char *inputChars, 
              std::string &varsToZero, List<Edge> &theImags)
{
  int i, length, childLength;
  std::string temp, equation, answerString, childString;
  int answer=0;
  int tag;
  char in;
  int totalBifur,currChild=1;
  bool useFileToBifur, useFileTotal;
  // stores an Edge so that it can be used for setting the origin
  Edge forOriginSet, forOriginSet2;    

  childLength=(theCluster.children).returnLen();

  std::ofstream outf;
  outf.open("solveCluster.out", std::ios::app);
  outf << "The Beginning:++++++++++++++++++++++++++++" << std::endl;
  outf << " Cluster is:"  << std::endl;
  outf << theCluster << std::endl;

  // if the cluster has no children or no original vertices it must be an 
  // original vertex end the recursion
  if(childLength==0 || theCluster.isSolved() || theCluster.returnType()==2)
    {
	    theCluster.setSolved(true);
	    outf << "The childLength = " << childLength << std::endl;
	    outf << "The cluster is solved? " << theCluster.isSolved();
	    outf << "The cluster type is: " << theCluster.returnType();
	    return 0;
    }

  //solver the children of this cluster and store the return value in tag
  tag=solveForest(graph0, theCluster.children, Tree, vars, equationCount, 
                  withHeldCluster, aOverlap, singleVertex, nextVerName, 
                  nextEdgeName, glo_flag, search_flag, inputFloats, currPosF, 
                  inputInts, currPosI, bifurAnswers, toSolverTrees, usedBifurs,
                  roots, first, autoSolve, usingArrays, treeFlag, startF, 
                  startI, graphDimen, gGraph1, inputChars, varsToZero, theImags);

  outf <<"Children Solved"<<std::endl;
 
  // if the return from the children is -2, then no solution is found, pass this
  // up the calling stack
  if(tag==-2) return(-2);

  // if resolve is false, no additional bifurcation options remain, a -1 tag for
  // no solution by additional solutions remain is invalid here pass value up 
  // calling stack
  if(!resolve && tag==-1) return(-1);

  // answer is set to three when a valid solution is found, otherwise this loop 
  // tries to find a solution with each different set of bifurcations of its 
  // children
  while (answer != 3)
    {
      useFileToBifur=true;
      useFileTotal=false;

	    //empty the lists of variables and imaginary constaints
      vars.makeEmpty();
      theImags.makeEmpty();
   
      outf <<"Solving Cluster "<<theCluster.returnName()<<"..."<<std::endl;
      answer=0;
      totalBifur=0;
      
	    //otput the current cluster to the screen
      print(graph0, theCluster.children);
	
	    outf << "The graph0 is:" << std::endl;
	    outf << graph0 << std::endl;
	    outf << "The Cluster is:" << std::endl;
	    outf << theCluster << std::endl;
	 
	    //count the total number of bifurcations availible to the children
      for(i=1;i<=childLength;i++)
        if(theCluster.children.retrieve(i).returnOrigLen()==0)
          totalBifur++;
 
      outf << "The totalBifur is: " << totalBifur << std::endl;
    
      outf <<"Bifurcations counted."<<std::endl;

      bool getNextB;

      // in the autosolve mode, select the next bifurcation combination with the
      // getNextBifur method, if no solution exists when immediate children are 
      // resolved, resolve their children
      if(autoSolve)
        {
          getNextB=getNextBifurcation(graph0,theCluster);
          print(graph0, theCluster.children);
          if(getNextB)
            while(currChild<=childLength 
                  && solveCluster(graph0,
                                  theCluster.children.retrieve(currChild), 
                                  true, Tree, vars, equationCount, 
                         withHeldCluster, aOverlap, singleVertex,
                         nextVerName, nextEdgeName, glo_flag,
                         search_flag, inputFloats, currPosF, inputInts, 
                         currPosI, bifurAnswers, toSolverTrees, usedBifurs,
                         roots, first, autoSolve, usingArrays, treeFlag, 
                         startF, startI, graphDimen, gGraph1, inputChars, 
                         varsToZero, theImags) == -1)
                 currChild++;
          if(currChild>childLength) return(-1); 
        }        
      // if not set in autosolve, and the bifurcation answers returned from the 
      // sketcher have not been placed
      else if(usedBifurs)
        {
          outf <<"Solver usedBifurs"<<std::endl;

		      //save the state of the DRDag and the graph
          saveState(graph0, toSolverTrees, inputInts, inputFloats, treeFlag, 
                    gGraph1);

          // output all of the bifurcation options of all of the children of 
          // this cluster into the transfer array
		      outf <<"Solver state saved"<<std::endl;
          inputInts[0]++;
          currPosI=inputInts[0]+2;
          currPosF=(int) inputFloats[0];
          inputInts[inputInts[0]-1]=0;               

		      int count=0, currPosBackUp=currPosI++;
		      int theNumTrees=toSolverTrees->returnLen();
          for(i=1;i<=theNumTrees;i++)
            outputFinState(toSolverTrees->retrieve(i), currPosI, inputInts, 
                           count);
		    
          inputInts[currPosBackUp]=count;

          for(i=1;i<=childLength;i++)
            {  
		          outf <<"Child processed: "<<i<<std::endl;
              selectBifurcation (graph0, theCluster.children.retrieve(i), 
                                 useFileToBifur, inputFloats, currPosF, 
                                 inputInts, currPosI);
              useFileTotal=(useFileTotal || useFileToBifur);
              if(useFileToBifur) 
                {
                  outf <<"useFileToBifur is true"<<std::endl;
                  inputInts[inputInts[0]-1]++;
                  continue;
                }
		          outf <<"useFileToBifur is false"<<std::endl;
              parseBifurString(graph0, theCluster.children.retrieve(i));
		          outf <<"Bifur parsed"<<std::endl;
			        outf <<  "In " << i << ", the current child cluster is: " 
                   << std::endl;
			        outf << theCluster.children.retrieve(i).returnName() << std::endl;
              updateGraph(graph0, theCluster.children.retrieve(i));
 		          outf <<"Graph updated"<<std::endl;
            }
          inputInts[inputInts[0]]=0;
          inputInts[inputInts[0]+1]=inputInts[inputInts[0]-1];

          outf <<"Ending Solver usedBifurs"<<std::endl;
        }
	    // if the bifurcations have not been placed yet set the children of this 
      // cluster to have those bifurcation values
	    else 
	      {
		      outf <<"Solver not usedBifur"<<std::endl;
		
	        tag=0;
		      for(i=1;i<=childLength;i++)
		        {
		      	  //if(theCluster.children.retrieve(i).returnCurrBifur()>=0) 
              //  continue;
		      	  if(theCluster.children.retrieve(i).children.returnLen()==0) 
                continue;
		      	  outf <<"Bifur Used: "<<bifurAnswers[tag]<<std::endl;
		      	  theCluster.children.retrieve(i).setCurrBifur(bifurAnswers[tag++]);
		      	  parseBifurString(graph0, theCluster.children.retrieve(i));
		      	  updateGraph(graph0, theCluster.children.retrieve(i));
		      	  usedBifurs=true;
		        }
	      }                   

      // useFileTotal is set if any of the children have bifurcations, meaning 
      // that output to the sketcher has been generated, and the method must be 
      // closed and control returned to the sketcher so that an answer to the 
      // bifurcations can be chosen
      if(useFileTotal) outf <<"Bifurs written, returning"<<std::endl;
      if(useFileTotal) return -2;

	    print(graph0,theCluster.children);	 

	    //name of input file generated for Maple
      temp="input.txt";
      aOverlap=0;
      equationCount=0;

	    //sets the global cluster pointer, withHeldCluster
      setWithHeldCluster(theCluster, withHeldCluster);
      outf <<"ABOUT TO SET REDUCTION"<<std::endl;

	    //reduction is only used when the cluste contains distance constraints
      bool useReduction=true;
      int theVName;
      length=graph0.returnNumVer();
      for(i=1;i<=length;i++)
        {
          outf <<useReduction<<" ";
          outf <<graph0.returnVertByIndex(i).returnType()<<std::endl;
          theVName=graph0.returnVertByIndex(i).returnName();
          if(getChildNameWithVertex(theCluster, theVName)!=theVName) continue;
          if(graph0.returnVertByIndex(i).returnType()!=0 && 
	        graph0.returnVertByIndex(i).returnType()!=6  ) useReduction=false;
        }
      
      if(useReduction) setValueReduction(graph0, theCluster);
      
      std::ofstream inputFile;

	    //delete the old input file
      remove(temp.c_str());

      outf <<"Input File opened"<<std::endl;   
      inputFile.open(temp.c_str());

	    std::string outputString;

      //generate equations
	    outputString=getEquation(graph0, theCluster, inputFile, Tree, vars, 
                               equationCount, withHeldCluster, aOverlap, 
                               singleVertex, nextVerName, nextEdgeName, 
                               glo_flag, search_flag, varsToZero, graphDimen);
	    
	    inputFile<<outputString<<std::endl;
	    inputFile.close();

	    //std::ofstream newInputFile;
	    outf << "Tree Flag in mfa9Solver.cpp: " << treeFlag << std::endl;
	    if (treeFlag==1)
	      {
	        char confirm;
	        outf << "Would you like to supply the file containing modified "
               << "equations: (Y/N)? " ;
	        std::cout << "Would you like to supply the file containing modified "
                    << "equations: (Y/N)? " ;
	        std::cin >> confirm;
	        outf << std::endl;
	        if (confirm == 'y' || confirm =='Y')
	          {
		          outf << "Supply name of file : ";
		          std::string temp_buff;
		          std::cin >> temp_buff;
		          outf << std::endl;
		          inputFile.open(temp_buff.c_str());
              //as of now copy the same file
		          inputFile << outputString <<std::endl;  
		          inputFile.close();
	          }
	      }


	    // the output information restored and altered in case the numeric solver 
      // must be used
	    int semiCount=0;
      std::ifstream outTest;
      std::string stringInputData="";
      outTest.open(temp.c_str());
	    outTest>>in;
	    while(!outTest.eof() && in!=',') outTest>>in;
	      while(!outTest.eof() && semiCount<1)
          {
	          outTest>>in;
            if(in==';')
              {
			          stringInputData+=in;
                stringInputData+='\n';
                semiCount++;
	            }
	          else if(in=='=')
		          {	
                stringInputData+='\n';
			          stringInputData+=in;
		          }
		        else
      		    stringInputData+=in;
          }
      outTest.close();

	    //generated equations output to the screen         
      outTest.open(temp.c_str());
      outTest>>in;
      while(in!='{') outTest>>in;
      outTest>>in;
      while(in!='}')  
        { 
          if(in==',' || in==';') outf <<std::endl;
          else outf <<in;
          outTest>>in;
        }
      outf <<std::endl;
	    outf << "The Var string is: " <<getVarString(vars)<<std::endl;
      outTest.close();

	    outf <<"String input data"<<std::endl;

	    outf <<stringInputData<<std::endl;

      //maple shelled
      shellMaple();

      //postProcessMatlab();
      //bifurcation strings are read from output.txt, the maple output file

	    outf <<"After postprocesser"<<std::endl;

      setBifurs("output.txt", graph0, theCluster, false);

	    outf <<"After bifurcations set"<<std::endl;

 	    // if no solution is found with the symbolic solver, the number solver is 
      // tried
	    if(theCluster.returnNumBifurs()==0)
        {
          outf <<"Using Numeric Solver"<<std::endl;
          inputFile.open(temp.c_str());
          inputFile<<"interface(prettyprint=0);"<<std::endl;
          inputFile<<"timelimit(200,f";
          inputFile<<stringInputData;
          inputFile.close();
          shellMaple();
          setBifurs("output.txt", graph0, theCluster, true);
        }

	    //found bifurcations are printed
      printBifurcations(theCluster, outf);

	    outf <<"After printing bifurs, graph is:"<<std::endl;
	    outf << graph0 << std::endl;

      //bifurcations are checked to see if they meet the imaginary constraints
      checkBifurs(graph0, theCluster, theImags);
	    outf <<"After check bifurs, graph is:"<<std::endl;
	    outf << graph0 << std::endl;

	    //bifurcation choice is set to -1 -- none chosen yet
      theCluster.setCurrBifur(-1);

	    //if when autosolving no valid bifurcations are found, terminate
      if(theCluster.returnNumBifurs()==0 && !useFileTotal && !autoSolve) 
        {
	        std::string fName;

          int verCount;
	        int edgeCount;

	        verCount=graph0.returnNumVer();
	        edgeCount=graph0.returnNumEdg();

	        outf <<"Num Edges="<<edgeCount<<std::endl;

	        bool loadData=true;

	        switch(verCount)
	          {
/*

		case 6:	 fName="oct.dat";
			 outf <<"octPlat Loaded"<<std::endl;
			 break;
		case 8:  fName="sqr.dat";
			 outf <<"squarePlat Loaded"<<std::endl;
			 break;
		case 10: fName="pen.dat";
			 outf <<"pentPlat Loaded"<<std::endl;
			 break;
*/

		          default: loadData=false;
			                 break;
	          }

	        //used a canned answer file	
	        if(loadData)
	          {
	            std::ifstream theData;
		
    	        theData.open(fName.c_str());

              saveState(graph0, toSolverTrees, inputInts, inputFloats, 
                        treeFlag, gGraph1);
		
              currPosI=inputInts[0];
              currPosF=(int) inputFloats[0];
		
              int inputNum;

	            theData>>inputNum;
	            while(inputNum!=-1)
	              {
	                inputInts[currPosI++]=inputNum;
	  	            theData>>inputNum;
	              }
		
	            int countFloat, i;
	            float inputFlt;

	            theData>>countFloat;
		
	            for(i=0;i<countFloat;i++)
	              {
	  	            theData>>inputFlt;
		              inputFloats[currPosF++]=inputFlt;
	              }

	            theData.close();
		
		          outf << "At the canned file end, the graph0 is:" << std::endl;
		          outf << graph0 << std::endl;

	            return(-2);
	          }
	        //report solve failure
	        else
	          {
		          saveState(graph0, toSolverTrees, inputInts, inputFloats, 
                        treeFlag, gGraph1);
		          currPosI=inputInts[0];
              currPosF=(int) inputFloats[0];
		          inputInts[currPosI++]=-3;
		          inputInts[currPosI++]=0;
		          outf << "At the slove failure end, the graph0 is:" << std::endl;
		          outf << graph0 << std::endl;
              return(-2);
	          }
        } 

      // if there are no bifurcations and in autosolve, resolve this cluster 
      // with different bifurcations
      if(theCluster.returnNumBifurs()==0 && autoSolve) answer=1;

      //if this cluster has bifurcations, either in autosolve or not, continue
      if(theCluster.returnNumBifurs()!=0 && autoSolve) answer=3;
      if(!autoSolve) answer=3;
    }
  
  //set the fin flag of this cluster to true
  theCluster.setSolved(true);
  outf << "At the end, the graph0 is:" << std::endl;
  outf << graph0 << std::endl;
  outf.close();
  return 0;
}

//! calls solve cluster for every cluster in theForest
int 
solveForest (Graph &graph0, List<Cluster> &theForest, the_Tree &Tree,
             List<std::string>& vars, int equationCount, int withHeldCluster, 
             int aOverlap, int singleVertex, int nextVerName, int nextEdgeName, 
             int glo_flag, int search_flag, float *inputFloats, int currPosF, 
             int *inputInts, int currPosI, int *bifurAnswers, 
             List<Cluster> *toSolverTrees, bool usedBifurs, 
             List<Cluster> &roots, bool first, bool autoSolve, bool usingArrays,
             int treeFlags, int startF, int startI, int graphDimen, 
             Graph &gGraph1, char *inputChars, std::string &varsToZero, 
             List<Edge> &theImags)
{
  int length, i, tag;

  length=theForest.returnLen();
  for(i=1;i<=length;i++)
    {
      std::cout <<"About to call Solve Cluster"<<std::endl;
      tag=solveCluster(graph0, theForest.retrieve(i), false, Tree, vars, 
                       equationCount, withHeldCluster, aOverlap, singleVertex,
                       nextVerName, nextEdgeName, glo_flag, search_flag, 
                       inputFloats, currPosF, inputInts, currPosI, bifurAnswers,
                       toSolverTrees, usedBifurs, roots, first, autoSolve, 
                       usingArrays, treeFlags, startF, startI, graphDimen, 
                       gGraph1, inputChars, varsToZero, theImags);
      if(tag<0) return tag;
    }
  return 0;
}

//! test method which generates an equation for every type of constraint/vertex combination
void 
testEquations (Graph &graph0, List<std::string> &vars, List<Edge> &theImags, 
               Vertex::Type type1, Vertex::Type type2, Vertex testVertex1, 
               Vertex testVertex2)
{
   int i,j,k,part1,part2;
   Edge testEdge;
   std::ofstream dataOut;
   Cluster dummy;
   std::string outData;
   std::string one, two, three;

   dataOut.open("../outFile.txt");

   testVertex1.setName(1);
   testVertex2.setName(2);
   testEdge.setName(999);

   for(i=0;i<=6;i++)
   {
      switch(i)
      {
          case 0: one="Distance";
                  break;
          case 1:
          case 2: one="Incidence";
                  break;
          case 3: one="Angle";
                  break;
          case 4: one="Parallel";
                  break;
          case 5: one="Perpendicular";
                  break;
          case 6: one="Tangency";
                  break;
      }
      dataOut<<one+" Equations:"<<std::endl;
      for(j=0;j<=12;j++)
      {
         switch(j)
         {
             case 0: two="Point";
                     type1=Vertex::Point;
                     part1=1;
                     break;
             case 1: two="Line";
                     type1=Vertex::Line;
                     part1=0;
                     break;
             case 2: two="Ray (arb)";
                     type1=Vertex::Ray;
                     part1=0;
                     break;
             case 3: two="Ray (Pt1)";
                     type1=Vertex::Ray;
                     part1=1;
                     break;
             case 4: two="Line Seg (arb)";
                     type1=Vertex::LineSeg;
                     part1=0;
                     break;
             case 5: two="Line Seg (Pt1)";
                     type1=Vertex::LineSeg;
                     part1=1;
                     break;
             case 6: two="Line Seg (Pt2)";
                     type1=Vertex::LineSeg;
                     part1=2;
                     break;
             case 7: two="Circle (arb)";
                     type1=Vertex::Circle;
                     part1=0;
                     break;
             case 8: two="Circle (center)";
                     type1=Vertex::Circle;
                     part1=3;
                     break;
             case 9: two="Arc (arb)";
                     type1=Vertex::Arc;
                     part1=0;
                     break;
             case 10: two="Arc (Pt1)";
                      type1=Vertex::Arc;
                      part1=1;
                      break;
             case 11: two="Arc (Pt2)";
                      type1=Vertex::Arc;
                      part1=2;
                      break;
             case 12: two="Arc (Center)";
                      type1=Vertex::Arc;
                      part1=3;
                      break;
         }
         dataOut<<" End 1 is a/an "+two<<std::endl;
         for(k=0;k<=12;k++)
         {
            switch(k)
            {
                case 0:  three="Point:          ";
                         type2=Vertex::Point;
                         part2=1;
                         break;
                case 1:  three="Line:           ";
                         type2=Vertex::Line;
                         part2=0;
                         break;
                case 2:  three="Ray (arb):      ";
                         type2=Vertex::Ray;
                         part2=0;
                         break;
                case 3:  three="Ray (Pt1):      ";
                         type2=Vertex::Ray;
                         part2=1;
                         break;
                case 4:  three="Line Seg (arb): ";
                         type2=Vertex::LineSeg;
                         part2=0;
                         break;
                case 5:  three="Line Seg (Pt1): ";
                         type2=Vertex::LineSeg;
                         part2=1;
                         break;
                case 6:  three="Line Seg (Pt2): ";
                         type2=Vertex::LineSeg;
                         part2=2;
                         break;
                case 7:  three="Circle (arb):   ";
                         type2=Vertex::Circle;
                         part2=0;
                         break;
                case 8:  three="Circle (center):";
                         type2=Vertex::Circle;
                         part2=3;
                         break;
                case 9:  three="Arc (arb):      ";
                         type2=Vertex::Arc;
                         part2=0;
                         break;
                case 10: three="Arc (Pt1):      ";
                         type2=Vertex::Arc;
                         part2=1;
                         break;
                case 11: three="Arc (Pt2):      ";
                         type2=Vertex::Arc;
                         part2=2;
                         break;
                case 12: three="Arc (center):   ";
                         type2=Vertex::Arc;
                         part2=3;
                         break;
            }
            outData="";
            if(i<2) testEdge.setType(i);
            else testEdge.setType(i-1);
            testEdge.setPart(0,part1);
            testEdge.setPart(1,part2);
            testVertex1.setType(type1);
            testVertex2.setType(type2);
            testEdge.setValue(5.0);
            outData=getEquationInCluster(graph0, testEdge, dummy, vars, theImags);
            if(isImaginary(graph0,testEdge)) outData+=" *** IMAGINARY ***";
            if(outData!="")
            {
              dataOut<<"  End 2 is a/an "+three<<" ";
              dataOut<<outData<<std::endl;
            }
         }
      }
   }
   std::cout<<getSinCosConstraint(vars);
   dataOut<<getVarString(vars)<<std::endl;
   dataOut.close();
}

//! used for testing only
//! reads a graph struction from text input in a file
//void getGraphFromFile(Graph &graph0, List<Cluster> &SolverTrees)
//{
//   std::ifstream dataIn;
//   std::string filename;
//   int numShapes;
//   int numEdges;
//   Vertex::Type type;
//   int i, ID, end1, end2;
//   char s;
//   float value;
//   List<int> originalV, nullIntList, originalV2;
//   List<Vertex> vList, nullVList;
//   List<Edge> eList, nullEList;
//   List<Cluster> cList, nullCList;
//   Graph newGraph;
//
//   nullIntList.makeEmpty();
//   nullVList.makeEmpty();
//   nullEList.makeEmpty();
//   nullCList.makeEmpty();
//
//   std::cout<<"Enter a filename: ";
//   std::cin>>filename;
// 
//   dataIn.open(filename.c_str());
//
//   dataIn>>s;
//
//   if(s=='Y' || s=='y') toSolve=true;
//   else toSolve =false;   
//
//   dataIn>>numShapes;
//
//   for(i=0;i<numShapes;i++)
//   {
//      originalV.makeEmpty();
//      dataIn>>ID;
//      originalV2.append(ID);
//      originalV.append(ID);
//      Vertex::Type(dataIn)>>type;
//      Vertex currVert(ID, type);
//      vList.append(currVert);
//      Cluster currClust;
//      currClust.formCl(currVert,nullIntList,nullEList,nullEList,originalV);
//      currClust.children=nullCList;
//      cList.append(currClust);
//   }
//
//   dataIn>>numEdges;
//
//   for(i=0;i<numEdges;i++)
//   {
//      dataIn>>ID;
//      Vertex::Type(dataIn)>>type;
//      value=0;
//      if(type==0 || type==2) dataIn>>value;
//      dataIn>>end1;
//      dataIn>>end2;
//      Edge currEdge;
//      currEdge.setName(ID);
//      currEdge.setType(type);
//      currEdge.setValue(value);
//      currEdge.setEnd(0,end1);
//      currEdge.setEnd(1,end2);
//      eList.append(currEdge);
//   }
//
//   Vertex currVert;
//
//   currVert.setName(99);
//   currVert.setType(Vertex::Cluster);
//   currVert.setDepth(1);
//
//   Cluster newClust;
//
//   newClust.formCl(currVert,nullIntList,nullEList,nullEList,originalV2);
//   newClust.children=cList;
//
//   SolverTrees.makeEmpty();
//   SolverTrees.append(newClust);
//
//   newGraph.setVlist(vList);
//   newGraph.setElist(eList);
//
//   graph0=newGraph;
//
//   dataIn.close();
//}

//! stores a string in the output arrays by storing the ascii value of each of its chars in 
//! consequtive integers
void stringToArray(std::string theString, int*& theInts)
{
    int indexI=theInts[0];
    int i, length=theString.size();

    for(i=0;i<length;i++) theInts[indexI++]=theString[i];
    theInts[indexI++]=-1;
    theInts[0]=indexI;
}

//! reads a string in the above format
std::string readStringFromArray(int& start, int* theInts)
{
    std::string output="";    

    while(theInts[start]!=-1)
         output+=(char) theInts[start++];

    start++;
    return output;
}

//! stores a vertex in the output arrays
void vertexToArray(Vertex &theVertex, int*& theInts, float*& theFloats)
{
    int indexI=theInts[0];
    int indexF=(int) theFloats[0];
    int i, nIncid;

    theInts[indexI++]=theVertex.returnName();
    theInts[indexI++]=theVertex.returnType();
    theInts[indexI++]=theVertex.returnWeight();
    theInts[indexI++]=theVertex.returnDepth();
    theInts[indexI++]=theVertex.returnLabel();
    theInts[indexI++]=theVertex.returnScan();
    theInts[indexI++]=theVertex.isFrozen();
    theInts[indexI++]=theVertex.returnPosFlow();
    theInts[indexI++]=theVertex.returnEstFlow();
    theInts[indexI++]=(theVertex.returnIgnore() ? 1 : 0);
    nIncid=theInts[indexI++]=theVertex.numIncid();
    for(i=1;i<=nIncid;i++) theInts[indexI++]=theVertex.returnIncid(i);
    theInts[indexI++]=theVertex.returnPredEdg();
    for(i=0;i<9;i++) theInts[indexI++]=theVertex.returnFreeDegs(i);
    theInts[indexI++]=theVertex.leftEndIncid.returnLen();
    for(i=1;i<=theVertex.leftEndIncid.returnLen();i++)
	theInts[indexI++]=theVertex.leftEndIncid.retrieve(i);
    theInts[indexI++]=theVertex.rightEndIncid.returnLen();
    for(i=1;i<=theVertex.rightEndIncid.returnLen();i++)
        theInts[indexI++]=theVertex.rightEndIncid.retrieve(i);
    theInts[0]=indexI;

    for(i=0;i<9;i++) theFloats[indexF++]=theVertex.returnDegValueByName(i);
    theFloats[0]=indexF;
}

//! Reads a vertex from the output arrays
//! \param[out] vertex    The constructed vertex
//! \param[in]  startI    Start of the integer values
//! \param[in]  theInts   Array with the integer values
//! \param[in]  startF    Start of the float values
//! \param[in]  theFloats Array with the float values
void
readVertexFromArray (Vertex &vertex, int &startI, int* theInts, int& startF, 
                     float* theFloats)
{   
  int i, count;    

  vertex.setName(theInts[startI++]);
  vertex.setType(Vertex::Type(theInts[startI++]));
  vertex.setWeight(theInts[startI++]);
  vertex.setDepth(theInts[startI++]);
  vertex.setLabel(theInts[startI++]);
  vertex.setScan(theInts[startI++]);
  count=theInts[startI++];
  if(count==2) vertex.freezeForever();
  if(count==1) vertex.freeze();
  vertex.setPosFlow(theInts[startI++]);
  vertex.setEstFlow(theInts[startI++]);
  vertex.setIgnore(theInts[startI++]==1);
  count=theInts[startI++];
  for (i = 0; i < count; i++)
    vertex.appendIncid(theInts[startI++]);
  vertex.setPredEdg(theInts[startI++]);
  for (i = 0; i < 9; i++) 
    vertex.initialValue(i,theFloats[startF++],theInts[startI++]);
  count=theInts[startI++];
  for (i = 0; i < count; i++)
	  vertex.leftEndIncid.append(theInts[startI++]);
  count=theInts[startI++];
  for (i = 0; i < count; i++)
    vertex.rightEndIncid.append(theInts[startI++]);
}    
    
//! outputs an edge to the output arrays
void edgeToArray(Edge &theEdge, int*& theInts, float*& theFloats)
{
    int indexI=theInts[0];
    int indexF=(int) theFloats[0];
    
    theInts[indexI++]=theEdge.returnName();
    theInts[indexI++]=theEdge.returnType();
    theInts[indexI++]=theEdge.returnWeight();
    theInts[indexI++]=theEdge.returnLabel();
    theInts[indexI++]=theEdge.returnScan();
    theInts[indexI++]=theEdge.returnPosFlow();
    theInts[indexI++]=theEdge.returnFlow1();
    theInts[indexI++]=theEdge.returnFlow2();
    theInts[indexI++]=theEdge.returnEnd1();
    theInts[indexI++]=theEdge.returnPart1();
    theInts[indexI++]=theEdge.returnEnd2();
    theInts[indexI++]=theEdge.returnPart2();
    theInts[indexI++]=theEdge.returnPredVer();
    theInts[0]=indexI;

    theFloats[indexF++]=theEdge.returnValue();
    theFloats[0]=indexF;
}

//! Reads an edge from the output arrays
//! \param[out] edge      The constructed edge
//! \param[in]  startI    Start of the integer values
//! \param[in]  theInts   Array with the integer values
//! \param[in]  startF    Start of the float values
//! \param[in]  theFloats Array with the float values
void
readEdgeFromArray (Edge &edge, int &startI, int* theInts, int &startF, 
                   float* theFloats)
{    
  edge.setName   (theInts[startI++]);
  edge.setType   (theInts[startI++]);
  edge.setWeight (theInts[startI++]);
  edge.setLabel  (theInts[startI++]);
  edge.setScan   (theInts[startI++]);
  edge.setPosFlow(theInts[startI++]);
  edge.setFlow1  (theInts[startI++]);
  edge.setFlow2  (theInts[startI++]);
  edge.setEnd    (0, theInts[startI++]);
  edge.setPart   (0, theInts[startI++]);
  edge.setEnd    (1, theInts[startI++]);
  edge.setPart   (1, theInts[startI++]);    
  edge.setPredVer(theInts[startI++]);
  edge.setValue  (theFloats[startF++]);
}
    
//! outputs a graph to an array
void graphToArray(Graph &graph0, int*& theInts, float*& theFloats)
{
    int indexI=theInts[0];
    int i, count;
   
    theInts[indexI++]=graph0.returnDimen();
    theInts[indexI++]=graph0.returnDepth();
    count=theInts[indexI++]=graph0.returnNumVer();
    theInts[0]=indexI;
    for(i=1;i<=count;i++) vertexToArray(graph0.returnVertByIndex(i), theInts, theFloats);
    indexI=theInts[0];

    count=theInts[indexI++]=graph0.returnNumEdg();
    theInts[0]=indexI;
    for(i=1;i<=count;i++) edgeToArray(graph0.returnEdgeByIndex(i), theInts, theFloats);
}

//! Reads a graph from the arrays
//! \param[out] graph     The constructed graph
//! \param[in]  startI    Start of the integer values
//! \param[in]  theInts   Array with the integer values
//! \param[in]  startF    Start of the float values
//! \param[in]  theFloats Array with the float values
void
readGraphFromArray (Graph &graph, int &startI, int* theInts, int &startF, 
                    float* theFloats)
{
  int i, count;

  graph.setDimen(theInts[startI++]);
  graph.setDepth(theInts[startI++]);
  count = theInts[startI++];
  for (i = 0; i < count; i++)
    {
      Vertex newVert;
      readVertexFromArray(newVert, startI, theInts, startF, theFloats);
      graph.appendVertex(newVert);
    }
  count = theInts[startI++];
  for (i = 0; i < count; i++)
    {
      Edge newEdge;
      readEdgeFromArray(newEdge, startI, theInts, startF, theFloats);
      graph.appendEdge(newEdge);
    }    
}        

//! outputs a cluster to the arrays
void clusterToArray(Cluster &theCluster, int*& theInts, float*& theFloats)
{
   vertexToArray(theCluster.returnCore(), theInts, theFloats);

   int indexI=theInts[0];
   int indexF=(int) theFloats[0];
   int i, j, count, mem;
   
   theInts[indexI++]=theCluster.returnGroup();
   theInts[indexI++]=theCluster.returnType();
   count=theInts[indexI++]=theCluster.returnFronLen();
   for(i=1;i<=count;i++) theInts[indexI++]=theCluster.returnFrontier(i);
   count=theInts[indexI++]=theCluster.returnInnerELen();
   theInts[0]=indexI;
   for(i=1;i<=count;i++) edgeToArray(theCluster.returnInnerE(i), theInts, theFloats);
   indexI=theInts[0];
   count=theInts[indexI++]=theCluster.returnOuterELen();
   theInts[0]=indexI++;
   for(i=1;i<=count;i++) edgeToArray(theCluster.returnOuterE(i), theInts, theFloats);
   indexI=theInts[0];
   indexF=(int) theFloats[0];
   count=theInts[indexI++]=theCluster.returnOrigLen();
   for(i=1;i<=count;i++) theInts[indexI++]=theCluster.returnOrigV(i);
   count=theInts[indexI++]=theCluster.returnNumBifurs();
   mem=theInts[indexI++]=theCluster.returnCurrBifur();
   theInts[0]=indexI;
   for(i=1;i<=count;i++)
   {
      theCluster.setCurrBifur(i);
      stringToArray(theCluster.returnCurrBifurString(), theInts);
   }   
   theCluster.setCurrBifur(mem);
   indexI=theInts[0];
   theInts[indexI++]=theCluster.currAlias;
   count=theInts[indexI++]=theCluster.left.returnLen();
   for(i=1;i<=count;i++)
	theInts[indexI++]=theCluster.left.retrieve(i);
   count=theInts[indexI++]=theCluster.right.returnLen();
   for(i=1;i<=count;i++)
        theInts[indexI++]=theCluster.right.retrieve(i);
   count=theInts[indexI++]=theCluster.lines.returnLen();
   for(i=1;i<=count;i++)
        theInts[indexI++]=theCluster.lines.retrieve(i);
   if(theCluster.isSolved()) theInts[indexI++]=0;
   else theInts[indexI++]=-1;
   theInts[indexI++]=theCluster.returnConst();
   mem=theInts[indexI++]=theCluster.returnCurrDeg();
   count=theInts[indexI++]=theCluster.returnNumDeg();

   for(i=1;i<=count;i++)
   {
      theCluster.setCurrDeg(i);
      for(j=0;j<9;j++) theFloats[indexF++]=theCluster.returnValue(j);
   }
   theCluster.setCurrDeg(mem);
   theFloats[0]=indexF;

   count=theInts[indexI++]=theCluster.children.returnLen();
   theInts[0]=indexI;
   for(i=1;i<=count;i++)
      clusterToArray(theCluster.children.retrieve(i), theInts, theFloats);
}

//! reads a cluster from the arrays
void readClusterFromArray(Cluster &theCluster, int &startI, int* theInts, int &startF, float* theFloats)
{
   Vertex core;

   readVertexFromArray(core, startI, theInts, startF, theFloats);

   int i, j, count;

   theCluster.setGroup(theInts[startI++]);
   theCluster.setType(theInts[startI++]);

   List<int> fronts, origs;
   List<Edge> inner, outer;

   count=theInts[startI++];
   for(i=0;i<count;i++) fronts.append(theInts[startI++]);
   
   count=theInts[startI++];
   for(i=0;i<count;i++)
   {
      Edge newEdge;
      readEdgeFromArray(newEdge, startI, theInts, startF, theFloats);
      inner.append(newEdge);
   }

   count=theInts[startI++];
   for(i=0;i<count;i++)
   {
      Edge newEdge;
      readEdgeFromArray(newEdge, startI, theInts, startF, theFloats);
      outer.append(newEdge);
   }

   count=theInts[startI++];
   for(i=0;i<count;i++) origs.append(theInts[startI++]);

   theCluster.formCl(core, fronts, inner, outer, origs);

   List<std::string> strings;
   int currBifur;

   count=theInts[startI++];
   currBifur=theInts[startI++];
   for(i=0;i<count;i++)
   { 
      std::string test=readStringFromArray(startI, theInts);
      strings.append(test);
   }
   theCluster.setBifurs(strings);
   theCluster.setCurrBifur(currBifur);

   theCluster.currAlias=theInts[startI++];
   count=theInts[startI++];
   for(i=0;i<count;i++)
	theCluster.left.append(theInts[startI++]);
   count=theInts[startI++];
   for(i=0;i<count;i++)
        theCluster.right.append(theInts[startI++]);
   count=theInts[startI++];
   for(i=0;i<count;i++)
        theCluster.lines.append(theInts[startI++]);

   theCluster.setSolved(theInts[startI++]==0);
   theCluster.setConst(theInts[startI++]);

   List<DegValues> values;
   int currDeg;

   currDeg=theInts[startI++];
   count=theInts[startI++];

   for(i=0;i<count;i++)
   {
      DegValues newDeg;
      for(j=0;j<9;j++) newDeg.setValue(j,theFloats[startF++]);
      values.append(newDeg);
   }
   theCluster.setDegValues(values);
   theCluster.setCurrDeg(currDeg);

   count=theInts[startI++];
   for(i=0;i<count;i++)
   {
      Cluster newClust;
      readClusterFromArray(newClust, startI, theInts, startF, theFloats);
      theCluster.children.append(newClust);
   }
}


/*

THE JNI ARRAYS BEING LOADED AND UNLOADED WITH THE TREE INFORMATION


//stores the root of the Conversion Tree in the output arrays by storing the pointer to the Root node of the Tree 
void treeToArray(Node *Root, int*& theInts)
{
    int indexI=theInts[0];
    theInts[indexI++]=(int)Root;
    theInts[0]=indexI;
}

//reads the root of the Tree from the array
Node* readTreeFromArray(int& start, int* theInts)
{
    Node *Root=(Node *)theInts[start++];
    start++;
    return Root;
}

*/

//! prints the arrays to a file
void outputArrays(int* theInts, float* theFloats)
{
   int i;
   std::ofstream arrayOut;

   arrayOut.open("arrayOut.txt");

   for(i=0;i<INTSIZE;i++)
      arrayOut<<theInts[i]<<std::endl;
   
   for(i=0;i<FLOATSIZE;i++)
      arrayOut<<theFloats[i]<<std::endl;

   arrayOut.close();
}


//! reads the arrays from a file
void inputArrays(int*& theInts, float*& theFloats)
{
   int i;

   std::ifstream arrayIn;

   arrayIn.open("arrayOut.txt");

   for(i=0;i<INTSIZE;i++) 
   {  
      arrayIn>>theInts[i];
      if(theInts[0]==-1) return;
   }

   for(i=0;i<FLOATSIZE;i++) arrayIn>>theFloats[i];   

   arrayIn.close();
}

//! saves the DRTree and the graph into the output arrays, used when called within this file
void 
saveState (Graph &graph0, List<Cluster>* toSolverTrees, int *inputInts,
           float *inputFloats, int treeFlag, Graph& gGraph1)
{
     int i, length;

     length=toSolverTrees->returnLen();

     inputInts[0]=2;
     inputFloats[0]=1.0f;
     inputInts[1]=treeFlag;
/*

     std::cout << "Comes into calling one" << std::endl;
     Tree.copyTreeIntoArray(inputInts, inputChars);
     std::cout << "Comes into after calling one" << std::endl;
*/

     graphToArray(gGraph1, inputInts, inputFloats);
     graphToArray(graph0, inputInts, inputFloats);
     inputInts[inputInts[0]++]=length;
     for(i=1;i<=length;i++)
        clusterToArray(toSolverTrees->retrieve(i), inputInts, inputFloats);
}

/* LEGACY CODE
saves the DRTree and the graph into the output arrays, used when caled outside this file
void saveState(Graph &graph1, Graph &graph0, List<Cluster> &SolverTrees, jint*& thejInts, jdouble*& thejDoubles)
{
     int i, length;
     int *inputInts=new int[INTSIZE];
     float *inputFloats=new float[FLOATSIZE];

     length=SolverTrees.returnLen();

     inputInts[0]=1;
     inputFloats[0]=1.0f;
     graphToArray(graph1, inputInts, inputFloats);
     graphToArray(graph0, inputInts, inputFloats);
     inputInts[inputInts[0]++]=length;
     for(i=1;i<=length;i++)
        clusterToArray(SolverTrees.retrieve(i), inputInts, inputFloats);
     for(i=0;i<INTSIZE;i++)
        thejInts[i]=inputInts[i];
     for(i=0;i<FLOATSIZE;i++)
        thejDoubles[i]=inputFloats[i];     
}

*/

//! loads the DRTree and graph from the arrays
void
loadState(Graph &graph1, Graph &graph0, List<Cluster> &SolverTrees, int &startI,
          jint *thejInts, int &startF, jdouble *thejDoubles, jchar *thejChars)
{
  int i, length;
  int   *inputInts   = new int[INTSIZE];
  float *inputFloats = new float[FLOATSIZE];
  char  *inputChars  = new char[CHARSIZE];

  for(i=0;i<INTSIZE;i++)
    inputInts[i]=thejInts[i];
 
  for(i=0;i<FLOATSIZE;i++)
    inputFloats[i]=(float) thejDoubles[i];

  for(i=0;i<CHARSIZE;i++)
    inputChars[i]=thejChars[i];
/*
  std::cout << "Code did come into this.... see this here??" <<  std::endl;
  Tree.copyArrayIntoTree(startI, inputInts, inputChars);
*/
  graph0.makeEmpty();
  graph1.makeEmpty();
  SolverTrees.makeEmpty();
  readGraphFromArray(graph1, startI, inputInts, startF, inputFloats);
  readGraphFromArray(graph0, startI, inputInts, startF, inputFloats);

  length = inputInts[startI++];

  for (i = 0; i < length; i++)
    {
      Cluster newClust;
      readClusterFromArray(newClust, startI, inputInts, startF, inputFloats);
      SolverTrees.append(newClust);
    }

  startI++;
}

//! Sets the contents of the globals inputInts and inputFloats 
//! to output arrays inputTheInts and inputDouble
void 
setArraysForOutput (jint*& theJInts, jdouble*& theJDoubles, 
                    int *inputInts, float *inputFloats)
{
   int i;

   for(i=0;i<FLOATSIZE;i++)
      theJDoubles[i]=inputFloats[i];

   outputArrays(inputInts, inputFloats);
}

//! Sets the contents of the globals inputInts and inputFloats
//! to input arrays inputTheInts and inputDouble
void 
setArraysForInput (jint*& theJInts, jdouble*& theJDoubles, jchar*& theJChars, 
                   char *inputChars, int *inputInts, float *inputFloats)
{
   int i;

   inputChars=new char[CHARSIZE];

   inputChars=(char*) theJChars;

   inputInts=new int[INTSIZE];

   inputInts=(int*) theJInts;

   inputFloats=new float[FLOATSIZE];

   for(i=0;i<FLOATSIZE;i++)
      inputFloats[i]=(float) theJDoubles[i];   
}


//! given theEdge as input, resets all of the clusters in SolverTrees that 
//! contain both endpoints of theEdge as original vertices.  the method 
//! returns a count of the number of the vertices so reset
int 
resetTreesByEdge (List<Cluster> SolverTrees, Edge &theEdge)
{
   int i, length;
   int end1, end2;
   int count=0;

   length=SolverTrees.returnLen();
   end1=theEdge.returnEnd1();
   end2=theEdge.returnEnd2();

   for(i=1;i<=length;i++)
      if(inOriginalV(end1, SolverTrees.retrieve(i)) 
         && inOriginalV(end2, SolverTrees.retrieve(i)))
        {
          SolverTrees.retrieve(i).setSolved(false);
          count+=1+resetTreesByEdge(SolverTrees.retrieve(i).children, theEdge);
        }

   return count;
}

//! checks to see if theEdge is valid using the already solved values in 
//! SolverTrees
bool 
checkEdge (Edge &theEdge, Graph &graph0, List<Cluster> &SolverTrees, 
           List<std::string>& vars, int graphDimen, List<Edge> &theImags)
{
   int end1, end2;
   Vertex v1, v2;
   std::string input;

   vars.makeEmpty();
   input=getEquationInCluster(graph0, theEdge, SolverTrees.retrieve(1), vars,
                              theImags);
   end1=theEdge.returnEnd1();
   v1=graph0.returnVertByName(end1);
   end2=theEdge.returnEnd2();
   v2=graph0.returnVertByName(end2);
   input=switchString(v1, v1.returnType(), v1.returnName(), 0, input, false, 
                      vars, graphDimen);
   input=switchString(v2, v2.returnType(), v2.returnName(), 0, input, false,
                      vars, graphDimen);	

   input.replace(input.find("=",0),1,"-");

   std::ofstream inputFile;
   remove("input.txt");
   inputFile.open("input.txt");

   inputFile<<"evalb(abs("<<input<<")<0.00001);"<<std::endl;
   inputFile.close();

   shellMaple();        

   std::cout<<input<<std::endl;
   std::cout<<getVarString(vars)<<std::endl;

   std::ifstream outputFile;
   
   outputFile.open("output.txt");

   while(outputFile.get()!=';') if(outputFile.eof()) return false;
   
   char in;

   outputFile>>in;
   while(in!='t' || in!='f')
   {
        if(outputFile.eof()) return false;
        outputFile>>in;
   }
   if(in=='f') return false;
   else return true;
}

//! deletes clusters from SolverTrees that contain theEdge
void deleteClusterWithEdge(Graph &graph0, List<Cluster> &SolverTrees, Edge &theEdge)
{
   int end1, end2;

   end1=theEdge.returnEnd1();
   end2=theEdge.returnEnd2();
   
   int i=1, length=SolverTrees.returnLen();
   
   while(i<=length)
   {
      print(graph0, SolverTrees);
      if(inOriginalV(end1,SolverTrees.retrieve(i)) && inOriginalV(end2,SolverTrees.retrieve(i)))
      {
        int j,childLength;

        childLength=SolverTrees.retrieve(i).children.returnLen();
        
        for(j=1;j<=childLength;j++)
           SolverTrees.append(SolverTrees.retrieve(i).children.retrieve(j));

	SolverTrees.deleteIndex(i);
      }
      else i++;
      length=SolverTrees.returnLen();
   }
}


void getClusterByName(Cluster &outputCluster, List<Cluster> &SolverTrees, int name)
{
	int i, length=SolverTrees.returnLen();

	for(i=1;i<=length;i++)
		if(SolverTrees.retrieve(i).returnName()==name)
		{
			outputCluster=SolverTrees.retrieve(i);
			return;
		}

	for(i=1;i<=length;i++)
		getClusterByName(outputCluster,SolverTrees.retrieve(i).children,name);
}


//! Main solver function
//! \param[out] graph1       The output graph
//! \param[in]  graph0       The input graph
//! \param[in]  SolverTrees  List of all the cluster
//! \param[in]  inputTheInts Integer input from Java
//! \param[in]  inputDouble  Double input from Java
//! \param[in]  inputChar    Char input from Java
void 
Solver (Graph &graph1, Graph &graph0, List<Cluster> &SolverTrees, 
        jint* inputTheInts, jdouble* inputDouble, jchar* inputChar, 
        the_Tree &Tree, List<std::string>& vars, int equationCount, 
        int withHeldCluster, int aOverlap, int singleVertex,
        int nextVerName, int nextEdgeName, int glo_flag, int search_flag,
        float *inputFloats, int currPosF, int *inputInts, int currPosI,
        int *bifurAnswers, List<Cluster> *toSolverTrees, bool usedBifurs,
        List<Cluster> &roots, bool first, bool autoSolve, bool usingArrays,
        int treeFlag, int startF, int startI, int graphDimen, Graph &gGraph1,
        char *inputChars, std::string &varsToZero, List<Edge> &theImags)
{
  //Variables
  int i, numTrees=SolverTrees.returnLen();
  std::ofstream outfile;
  std::string answer;
  int count, tag;
  bool useFileTotal, useFileToBifur;
  std::ofstream testFile1, testFile2;


  copyG(graph1, gGraph1);

	std::ofstream outf;
  //	outf.open("solver.out", std::ios::app);
  outf <<"Solver Start+++++, let's look at the solver trees first:"<<std::endl;
	printForest(SolverTrees, outf, 0);

  //   parseForExternalOverCons(graph0,&SolverTrees);
   
  setArraysForInput(inputTheInts, inputDouble, inputChar, inputChars, 
                    inputInts, inputFloats);

  graphDimen=graph0.returnDimen();

  //Global Initializations
  startI=2;
  startF=1;
  treeFlag=inputInts[1];
  usingArrays=(inputInts[0]==2 || inputInts[0]==1);
  autoSolve=(inputInts[0]==1);
  first=true;
  roots=SolverTrees;
  vars.makeEmpty();
  usedBifurs=true;
  toSolverTrees=&SolverTrees;

  outf << "AutoSolve: " << (autoSolve ? "true" : "false") << std::endl;
  outf << "Variable Initialized usingArrays: " 
       << (usingArrays ? "true" : "false") << std::endl;

  //if the DRDag has just been generated, outputs it to the sketcher
  if (!usingArrays)
    {
      saveState (graph0, toSolverTrees, inputInts, inputFloats, treeFlag, 
                 gGraph1);
      std::cout<<"State Saved"<<std::endl;
      inputInts[inputInts[0]]=-1;
      inputInts[0]++;
      
      int backupIndex=inputInts[0];

      outf <<"DRDAG Output"<<std::endl;

      outputDRDAGToArray(SolverTrees, backupIndex, inputInts, true);

      for(i=backupIndex; i<backupIndex+100; i++)
	    outf <<inputInts[i]<<std::endl;

      outf <<"DAG Output"<<std::endl;
      outputArrays(inputInts, inputFloats);
      setArraysForOutput(inputTheInts, inputDouble, inputInts, inputFloats);
      outf <<"Arrays output, Solver returns"<<std::endl;
      return;
    }
  else
    {
      // runs the solver on the DRDag and if necessary sets the bifurcation of 
      // the root nodes in the DRDag

      graph0.makeEmpty();
      SolverTrees.makeEmpty();
      gGraph1.makeEmpty();
      //    Tree.copyArrayIntoTree(startI, inputInts, inputChars);
      
      for(i=startI;i<startI+100;i++)
	      outf <<"Integer after Tree: "<<inputInts[i]<<std::endl;

      readGraphFromArray(graph1, startI, inputInts, startF, inputFloats);
      readGraphFromArray(graph0, startI, inputInts, startF, inputFloats);

      graphDimen=graph0.returnDimen();
      
      int length=inputInts[startI++]; 

      for(i=0;i<length;i++)
        {
          Cluster newClust;
          readClusterFromArray (newClust, startI, inputInts, startF, 
                                inputFloats);
          SolverTrees.append(newClust);
        }
    
      outf <<"Graph and Cluster are read:"<<std::endl;
      
      outf << "The graph0 is: " << std::endl;
      numTrees=SolverTrees.returnLen();
      outf << graph0 << std::endl;
      print(graph0, SolverTrees);
      outf << "The solver trees are: " << std::endl;
      printForest(SolverTrees, outf, 0);

	    outf<<"the cluster is: " << std::endl;
      outf << SolverTrees.retrieve(i) << std::endl;
	    outf <<"is solved?" << std::endl;
	    outf << SolverTrees.retrieve(i).isSolved();
      outf <<"value at startI="<<inputInts[startI]<<std::endl;
      count=inputInts[startI];
      if(count>0) bifurAnswers=new int[count];

      for(i=1;i<=count;i++)
        {
	        if(i==1 && inputInts[startI+i]==-1)
	          {
	            for(int j=1;j<=SolverTrees.returnLen();j++)
		            resetFinByClusterName (SolverTrees.retrieve(j),
                                       inputInts[startI+2]);
	            break;
	          }
	        usedBifurs=false;	
          bifurAnswers[i-1]=inputInts[startI+i]+1;
          outf <<bifurAnswers[i-1]<<std::endl;
        }

      outf <<"Bifucations read, number="<<count<<std::endl;

      tag=0;
      for(i=1;i<=numTrees;i++)
        {
	        outf <<"In Solve Forest Loop"<<std::endl;
          tag=solveForest(graph0, SolverTrees, Tree, vars, equationCount, 
                          withHeldCluster, aOverlap, singleVertex,
                          nextVerName, nextEdgeName, glo_flag, search_flag, 
                          inputFloats, currPosF, inputInts, currPosI, 
                          bifurAnswers, toSolverTrees, usedBifurs, roots, first,
                          autoSolve, usingArrays, treeFlag, startF, startI, 
                          graphDimen, gGraph1, inputChars, varsToZero, 
                          theImags);
          if(tag==-2)
            {
              outf <<"Return by tag"<<std::endl; 
              setArraysForOutput (inputTheInts, inputDouble, inputInts, 
                                  inputFloats);
              return;
            }
        }

      outf <<"Solver ran, return value="<<tag<<std::endl;

      useFileToBifur=true;
      useFileTotal=false;     

      outf <<"usedBifurs="<<(usedBifurs ? "true" : "false")<<std::endl;

      if(usedBifurs && !autoSolve)
        { 
          saveState (graph0, toSolverTrees, inputInts, inputFloats, treeFlag, 
                     gGraph1);
          inputInts[0]++;
          currPosI=inputInts[0]+2;
          currPosF=(int) inputFloats[0];
          inputInts[inputInts[0]-1]=0;

          int count=0, currPosBackUp=currPosI++;
          for(i=1;i<=numTrees;i++)
            outputFinState(SolverTrees.retrieve(i), currPosI, inputInts, count);
          inputInts[currPosBackUp]=count;

          for(i=1;i<=numTrees;i++)
            {
              selectBifurcation (graph0,SolverTrees.retrieve(i),useFileToBifur, 
                                 inputFloats, currPosF, inputInts, currPosI);
              useFileTotal=(useFileTotal || useFileToBifur);
              if(useFileToBifur)
                {
                  inputInts[inputInts[0]-1]++;
                  continue;
                } 
              parseBifurString(graph0, SolverTrees.retrieve(i));
              updateGraph(graph0, SolverTrees.retrieve(i));  
            }
          inputInts[inputInts[0]]=0;
          inputInts[inputInts[0]+1]=inputInts[inputInts[0]-1];
        }
      else if(!autoSolve)
        {
          tag=0;
          for(i=1;i<=numTrees;i++)
            {
              if(SolverTrees.retrieve(i).returnCurrBifur()>=0) continue;
              SolverTrees.retrieve(i).setCurrBifur(bifurAnswers[tag++]);
              parseBifurString(graph0, SolverTrees.retrieve(i));
              updateGraph(graph0, SolverTrees.retrieve(i));
            }
        }

      if(useFileTotal && !autoSolve) 
        {
          outf <<"Return by useFileTotal"<<std::endl;
          setArraysForOutput(inputTheInts, inputDouble, inputInts, inputFloats);
          return;
        }

      if(autoSolve)
        {
          saveState (graph0, toSolverTrees, inputInts, inputFloats, treeFlag, 
                     gGraph1);
          for(i=1;i<=numTrees;i++)
            {
              SolverTrees.retrieve(i).setCurrBifur(1);
              parseBifurString(graph0, SolverTrees.retrieve(i));
              updateGraph(graph0, SolverTrees.retrieve(i));
            }
        }

      saveState (graph0, toSolverTrees, inputInts, inputFloats, treeFlag, 
                 gGraph1);
      currPosI=inputInts[0]++;
      inputInts[currPosI++]=1;
      currPosF=(int) inputFloats[0];
      inputInts[currPosI++]=1;
      inputInts[currPosI++]=numTrees;
      for(i=1;i<=numTrees;i++)
        {
	        updateGraph(graph0, SolverTrees.retrieve(i));	
          inputInts[currPosI++]=SolverTrees.retrieve(i).returnName();
          generateOutputToArray(graph0, SolverTrees.retrieve(i), true, 
                                inputFloats, currPosF, inputInts, currPosI);
        }
    }

  setArraysForOutput(inputTheInts, inputDouble, inputInts, inputFloats);

  outputArrays(inputInts, inputFloats);

  outf <<"Final Bifurcation Return"<<std::endl;

  outf << graph0 << std::endl;
  print(graph0,SolverTrees);   
   
  return;
}


std::string 
getEquation (Graph &graph0, Cluster &theCluster, std::ostream &inputFile, 
             the_Tree &Tree, List<std::string>& vars, int equationCount, 
             int withHeldCluster, int aOverlap, int singleVertex,
             int nextVerName, int nextEdgeName, int glo_flag, int search_flag,
             std::string &varsToZero, int graphDimen)
{
  //the_Tree Tree;

  std::ofstream outf;
  outf.open("getEquation.out", std::ios::app);
  outf << "The Cluster is:" << std::endl;
  outf << theCluster << std::endl;

  ClustData test;
  test=summCluster(graph0, theCluster);

  outf<<"SummCluster information: "<<std::endl;
  outf<<test<<std::endl;

  int length=test.length, j;
  size_t i;
  outf << "Length : " << length << std::endl;

  std::string tempString, newString, outputString;
  std::string stringArray[500];
  Vertex vEnd1, vEnd2;

	outf << "Before search_tree, vars are: " << getVarString(vars) << std::endl;
  outf<<"search_flag: "<<search_flag<<std::endl;

  if (search_flag==1)
    outputString+=Tree.search_Tree(graph0, theCluster, inputFile,
                                   withHeldCluster, graphDimen, glo_flag, vars);
  if (search_flag==2)
    outputString+=Tree.search_Tree(graph0, theCluster, inputFile, search_flag,
                                   withHeldCluster, graphDimen, glo_flag, vars);

	outf<<"the cluster's constraint is: " << theCluster.returnConst() 
      << std::endl;
	outf << "After search_tree, the string is: " << std::endl << outputString 
       << std::endl;

  //remove one constraint for overconstrainted example
  if(theCluster.returnConst()>1 && theCluster.returnDepth()<=3)
    {
	    outf<<"before erasing, the string is: " << std::endl << outputString 
          << std::endl;

	    int pos1 = outputString.find('{');
     	int pos2 = outputString.find(',', pos1+1);
	    outf << "pos1 and pos2 are: "  << pos1 << "  and   " << pos2 << std::endl;
 	    outputString.erase(pos1+1, pos2-pos1);
    }

  outf << "The outpurtString after search_Tree is: " << std::endl 
       << outputString << std::endl;
  outf<<"Vars right after search"<<std::endl;
  outf<<getVarString(vars)<<std::endl;

  int commaCount=0;
  for(i=0;i<=outputString.length();i++)
	  if(outputString[i]==',') commaCount++;

  outf<< " commaCount = " << commaCount<<std::endl;

  // outf<<"Original Output String: "<<outputString<<std::endl;

  // additional constraints are generated, see the appropriate methods for more 
  // details

  int tag;
  Edge forOriginSet, forOriginSet2;

  tag=1;

  equationCount=commaCount;

  outf<<"Edge Types:"<<std::endl;
  for(j=0;j<test.length;j++)
    outf<<test.edgeType[j]<<std::endl;


  if(test.length > 0)
    {
	    forOriginSet=graph0.returnEdgeByName(test.edgeID[0]);

	    outf << "the forOriginSet is: " << forOriginSet << std::endl;
 	    while(tag<test.length && test.edgeType[tag]==1)
        {
	    	  forOriginSet=graph0.returnEdgeByName(test.edgeID[tag]);
	    	  outf << "tag is: " << tag << std::endl;
	    	  tag++;
	    	  outf<<"In while, fororinginSet :" << forOriginSet<<std::endl;
      	}

      if(test.length>1)
	      forOriginSet2=graph0.returnEdgeByName(test.edgeID[1]);

      if(tag>=test.length && test.length>1)
        {
          if(forOriginSet.returnName()==test.edgeID[0])
	    		  forOriginSet2=graph0.returnEdgeByName(test.edgeID[1]);
	    	  else
            forOriginSet2=graph0.returnEdgeByName(test.edgeID[0]);
        }
      outf << "just before while(tag<test....)" << std::endl;
	    outf << "the two edges are: " << forOriginSet << std::endl 
           << forOriginSet2 << std::endl;
      while(tag<test.length && test.edgeType[tag]!=1)
	      {
       	  forOriginSet2=graph0.returnEdgeByName(test.edgeID[tag]);
	        tag++;
	      }

      //if(graph0.returnNumVer()==3 && graph0.returnNumEdg()==3)
      //  forOriginSet=graph0.returnEdgeByName(test.edgeID[1]);

      if(graph0.returnNumVer()==4 && graph0.returnNumEdg()==8)
        forOriginSet=graph0.returnEdgeByName(test.edgeID[1]);
	    outf << "Finally, the edges are: " << forOriginSet << std::endl 
           << forOriginSet2 << std::endl;
    }
  tag=0;

  std::string over;

  outf<<"EqnCount="<<equationCount<<std::endl;

  over=getOverlapConstraint(graph0, theCluster, test.length, vars, 
                            equationCount, withHeldCluster,
                            aOverlap, singleVertex,
                            nextVerName, nextEdgeName);



  outf<<"After getOver Output String: "<<over<<std::endl;
  outf<<"EqnCount="<<equationCount<<std::endl;
  if(test.length==0)
	over.erase(0,1);
  
  outputString+=over;

	outf<< "after getOver, vars are: (" << vars.returnLen() << ")" << std::endl;
	outf << getVarString(vars) << std::endl;

  outputString+=getRotationEquations(theCluster, vars, equationCount, withHeldCluster);
  outf << "After getRotationEquations, the equation number is: " 
       << equationCount << std::endl;

	outf<< "after getRotation, vars are: (" << vars.returnLen() << ")" << std::endl;
	outf << getVarString(vars) << std::endl;

  outputString+=getLineConstraint(graph0,theCluster.children, vars, equationCount);
  outf << "After getLineConstraint, the equation number is: " 
       << equationCount << std::endl;
  outputString+=getSinCosConstraint(vars);

  outf<<"After more Output String: "<<outputString<<std::endl;

  outf<<"Var Length = "<<vars.returnLen()<<", Eq Count = "<<equationCount
      <<std::endl;

  std::string originTemp; 

  for(int i=1;i<=theCluster.children.returnLen();i++)
    {
	    if(theCluster.children.retrieve(i).returnType()!=2 
	       && theCluster.children.retrieve(i).returnType()!=5) 
	    	continue;

	    int cName=theCluster.children.retrieve(i).returnName();
	    int repName=theCluster.children.retrieve(i).currAlias;
	    std::string r1,r2,r3,r4,r5,r6,s1,s2,s3,s4,s5,s6;

	    r1="x"+toString(cName);
	    r2="y"+toString(cName);
	    r3="z"+toString(cName);
	    r4="c"+toString(cName);
      r5="d"+toString(cName);
      r6="e"+toString(cName);
	    outf << "r1 - r6 are: " << r1 << "  " << r2 << "  " << r3 << "  " << r4 
           << "  " << r5 << "  " << r6 << std::endl;

	    for(int q=0;q<=theCluster.children.retrieve(i).lines.returnLen();q++)
	      {
	    	  if(q==0)
	    	  	repName=theCluster.children.retrieve(i).currAlias*1000+cName;
	    	  else
	    	  	repName=theCluster.children.retrieve(i).lines.retrieve(q)*1000+cName;

	    	  s1="x"+toString(repName);
	        s2="y"+toString(repName);
          s3="z"+toString(repName);
	    	  s4="c"+toString(repName);
	        s5="d"+toString(repName);
          s6="e"+toString(repName);
	    	  outf << "s1 - s6 are: " << s1 << "  " << s2 << "  " << s3 << "  " 
               << s4 << "  " << s5 << "  " << s6 << std::endl;
              
	        outputString=replaceAll(outputString,s1,r1, true);
          outputString=replaceAll(outputString,s2,r2, true);
          outputString=replaceAll(outputString,s3,r3, true);
          outputString=replaceAll(outputString,s4,r4, true);
          outputString=replaceAll(outputString,s5,r5, true);
          outputString=replaceAll(outputString,s6,r6, true);

	    	  if(!vars.hasElem(r1)) vars.append(r1);
	    	  if(!vars.hasElem(r2)) vars.append(r2);       
	    	  if(!vars.hasElem(r4)) vars.append(r4);       
	    	  if(!vars.hasElem(r5)) vars.append(r5);      
	    	  if(theCluster.children.retrieve(i).returnType()==2) 
	    	    {//z in 3D
	    	  	  if(!vars.hasElem(r6)) vars.append(r6);
	    	  	  if(!vars.hasElem(r3)) vars.append(r3);       
	    	    }

	    	  if(vars.hasElem(s1)) vars.deleteElem(s1);
          if(vars.hasElem(s2)) vars.deleteElem(s2);
          if(vars.hasElem(s3)) vars.deleteElem(s3);
          if(vars.hasElem(s4)) vars.deleteElem(s4);
          if(vars.hasElem(s5)) vars.deleteElem(s5);
          if(vars.hasElem(s6)) vars.deleteElem(s6);
	      }
			

	    for(int q=1;q<=theCluster.children.retrieve(i).left.returnLen();q++)
	      {
		      repName=theCluster.children.retrieve(i).left.retrieve(q)*1000+cName;
		      
		      s1="x"+toString(repName);
	        s2="y"+toString(repName);
          s3="z"+toString(repName);
		      outf << "In left part, s1 - s3 are: " << s1 << "  " << s2 << "  " 
               << s3 << std::endl;
		      outputString=replaceAll(outputString,s1,r1, true);
          outputString=replaceAll(outputString,s2,r2, true);
          outputString=replaceAll(outputString,s3,r3, true);

          if(!vars.hasElem(r1)) vars.append(r1);
          if(!vars.hasElem(r2)) vars.append(r2);
		      if(theCluster.children.retrieve(i).returnType()==2) 
		        {//z in 3D
	            if(!vars.hasElem(r3)) vars.append(r3);
 		        }
             
          if(vars.hasElem(s1)) vars.deleteElem(s1);
          if(vars.hasElem(s2)) vars.deleteElem(s2);
          if(vars.hasElem(s3)) vars.deleteElem(s3);
        }

      for(int q=1;q<=theCluster.children.retrieve(i).right.returnLen();q++)
        {
          repName=theCluster.children.retrieve(i).right.retrieve(q)*1000+cName;
        
          s1="x"+toString(repName);
          s2="y"+toString(repName);
          s3="z"+toString(repName);
		      outf << "In right part, s1 - s3 are: " << s1 << "  " << s2 << "  " 
               << s3 << std::endl;
   
          outputString=replaceAll(outputString,s1,r4, true);
          outputString=replaceAll(outputString,s2,r5, true);
          outputString=replaceAll(outputString,s3,r6, true);

          if(!vars.hasElem(r1)) vars.append(r4);
          if(!vars.hasElem(r2)) vars.append(r5);
		      if(theCluster.children.retrieve(i).returnType()==2) 
		        {//z in 3D
	            if(!vars.hasElem(r3)) vars.append(r6);
 		        }
              
          if(vars.hasElem(s1)) vars.deleteElem(s1);
          if(vars.hasElem(s2)) vars.deleteElem(s2);
          if(vars.hasElem(s3)) vars.deleteElem(s3); 
        }

	    float theValue=findDist(graph0,theCluster.children.retrieve(i));
	    theValue=rint(theValue);	
	    outf << "theValue is: " << theValue << std::endl;
	    outputString+=",("+toString(theValue)+")^2";
	    if(theCluster.children.retrieve(i).returnType()==2)
	    	outputString+="=("+r1+"-"+r4+")^2+("+r2+"-"+r5+")^2+("+r3+"-"+r6+")^2";
	    else
	    	outputString+="=("+r1+"-"+r4+")^2+("+r2+"-"+r5+")^2";
	    equationCount++;
	    outf << "outputstring is: " << std::endl << outputString << std::endl;
	    outf << "equation number is: " << equationCount << std::endl;
    }
		
  outf<<"After alias Output String: "<<outputString<<std::endl;
	//UGLY CODE, REMOVE IT LATER
	if(graph0.returnDimen()==2 && theCluster.children.returnLen()==6 
     && graph0.returnNumVer()>6)	
	  {
		  outputString+=",x33=0,y33=0,c33=0";
		  equationCount+=3;
	  }
	else
	  {  
      if(vars.returnLen()>equationCount && (graph0.returnDimen()!=3 
         || theCluster.returnCore().returnDepth()==1))
	      {
  		    originTemp=getOriginEquations(forOriginSet, forOriginSet2, graph0, 0, 
                                        theCluster.returnType(), varsToZero);
    		  if(originTemp.size()>0) outputString+=","+originTemp;
	      }
	  }
  outf<<"after getOrigin Output String: "<<outputString<<std::endl;
  outf<<"Equation Count right before Special case="<<equationCount<<std::endl;

  outf<<"VarLen="<<vars.returnLen()<<" EqnCount="<<equationCount<<std::endl;

  if(vars.returnLen()==9 && equationCount==7 && originTemp=="")
    {
	    int i=1, count=0;

	    while(count<2)
	      {
	    	  switch(vars.retrieve(i)[0])
	    	    {
	    	  	  case	'p':
	    	  	  case	'q':
	    	  	  case	'f':	break;

	    	  	  case	's':
	    	  	  case	'j':
	    	  	  case	'n':	if(outputString.length()>1)
	    	  	  			        outputString+=",";
	    	  	  		        outputString+=vars.retrieve(i)+"=0";
	    	  	  		        count++;
                          break;
	    	  	  case	't':
	    	  	  case 	'h':
	    	  	  case 	'k':	if(outputString.length()>1)
	    	  	  			        outputString+=",";
	    	  	  		        outputString+=vars.retrieve(i)+"=1"; 
                          count++;
	    	  	  		        break;
	    	    }
	    	  i++;
	      }
	    equationCount=9;
    }			

  if(vars.returnLen()>equationCount && originTemp=="")
    outputString+=","+getSpecialCaseEquations(graph0, theCluster, 1, outputString);
                
  outf<<"After Special Output String: "<<outputString<<std::endl;

  outputString+="},";
  outputString+=getVarString(vars);
  outputString+="));\n";
  outputString+="allvalues(%);\n";
  outputString+="evalf(%);\n";
  outf<<"OUTPUT FILE WRITTEN"<<std::endl;

  size_t loc=60;
  
  while(loc<outputString.size())
    {
	    loc=outputString.find_first_of("*+-/",loc);
	    if(loc<0 || loc>outputString.size())
	    	break;
	    outputString.insert(loc,"\n");
	    loc+=60;
    }

  outf<<outputString<<std::endl;
	
  return outputString;
}
