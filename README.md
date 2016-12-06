# Plotting Library Cpp
Simple Plotting Library for C++

###What's this project all about?
This is a simple plotting library that I wrote mostly for myself in C++. The Purpose of it is to be a light header-only library 
to allow easy plotting in C++.

###The Code
The Code has been tested on Linux Ubuntu 16.04 with C++11. You should be able to replicate the results yourself just by pulling the repository and compiling the plot.cpp file.

Note: The images are all saved as .ppm files.

Quick Exampels:

<img src="https://s12.postimg.org/3s6da9p8d/group_Point_Plot.png" width="250" height="250">
<img src="https://s12.postimg.org/ueitz8tfh/test_Line_Plot.png" width="250" height="250">
<img src="https://s12.postimg.org/hbn7fz37h/test_Line_Plot_Parabola.png" width="250" height="250">

Example Code for the above plots:

```cpp
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
```



Panagiotis Petridis, High School Student

Greece

If you have an opening in your team be sure to shoot me an email!

