# Plotting Library Cpp
Simple Plotting Library for C++

### What's this project all about?
This is a simple plotting library that I wrote mostly for myself in C++. The Purpose of it is to be a light header-only library 
to allow easy plotting in C++.

### The Code
The Code has been tested on Linux Ubuntu 16.04 with C++11. You should be able to replicate the results yourself just by pulling the repository and compiling the plot.cpp file.

Note: The images are all saved as .ppm files.

Example plots:

<img src="https://s12.postimg.org/3s6da9p8d/group_Point_Plot.png" width="250" height="250">
<img src="https://s12.postimg.org/ueitz8tfh/test_Line_Plot.png" width="250" height="250">
<img src="https://s12.postimg.org/hbn7fz37h/test_Line_Plot_Parabola.png" width="250" height="250">

Example Code:

```cpp
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
```

Plotting the Iris Dataset:

<img src="https://s16.postimg.org/r5ts860n9/Iris_Petal_Length_Sepal_Length.png" width="768" height="512">

```cpp
#include <bits/stdc++.h>
#include "plot.h"

using namespace std;

/*
1. sepal length in cm
2. sepal width in cm
3. petal length in cm
4. petal width in cm
5. class:
	Iris-setosa --> 0
	Iris-versicolor --> 1
	Iris-virginica --> 2
*/

int main(){
	// Create containers to store each class
	//50 samples for each class. Each one with 4 Features + class Label
	vector< vector<double> > Iris_setosa(50, vector<double>(5));
	vector< vector<double> > Iris_versicolor(50, vector<double>(5));
	vector< vector<double> > Iris_virginica(50, vector<double>(5));

	// Choose colors to represent each class
	Color setosaColor(60,20,180);
	Color versicolorColor(180,20,60);
	Color virginicaColor(20,180,60);

	// Read data to stdin
	freopen("iris.data", "r", stdin); // Read data to stdin

	// Fill each container
	// 150 train samples
	for(int sample = 0; sample < 150; sample++){
		// 4 Features + Class Label
		for(int feature = 0; feature < 5; feature++){
			if(sample<50)cin >> Iris_setosa[sample][feature];
			else if(sample<100)cin >> Iris_versicolor[sample%50][feature];
			else if(sample<150)cin >> Iris_virginica[sample%100][feature];
		}
	}
	// Set Width and height of plot
	setHeight(512);
	setWidth(512+256);
	
	// In this tutorial we will be plotting the "petal length" against the "sepal length" for each sample
	// First since we are creating a GroupPlot let's add our colors, symbols and data into containers
	vector< vector< vector<double> > > plotData = {Iris_setosa, Iris_versicolor, Iris_virginica};
	vector<Color> colors = {setosaColor, versicolorColor, virginicaColor};
	vector<string> symbols = {"*","*","*"};

	// Now let's plot the graph
	// Filename, DataVector, xAxis, yAxis, dotSize, colorVector, Symbols
	plotPoints("Iris.PetalLength.SepalLength.ppm", plotData, 0, 2, 4, colors, symbols);
}
```


Panagiotis Petridis, High School Student

Greece

If you have an opening in your team be sure to shoot me an email!


