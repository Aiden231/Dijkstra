#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 10000

// 노드 구조체
typedef struct node {
	int vertex;
	int weight;
	struct node* next;
} Node;

// 구조체 (인접 리스트)
typedef struct graphType {
	int n;
	Node* adjList[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int prev[MAX_VERTICES];

// choose 함수
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

// 출력 함수
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

// 간선 추가 함수
void insert_edge(GraphType* g, int src, int dest, int weight) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = dest;
	newNode->weight = weight;
	newNode->next = g->adjList[src];
	g->adjList[src] = newNode;
}

// 다익스트라 찾기 
void shortest_path(GraphType* g, int start) {
	int i, u, w;
	for (i = 0; i < g->n; i++) {
		distance[i] = INF;
		found[i] = FALSE;
	}
	distance[start] = 0;

	for (i = 0; i < g->n; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		prev[i] = u;
		found[u] = TRUE;

		Node* current = g->adjList[u];
		while (current != NULL) {
			w = current->vertex;
			if (!found[w]) {
				if (distance[u] + current->weight < distance[w]) {
					distance[w] = distance[u] + current->weight;
				}
			}
			current = current->next;
		}
	}
}

int main()
{
	printf("Dijkstra Algorithm / 2번까지 구현\n\n");
	
	GraphType g = { 10, {NULL} };

	insert_edge(&g, 0, 1, 3);
	insert_edge(&g, 0, 5, 11);
	insert_edge(&g, 0, 6, 12);
	insert_edge(&g, 1, 2, 5);
	insert_edge(&g, 1, 3, 4);
	insert_edge(&g, 1, 4, 1);
	insert_edge(&g, 1, 5, 7);
	insert_edge(&g, 1, 6, 8);
	insert_edge(&g, 2, 3, 2);
	insert_edge(&g, 2, 6, 6);
	insert_edge(&g, 2, 7, 5);
	insert_edge(&g, 3, 4, 13);
	insert_edge(&g, 3, 7, 14);
	insert_edge(&g, 3, 9, 16);
	insert_edge(&g, 4, 5, 9);
	insert_edge(&g, 4, 8, 18);
	insert_edge(&g, 4, 9, 17);
	insert_edge(&g, 6, 7, 13);
	insert_edge(&g, 7, 9, 15);
	insert_edge(&g, 8, 9, 10);

	shortest_path(&g, 0);

  	// 출력
	for (int i = 0; i < g.n; i++) {
		printf("%d ", prev[i]+1);
	}

	return 0;
}