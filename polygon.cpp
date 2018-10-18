polygon::polygon(int n, point c, float l){
	/**
	n : number of vertices
	c : center of ploygon
	l : length of polygon
	*/
	vertices = n;
	center = c;
	length = l;

	float angle = (n - 2) * 90.0 / n;
	float h = l * tan(angle * PI / 180.0) / 2;
	//printf("angle = %f, h = %f\n",angle, h);

	point s = mp(center.X - l/2.0, center.Y - h);
	__compute_vertices(s);
}

void polygon::__compute_vertices(point start){
	v.clear();
    point tmp;        // create a tmp point
    v.pb(start);      // add the start point to the vector
	float angle, theta = 180 - ((vertices - 2) * 180) / vertices; 
    for(int i = 0;i < vertices - 1;i++){
        angle = i * theta; // get value of angle
        tmp.X = start.X + length * cos(angle * PI / 180); // compute X value of next point
        tmp.Y = start.Y + length * sin(angle * PI / 180); // compute Y value of next point
        v.pb(tmp);                                   // add computed point to vector v
        start = tmp;                                 // set start to hold the new computed point
    }
    //for(auto cur : v)
    //	printf("point : %f %f\n", cur.X, cur.Y);
}

void polygon::move(point change){
	glTranslatef(change.X, change.Y, 0);
	draw(-10.0);
}

void polygon::draw(float lvl){
	// draw the polygon
    glBegin(GL_POLYGON);
        for(auto cur: v)
            glVertex3f(cur.X, cur.Y, lvl);
    glEnd();
}