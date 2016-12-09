#include <bits/stdc++.h>
#include "plot.h"

using namespace std;

int main(){
	setHeight(1024);
	setWidth(1024);
	vector< vector<int> > testLine = {{0,0},{1,2},{2,4},{4,8},{8,16}}; // y = x*2
	vector< vector<int> > testLineWeird = {{0,0},{1,2},{2,4},{4,3},{8,16}};
	vector< vector<int> > testPoints = {{0,0}, {5,5}, {1,6}, {3,2}, {1,2}, {3,4}, {2,3}, {2,2}, {3,3}, {5,2}, {7,8}};
	vector< vector<int> > parabola;
	for(int i = 0; i <= 100; i++)parabola.push_back({i, i*i});

	// In order to make a plot we need to put each one of our parameters in a vector. So that we can plot multiple
	// point groups with different colors as well as get a bit more flexibility

	// Here are some quick examples

	plotPoints("selectionDotWithGrid.ppm", vector< vector< vector<int> > >{testPoints}, 0, 1, 7, vector<Color>{Color(60,10,255)}, vector<string>{"*"});
    plotPoints("selectionCrossWithGrid.ppm", vector< vector< vector<int> > >{testPoints}, 0, 1, 7, vector<Color>{Color(60,10,255)}, vector<string>{"+"});
	plotLine("testLinePlotParabola.ppm", vector< vector< vector<int> > >{parabola}, 0, 1, 1, vector<Color>{Color(60,10,255)});
	plotPoints("groupPointPlot.ppm", vector< vector< vector<int> > >{testPoints, testLineWeird}, 0, 1, 	6, vector<Color>{Color(60,10,255), Color(255,10,60)}, vector<string>{"*","*"});
}