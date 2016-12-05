# Plotting Library Cpp
Simple Plotting Library for C++

###What's this project all about?
This is a simple plotting library that I wrote mostly for myself in C++. The Purpose of it is to be a light header-only library 
to allow easy plotting in C++.

###The Code
The Code has been tested on Linux Ubuntu 16.04 with C++11. You should be able to replicate the results yourself just by pulling the repository and compiling the plot.cpp file.

Note: The images are all saved as .ppm files.

Quick Exampels:

![alt tag](https://s14.postimg.org/6mxa1b2sh/test_Selection_Cross.png)
![alt tag](https://s14.postimg.org/sndmhxlgh/test_Selection_Dot.png)

Example Code for the above plots:

```cpp
int main(){
	setHeight(256);
	setWidth(256);
	vector< vector<int> > testPoints = {{0,0}, {5,5}, {1,6}, {3,2}, {1,2}, {3,4}, {2,3}, {2,2}, {3,3}, {5,2}, {7,8}};
	plotPoints("testSelectionDot.ppm", testPoints, 4, Color(60,10,255), "*");
	plotPoints("testSelectionCross.ppm", testPoints, 4, Color(60,10,255), "+");
}
```



Panagiotis Petridis, High School Student

Greece

If you have an opening in your team be sure to shoot me an email!
