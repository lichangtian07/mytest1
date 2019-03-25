
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define V	9

typedef enum{
	false = 0,
	true = 1
} bool;

// printf Solution 
void printSolution(int dist[], int n)
{
	int	 i = 0;
	
	printf("顶点\t\t距离源点的最短路径\n");
	for(i = 0; i  < V; i ++)
	{
		printf("%d\t\t%d\n", i, dist[i]);
	}
}

/*
**	function	：	minDistance
**	input		:	dist	[M, M, M, M, ... M]
**	input		:	sptSet	[f, f, f, f, ... f]
**
**	return		:	min
*/
int minDistance(int dist[], bool sptSet[])
{
	int		min	= INT_MAX;
	int		min_index;
	int		v;
	
	for(v = 0; v < V; v++)
	{
		if(sptSet[v] == false && dist[v] < min)
		{
			min	= dist[v];
			min_index = v;
		}
	}

	return min_index;
}

void printMatrixHead(char * matrixname, int n)
{
	int		i = 0;

	printf("%s : [", matrixname);

	for(i = 0; i < n ; i ++)
	{
		printf("\t%d", i);
	}
	
	printf("]\n");
}

void printdist(int dist[], int n)
{
	int		i = 0;

	printf("dist : [");
	for(i = 0; i < n; i ++)
	{
		if(dist[i] == INT_MAX)
		{
			printf("\t%c", 'M');
		}
		else
		{
			printf("\t%d", dist[i]);
		}
	}
	printf("]\n");
}

void printsptSet(bool sptSet[], int n)
{
	int		i = 0;

	printf("sptSet: [");
	for(i = 0; i < n ; i ++)
	{
		printf("\t%c", sptSet[i]?'t':'f');
	}

	printf("]\n");
}

void printDigitalMatrix(int matrix[V][V], int Vex, char *str)
{
	int		i = 0;
	int		j = 0;

	printf("%s: \n", str);

	for(i = 0; i < V; i ++)
	{
		printf("[");

		for(j = 0; j < V; j ++)
		{
			if( matrix[i][j] == INT_MAX)
			{
				printf("\t%c", 'M');
			}
			else
			{
				printf("\t%d", matrix[i][j]);
			}
		}
		printf("\t]\n");

	}
}

void printBoolMatrix(bool matrix[V][V], int Vex, char *str)
{
	int		i = 0;
	int		j = 0;
	
	printf("%s: \n", str);

	for(i = 0; i < V; i++)
	{
		printf("[");
		for(j = 0; j < V; j ++)
		{
			printf("\t%c", matrix[i][j]?'t':'f');
		}
		printf("\t]\n");
	}
}

void copyDigitalArray(int matrix[V][V], int array[], int line, int Range)
{
	int		i = 0;
	
	for(i = 0; i < Range; i ++)
	{
		matrix[line][i] = array[i];
	}
}

void copyBoolArray(bool matrix[V][V], bool array[], int line, int Range)
{
	int		i = 0;
	
	for(i = 0; i < Range; i ++)
	{
		matrix[line][i] = array[i];
	}
}

/*
**
**	dijkstra
**	input	:	graph[v][v] graph for vector
**	input	:	src the point
**
*/

void dijkstra(int graph[V][V], int src)
{
	int		dist[V];
	// distance from src to i 
	bool	sptSet[V];
	int		i = 0;
	int		count = 0;
	int		u = 0;
	int		v = 0;
	
	int		distmatrix[V][V];
	bool	sptSetMatrix[V][V];
	
	/*
	**	Initialize all distance INFINITE and sptSet[] as false
	**			[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
	**	dist	[M, M, M, M, M, M, M, M, M, M]
	**	sptSet	[f, f, f, f, f, f, f, f, f, f]
	**
	*/
	for(i = 0; i < V; i ++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	/*
	** Distance of source vertex from itself is always 0
	** src the point of start
	*/
	dist[src] = 0;

	//printMatrixHead("dist", V);
	//printMatrixHead("sptSet", V);
	
	//count
	for (count = 0; count < V - 1; count ++)
	{
		//printdist(dist, V);
		//printsptSet(sptSet, V);
		copyDigitalArray(distmatrix, dist, count, V);
		copyBoolArray(sptSetMatrix, sptSet, count, V);
		/*
		**	the dist[] 中找到最小的点并且返回
		**	第一次返回为 0  即 最小值为 dist[0] == 0
		**	第二次返回为 1  即 最小值为 dist[1] == 3
		**	第三次返回为 2  即 最小值为 dist[2] == 9
		**
		*/
		u = minDistance(dist, sptSet);
		/*
		**	sptSet[u] 设置为true  表示已经遍历过 点集合
		**						[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
		**	第一次返回 sptSet	[t, f, f, f, f, f, f, f, f, f]
		**	第一次返回 sptSet	[t, t, f, f, f, f, f, f, f, f]
		**	第一次返回 sptSet	[t, t, t, f, f, f, f, f, f, f]
		**
		*/
		sptSet[u] = true;

		for(v = 0; v < V; v ++)
		{
			/*
			** 第一次 v[0 1 2...V]:graph[0][v] 即第0行未遍历过的点 sptSpec[v] == false 且 dist[0] + graph[0][v] < dist [v] 
			**                    :					[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			**                    :找出最小的dist[]=[0, 3, f, f, f, f, f, f, f, f]
			** 第二次 v[0 1 2...V]:graph[1][v] 即第1行未遍历过的点 sptSpec[v] == false 且 dist[0] + graph[0][v] < dist [v] 
			**                    :					[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			**                    :找出最小的dist[]=[0, 3, 9, f, f, f, f, f, f, f]
			** 第三次 v[0 1 2...V]:graph[2][v] 即第1行未遍历过的点 sptSpec[v] == false 且 dist[0] + graph[0][v] < dist [v] 
			**                    :					[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			**                    :找出最小的dist[]=[0, 3, 9,11, f, f, f, f, f, f]
			**
			*/
			if(!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
			}
		}

	}
		
	copyDigitalArray(distmatrix, dist, count, V);
	copyBoolArray(sptSetMatrix, sptSet, count, V);

	printDigitalMatrix(distmatrix, V, "The dist matrix");
	printBoolMatrix(sptSetMatrix, V, "The sptSet matrix");
	// print the construct distance array
	printSolution(dist, v);

}



int main(int argc, char * argv[])
{
	/* Let us create the example graph discussed above*/
	int		graph[V][V] = {
		{0, 3, 0, 0, 0, 0, 4, 0, 0},
		{3, 0, 6, 0, 0, 0, 0, 0,16},
		{0, 6, 0, 2, 0, 0, 0, 0,17},
		{0, 0, 2, 0, 4, 0, 0, 0, 9},
		{0, 0, 0, 4, 0,11, 0, 7, 0},
		{0, 0, 0, 0,11, 0,20, 0, 0},
		{4, 0, 0, 0, 0,20, 0,10, 0},
		{0, 0, 0, 0, 7, 0,10, 0, 1},
		{0,16,17, 9, 0, 0, 0, 1, 0}
	};
	
	dijkstra(graph, 0);

	return  0;
}




