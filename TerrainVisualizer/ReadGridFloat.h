#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "ContourLine.h"
#include "TerrainVisualizer.h"


#ifndef READ_GRID_FLOAT_H
#define READ_GRID_FLOAT_H

//	Defines the byte order of the gridFloat file
enum byteOrder {
	MSBFIRST = 0,
	LSBFIRST = 1,
	VMS_FFLOAT = 2
};

//	Holds the definition for the gridFloat.
struct gridFloatData {
	int ncols;
	int nrows;
	float xllcorner;
	float yllcorner;
	float cellsize;
	int NODATA = -9999;
	byteOrder order;
	int highestValue;
	int lowestValue;

	std::array<float, 2> posHighestPoint;
};


class ReadGridFloat {


public:
	float static ReverseFloat(const float inFloat);
	int GetGridFloatFromFile(std::string, std::vector<std::vector<float>> &, struct gridFloatData &);
};


#endif // !READ_GRID_FLOAT_H
