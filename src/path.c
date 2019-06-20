#include <stdlib.h>
#include "path.h"


int reversal_state(Node *v)
{
	// defined as the XOR of the reversal bits on the path
	// from v to the root of its tree

	int reversal = v->reversed;
	while(v->dparent != NULL){
		v = v->dparent;
		reversal = reversal ^ v->reversed;
	}
	return reversal;
}

Path *path(Vertex *v)
{
	Node *w = v;
	while(w->bparent != NULL)
		w = w->bparent;
	return w;
}

Vertex *head(Path *p)
{
	if(p->reversed)
		return p->btail;
	else
		return p->bhead;
}

Vertex *tail(Path *p){
	if (p->reversed) {
		return p->bhead;
	} else {
		return p->btail;
	}
}

Vertex *find_deepest_right_child(Vertex *v)
{
	Node *w;
	int reversal;

	while(v != NULL){
		reversal = reversal_state(v);
		//find deepest w node on the path that is a right child
		if(!reversal){
			if(v->bright != NULL){
				v = v->bright;
				w = v;
			}
		}
		else{
			if(v->bleft != NULL){
				v = v->bleft;
				w = v;
			}
		}
	}
	return w;
}

Vertex *find_deepest_left_child(Vertex *v)
{ //symmetric to "left child"	
	Node *w; //current deepest left child
	int reversal;

	while(v != NULL){
		reversal = reversal_state(v);
		//find deepest w node on the path that is a left child
		if (!reversal){
			if (v->bleft != NULL){
				v = v->bleft;
				w = v;
			}
		} else {
			if (v->bleft != NULL){
				v = v->bright;
				w = v;
			}
		}
	}
	return w;
}


Vertex *before(Vertex *v)
{
	Node *u;
	Node *w = find_deepest_right_child(v);

	//find out who is u - w's sibling
	if (w->bparent->bleft == w) {
		u = w->bparent->bright;
	} else {
		u = w->bparent->bleft; //sanity check could be added here
	}

	//return u's rightmost external descendant
	if(u->external) 
		return u;	
	else if (reversal_state(u)) //FIXME calculating twice
		return u->bhead;
	else 
		return u->btail;
	

	return u;
}

Vertex *after(Vertex *v)
{
	Node *u;
	Node *w = find_deepest_right_child(v);

	if (w->bparent->bleft == w)
		u = w->bparent->bright;
	else
		u = w->bparent->bleft; //sanity check could be added here

	return u;
}

int pcost(Vertex *v)
{
	Node *w = find_deepest_left_child(v);
	return w->bparent->netcost + grossmin(w->bparent);
}

Vertex *pmincost(Path *p)
{
	Vertex *u = p;
	int reversal = p->reversed; // p is root
	
	//until(u->netcost  == 0 && 
	//                (u->bright->external || u->bright->netmin>0))

	if (!reversal){
		while (u->netcost != 0 ||				\
		       (!u->bright->external && is_right_child(u))){
			//FIXME comparing double to 0		
			if(u->bright != NULL &&		\
			   !u->bright->external &&	\
			   u->bright->netcost == 0)
				u = u->bright;
			else if (u->netcost > 0)
				u = u->bleft;
			reversal = u->reversed ^ reversal;
		}
		
		//FIXME is this the same as "rightmost external descendant"?
		//because it should be!
		return find_deepest_right_child(u->bleft);
	} else { //notice: is_right_child already checks for reversal
		while (u->netcost != 0 ||				\
		       (!u->bleft->external && is_right_child(u))){
			if(u->bleft != NULL &&		\
			   !u->bleft->external &&	\
			   //FIXME comparing double to 0 		   
			   u->bleft->netcost == 0)
				u = u->bleft;
			else if (u->netcost > 0)
				u = u->bright;
			reversal = u->reversed ^ reversal;
		}
		
		//FIXME is this the same as "rightmost external descendant"?
		//because it should be!
		return find_deepest_right_child(u->bleft);
	}
}

void pupdate(Path *p, double x)
{
	p->netmin += x;
}

void reverse(Path *p)
{
	p->reversed = !p->reversed;
}

Path *concatenate(Path *p, Path *q, double x){return NULL;}
Quadruple *split(Vertex *v){return NULL;}

int grossmin(Vertex *v)
{
	int sum = 0;
	while (v->bparent != NULL) {
		sum += v->netmin;
		v = v->bparent;
	}
	return sum;
}

int grosscost(Vertex *v)
{
	return v->netcost + grossmin(v);
}

int is_right_child(Vertex *v)
{
	if (v->bparent == NULL)
		return 0;
	if (v->reversed)
		return (v->bparent->bleft == v);
	else
		return (v->bparent->bright == v);
}

int is_left_child(Vertex *v)
{
	if (v->bparent == NULL)
		return 0;	
	if (v->reversed)
		return (v->bparent->bleft == v);
	else
		return (v->bparent->bright == v);
}

Node *construct(Node *v, Node *w, double x)
{//returns new node with childs v,w and grosscost x
	double grossmin, c;
	Node *r = (Node*) malloc(sizeof(Node));
	
	r->bleft = v;
	r->bright = w;
	r->reversed = 0;
	
	//cost relationships:
	//netcost(v) = grosscost(v)-grossmin(v)
	//netmin(v) = grossmin(v) if v is root
	//grossmin(v) = min(grosscost(w)) for w descendant of v

	//grosscost = netcost + grossmin
	//netcost = grosscost - grossmin;

	grossmin = grosscost(r->bleft);
	c = grosscost(r->bleft);

	if(c < grossmin)
		grossmin = c;

	r->netmin = grossmin;
	r->netcost = x - grossmin;

	r->weight = v->weight + w->weight;

	return r;
}

Quadruple *destroy(Node *u)
{
	Node *v, *w;
	int x;
	
	v = u->bleft;
	w = u->bright;
	x = grosscost(u);

	Quadruple *a = (Quadruple*) malloc(sizeof(Quadruple));
	a->p = v;
	a->q = w;
	a->x = x;

	return a;
}

void rotate_left(Node *v)
{
	Node *p, *q, *r, *v2;

	r = v->bright;
	v2 = v->bleft;
	p = v2->bleft;
	q = v2->bright;

	v->bleft = p;
	v->bright = v2;
	v2->bleft = q;
	v2->bright = r;

	//FIXME: should I do this or call update_weight()?
	v2->weight = q->weight + r->weight;
}

void rotate_right(Node *v)
{
	Node *p, *q, *r, *v2;

	p = v->bleft;
	v2 = v->bright;
	q = v2->bleft;
	r = v2->bright;

	v->bleft = v2;
	v2->bleft = p;
	v2->bright = q;
	v->bright = r;

	//FIXME: should I do this or call update_weight()?
	v2->weight = q->weight + r->weight;
	
}

int update_weight(Node *v)
{
	if (v->bparent == NULL)
		v->weight = size(v);
	else
		v->weight = size(v) - size(v->bparent);

	return v->weight;
}

Path *splice(Path *p)
{
	Vertex *v;
	Path *q, *r;
	double x, y;

	v = tail(p)->dparent;
	Quadruple *quad = split(v);
	q = quad->p;
	r = quad->q;
	x = quad->x;
	y = quad->y;

	v->weight = v->weight - p->weight;

	if (q != NULL) {
		tail(q)->dparent = v;
		tail(q)->dcost = x;
	}

	p = concatenate(p, path(v), tail(p)->dcost);

	if (r == NULL)
		return p;
	else
		return concatenate(p, r, y);

	return NULL;
}

Path *expose(Vertex *v)
{
	Path *p, *q, *r;
	double x, y;

	Quadruple *quad = split(v);
	q = quad->p;
	r = quad->q;
	x = quad->x;
	y = quad->y;

	if (q != NULL) {
		tail(q)->dparent = v;
		tail(q)->dcost = x;
	}

	if (r == NULL)
		p = path(v);
	else
		p = concatenate(path(v), r, y);

	while (tail(p)->dparent != NULL)
		p = splice(p);
		

	return p;
}

int size (Vertex *V)
{ //TODO
	return 42;
}

