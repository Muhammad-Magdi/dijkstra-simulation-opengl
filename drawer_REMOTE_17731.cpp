// public methods
drawer::drawer(unordered_map<int, node>& ns, unordered_map<int, edge>& es){
	// role : constructor for class drawer
	// in   : unorderd_map<node>& ns --> description of graph nodes.
	//        unorderd_map<edge>& es --> descrption of graph edges
	nodes = ns;
	edges = es;
}

void drawer::updateNodeClr(int id, RGB* c){
	// role : updates the color of the node with the given id with the given color, and draw it.
	// in   : int id --> id of the node to change its color
	//        RGB c  --> new color to be assigned to the node with the given id
	// out  : void
	nodes[id].color = c;
	this->drawNode(id);
}

void drawer::updateEdgeClr(int id, RGB* c){
	// role : updates the color of the edge with the given id with the given color, and draw it.
	// in   : int id --> id of the edge to change its color
	//        RGB c  --> new color to be assigned to the edge with the given id
	// out  : void
	edges[id].color = c;
	this->drawEdge(id);
}

void drawer::drawGrid(int x_limit, int y_limit, RGB* color){
	// rule : draws a grid for visual and testing purposes only.
	// in   : x_limit --> max value to be displayed for x, e.g. -x_limit <= x <= x_limit
	//        x_limit --> max value to be displayed for y, e.g. -y_limit <= y <= y_limit
	//        color   --> color of lines in the grid
	// out  : void
	glPushMatrix();
	glBegin(GL_LINES);
	glLineWidth(0.1);
	for(int i = -x_limit;i <= x_limit;i++){
		glVertex3f(i, y_limit, -10.0);
		glVertex3f(i, -y_limit, -10.0);
	}

	for(int i = -y_limit;i <= y_limit;i++){
		glVertex3f(x_limit, i, -10.0);
		glVertex3f(-x_limit, i, -10.0);
	}
	glPopMatrix();
}

void drawer::reset(){
	// role : display the current state of the graph
	// in   : void
	// out  : void
	for(auto n: nodes)
		this->drawNode(n.X);

	for(auto e:edges)
		this->drawEdge(e.X);
}


void drawer::drawPath(vector<int>& path){
	// role : draw the path given in ther parameter list
	// in   : vector<int>& path --> vector of integers, each of which is the id for a node on the path to be displayed
	// out  : void

	// step  : it's the distance moved by our moving node after each iteration
	// theta : the slope angle of the current line to be traced (radians)
	// delay_loops : number of loops spent as "nop"
	float step = 0.1, theta;
	int delay_loops = 1000;
	point cur_node = nodes[*(path.begin())].location;   // read the first point 
	this->drawMover(cur_node);                          // draw our mover at this location
	path.erase(path.begin());                           // erase the first node in the vector
	while(path.size() > 0){
		// update current position
		point target_node = nodes[*(path.begin())].location; // read the first point in vector and take it as current target
		// if target is reached
		if(euclidean_distance(target_node, cur_node) <= 0.1){
			cur_node = target_node;  // set current node to target
			path.erase(path.begin());// remove target
		}else{ // otherwise
			// compute theta
			theta = atan((cur_node.Y - target_node.Y)/(cur_node.X - target_node.X));
			// update current node co-ordinates
			cur_node.X += step * cos(theta);
			cur_node.Y += step * sin(theta);
		}
		// draw current node position
		this->drawMover(cur_node);

		// add delay
		int cnt = delay_loops;
		while(cnt--);
	}
}

// helper functions
float euclidean_distance(point s, point e){
	return sqrt((s.X - e.X)*(s.X - e.X) + (s.Y - e.Y)*(s.Y - e.Y));
}

// private methods
void drawer::drawMover(point loc){
	// role : draw the moving node that moves from source point to destination point
	// in   : point loc --> the position to draw the image in
	// out  : void
	glPushMatrix();
	glTranslatef(loc.X, loc.Y, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	mover->draw();
	glPopMatrix();
}

void drawer::drawNode(int id){
	// role : draw the node with the given id
	// in   : int id --> the id of the node to be drawn
	// out  : void
	node cur = nodes[id];
	glPushMatrix();
	glTranslatef(cur.location.X, cur.location.Y, 0.0);
	glColor3f(cur.color->red, cur.color->green, cur.color->blue);
	a->draw();
	glPopMatrix();
}

void drawer::drawEdge(int id){
	// role : draw the edge with the given id
	// in   : int id --> the id of the node to be diaplayed
	// out  : void
	edge e = edges[id];
	point src = this->nodes[e.src_id].location,
	      dst = this->nodes[e.dst_id].location;
	RGB* color = e.color;

	glPushMatrix();
	glBegin(GL_LINES);
	glLineWidth(0.1);
	glColor3f(color->red, color->green, color->blue);
	glVertex3f(src.X, src.Y, -10.0);
	glVertex3f(dst.X, dst.Y, -10.0);
	glPopMatrix();
}