

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/*
** the Vetex define
*/
#define	 V	9 

void printMatrix(int matrix[V][V], int Vex, char * matrixname)
{
	int		i = 0;
	int		j = 0;
	
	printf("%s: \n", matrixname);
	for (i = 0 ; i < Vex; i ++)
	{
		printf("[");
		for(j = 0; j < Vex; j++)
		{
			printf("\t%d",matrix[i][j]);
		}
		printf("\t]\n");
	}

}

void printArrayIndex(int Vex, char * arrayname)
{
	int		v;
	
	printf("%s [", arrayname);
	for(v = 0; v < Vex; v ++)
	{
		printf("\t%d", v);
	}
	printf("\t]\n");
}

void printDigitalArray(int array[], int Vex, char * arrayname)
{
	int		v;
	
	printf("%s [", arrayname);
	for(v = 0; v < Vex; v ++)
	{
		if(array[v] == INT_MAX)
		{
			printf("\t%c", 'M');
		}
		else
		{
			printf("\t%d", array[v]);	
		}
	}
	printf("\t]\n");
}
void printBoolArray(bool array[], int Vex, char * arrayname)
{
	int		v;
	
	printf("%s [", arrayname);
	for(v = 0; v < Vex; v ++)
	{
		printf(" %c", array[v]?'t':'f');
	}
	printf(" ]\n");
	
}

void printDigitalMatrix(int matrix[V][V], int Vex, char * matrixname)
{
	int		i=0;
	int		j=0;
	
	printf("%s: \n", matrixname);
	for (i = 0 ; i < Vex; i ++)
	{
		printf("[");
		for(j = 0; j < Vex; j++)
		{
			if(matrix[i][j] == INT_MAX)
			{
				printf("\t%c", 'M');
			}
			else
			{
				printf("\t%d",matrix[i][j]);
			}
		}
		printf("\t]\n");
	}
}
void printBoolMatrix(bool matrix[V][V], int Vex, char * matrixname)
{
	int		i=0;
	int		j=0;
	
	printf("%s: \n", matrixname);
	for (i = 0 ; i < Vex; i ++)
	{
		printf("[");
		for(j = 0; j < Vex; j++)
		{
			printf("\t%c", matrix[i][j]?'t':'f');
		}
		printf("\t]\n");
	}	
}

void copyDigitalArray(int matrix[V][V], int digital[], int line, int Range)
{	
	int  r = 0;
	for(r=0; r < Range; r ++)
	{
		matrix[line][r] = digital[r];
	}	
}

void copyBoolArray(bool matrix[V][V], bool set[], int line, int Range)
{	
	int  r = 0;
	for(r=0; r < Range; r ++)
	{
		matrix[line][r] = set[r];
	}	
}

void printSolution(int dist[], int src , int Vex)
{
	int			v;
	printf("vertex \t\tdistance from source %d\n", src);
	for( v = 0; v < Vex; v++)
	{
		printf("%d \t\t%d\n", v, dist[v]);
	}
}
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
int mindistance(int dist[], bool sptSet[], int Vex )
{
	int		v;
	int		u = 0;
	int		min= INT_MAX;

	for( v = 0; v < Vex; v ++)
	{
		if(sptSet[v] == false && dist[v] < min)
		{
			u = v;
			min = dist[v];
		}
	}

	return u;
}
void initialdist(int dist[], int Vex)
{
	int		v = 0;

	for (v = 0 ; v < Vex; v ++)
	{
		dist[v] = INT_MAX; 
	}

}

void initialsptSet(bool sptSet[], int Vex)
{
	int		v = 0;

	for (v = 0 ; v < Vex; v ++)
	{
		sptSet[v] = false; 
	}
}
/*
**  
**
**
*/
void dijkstra(int graph[V][V], int src, int Vex, int dist[], bool sptSet[])
{
	int			v;
	int			u;
	int			i;
	int			DistMatrix[V][V];
	bool		SptSetMatrix[V][V];
	
	dist[src] = 0;
	//sptSet[src] = true;
	// find count  = V-1 exclude the vex = 0 
	//printArrayIndex(Vex,"dist");
	//printArrayIndex(Vex,"sptSet");
	for(i = 0; i < V - 1; i ++)
	{
		//printDigitalArray(dist, Vex, "dist");
		//printBoolArray(sptSet, Vex, "sptSet");
		copyDigitalArray(DistMatrix, dist, i, Vex);
		copyBoolArray(SptSetMatrix, sptSet, i, Vex);
		u = mindistance(dist, sptSet, Vex);
		sptSet[u] = true;

		for(v = 0 ; v < Vex ; v ++)
		{
			if(sptSet[v] == false && graph[u][v] && dist[u] + graph[u][v] < dist[v] )
			{
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	copyDigitalArray(DistMatrix, dist, i, Vex);
	copyBoolArray(SptSetMatrix, sptSet, i, Vex);
	printDigitalMatrix(DistMatrix, Vex, "Distance Matrix");
	printBoolMatrix(SptSetMatrix, Vex, "Spt Set Matrix");
	//printDigitalArray(dist, Vex, "dist");
	//printBoolArray(sptSet, Vex, "sptSet");
	
}

int main()
{
	int graph[V][V] = {
		{0,4,0,0,0,0,0,8,0},
		{4,0,8,0,0,0,0,11,0},
		{0,8,0,7,0,4,0,0,2},
		{0,0,7,0,9,14,0,0,0},
		{0,0,0,9,0,10,0,0,0},
		{0,0,4,0,10,0,2,0,0},
		{0,0,0,14,0,2,0,1,6},
		{8,11,0,0,0,0,1,0,7},
		{0,0,2,0,0,0,6,7,0}
	};
	
	int	*		dist;
	bool *		sptSet;
	int			src = 0;
	/* 
	** initial function 
	** dist    [M, M, M, M, M, M, M, M, M]
	** sptSet  [f, f, f, f, f, f, f, f, f]
	*/
	dist = (int *)malloc(V*sizeof(int));
	sptSet = (bool *)malloc(V*sizeof(bool));
	initialsptSet(sptSet, V);
	initialdist(dist, V);

	printMatrix(graph, V, "graph");	
	// the main solution
	dijkstra(graph, src, V, dist, sptSet);

	// print the solution
	printSolution(dist, src , V);
	

	free(dist);
	free(sptSet);
	dist=NULL;
	sptSet=NULL;

	return 0;
}



