#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define vertex char[35]

typedef struct graph* Graph;
typedef struct node* link;

static link newNode(vertex w, link prox);

#endif // GRAPH_H_INCLUDED
