#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 10000

typedef struct graphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_status(GraphType* g) {
	printf("Distance : ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) printf("* ");
		else printf("%d ", distance[i]);
	}
	printf("\n");
	
	printf("Found : ");
	for (int i = 0; i < g->n; i++) {
		printf("%d ", found[i]);
	}
	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;
	for (i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
			}
		}
	}
}

int main()
{
	printf("Dijkstra Algorithm / 1번까지 구현\n\n");
	
	GraphType g = { 10,
	{{0,3,INF,INF,INF,11,12,INF,INF,INF},
	{3,0,5,4,1,7,8,INF,INF,INF},
	{INF,5,0,2,INF,INF,6,5,INF,INF},
	{INF,4,2,0,13,INF,INF,14,INF,16},
	{INF,1,INF,13,0,9,INF,INF,18,17},
	{11,7,INF,INF,9,0,INF,INF,INF,INF},
	{12,8,6,INF,INF,INF,0,13,INF,INF},
	{INF,INF,5,14,INF,INF,13,0,INF,15},
	{INF,INF,INF,INF,18,INF,INF,INF,0,10},
	{INF,INF,INF,16,17,INF,INF,15,10,0}}
	};
	
	shortest_path(&g, 0);

	printf(" 순서 출력 \n");

	return 0;
}