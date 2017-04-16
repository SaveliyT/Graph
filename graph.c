#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


struct graph * create_graph(struct graph * mygraph){	// создаем граф
	i = 0, j = 0;
	mygraph = (struct graph *)malloc(sizeof(struct graph)); //выделяем память под граф
	if(mygraph == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}
	mygraph->n = 1; // кол-во узлов = 1
	
	mygraph->m = (int**)malloc(sizeof(int*)); //выделяем память под массив указателей на начало строк
	if(mygraph->m == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}
	mygraph->m[i] = (int*)malloc(sizeof(int)); //выделяем память под массив строк
	if(mygraph->m[i] == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}
	return(mygraph);
}

struct graph * add_node(struct graph * mygraph){ // добавление в граф одного узла
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}
	i = 0, j = 0;
	mygraph->n += 1; //увеличиваем счетчик кол-ва на один
	int g; 			
	g = mygraph->n; // чтобы каждый раз не писать mygraph->n вводим g

	mygraph->m = (int**) realloc (mygraph->m , g*sizeof(int*)); //увеличиваем кол-во строк матрицы до размера g
	if(mygraph->m == NULL){
		printf("realloc returned null pointer\n");
		exit(-1);
	}

	for(i = 0 ; i < g - 1 ; ++i)
	{
		mygraph->m[i] = (int *) realloc (mygraph->m[i] , g*sizeof(int)); //увеличиваем каждую строку матрицы, кроме последней до размера g
		if(mygraph->m[i] == NULL){
			printf("realloc returned null pointer\n");
			exit(-1);
		}
		mygraph->m[i][g-1] = 0; //обнуляем последий элемент каждой строки, кроме последней
	}

	mygraph->m[g - 1] = (int *) malloc (g*sizeof(int)); // выделяем память для последней строки
	if(mygraph->m[g - 1] == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}
	for(i = 0 ; i < g - 1 ; ++i){
		mygraph->m[g - 1][i] = 0; //обнуляем последнюю строку
	}

	return(mygraph);
}

struct graph * add_link(struct graph * mygraph, int i, int j, int lenght){ //добавление в граф связи от элемента i до элемента j длинны lenght 
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}

	if( i > mygraph->n || j > mygraph->n){ //проверка, что передаваемые в функции номера узлов не больше самого кол-ва узлов в графе
		printf("no such node!\n");
		return(mygraph);
	}

	if(mygraph->m[i-1][j-1] == lenght){ //проверка, существует ли уже данная связь
		printf("link already exists!\n");
		return(mygraph);
	}
	if(mygraph->m[j-1][i-1] != 0 && mygraph->m[j-1][i-1] != lenght){ //проверка, что уже существует данная связь, но другой длинны
		printf("wrong lenght from %d to %d\n", i, j);
		return(mygraph);
	}

	else mygraph->m[i-1][j-1] = lenght; // если все ок, то в матрице iый jый элемент приравниваем к длине связи
	return(mygraph);
}

struct graph * destroy_node(struct graph * mygraph, int m){ // удаление узла, m - номер узла
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}

	if(mygraph->n < m){
		printf("nothing to destroy!\n");
		return(mygraph);
	}

	for(i = m; i < mygraph->n; i++){					//перенос всех элементов строчек,
		for (j = 0; j < mygraph->n; j++){				//начиная с m+1-ой строки, на строку выше
			mygraph->m[i-1][j] = mygraph->m[i][j];
		}
	}

	for(i = m; i < mygraph->n; i++){					//перенос всех элементов стобцов, начиная 
		for (j = 0; j < mygraph->n; j++){				//с  m+1-го столбца, на столбец левее
			mygraph->m[j][i-1] = mygraph->m[j][i];
		}
	}
	mygraph->n--;
	mygraph->m = (int**) realloc (mygraph->m , (mygraph->n)*sizeof(int*)); 		//удаление последней строки и 
	if(mygraph->m == NULL){														//уменьение размера матрицы на одну строку
		printf("realloc returned null pointer\n");
		exit(-1);
	}

	for(i = 0 ; i < mygraph->n ; ++i){
		mygraph->m[i] = (int *) realloc (mygraph->m[i] , (mygraph->n)*sizeof(int)); //уменьшение размера каждой строки на 1 элемент
		if(mygraph->m[i] == NULL){													//(уменьшение размера матрицы на 1 столбец)
			printf("realloc returned null pointer\n");
			exit(-1);
		}
	}
	free(mygraph->m[mygraph->n + 1]);

	return(mygraph);

}

struct graph * destroy_link(struct graph * mygraph, int i, int j){ // удаление связи между элементами i и j
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}

	if (i > mygraph->n || j > mygraph->n){ 							//проверка, что передаваемые в функции номера узлов 
		printf("wrong node number(s)!\n");							//не больше самого кол-ва узлов в графе
		return(mygraph);
	}
	if(mygraph->m[i-1][j-1] == 0){									//проверка, существует ли данная связь
		printf("nothing to destroy!\n");
		return(mygraph);
	}
	else mygraph->m[i-1][j-1] = 0;									//если все ок, то в матрице iый jый элемент приравниваем к нулю
	return(mygraph);
}


void find_the_shortest_way(struct graph* mygraph, int a, int b){ // поиск кратчайшего пути из a в b (алгоритм Дейкстры)
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}
	int * path; //метки узлов
	int * way; //кратчайший путь
	int * flag; //флаги (1 - узел рассмотрен, 0 - узел не рассмотрен)
	int * p; //последний узел в кратчайшем пути до искомого узла
	int k = 0;//счетчик
	int c = 0;//
	int min = 10000, num = 0;

	path = (int*)malloc(mygraph->n*sizeof(int)); //выделение памяти 
	if(path == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}

	flag = (int*)malloc(mygraph->n*sizeof(int)); //выделение памяти
	if(flag == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}

	p = (int*)malloc(mygraph->n*sizeof(int)); // выделение памяти
	if(p == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}

	way = (int*)malloc(sizeof(int)); //выделение памяти
	if(way == NULL){
		printf("malloc returned null pointer\n");
		exit(-1);
	}

	for (i = 0; i < mygraph->n; ++i){
		path[i] = 10000; //установление меток всех элементов 10000
		flag[i] = 0;	//установление всех флагов 0
		p[i] = a;		//установление всех элементов массива р равными номеру начального узла (а)
	} 

	path[a - 1] = 0;//обнуление метки исходного узла
	k = a - 1; //начинаем рассматривать а-ый узел
	while(1){	
		
		for (i = 0; i < mygraph->n; i++){					// Рассматривае все узлы, которые еще не рассмотрены, 
			if(((mygraph->m[k][i] + path[k]) < path[i]) && 	// и в которые можно попасть из узла на котором счетчик.
			(mygraph->m[k][i] != 0) && (flag[i] != 1)){ 	// Если сумма расстояния до рассматриваемого узла и метки того узла, на котором
				path[i] = mygraph->m[k][i] + path[k];		// счетчик, меньше, чем метка рассматриваемого узла, метку рассматриваемого узла
				p[i] = k + 1;								// приравниваем к этой сумме
			}
		}
		c = 0;
		min = 1000;
		flag[k] = 1; //узел, на котором был счетчик  помечаем, как рассмотренный
		for (i = 0; i < mygraph->n; i++){ 					//ищем узел, с минимальной меткой 
			if ((path[i] < min) && (flag[i] != 1)){			
				min = path[i];
				num = i;
				c = 1;
			}
		}
		if(c == 0){											//если такого узла нет, то выходим из цикла
			break;
		}
		k = num; //ставим счетчик на узел с минимальной меткой

		printf("path: ");	
		for (int i = 0; i < mygraph->n; i++){
			printf("%d ", path[i]);
		}
		printf("\n");
		

	}
	if(path[b-1] == 10000){ // если метка узла, до которого надо было найти расстояние (b), не изменилась с 10000, 
		printf("there is no way from %d to %d\n", a, b); //значит пути из а в b нет
		exit(0);
	}

	i = 0;
	k = b - 1; // ставим счетчик на узел b

	while(1){// поиск кратчайшего пути
		if(p[k] == a){ //если последний узел в кратчайшем пути до узла, на котором метка, является узлом a, 
			way[i] = p[k]; // то выходим из цикла
			break;
		}
		way[i] = p[k]; // записываем в кратчайший путь последний узел до узла, на котором счетчик
		i++;
		way = (int*)realloc(way, i*sizeof(int)); //увеличиваем размер массива кратчайшего пути
		
		if(way == NULL){
			printf("realloc returned null pointer\n");
			exit(-1);
		}

		k = p[k] - 1; //ставим счетчик на узел, который был предыдущим до рассмтравиаемого в кратчайшем пути
	}

	printf("p: ");	
		for (int i = 0; i < mygraph->n; i++){
			printf("%d ", p[i]);
		}
		printf("\n");

	for( i ; i >= 0; i--){					// печать кратчайшего пути
		printf("%d->", way[i]);
	}
	printf("%d", b);
	printf("\n");



	printf("lenght = %d\n", path[b-1]); //печать расстояния в кратчайшем пути

	free(path);
	free(way);
	free(flag);
	free(p);
}

struct graph * destroy_graph(struct graph * mygraph){
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}

	for (i = 0; i < mygraph->n; ++i){
		free(mygraph->m[i]);
		mygraph->m[i] = NULL;
	}
	free(mygraph->m);
	mygraph->m = NULL;
	free(mygraph);
	mygraph = NULL;
	return(mygraph);
}

void print_matrix(struct graph * mygraph){ //печать матрицы
	if (mygraph == NULL){
		printf("error: function recieved null pointer\n");
		exit(-1);
	}
	for (i = 0; i < mygraph->n; i++){ // печать всех строчек
		for (j = 0; j < mygraph->n; j++){ //печать одной стрчкий
			printf("%4d ", mygraph->m[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}




