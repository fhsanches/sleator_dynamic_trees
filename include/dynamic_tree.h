//typedef path;
//typedef vertex;

//Path* splice(Path *p);
//Path* expose(Vertex *v);

Vertex* parent(Vertex *v);
Vertex* root(Vertex *v);
double cost(Vertex *v);
Vertex* mincost(Vertex *v);
void update(Vertex *v, double x);
void link(Vertex *v, Vertex *w, double x);
double cut(Vertex *v);
void evert(Vertex *v);
int weight(Vertex *v);

Vertex** top_light(Vertex *v);
Vertex** heavy_path(Vertex *v);
Vertex** list_nodes(Vertex *v);
