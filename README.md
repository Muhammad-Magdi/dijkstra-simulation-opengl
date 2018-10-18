# Dijkstra-Simulation-OpenGL
A simulation for Dijkstra algorithm using OpenGL

# How it works:
the program works on a single graph, the graph must be entered when first running the program, by entering 
the number of nodes (n), edges (m) and source point, then in the next m lines each edge is entered (start node, end node, cost)
after that the program starts by showing how the dijkstra algorithm step by step to find the shortest path from
source to all points in the graph, edges and nodes are coloered during the process, explored nodes are colored in blue,
and egdes that participated in relaxation are violet, and edges that has no effect on the shortest path are colored as gray.
once the simulation is over you can hit enter to make a query, in the terminal you would be asked to enter the target node,
the simulation will then display a green node moving from start node to end node.

# running images
![dijkstra simulation](https://github.com/Muhammad-Magdi/Dijkstra-Simulation-OpenGL/blob/master/dijkstra1.png)
![finding the path](https://github.com/Muhammad-Magdi/Dijkstra-Simulation-OpenGL/blob/master/run.png)

# future work
1 - adding graph nodes by mouse click.  
2 - adding graph edges by clicking two nodes.  
3 - make query from any point to any point.  
4 - requesting a query by clicking the source node and target node.  
