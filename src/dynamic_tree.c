#include <stdio.h>
#include <stdlib.h>

#include "path.h"
#include "dynamic_tree.h"

#define MAXNODES 5000

Node *H[MAXNODES]; //closest proper ancestor to the right
Node *E[MAXNODES]; //leftmost child


int main(){
  printf("You'd expect a nice, reasonable test output here. Alas, there is nothing!");
  return 0;
}


Vertex* parent(Vertex *v)
{
  if (tail(path(v)) == v)
    return v->dparent;
  else
    return after(v);
}

Vertex* root(Vertex *v)
{
  return tail(expose(v));
}

double cost(Vertex *v)
{
  if (tail(path(v)) == v)
    return v->dcost;
  else
    return pcost(v);
}

Vertex* mincost(Vertex *v)
{
  return pmincost(expose(v));
}

void update(Vertex *v, double x)
{
  pupdate(expose(v), x);
}

void link(Vertex *v, Vertex *w, double x)
{
  concatenate(path(v), expose(w), x);
}

double cut(Vertex *v)
{
  double y;

  expose(v);

  Quadruple *quad = split(v);

  y = quad->y;

  v->dparent = NULL;
  return y;
}

void evert(Vertex *v)
{
  reverse(expose(v));
  v->dparent = NULL;
}

int weight(Vertex *v)
{
	return 0;
  
}

//
Vertex** top_light(Vertex *v)
{
	
}


Vertex** heavy_path(Vertex *v)
{
	
	
}

Vertex** list_nodes(Vertex *v)
{
	
}
 
