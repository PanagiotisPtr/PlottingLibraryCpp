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
vector<point> getPointVec(vector< vector<T> > v){
	assert(v[0].size()==2);
	vector<point> temp;
	for(int i = 0; i < v.size(); i++)temp.push_back(point(v[i][0], v[i][1]));
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
	ppmHeader << "P3\n" << w << '\n' << h << '\n' << maxColorVal << '\n';
	return ppmHeader.str();
}

// Returns Pixels Vector
vector< vector<Color> > getPixelsVector(){
	return vector< vector<Color> > (h, vector<Color>(w));
}

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
			write << pixels[y][x].r << endl;
			write << pixels[y][x].g << endl;
			write << pixels[y][x].b << endl;
		}
	}

	write.close();
}

// Sets vector values and grid to the correct scale so that they display nicely on the image
void setVecToScale(vector<point> &points){
	double Xmax = -99999;
	double Xmin = +99999;
	for(int i = 0; i < points.size(); i++){
		if(points[i].x>Xmax)Xmax=points[i].x;
		if(points[i].x<Xmin)Xmin=points[i].x;
	}
	double Ymax = -99999;
	double Ymin = +99999;
	for(int i = 0; i < points.size(); i++){
		if(points[i].y>Ymax)Ymax=points[i].y;
		if(points[i].y<Ymin)Ymin=points[i].y;
	}
	double gloabalMin = min(Xmin, Ymin);
	double gloabalMax = max(Xmax, Ymax);
	//Set for X
	/*
	       (w-0)(x - min)
	f(x) = --------------  + a
	          max - min
	*/
	for(int i = 0; i < points.size(); i++){
		points[i].x = (int)(((w)*(points[i].x - gloabalMin))/(gloabalMax - gloabalMin));
		points[i].x -= points[i].x>0 ? 1 : 0;
	}

	//Set for Y
	/*
	       (h-0)(y - min)
	f(y) = --------------  + a
	          max - min
	*/
	for(int i = 0; i < points.size(); i++){
		points[i].y = (int)(((h)*(points[i].y - gloabalMin))/(gloabalMax - gloabalMin));
		points[i].y -= points[i].y>0 ? 1 : 0;
	}
}

// Makes cross on pixels
void makeCross(vector< vector<Color> > &pixels, int x, int y, int r, Color c){
	if(x<pixels[0].size() && x>=0 && y<pixels.size() && y>=0)pixels[y][x] = c;
	else return;
	for(int i = 1; i < r; i++){
		if(y+i<pixels.size()){pixels[y+i][x] = c; makeCross(pixels, x, y+i, r*0.15, c);}
		if(x+i<pixels[0].size()){pixels[y][x+i] = c; makeCross(pixels, x+i, y, r*0.15, c);}
		if(x-i>=0){pixels[y][x-i] = c; makeCross(pixels, x-i, y, r*0.15, c);}
		if(y-i>=0){pixels[y-i][x] = c; makeCross(pixels, x, y-i, r*0.15, c);}
		//if(x-i>0 && y-i>0)pixels[y-i][x-i] = c;
		//if(x+i<pixels[0].size() && y+i<pixels.size())pixels[y+i][x+i] = c;
	}
}

// Makes dot on pixels
void makeDot(vector< vector<Color> > &pixels, int x, int y, int r, Color c){
	if(x<pixels[0].size() && x>=0 && y<pixels.size() && y>=0)pixels[y][x] = c;
	else return;
	for(int i = 1; i < r; i++){
		if(y+i<pixels.size()){pixels[y+i][x] = c; makeDot(pixels, x, y+i, r-1, c);}
		if(x+i<pixels[0].size()){pixels[y][x+i] = c; makeDot(pixels, x+i, y, r-1, c);}
		if(x-i>=0){pixels[y][x-i] = c; makeDot(pixels, x-i, y, r-1, c);}
		if(y-i>=0){pixels[y-i][x] = c; makeDot(pixels, x, y-i, r-1, c);}
		//if(x-i>0 && y-i>0)pixels[y-i][x-i] = c;
		//if(x+i<pixels[0].size() && y+i<pixels.size())pixels[y+i][x+i] = c;
	}
}

// Plots points on image
// Example: plotPoints("test.ppm", {{1,2},{3,4}}, 4, Color(255,0,255), "*") //Symbols include (*, +) for Dot and Cross
template <typename T>
void plotPoints(string filename, vector< vector<T> > v, T r, Color c, string type){
	assert(validName(filename));
	vector< vector<Color> > pixels = getPixelsVector();
	vector<point> points = getPointVec(v);
	printPointVec(points); 
	cout << "---------------------" << endl;
	setVecToScale(points);
	printPointVec(points);

	setPixelsToWhite(pixels);

	for(int i = 0; i < points.size(); i++){
		int x = points[i].x;
		int y = points[i].y;
		if(type=="*")makeDot(pixels, x, y, r, c);
		if(type=="+")makeCross(pixels, x, y, r, c);
	}

	cout << "Really?" << endl;

	ofstream write;
	write.open(filename.c_str());

	write << getPPMHeader();

	for(int y = h-1; y >= 0; y--){
		for(int x = 0; x < w; x++){
			write << pixels[y][x].r << endl;
			write << pixels[y][x].g << endl;
			write << pixels[y][x].b << endl;
		}	
	}

	write.close(); 
}

int main(){
	//Testing
	setHeight(256);
	setWidth(256);
	vector< vector<int> > testPoints = {{0,0}, {5,5}, {1,6}, {3,2}, {1,2}, {3,4}, {2,3}, {2,2}, {3,3}, {5,2}, {7,8}};
	plotPoints("testSelectionDot.ppm", testPoints, 4, Color(60,10,255), "*");
	plotPoints("testSelectionCross.ppm", testPoints, 4, Color(60,10,255), "+");
}
