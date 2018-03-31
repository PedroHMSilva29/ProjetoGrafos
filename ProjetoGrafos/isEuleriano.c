#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_FILA  100
#define false 3
#define true 4
typedef int bool;

#define NONE  -1
#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct aresta {
	int nome;
	struct aresta *prox;
	int verts[2];
}Aresta;

typedef struct vert {
	int nome;
	int cor;
	Aresta *prim;
}Vertice;


void imprimeGrafo(Vertice G[], int ordem);
void criaGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int  calcumaTamanho(Vertice G[], int ordem);

/* IsEuleriano = IsConexo + Para todo g(VG), V é par */


void criaGrafo(Vertice **G, int ordem) {
	int i;
	*G = (Vertice*)malloc(sizeof(Vertice)*ordem);

	for (i = 0; i<ordem; i++) {
		(*G)[i].nome = i;
		(*G)[i].prim = NULL;
	}
}

int acrescentaAresta(Vertice G[], int ordem, int v1, int v2) {
	if (v1<0 || v1 >= ordem)
		return 0;
	if (v2<0 || v2 >= ordem)
		return 0;

	Aresta *A1 = (Aresta *)malloc(sizeof(Aresta));
	A1->nome = v2;
	A1->prox = G[v1].prim;
	A1->verts[0] = v1;
	A1->verts[1] = v2;
	G[v1].prim = A1;

	Aresta *A2 = (Aresta *)malloc(sizeof(Aresta));
	A2->nome = v1;
	A2->prox = G[v2].prim;
	A2->verts[0] = v1;
	A2->verts[1] = v2;
	G[v2].prim = A2;

	
}


int  calcumaTamanho(Vertice G[], int ordem) {
	int i;
	int totalArestas = 0;

	for (i = 0; i<ordem; i++) {
		int j;
		Aresta *aux = G[i].prim;
		for (j = 0; aux != NULL; aux = aux->prox, j++);
		totalArestas += j;
	}
	return totalArestas / 2 + ordem;
}

void imprimeGrafo(Vertice G[], int ordem) {
	int i;

	for (i = 0; i<ordem; i++) {
		printf("\nV%d: ", i);
		Aresta *aux = G[i].prim;
		for (; aux != NULL; aux = aux->prox)
			printf("%3d", aux->nome);
	}
	printf("\n\n");
}

bool isConexo(Vertice G[], int ordem) {
	int i,v1,v2,j,k;
	for (i = 0; i < ordem; i++) {
		G[i].cor = BRANCO;
	}

	for (i = 0; i<ordem;) {
		Aresta *aux = G[i].prim;
		if(i == 0)
			G[0].cor = CINZA;
		for (; aux != NULL; aux = aux->prox){
			if (G[i].cor != CINZA)
				return false;

			v1 = aux->verts[0];
			v2 = aux->verts[1];
			if(v1 != i && G[v1].cor != PRETO)
				G[v1].cor = CINZA;
			if (v2 != i && G[v2].cor != PRETO)
				G[v2].cor = CINZA;

		}
		G[i].cor = PRETO;

		for (j = 0; j < ordem; j++) {
			if (G[j].cor == CINZA) {
				i = j;
				break;
			}
		}
		k = 0;
		for (j = 0; j < ordem; j++) 
			if (G[j].cor == PRETO) 
				k++;

		if (k == ordem)
			return true;
		
	}

	for (i = 0; i < ordem; i++)
		if (G[i].cor != PRETO)
			return false;

	return false;
}

bool isVerticesPares(Vertice G[], int ordem) {

	int i;
	int grau = 0;
	for (i = 0; i<ordem; i++) {
		Aresta *aux = G[i].prim;
		for (; aux != NULL; aux = aux->prox) {
			if (aux != NULL) grau++;
			if (aux->prox == NULL) {
				if (grau % 2 == 1)
					return false;
				grau = 0;
			}
		}

	}
	return true;
}

bool isEuleriano(Vertice G[], int ordemG) {
	bool conexo = isConexo(G, ordemG);
	bool pares = isVerticesPares(G, ordemG);

	if (conexo && pares)
		return true;
	else
		return false;

}


int main(int argc, char *argv[]) {
	Vertice *G;
	int ordemG = 5;


	criaGrafo(&G, ordemG);
	acrescentaAresta(G, ordemG, 0, 4);
	acrescentaAresta(G, ordemG, 0, 1);
	acrescentaAresta(G, ordemG, 2, 3);
	acrescentaAresta(G, ordemG, 4, 2);
	acrescentaAresta(G, ordemG, 1, 3);

	printf("\nTamanho: %d\n", calcumaTamanho(G, ordemG));

	imprimeGrafo(G, ordemG);

	if (isEuleriano(G, ordemG) == true)
		printf("Grafo G e Euleriano!");
	else
		printf("Grafo G nao e Euleriano!");


	return 0;
}
