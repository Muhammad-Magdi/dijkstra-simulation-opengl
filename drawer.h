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

	RGB(float r, float g, float b){
		red = r;green = g;blue = b;
	}
};

struct node{
	point location;
	RGB* color;

	node(point p, RGB* c){
		location = p;color = c;
	}

	node(point p){
		location = p;
		color->red = 1.0; color->green = 1.0; color->blue = 1.0;
	}
};

struct edge{
	int src_id, dst_id;
	int cost;
	RGB* color;

	edge(int s, int e, int cst, RGB* c){
		src_id = s;dst_id = e;color = c;cost = cst;
	}

	edge(int s, int e,int cst = 1){
		color->red = 1.0; color->green = 1.0; color->blue = 1.0;
		src_id = s;dst_id = e;cost = cst;
	}
};

class drawer{
private:
	polygon* a = new polygon(15, mp(0, 0), 0.1);
	polygon* mover = new polygon(15, mp(0, 0), 0.05);
	unordered_map<int, node> nodes;
	unordered_map<int, edge> edges;

	void drawNode(int);
	void drawEdge(int);
	void drawMover(point);
	float euclidean_distance(point, point);

public:
	drawer(unordered_map<int, node>&, unordered_map<int, edge>& );
	void updateNodeClr(int, RGB*);
	void updateEdgeClr(int, RGB*);
	void drawGrid(int, int, RGB*);
	void drawPath(vector<int>&);
	void reset(void);
};

#include "drawer.cpp"

#endif