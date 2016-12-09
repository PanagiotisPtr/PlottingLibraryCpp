/*
MIT License

Copyright (c) 2016 Panagiotis Petridis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <bits/stdc++.h>

using namespace std;

int w = 128; // Width
int h = 128; // Height

int maxColorVal = 255; // Maximum Value that each color pixel can have

// Variables to set plot to scale
double Xmax = -99999;
double Xmin = +99999;
double Ymax = -99999;
double Ymin = +99999;


// RGB Color Struct
struct Color{
	double r; // Red
	double g; // Green
	double b; // Blue

	// Default Constructor
	Color(){
		r = 0;
		g = 0;
		b = 0;
	}

	// Constructor with parameters
	template<typename T>
	Color(T rr, T gg, T bb){
		r = (double)rr;
		g = (double)gg;
		b = (double)bb;
	}
};

// 2D point struct
struct point{
	double x;
	double y;

	// Default constructor
	point(){ x = 0; y = 0; }

	// Constructor with parameters
	template<typename T>
	point(T a, T b){ x = a; y = b; }
};

// Converts 2D vector to point vector
template <typename T>
vector<point> getPointVec(vector< vector<T> > v, int xAxis, int yAxis){
	vector<point> temp;
	for(int i = 0; i < v.size(); i++)temp.push_back(point(v[i][xAxis], v[i][yAxis]));
	return temp;
}

//Check if filename is valid
bool validName(string filename){
	return (filename.find(".ppm")==filename.size()-4);
}

// Sets color of all Pixels to white
void setPixelsToWhite(vector< vector<Color> > &pixels){
	for(int i = 0; i < pixels.size(); i++){
		for(int j = 0; j < pixels[i].size(); j++){
			pixels[i][j].r = 255;
			pixels[i][j].g = 255;
			pixels[i][j].b = 255;
		}
	}
}

// Prints point vector
void printPointVec(vector<point> a){ for(int i = 0; i < a.size(); i++)cout << "x: " << a[i].x << "\t" << "y: " << a[i].y << endl; }

// Returns PPM file Header
string getPPMHeader(){
	ostringstream ppmHeader;
	ppmHeader << "P3\n" << w << endl << h << endl << maxColorVal << endl;
	return ppmHeader.str();
}

// Gets a string version of everything that needs to be printed
string getPixelsPrintString(vector< vector<Color> > &pixels){
	ostringstream pixelsString;

	for(int y = h-1; y >= 0; y--){
		for(int x = 0; x < w; x++){
			pixelsString << pixels[y][x].r << endl;
			pixelsString << pixels[y][x].g << endl;
			pixelsString << pixels[y][x].b << endl;
		}	
	}

	return pixelsString.str();
}

// Returns Pixels Vector
vector< vector<Color> > getPixelsVector(){ return vector< vector<Color> > (h, vector<Color>(w)); }

// Sets image width
template<typename T>
void setWidth(T a){ w = a; }

// Sets image height
template<typename T>
void setHeight(T a){ h = a; }

// Tests that everything works properly
void testPlot(string filename){
	assert(validName(filename));
	vector< vector<Color> > pixels = getPixelsVector();
	ofstream write;
	write.open(filename.c_str());

	// Write PPM header 
	write << getPPMHeader();

	for(int y = 0; y < h; y++){
		for(int x = 0; x < w; x++){
			pixels[y][x].r = 255;
			pixels[y][x].g = 0;
			pixels[y][x].b = 255;
		}
	}

	write << getPixelsPrintString(pixels);

	write.close();
}

// Sets Global Minimum and Maximum Values
void setMinMaxScalers(vector<point> points){
	for(int i = 0; i < points.size(); i++){
		if(points[i].x>Xmax)Xmax=points[i].x;
		if(points[i].x<Xmin)Xmin=points[i].x;
	}
	for(int i = 0; i < points.size(); i++){
		if(points[i].y>Ymax)Ymax=points[i].y;
		if(points[i].y<Ymin)Ymin=points[i].y;
	}
}

// Sets vector values and grid to the correct scale so that they display nicely on the image
void setVecToScale(vector<point> &points){
	for(int i = 0; i < points.size(); i++){
		points[i].x = (int)(((w)*(points[i].x - Xmin))/(Xmax - Xmin));
		points[i].x -= points[i].x>0 ? 1 : 0;
	}

	for(int i = 0; i < points.size(); i++){
		points[i].y = (int)(((h)*(points[i].y - Ymin))/(Ymax - Ymin));
		points[i].y -= points[i].y>0 ? 1 : 0;
	}
}

// Makes cross on pixels
void makeCross(vector< vector<Color> > &pixels, int x, int y, double r, Color c){
	if(x<pixels[0].size() && x>=0 && y<pixels.size() && y>=0)pixels[y][x] = c;
	else return;
	for(int i = 1; i < r; i++){
		if(y+i<pixels.size()){pixels[y+i][x] = c; makeCross(pixels, x, y+i, r*0.15, c);}
		if(x+i<pixels[0].size()){pixels[y][x+i] = c; makeCross(pixels, x+i, y, r*0.15, c);}
		if(x-i>=0){pixels[y][x-i] = c; makeCross(pixels, x-i, y, r*0.15, c);}
		if(y-i>=0){pixels[y-i][x] = c; makeCross(pixels, x, y-i, r*0.15, c);}
	}
}

// Makes dot on pixels
void makeDot(vector< vector<Color> > &pixels, int x, int y, double r, Color c){
	if(x<pixels[0].size() && x>=0 && y<pixels.size() && y>=0)pixels[y][x] = c;
	else return;
	for(int i = 1; i < r; i++){
		if(y+i<pixels.size()){pixels[y+i][x] = c; makeDot(pixels, x, y+i, r-1, c);}
		if(x+i<pixels[0].size()){pixels[y][x+i] = c; makeDot(pixels, x+i, y, r-1, c);}
		if(x-i>=0){pixels[y][x-i] = c; makeDot(pixels, x-i, y, r-1, c);}
		if(y-i>=0){pixels[y-i][x] = c; makeDot(pixels, x, y-i, r-1, c);}
	}
}

// Adds Grid to plot
void addGridToPlot(vector< vector<Color> > &pixels){
	for(int y = h-1; y >= 0; y--){
		for(int x = 0; x < w; x++){
			if(x%((int)w/10)==0 || y%((int)h/10)==0){
				pixels[y][x].r = 180;
				pixels[y][x].g = 180;
				pixels[y][x].b = 180;
			}
		}	
	}
}

// Prints empty image with grid
void plotTestGrid(string filename){
	assert(validName(filename));
	vector< vector<Color> > pixels = getPixelsVector();
	setPixelsToWhite(pixels);
	addGridToPlot(pixels);
	ofstream write;
	write.open(filename.c_str());

	write << getPPMHeader();
	write << getPixelsPrintString(pixels);

	write.close();
}

// Plots Points on image
template <typename T>
void plotPoints(string filename, vector< vector< vector<T> > > vVec, int xAxis, int yAxis, double r, vector<Color> cVec, vector<string> typeVec){
	assert(validName(filename));
	vector< vector<Color> > pixels = getPixelsVector();
	setPixelsToWhite(pixels);
	addGridToPlot(pixels);

	Xmax = -99999;
	Xmin = +99999;
	Ymax = -99999;
	Ymin = +99999;

	for(int i = 0; i < vVec.size(); i++)setMinMaxScalers(getPointVec(vVec[i], xAxis, yAxis));

	for(int i = 0; i < vVec.size(); i++){
		vector<point> points = getPointVec(vVec[i], xAxis, yAxis);
		setVecToScale(points);
		string type = typeVec[i];
		Color c = cVec[i];
		for(int i = 0; i < points.size(); i++){
			int x = points[i].x;
			int y = points[i].y;
			if(type=="*")makeDot(pixels, x, y, r, c);
			if(type=="+")makeCross(pixels, x, y, r, c);
		}
	}

	ofstream write;
	write.open(filename.c_str());

	write << getPPMHeader();
	write << getPixelsPrintString(pixels);

	write.close(); 
}

// adds thicknss to pixels
void paintUpDownOnPixels(int x, int y, int thickness, Color c, vector< vector<Color> > &pixels){
	for(int i = 1; i <= thickness; i++){
		if(y+i<pixels.size())pixels[y+i][x] = c;
		if(y-i>=0)pixels[y-i][x] = c;
		if(x+i<pixels.size())pixels[y][x+i] = c;
		if(x-i>=0)pixels[y][x-i] = c;
		if(x-i>=0 && y-i>=0)pixels[y-i][x-i] = c;
		if(x+i<pixels.size() && y+i<pixels.size())pixels[y+i][x+i] = c;
	}
}

// Draws Line on Pixels
void makeLineOnPixels(int x1, int y1, int x2, int y2, Color c, double r, vector< vector<Color> > &pixels){
	double dx = x2 - x1;
	double dy = y2 - y1;
	int x = x1;
	while(x != x2){
		int y = y1 + dy * (x-x1)/dx;
		pixels[y][x] = c;
		paintUpDownOnPixels(x, y, r, c, pixels);
		x = x>x2 ? x-1 : x+1;
	}
}

template <typename T>
void plotLine(string filename, vector< vector< vector<T> > > vVec, int xAxis, int yAxis, double r, vector<Color>cVec){
	assert(validName(filename));
	vector< vector<Color> > pixels = getPixelsVector();
	setPixelsToWhite(pixels);
	addGridToPlot(pixels);

	Xmax = -99999;
	Xmin = +99999;
	Ymax = -99999;
	Ymin = +99999;

	for(int i = 0; i < vVec.size(); i++)setMinMaxScalers(getPointVec(vVec[i], xAxis, yAxis));
	
	for(int vi = 0; vi < vVec.size(); vi++){
		vector<point> points = getPointVec(vVec[vi], xAxis, yAxis);
		setVecToScale(points);
		Color c = cVec[vi];
		for(int i = 1; i < points.size(); i++){
			if(i==0)makeLineOnPixels(0, 0, points[i].x, points[i].y, c, r, pixels);
			else makeLineOnPixels(points[i-1].x, points[i-1].y, points[i].x, points[i].y, c, r, pixels);
		}
	}

	ofstream write;
	write.open(filename.c_str());

	write << getPPMHeader();
	write << getPixelsPrintString(pixels);

	write.close();

}