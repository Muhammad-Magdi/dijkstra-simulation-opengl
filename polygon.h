#ifndef MY_POLYGON_H
#define MY_POLYGON_H

#include <bits/stdc++.h>

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define point pair<float, float>
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define PI 3.14159265359
#define rep(i, n) for(int i = 0;i < n;i++)

class polygon{
	// this class holds the data for a regular polygon
private:
	point center;
	float length;
	int vertices;
	vector<point> v;

	void __compute_vertices(point start);
public:
	polygon(int n, point c, float l);
	void draw(float lvl);
	void move(point change);
};

#include "polygon.cpp"

#endif