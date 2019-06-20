typedef struct node_st {
	int external;
	struct node_st *bparent;
	int rank;

	int weight; //external nodes only
	//wt(v) = size(v) if no solid edge enters v (ergo, bparent(v) == null)
	// size(v) - size(w) if the solid edge (w,v) enters v

	//internal nodes only
	//prolly should be in a separate structure but I'm so lazy...

	struct node_st *bleft, *bright, *bhead, *btail;
	int reversed;

	int netcost;
	int netmin;

	//vertex data
	struct node_st *dparent; //originally vertex_st
	double dcost;
  
} Node;

/* #define Path Node */
/* #define Vertex Node */

typedef Node Path;
typedef Node Vertex;

typedef struct quadruple_st{
	Path *p, *q;
	double x, y;  
} Quadruple;

//nodes
int grosscost(Vertex *v);
int grossmin(Vertex *v);

Path* splice(Path *p);
Path* expose(Vertex *v);

//paths
Path *path(Vertex *v);
Vertex *head(Path *p);
Vertex *tail(Path *p);
Vertex *before(Vertex *v);
Vertex *after(Vertex *v);
int pcost(Vertex *v);
Vertex *pmincost(Path *p);
void pupdate(Path *p, double x);
void reverse(Path *p);
Path *concatenate(Path *p, Path *q, double x);
Quadruple *split(Vertex *v);

//requirements for concatenate and split
Node *construct(Node *v, Node *w, double x);
Quadruple *destroy(Node *u);
void rotate_left(Node *v);
void rotate_right(Node *v);

//auxiliar functions
Vertex* find_deepest_right_child(Vertex *v);
Vertex* find_deepest_left_child(Vertex *v);
int is_right_child(Vertex *v);
int is_left_child(Vertex *v);

int size(Vertex *v);
