// #include <bits/stdc++.h>
#include <GL/glut.h>
#include "drawer.h"

using namespace std;

const int N = 1e2+5, M = 1e5+5, OO = 0x3f3f3f3f;

int n, m, u, v, c, q, src;
vector<pair<int, int> > adj[N];

map<pair<int, int>, int> edgeID;
int dis[N];

/*
  Edge Color:
    default = grey
    in queue = while
    used in relaxation = red
  Node Color:
    default = white
    final state = blue
*/
void Dijkstra(drawer dr){
  priority_queue<pair<int, int> > q;
  memset(dis, OO, sizeof dis);
  dis[src] = 0;
  q.push({0, src});
  while(!q.empty()){
    int u = q.top().second, d = -q.top().first;
    q.pop();
    if(dis[u] < d)  continue;
    //Update node color
    //update edge color
    for(pair<int, int> e : adj[u]){
      int v = e.first, c = e.second;
      if(dis[v] > dis[u] + c){
        //update edgeID[{u, v}] color
        dis[v] = dis[u] + c;
        q.push({-dis[v], v});
      }
    }
  }
}

unordered_map<int, node>  nodes;
unordered_map<int, edge> edges;

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

int main(int argc, char** argv) {
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("Here's Dijkstra"); // Create a window with the given title
  // glutDisplayFunc(display); // Register display callback handler for window re-paint
  cin >> n >> m >> src;
  for(int i = 0 ; i < m ; ++i){
    cin >> u >> v >> c;
    edges[i] = edge(u, v, c);
    edgeID[{u, v}] = i;
    adj[u].push_back({v, c});
  }
  drawer dr(nodes, edges);
  BFS();
  Dijkstra(dr);
  cin >> q;
  while(q--){
    cin >> v;

  }
  // glutMainLoop();           // Enter the infinitely event-processing loop
  return 0;
}
