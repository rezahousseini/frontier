//! \file ClustData.h
//! \brief Class for cluster data

#define CDATALEN	8

#ifndef INCLUDE_CLUSTDATA_H
#define INCLUDE_CLUSTDATA_H

#include <iostream>


class ClustData
{
  public:

  int   length;
  bool  *inOrBetween;
  float *values;
  int   *edgeID;
  int   *edgeType;
	int  	*e1ID;    //!< ID of edge 1
	int  	*e2ID;    //!< ID of edge 2
  int   *e1Type;  //!< Type of edge 1
  int   *e2Type;  //!< Type of edge 2
	int  	*e1Part;  //!< Part of edge 1
	int  	*e2Part;  //!< Part of edge 2

	void create(int len);
	void init();
	void destroy();
	void copy(const ClustData &oldClustData);

	ClustData();

  ClustData(int len);	

  ClustData(const ClustData &oldClustData); 

  ~ClustData() { destroy();	}

	ClustData& operator = (const ClustData &oldClustData);	

  friend std::ostream& operator <<(std::ostream&, const ClustData&);
};

#endif // INCLUDE_CLUSTDATA_H
