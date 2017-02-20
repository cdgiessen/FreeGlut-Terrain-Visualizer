#pragma once
#include <array>
#include <vector>

#include "TerrainVisualizer.h"
#include "GridFloatData.h"

#ifndef CONTOUR_LINE_H
#define CONTOUR_LINE_H

class ContourLine {


public :
	//	Vetor of a Vector of a Vector of a Vector of points, which represents the contour lines in each cell in each level 
	std::vector< struct lineSeg> line;

	int static getContourCase(bool TL, bool TR, bool BL, bool BR);
	void static getContourLine(int loopUpCase, int x, int y, float iso, ContourLine lines, std::vector<std::vector<float>> *data);

	float static lerp(float v1, float v2, float iso, int a1, int a2);


	void DrawContourLines(std::vector<ContourLine> lines, std::array<float, 3> lowColor, std::array<float, 3> highColor);	
	void displayContour(ContourLine &);

	void static MakeContourLines(GridFloatData data, std::vector<ContourLine> lines, int numSteps, int step);

	ContourLine();
	~ContourLine();
};
#endif // !CONTOUR_LINES_H
