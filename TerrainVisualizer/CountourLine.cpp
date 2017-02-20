#include "ContourLine.h"

//	Returns the case of the 4 combinations
int ContourLine::getContourCase(bool TL, bool TR, bool BL, bool BR) {
	int result = 0;
	if (BL)
		result++;
	if (BR)
		result += 2;
	if (TR)
		result += 4;
	if (TL)
		result += 8;
	return result;
}


//	
void ContourLine::getContourLine(int loopUpCase, int x, int y, float iso, ContourLine lines, std::vector<std::vector<float>> *data) {
	lineSeg line;
	//	bottom Left Corner - done
	if (loopUpCase == 0 || loopUpCase == 15) {
		return;
	}
	else if (loopUpCase == 1 || loopUpCase == 14) {
		
		line.a.x = (float)x;
		line.a.y = lerp(data.at(x).at(y), data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = lerp(data.at(x).at(y + 1), data.at(x + 1).at(y + 1), iso, x, x + 1);
		line.b.y = (float)y + 1;

		lines.line.push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	Bottom right Corner - done
	else if (loopUpCase == 2 || loopUpCase == 13) { 
		line.a.x = lerp(data.at(x).at(y + 1), data.at(x + 1).at(y + 1), iso, x, x + 1);
		line.a.y = (float)y + 1;

		line.b.x = (float)x + 1;
		line.b.y = lerp(data.at(x + 1).at(y), data.at(x + 1).at(y + 1), iso, y, y + 1);
		lines.line.push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	Top right Corner - done
	else if (loopUpCase == 4 || loopUpCase == 11) {
		line.a.x = lerp(data.at(x).at(y), data.at(x + 1).at(y), iso, x, x + 1);
		line.a.y = (float)y;

		line.b.x = (float)x + 1;
		line.b.y = lerp(data.at(x + 1).at(y), data.at(x + 1).at(y + 1), iso, y, y + 1);
		lines.line.push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	Top left Corner
	else if (loopUpCase == 7 || loopUpCase == 8) {
		line.a.x = (float)x;
		line.a.y = lerp(data.at(x).at(y), data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = lerp(data.at(x).at(y), data.at(x + 1).at(y), iso, x, x + 1);
		line.b.y = (float)y;
		lines.line.push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	horizontal straight - done
	else if (loopUpCase == 3 || loopUpCase == 12) {
		line.a.x = (float)x;
		line.a.y = lerp(data.at(x).at(y), data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = (float)x + 1;
		line.b.y = lerp(data.at(x + 1).at(y), data.at(x + 1).at(y + 1), iso, y, y + 1);
		lines.line.push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	vertical straight
	else if (loopUpCase == 6 || loopUpCase == 9) {
		line.a.x = lerp(data.at(x).at(y), data.at(x + 1).at(y), iso, x, x + 1);
		line.a.y = (float)y;

		line.b.x = lerp(data.at(x).at(y + 1), data.at(x + 1).at(y + 1), iso, x, x + 1);
		line.b.y = (float)y + 1;

		lines.line.push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}

	//	Special cases
	else if (loopUpCase == 5) {
		line.a.x = lerp(data.at(x).at(y), data.at(x + 1).at(y), iso, x, x + 1);
		line.a.y = (float)y;

		line.b.x = (float)x + 1;
		line.b.y = lerp(data.at(x + 1).at(y), data.at(x + 1).at(y + 1), iso, y, y + 1);

		lines.line.push_back(line);

		lineSeg lineB;
		lineB.a.x = (float)x;
		lineB.a.y = lerp(data.at(x).at(y), data.at(x).at(y + 1), iso, y, y + 1);

		lineB.b.x = lerp(data.at(x).at(y + 1), data.at(x + 1).at(y + 1), iso, x, x + 1);
		lineB.b.y = (float)y + 1;

		lines.line.push_back(line);
	}
	else if (loopUpCase == 10) {
		line.a.x = (float)x;
		line.a.y = lerp(data.at(x).at(y), data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = lerp(data.at(x).at(y), data.at(x + 1).at(y), iso, x, x + 1);
		line.b.y = (float)y;
		lines.line.push_back(line);

		lineSeg lineB;
		lineB.a.x = lerp(data.at(x).at(y + 1), data.at(x + 1).at(y + 1), iso, x, x + 1);
		lineB.a.y = (float)y + 1;

		lineB.b.x = (float)x + 1;
		lineB.b.y = lerp(data.at(x + 1).at(y), data.at(x + 1).at(y + 1), iso, y, y + 1);

		lines.line.push_back(line);
	}
}

//	V1 = data.data(x,y), V2 = data.data(x + 1, y + 1), iso = contourlineHeight, a1 = x1 or y1, a2 = x2 or y2
float ContourLine::lerp(float v1, float v2, float iso, int a1, int a2) {
	return (iso - v2) * (a1 - a2) / (v1 - v2) + a2;
}

	//-------------------------------------------------------------------------
	//  This function is passed to glutDisplayFunc in order to display 
	//	OpenGL contents on the window.
	//-------------------------------------------------------------------------
void ContourLine::displayContour(ContourLine &line) {
		
	
}

void ContourLine::DrawContourLines(std::vector<ContourLine> lines, std::array<float, 3> lowColor, std::array<float, 3> highColor) {
	//  Clear the window or more specifically the frame buffer...
	//  This happens by replacing all the contents of the frame buffer by the clear color (white in our case)
	glClear(GL_COLOR_BUFFER_BIT);

	int numLines = lines.size();

	for (int i = 0; i < numLines; i++) {
		std::array<float, 3> color = { 0,0,0 };
		color[0] = lowColor[0] + i*(highColor[0] - lowColor[0]) / numLines;
		color[1] = lowColor[1] + i*(highColor[1] - lowColor[1]) / numLines;
		color[2] = lowColor[2] + i*(highColor[2] - lowColor[2]) / numLines;
		/*
		std::cout << "Color "<< color[0] << " " << color[1] << " " << color[2] << "\n";
		std::cout << "number of contour line Segments " << contours.at(i).size() << "\n";
		std::cout << "\n";
		*/
		for (lineSeg line : lines.at(i).line) {
			//std::cout << line.a.x << " " << line.a.y << "\n";
			TerrainVisualizer::DrawLine(line.a, line.b, color);
		}
		//std::cout << "\n";
	}

	glutSwapBuffers();
}

//int loopUpCase, int x, int y, float iso, ContourLine *lines, std::vector<std::vector<float>> data)
void ContourLine::MakeContourLines(GridFloatData data, std::vector<ContourLine> lines, int numSteps, int step){


	int isoVal = data.lowestValue;
	for (int i = 0; i < numSteps; i++) {
		ContourLine line;
		for (int j = 0; j < data.nrows - 1; j++) {
			for (int k = 0; k < data.ncols - 1; k++) {
				ContourLine::getContourLine(ContourLine::getContourCase(
					data.data.at(j).at(k) >= isoVal,
					data.data.at(j + 1).at(k) >= isoVal,
					data.data.at(j).at(k + 1) >= isoVal,
					data.data.at(j + 1).at(k + 1) >= isoVal),
					j, k, (float)isoVal,
					line , data.data);
				//std::cout << contours.at(i).at(j).a.x << " ";
			}
			//std::cout << '\n';
			lines.at(i) = line;
		}
		isoVal += step;
		//std::cout << '\n';
	}

}

ContourLine::ContourLine() {

}

ContourLine::~ContourLine() {

}
