#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main(int argc, char const *argv[])
{
	struct graph * mygraph = NULL;
	mygraph = create_graph(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = add_node(mygraph);
	mygraph = destroy_node(mygraph, 9);
	mygraph = destroy_node(mygraph, 9);

	mygraph = add_link(mygraph, 1, 2, 50);
	mygraph = add_link(mygraph, 1, 7, 56);
	mygraph = add_link(mygraph, 1, 8, 18);
	mygraph = add_link(mygraph, 2, 1, 50);
	mygraph = add_link(mygraph, 2, 3, 15);
	mygraph = add_link(mygraph, 2, 7, 5);
	mygraph = add_link(mygraph, 3, 4, 4);
	mygraph = add_link(mygraph, 3, 6, 4);
	mygraph = add_link(mygraph, 3, 7, 74);
	mygraph = add_link(mygraph, 4, 5, 18);
	mygraph = add_link(mygraph, 4, 7, 49);
	mygraph = add_link(mygraph, 4, 8, 46);
	mygraph = add_link(mygraph, 5, 4, 18);
	mygraph = add_link(mygraph, 5, 6, 10);
	mygraph = add_link(mygraph, 5, 7, 14);
	mygraph = add_link(mygraph, 6, 5, 10);
	mygraph = add_link(mygraph, 7, 1, 56);
	mygraph = add_link(mygraph, 7, 2, 5);
	mygraph = add_link(mygraph, 7, 3, 74);
	mygraph = add_link(mygraph, 7, 5, 14);
	mygraph = add_link(mygraph, 7, 8, 19);
	mygraph = add_link(mygraph, 8, 1, 18);
	print_matrix(mygraph);
	find_the_shortest_way(mygraph, 8, 6);
	mygraph = destroy_link(mygraph, 1, 2);
	mygraph = destroy_link(mygraph, 1, 7);
	print_matrix(mygraph);
	find_the_shortest_way(mygraph, 8, 6);

	

	mygraph = destroy_graph(mygraph);
	return 0;
}		