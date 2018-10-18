#include <GL/glut.h>
#include "drawer.h"

using namespace std;

const int N = 1e2+5, M = 1e5+5, OO = 0x3f3f3f3f;

int n, m, u, v, c, q, src;
vector<pair<int, int> > adj[N];
map<pair<int, int>, int> edgeID;
unordered_map<int, node>  nodes;
unordered_map<int, edge> edges;
int dis[N], parent[N];

bool busy;

struct event{
	bool isNode;
	int id;
	RGB color;
	event(){}
	event(bool _isNode, int _id, RGB _color){
		isNode = _isNode;
		id = _id;
		color = _color;
	}
};

vector<event> events;

drawer* dr;
vector<int> path;

void Dijkstra();
void BFS();
void display();
void getPath(int v);

// interrupt functions
void handleKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);
void timer(int);
void timer1(int);
void initRendering();

int main(int argc, char** argv) {
	// freopen("i.in", "r", stdin);
	// reading graph descrption
	cout << "Welcome to dijkstra simulator\n";
	cout << "enter number of nodes : ";cin >> n;
	cout << "enter number of edges : ";cin >> m;
	cout << "enter source node id  : ";cin >> src;

	cout << "enter " << m << " egdes.\nfor each you are to enter Start_node end_node edge_cost\n";
	for(int i = 0 ; i < m ; ++i){
		printf("enter data for %d edge : ", i + 1);
		scanf("%d %d %d", &u, &v, &c);
		adj[u].push_back({v, c});
		adj[v].push_back({u, c});
		edges[i] = edge(u, v, c);
		edgeID[{u, v}] = edgeID[{v, u}] = i;
	}

	// assign points to nodes such that nodes with same level of BFS have same x_axis value,
	// and spreded on y_axis based on their number
	BFS();

	// initialize the drawing object
	dr = new drawer(nodes, edges);
	
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Set the window size
	
	//Create the window
	glutCreateWindow("Dijkstra simulator");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(0, timer1, 0);

	// make the dijkstra preprocessing
	printf("starting dijkstra simulation\n");
	Dijkstra();

	// display();
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0;
}

void display() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	// add some nice caption
	glColor3f(0.0, 1.0, 0.0);
	dr->renderbitmap(-2.0, 3.0, -10.0, GLUT_BITMAP_HELVETICA_18, "GLUT dijkstra simulation");

	dr->reset();
	dr->drawPath();

	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers(); //Send the 3D scene to the screen
}

void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
	glutPostRedisplay();
	//cout << "key = " << key << " pressed" << endl;
	switch (key){
		case 13:	//Enter Key
			if(!busy && !dr->isDrawing()){
				cout << "==============================================\n";
				cout << "Enter The destination node number: ";
				cin >> v;
				if(v < 1 || v > n){
					printf("point out of range\n");
					break;
				}
				getPath(v);
				dr->setPath(path);
			}
			break;
		case 27: //Escape key
			printf("escape\n");
			exit(0); //Exit the program
			break;
	}
}

int i;
int counter = 0;

void timer1(int){
	glutPostRedisplay();
	glutTimerFunc(100, timer1, 0);
	// this part should only work during simulation phase
	if(counter % 5 == 0 && events.size() > 0){
		busy = 1;
		switch (events.begin()->isNode) {
			case 1:	dr->updateNodeClr(events[i].id, events.begin()->color);
				break;
			case 0:	dr->updateEdgeClr(events[i].id, events.begin()->color);
		}
		events.erase(events.begin());
		counter++;
	}else if(events.size() > 0){
		counter++;
	}else{
		busy = 0;
	}
}

void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
		(double)w / (double)h, //The width-to-height ratio
		1.0,                   //The near z clipping coordinate
		200.0);                //The far z clipping coordinate
}


void Dijkstra(){
	priority_queue<pair<int, int> > q;
	memset(dis, OO, sizeof dis);
	dis[src] = 0;
	parent[src] = -1;
	q.push({0, src});
	while(!q.empty()){
		int u = q.top().second, d = -q.top().first;
		q.pop();
		if(dis[u] < d)  continue;
		if(u != src){
			events.push_back(event(0, edgeID[{parent[u], u}], RGB(255, 0, 255)));
		}
		events.push_back(event(1, u, RGB(62, 105, 144)));
		display();
		for(pair<int, int> e : adj[u]){
			int v = e.first, c = e.second;
			if(dis[v] > dis[u] + c){
				events.push_back(event(0, edgeID[{u, v}], RGB(0.5f, 0.5f, 0.5f)));
				display();
				dis[v] = dis[u] + c;
				q.push({-dis[v], v});
				parent[v] = u;
			}
		}
	}
}

void BFS(){     //used to classify the nodes into levels to be displayed
	queue<int> q;
	int level[N], levelNodes[10] = {}, levelDrawn[10] = {};
	memset(level, OO, sizeof level);
	level[src] = 0;
	levelNodes[0] = 1;
	q.push(src);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		nodes[u] = node(point(level[u]-3, (-levelNodes[level[u]])/2+levelDrawn[level[u]]++));
		for(pair<int, int> p : adj[u]){
			v = p.first;
			if(level[v] == OO){
				level[v] = level[u]+1;
				levelNodes[level[v]]++;
				q.push(v);
			}
		}
	}
}

void getPath(int v){
	path.clear();
	while(~v){
		path.push_back(v);
		v = parent[v];
	}
	reverse(path.begin(), path.end());
}
