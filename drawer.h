#ifndef DRAWER_H
#define DRAWER_H

#include <bits/stdc++.h>
#include "polygon.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;


struct RGB{
	float red, green, blue;

	RGB(float r = 1, float g = 1, float b = 1){
		red = r;green = g;blue = b;
	}

	RGB(int r, int g, int b){
		red = r/255.0, green = g/255.0, blue = b/255.0;
	}
};

struct node{
	point location;
	RGB color;

	node(){}

	node(point p, RGB c){
		location = p;color = c;
	}

	node(point p){
		location = p;
	}
};

struct edge{
	int src_id, dst_id;
	int cost;
	RGB color;

	edge(){}

	edge(int s, int e, int cst, RGB c){
		src_id = s;dst_id = e;color = c;cost = cst;
	}

	edge(int s, int e, int cst = 1){
		src_id = s;dst_id = e;cost = cst;
		color = RGB(1.0f, 1.0f, 1.0f);
	}

};

class drawer{
private:
	polygon* a = new polygon(15, mp(0, 0), 0.1);
	polygon* mover = new polygon(15, mp(0, 0), 0.05);
	unordered_map<int, node> nodes;
	unordered_map<int, edge> edges;

	vector<int> path;
	point mover_location;

	void drawNode(int);
	void drawEdge(int);
	void drawMover(point);
	float euclidean_distance(point, point);

public:
	drawer(unordered_map<int, node>&, unordered_map<int, edge>& );
	void updateNodeClr(int, RGB);
	void updateEdgeClr(int, RGB);
	void drawGrid(int, int, RGB);
	void drawPath();
	void setPath(vector<int>);
	void reset(void);
	bool isDrawing();
	void renderbitmap(float x, float y, float z, void *font, string s); //show the characters in its position on the screen
};

#include "drawer.cpp"

#endif
