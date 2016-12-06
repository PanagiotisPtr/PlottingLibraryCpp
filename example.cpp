#include <bits/stdc++.h>
#include "plot.h"

using namespace std;

int main(){
	//Testing
	setHeight(512);
	setWidth(512);
	vector< vector<int> > testLine = {{0,0},{1,2},{2,4},{4,8},{8,16}}; // y = x*2
	vector< vector<int> > testLineWeird = {{0,0},{1,2},{2,4},{4,3},{8,16}};
	vector< vector<int> > testPoints = {{0,0}, {5,5}, {1,6}, {3,2}, {1,2}, {3,4}, {2,3}, {2,2}, {3,3}, {5,2}, {7,8}};
	vector< vector<int> > parabola;
	for(int i = 0; i <= 100; i++)parabola.push_back({i, i*i});

	plotPoints("selectionDotWithGrid.ppm", testPoints, 3, Color(60,10,255), "*");
    	plotPoints("selectionCrossWithGrid.ppm", testPoints, 5, Color(60,10,255), "+");
    	plotLine("testLinePlotParabola.ppm", parabola, 1, Color(60,10,255));
	plotPoints("groupPointPlot.ppm", vector< vector< vector<int> > >{testPoints, testLineWeird}, 5, vector<Color>{Color(60,10,255), Color(255,10,60)}, vector<string>{"*","*"});
}
