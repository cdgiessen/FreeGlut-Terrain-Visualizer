#include "TerrainVisualizer.h"

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init() {	fgRef->init();}
void TerrainVisualizer::init()
{
	//  Set the frame buffer clear color to black. 
	glClearColor(1.0, 1.0, 1.0, 1.0); //White is a nice background color. 
	//glOrtho(camLeft, camRight, camBottom, camTop, camNear, camFar);
	glViewport(0, 0, window_width, window_height);
	glEnable(GL_DEPTH_TEST);
}

void idle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
}

void menu(int option) {
	switch (option){
	case 100:
		fgRef->eyePos = { -3,1,-3 };
		break;
	case 1: //polygon
		fgRef->showPolygons = !fgRef->showPolygons;
		break;
	case 2: //wireframe
		fgRef->showWireframe = !fgRef->showWireframe;
		break;
	case 3: //contours
		fgRef->showContours = !fgRef->showContours;
		break;
	case 10: //low red
		fgRef->lowColor = { 1,0,0 };
		break;
	case 11: //low blue
		fgRef->lowColor = { 0,0,1 };
		break;
	case 12: //low green
		fgRef->lowColor = { 0,1,0 };
		break;
	case 13: //low white
		fgRef->lowColor = { 1,1,1 };
		break;
	case 14: //low black
		fgRef->lowColor = { 0,0,0 };
		break;
	case 20: //high red
		fgRef->highColor = { 1,0,0 };
		break;
	case 21: //high blue
		fgRef->highColor = { 0,0,1 };
		break;
	case 22: //high green
		fgRef->highColor = { 0,1,0 };
		break;
	case 23: //high white
		fgRef->highColor = { 1,1,1 };
		break;
	case 24: //high black
		fgRef->highColor = { 0,0,0 };
		break;
	}
	
	glutPostRedisplay();
}

void createGLUTMenus() {
	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	displayMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Toggle Polygon", 1);
	glutAddMenuEntry("Toggle Wireframe", 2);
	glutAddMenuEntry("Toggle Contours", 3);

	lowColMenu = glutCreateMenu(menu);

	//add entries to our menu
	glutAddMenuEntry("Red", 10);
	glutAddMenuEntry("Blue", 11);
	glutAddMenuEntry("Green", 12);
	glutAddMenuEntry("White", 13);
	glutAddMenuEntry("Black", 14);
	highColMenu = glutCreateMenu(menu);

	glutAddMenuEntry("Red", 20);
	glutAddMenuEntry("Blue", 21);
	glutAddMenuEntry("Green", 22);
	glutAddMenuEntry("White", 23);
	glutAddMenuEntry("Black", 24);

	mainMenu = glutCreateMenu(menu);

	glutAddSubMenu("Change displaying types", displayMenu);
	glutAddSubMenu("Change high color", highColMenu);
	glutAddSubMenu("Change low color", lowColMenu);
	glutAddMenuEntry("Reset Viewport", 100);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//	OpenGL contents on the window.
//-------------------------------------------------------------------------
void display(void) {	fgRef->display();}
void TerrainVisualizer::display(void)
{
	//  Clear the window or more specifically the frame buffer...
	//  This happens by replacing all the contents of the frame buffer by the clear color (white in our case)
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Set-up the camera
	gluLookAt(eyePos[0], eyePos[1], eyePos[2], 
		targetPos[0], targetPos[1], targetPos[2], upVector[0], upVector[1], upVector[2]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(showPolygons)
		TerrainVisualizer::DrawTerrainPolygon();
	if(showWireframe)
		TerrainVisualizer::DrawTerrainWireframe();
	if(showContours)
		TerrainVisualizer::DrawContourLines();
	glutSwapBuffers();
}

//-------------------------------------------------------------------------
//  This function is passed to the glutReshapeFunc and is called
//  whenever the window is resized.
//-------------------------------------------------------------------------
void reshape(int w, int h) {	fgRef->reshape(w, h);}
void TerrainVisualizer::reshape(int w, int h)
{
	//  Stay updated with the window width and height
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//  Keep the correct aspect ratio
	if (aspectRatio*h > w)
		glViewport(0, 0, w, (int)(w / aspectRatio));
	else
		glViewport(0, 0, (int)(aspectRatio*h), h);

	glOrtho(-1.5, 1.5, -1.5, 1.5, -1000, 1000);

	//  Print current width and height on the screen
	printf("Window Width: %d, Window Height: %d.\n", window_width, window_height);
}

//-------------------------------------------------------------------------
//  Gets keyboard input, if use hits escape, the window closes;
//-------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y) {	fgRef->keyboard(key, x, y);}
void TerrainVisualizer::keyboard(unsigned char key, int x, int y)
{
	//  Print what key the user is hitting
	//printf("User is hitting the '%c' key.\n", key);
	//`printf("ASCII code is %d.\n", key);
	bool updateSpherical = false, updateCartesian = false;
	if		(key == 'd') { eyePos[0] += dIncrement; updateSpherical = true; }
	else if (key == 'a') { eyePos[0] -= dIncrement; updateSpherical = true; }
	else if (key == 'w') { eyePos[1] += dIncrement; updateSpherical = true; }
	else if (key == 's') { eyePos[1] -= dIncrement; updateSpherical = true; }
	else if (key == 'q') { eyePos[2] += dIncrement; updateSpherical = true; }
	else if (key == 'e') { eyePos[2] -= dIncrement; updateSpherical = true; }
	else if (key == 'r') { eyeDist += dIncrement; updateCartesian = true; }
	else if (key == 'R') { eyeDist -= dIncrement; updateCartesian = true; }
	else if (key == 't') { theta += aIncrement; updateCartesian = true; }
	else if (key == 'T') { theta -= aIncrement; updateCartesian = true; }
	else if (key == 'p') { phi += aIncrement; updateCartesian = true; }
	else if (key == 'P') { phi -= aIncrement; updateCartesian = true; }
	switch (key)
	{
	case 27: //  User hits ESC key
		exit(1);
		break;

	case 119: //w
		
		break;
	case 115: //s

		break;
	case 97: //a

		break;
	case 100: //d

		break;
	case 113: //q

		break;
	case 101: //e

		break;
	case 87: //W

		break;
	case 83: //S

		break;
	case 65: //A

		break;
	case 68: //D

		break;
	case 81: //Q

		break;
	case 69: //E

		break;
	}
	if (updateSpherical)
	{
		eyeDist = sqrt(eyePos[0] * eyePos[0] + eyePos[1] * eyePos[1] + eyePos[2] * eyePos[2]);
		theta = atan2(eyePos[1], eyePos[0]);
		phi = acos(eyePos[2] / eyeDist);
		updateSpherical = false;
	}
	if (updateCartesian)
	{
		eyePos[0] = eyeDist*cos(theta)*sin(phi);
		eyePos[1] = eyeDist*sin(theta)*sin(phi);
		eyePos[2] = eyeDist*cos(phi);
		updateCartesian = false;
	}
	
	glutPostRedisplay();
}

//	V1 = GFdata(x,y), V2 = GFdata(x + 1, y + 1), iso = contourlineHeight, a1 = x1 or y1, a2 = x2 or y2
float TerrainVisualizer::lerp(float v1, float v2, float iso, int a1, int a2) {
	return (iso - v2) * (a1 - a2) / (v1 - v2) + a2;
}

//	Returns the case of the 4 combinations
int TerrainVisualizer::getContourCase(bool TL, bool TR, bool BL, bool BR) {
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

void TerrainVisualizer::makeContourLine(int loopUpCase, int x, int y, float iso, int level) {
	lineSeg line;
	//	bottom Left Corner - done

	if (loopUpCase == 0 || loopUpCase == 15) {
		return;
	}

	if (loopUpCase == 1 || loopUpCase == 14) {

		line.a.x = (float)x;
		line.a.y = lerp(data->data.at(x).at(y), data->data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = lerp(data->data.at(x).at(y + 1), data->data.at(x + 1).at(y + 1), iso, x, x + 1);
		line.b.y = (float)y + 1;

		contourLines.at(level).push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	Bottom right Corner - done
	else if (loopUpCase == 2 || loopUpCase == 13) {
		line.a.x = lerp(data->data.at(x).at(y + 1), data->data.at(x + 1).at(y + 1), iso, x, x + 1);
		line.a.y = (float)y + 1;

		line.b.x = (float)x + 1;
		line.b.y = lerp(data->data.at(x + 1).at(y), data->data.at(x + 1).at(y + 1), iso, y, y + 1);
		contourLines.at(level).push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	Top right Corner - done
	else if (loopUpCase == 4 || loopUpCase == 11) {
		line.a.x = lerp(data->data.at(x).at(y), data->data.at(x + 1).at(y), iso, x, x + 1);
		line.a.y = (float)y;

		line.b.x = (float)x + 1;
		line.b.y = lerp(data->data.at(x + 1).at(y), data->data.at(x + 1).at(y + 1), iso, y, y + 1);
		contourLines.at(level).push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	Top left Corner
	else if (loopUpCase == 7 || loopUpCase == 8) {
		line.a.x = (float)x;
		line.a.y = lerp(data->data.at(x).at(y), data->data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = lerp(data->data.at(x).at(y), data->data.at(x + 1).at(y), iso, x, x + 1);
		line.b.y = (float)y;
		contourLines.at(level).push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	horizontal straight - done
	else if (loopUpCase == 3 || loopUpCase == 12) {
		line.a.x = (float)x;
		line.a.y = lerp(data->data.at(x).at(y), data->data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = (float)x + 1;
		line.b.y = lerp(data->data.at(x + 1).at(y), data->data.at(x + 1).at(y + 1), iso, y, y + 1);
		contourLines.at(level).push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}
	//	vertical straight
	else if (loopUpCase == 6 || loopUpCase == 9) {
		line.a.x = lerp(data->data.at(x).at(y), data->data.at(x + 1).at(y), iso, x, x + 1);
		line.a.y = (float)y;

		line.b.x = lerp(data->data.at(x).at(y + 1), data->data.at(x + 1).at(y + 1), iso, x, x + 1);
		line.b.y = (float)y + 1;

		contourLines.at(level).push_back(line);
		//std::cout << line.a.x << " " << line.a.y << " " << line.b.x << " " << line.b.y << "\n";
	}

	//	Special cases
	else if (loopUpCase == 5) {
		line.a.x = lerp(data->data.at(x).at(y), data->data.at(x + 1).at(y), iso, x, x + 1);
		line.a.y = (float)y;

		line.b.x = (float)x + 1;
		line.b.y = lerp(data->data.at(x + 1).at(y), data->data.at(x + 1).at(y + 1), iso, y, y + 1);

		contourLines.at(level).push_back(line);

		lineSeg lineB;
		lineB.a.x = (float)x;
		lineB.a.y = lerp(data->data.at(x).at(y), data->data.at(x).at(y + 1), iso, y, y + 1);

		lineB.b.x = lerp(data->data.at(x).at(y + 1), data->data.at(x + 1).at(y + 1), iso, x, x + 1);
		lineB.b.y = (float)y + 1;

		contourLines.at(level).push_back(lineB);
	}
	else if (loopUpCase == 10) {
		line.a.x = (float)x;
		line.a.y = lerp(data->data.at(x).at(y), data->data.at(x).at(y + 1), iso, y, y + 1);

		line.b.x = lerp(data->data.at(x).at(y), data->data.at(x + 1).at(y), iso, x, x + 1);
		line.b.y = (float)y;
		contourLines.at(level).push_back(line);

		lineSeg lineB;
		lineB.a.x = lerp(data->data.at(x).at(y + 1), data->data.at(x + 1).at(y + 1), iso, x, x + 1);
		lineB.a.y = (float)y + 1;

		lineB.b.x = (float)x + 1;
		lineB.b.y = lerp(data->data.at(x + 1).at(y), data->data.at(x + 1).at(y + 1), iso, y, y + 1);

		contourLines.at(level).push_back(lineB);
	}
}

void TerrainVisualizer::generateContourLines() {
	//	std::cout << "numsteps = "<<numSteps << "\n";
	contourLines.resize(numSteps);
	int isoVal = low;
	for (int i = 0; i < numSteps; i++) {
		for (int j = 0; j < data->nrows - 1; j++) {
			for (int k = 0; k < data->ncols - 1; k++) {
				int caseNum = getContourCase(
					data->data.at(j).at(k) >= isoVal,
					data->data.at(j + 1).at(k) >= isoVal,
					data->data.at(j).at(k + 1) >= isoVal,
					data->data.at(j + 1).at(k + 1) >= isoVal);
				TerrainVisualizer::makeContourLine(	caseNum, j, k,	(float)isoVal, i);
				//std::cout << contours.at(i).at(j).a.x << " ";//*/
			}
			//std::cout << '\n';
		}
		isoVal += step;
		//std::cout << '\n';
	}
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates such that the window becomes centered
//-------------------------------------------------------------------------
void TerrainVisualizer::centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}

//	TODO:
void TerrainVisualizer::DisplayText() {

}

//-------------------------------------------------------------------------
//  Draws a line from x1,y1 to x2,y2 with color specified by color
//-------------------------------------------------------------------------
void TerrainVisualizer::DrawLine(point a, point b, std::array<float, 3> color) {
	glBegin(GL_LINES);

	glColor3f(color[0], color[1], color[2]);
	glVertex2f(a.x/100, a.y/100);
	glVertex2f(b.x/100, b.y/100);

	glEnd();
}

void TerrainVisualizer::DrawTerrainPolygon() {
	glPushMatrix();
	float rs = 100; //resize ammount. instead of 100x100 it would be 1x1
	for (float i = 0; i < data->nrows - 1; i++) {
		for (float j = 0; j < data->ncols - 1; j++) {
			glBegin(GL_POLYGON);
			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i - data->nrows/2) / rs, (data->data[i][j] - data->lowestValue) / data->range, (j - data->ncols / 2) / rs);

			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i - data->nrows / 2) / rs, (data->data[i][j+1] - data->lowestValue) / data->range, (j+1 - data->ncols / 2) / rs);

			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i+1 - data->nrows / 2) / rs, (data->data[i+1][j+1] - data->lowestValue) / data->range, (j+1 - data->ncols / 2) / rs);

			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i+1 - data->nrows / 2) / rs, (data->data[i+1][j] - data->lowestValue) / data->range, (j - data->ncols / 2) / rs);

			glEnd();
		}
	}
	glPopMatrix();

}

void TerrainVisualizer::DrawTerrainWireframe() {
	glPushMatrix();
	float rs = 100; //resize ammount. instead of 100x100 it would be 1x1
	for (float i = 0; i < data->nrows - 1; i++) {
		glBegin(GL_QUADS);
		for (float j = 0; j < data->ncols - 1; j++) {
			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i - data->nrows / 2) / rs, (data->data[i][j] - data->lowestValue) / data->range, (j - data->ncols / 2) / rs);

			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i + 1 - data->nrows / 2) / rs, (data->data[i + 1][j] - data->lowestValue) / data->range, (j - data->ncols / 2) / rs);

		}
		glEnd();
		glBegin(GL_QUADS);
		for (float j = 1; j < data->ncols; j++) {
			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i - data->nrows / 2) / rs, (data->data[i][j] - data->lowestValue) / data->range, (j - data->ncols / 2) / rs);

			glColor3f(lowColor[0] + (data->data[i][j] - data->lowestValue)* (highColor[0] - lowColor[0]) / data->range
				, lowColor[1] + (data->data[i][j] - data->lowestValue)* (highColor[1] - lowColor[1]) / data->range
				, lowColor[2] + (data->data[i][j] - data->lowestValue)* (highColor[2] - lowColor[2]) / data->range);
			glVertex3f((i + 1 - data->nrows / 2) / rs, (data->data[i + 1][j] - data->lowestValue) / data->range, (j - data->ncols / 2) / rs);

		}
		glEnd();
	}
	glPopMatrix();
}

void TerrainVisualizer::DrawContourLines() {
	for (int i = 0; i < contourLines.size(); i++) {
		for (int j = 0; j < contourLines.at(i).size(); j++) {
			glBegin(GL_LINES);

			glColor3f(lowColor[0] + i * (highColor[0] - lowColor[0]) / numSteps
				, lowColor[1] + i * (highColor[1] - lowColor[1]) / numSteps
				, lowColor[2] + i * (highColor[2] - lowColor[2]) / numSteps);
			glVertex3f((contourLines.at(i).at(j).a.x - data->nrows / 2)/ 100,
				(i*step - data->range)/ data->range + 1,
				(contourLines.at(i).at(j).a.y - data->ncols / 2)/ 100);
			
			glVertex3f((contourLines.at(i).at(j).b.x - data->nrows / 2) / 100,
				(i*step - data->range)/ data->range + 1,
				(contourLines.at(i).at(j).b.y - data->ncols / 2)/ 100);

			glEnd();
		}
	}
}

TerrainVisualizer::TerrainVisualizer(int argc, char **argv)
{
	//	Reads in the command line input. If there isn't 11 args, then the program uses the defaults. 
	//	Where the ned_86879038 is used as the input file.
	bool autoSetVars = false;
	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == "auto") {
			autoSetVars = true;
			std::cout << "Setting auto variables\n";
		}
	}
	/*
	if (argc == 10 || argc == 12) {
		std::string i_fileName;
		int i_low = 0, i_high = 10, i_step = 1;
		std::array<float, 3> i_lowColor = { 0,0,0 };
		std::array<float, 3> i_highColor = { 1,1,1 };
		bool i_marker = true;
		
		int curArgPlace = 1;

		std::cout << std::string(argv[curArgPlace]) + ".hdr" << "\n";
		std::cout << std::string(argv[curArgPlace]) + ".flt" << "\n";

		if (GridFloatData::fileExists(std::string(argv[curArgPlace]) + ".hdr") 
			&& GridFloatData::fileExists(std::string(argv[1]) + ".flt")) {
			fileName = argv[curArgPlace];
		}
		else {
			std::cout << "Error loading input files. Exiting program\n";
		} 
		curArgPlace++;
		if (argc == 12) {
			if (!(std::istringstream(argv[curArgPlace]) >> i_low)) {
				std::cout << "Invalid low. Setting default of " << low << "for low\n";
			}
			else {
				low = i_low;
				std::cout << "low is set to " << argv[curArgPlace] << "\n";
			}
			curArgPlace++;
			if (!(std::istringstream(argv[curArgPlace]) >> i_high)) {
				std::cout << "Invalid low. Setting default of " << high << "for low\n";
			}
			else {
				high = i_high;
				std::cout << "high is set to " << argv[curArgPlace] << "\n";
			}
			curArgPlace++;
			if (!(std::istringstream(argv[curArgPlace]) >> i_step)) {
				std::cout << "Invalid low. Setting default of " << step << "for low\n";
			}
			else {
				step = i_step;
				std::cout << "step is set to " << argv[curArgPlace] << "\n";
			}
		}	
		curArgPlace++;
		
		for (int i = 0; i < 3; i++) {
			if (!(std::istringstream(argv[curArgPlace]) >> i_lowColor[i])) {
				std::cout << "Invalid low. Setting default of " << i_lowColor[i] << "for low\n";
			}
			else {
				lowColor[i] = i_lowColor[i];
				std::cout << "low color is set to " << argv[curArgPlace] << "\n";
			}
			curArgPlace++;
		}
		for (int i = 0; i < 3; i++) {
			if (!(std::istringstream(argv[curArgPlace]) >> i_highColor[i])) {
				std::cout << "Invalid low. Setting default of " << i_highColor[i] << "for low\n";
			}
			else {
				highColor[i] = i_highColor[i];
				std::cout << "high color is set to " << argv[curArgPlace] << "\n";
			}
			curArgPlace++;
		}
		if (!(std::string(argv[curArgPlace]) == "true" || std::string(argv[curArgPlace]) == "false")) {
			std::cout << "Invalid marker. Setting to default value of " << marker << "\n";
		}
		else {
			(std::string(argv[curArgPlace]) == "true") ? marker = true : marker = false;
		}
		curArgPlace++;
	}*/
	
	fileName = "ned_86879038";

	data = new GridFloatData(fileName);

	high = data->highestValue;
	low = data->lowestValue;

	camRight = data->nrows / 12;
	camTop = data->ncols / 12;

	//	Sizes the vectors to the right capacity
	if (step == 0) 
		throw std::overflow_error("Divide by zero exception");
	numSteps = (high - low) / step;

	if (step < 0) {
		numSteps *= -1;
		int temp = low;
		low = high;
		high = temp;
	}
	TerrainVisualizer::generateContourLines();
	
	std::cout << "Number of rows is " << data->nrows << "\nNumber of columns is " << data->ncols << "\n";
	std::cout << "Top right corner elevation " << data->data[0][0] << '\n';
	std::cout << "Bottom left corner elevation " << data->data[data->nrows - 1][data->ncols - 1] << '\n';
	std::cout << "Highest Value = " << data->highestValue << "\n";
	std::cout << "Highest point is x: " << data->posHighestPoint[0] << " y: " << data->posHighestPoint[1] << "\n";
	std::cout << "Number of steps= " << numSteps<< "\n";

	if (data->nrows < max_init_window_height)
		;// window_width = data->nrows;
	if (data->ncols < max_init_window_width)
		;// window_height = data->ncols;
	aspectRatio = (float)data->ncols / data->nrows;
	
	fgRef = this;
}


TerrainVisualizer::~TerrainVisualizer()
{
	
}

//
int main(int argc, char **argv) {
	TerrainVisualizer terViz(argc, argv);

	glutInit(&argc, argv);
	fgRef->centerOnScreen();
	glutInitWindowSize(fgRef->window_width, fgRef->window_height);
	glutInitWindowPosition(fgRef->window_x, fgRef->window_y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(fgRef->window_title);

	//  View in full screen if the fullscreen flag is on
	if (fgRef->full_screen)
		glutFullScreen();

	glEnable(GL_DEPTH_TEST);

	//  Set OpenGL program initial state.
	init();

	// Set the callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	createGLUTMenus();

	std::cout << "\nBeginning Main Glut Loop\n";

	glutMainLoop();


	return 0;
}
