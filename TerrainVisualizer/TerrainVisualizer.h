#pragma once
#include <gl/freeglut.h>
#include <string>
#include <iostream>
#include <sstream>
#include <array>
#include <fstream>
#include <vector>
#include "GridFloatData.h"

#ifndef TERRAIN_VISUALIZER_H
#define TERRAIN_VISUALIZER_H

int displayMenu;
int lowColMenu;
int highColMenu;
int mainMenu;

constexpr double PI = 3.141592653589793238463;

struct point { float x;	float y; };

struct lineSeg {
	struct point a;
	struct point b;
};

class TerrainVisualizer
{
public:

	//	ints indicating the range and increment (for positive values) for the contour lines
	int low = 1000, high = 2600, step = 10;
	int numSteps;

	//	 color assigned to the low and high contour line
	std::array<float, 3> lowColor = { 0,0,0 };
	std::array<float, 3> highColor = { 1,1,1 };

	//  define the window position on screen and size
	int window_x;
	int window_y;
	int window_width = 600;
	int window_height = 600;
	int max_init_window_width = 800;
	int max_init_window_height = 600;

	float aspectRatio = 1;

	int camLeft = 0, camRight = 1, camBottom = 0, camTop = 1, camNear = 0, camFar = 1;

	//	Menu stuff
	bool showPolygons = true;
	bool showWireframe = false;
	bool showContours = false;

	//  variable representing the window title
	char *window_title = "Terrain Visualizer";

	//  Tells whether to display the window full screen or not
	//  Press Alt + Esc to exit a full screen.
	int full_screen = 0;

	//	Name of file to be read
	std::string fileName;
	GridFloatData *data;
	std::vector<std::vector<lineSeg>> contourLines;

	std::array<double, 3> eyePos = { -3,1,-3 };
	std::array<double, 3> targetPos = { 0,0,0 };
	std::array<double, 3> upVector = { 0,1, 0 };

	double fov = 45;
	double zNear = 0.1;
	double zFar = 1000;
	double dIncrement = .5;
	double aIncrement = 0.2;
	double eyeDist = sqrt(eyePos[0] * eyePos[0] + eyePos[1] * eyePos[1] + eyePos[2] * eyePos[2]);
	double phi = 0;
	double theta = 90.0 / 180.0*PI;

	void init();
	void display(void);
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void centerOnScreen();
	void makeContourLine(int loopUpCase, int x, int y, float iso, int level);
	void generateContourLines();
	int static getContourCase(bool TL, bool TR, bool BL, bool BR);
	float static lerp(float v1, float v2, float iso, int a1, int a2);

	void DisplayText();
	void DrawLine(struct point a, struct point b, std::array<float, 3> color);
	void DrawTerrainPolygon();
	void DrawTerrainWireframe();
	void DrawContourLines();

	TerrainVisualizer(int argc, char **argv);
	~TerrainVisualizer();
};

TerrainVisualizer* fgRef;

#endif
