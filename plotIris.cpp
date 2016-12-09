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