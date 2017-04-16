#ifndef GRAPH_H
#define GRAPH_H



int i,j;

struct graph{
	int **m;//матрицай
	int n; //размер матрицы
	
};

struct graph * create_graph(struct graph * mygraph); 						// создаем граф с одним узлом
struct graph * add_node(struct graph * mygraph); 							// добавление в граф одного узла
struct graph * add_link(struct graph * mygraph, int i, int j, int lenght);  //добавление в граф связи от элемента i до элемента j длинны lenght 
struct graph * destroy_node(struct graph * mygraph, int m); 				// удаление узла, m - номер узла
struct graph * destroy_link(struct graph * mygraph, int i, int j); 			// удаление связи между  элементами i и j
void find_the_shortest_way(struct graph* mygraph, int a, int b); 			// поиск кратчайшего пути из a в b
struct graph * destroy_graph(struct graph * mygraph); 						// удаление графа, освобождение памяти
void print_matrix(struct graph * mygraph); 									// печать матрицы

#endif