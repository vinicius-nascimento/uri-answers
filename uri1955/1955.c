#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

typedef struct no {
	int chave;
	struct no *prox;
} No;

typedef struct fila {
	unsigned int tamanho;
	No *inicio;
	No *fim;
} Fila;

typedef struct aresta {
    int v;
    int w;
} Aresta;

typedef struct grafo {
	int V;
	int E;
	int **adj;
} Grafo;

Fila *criaFila(void){
	Fila *nova = (Fila *) malloc (sizeof (Fila));
	if (nova == NULL){
		printf ("Erro.\n");
		exit (1);
	}
	nova->inicio = NULL;
	nova->fim = NULL;
	nova->tamanho = 0;
	return nova;
}

Fila *insere(Fila *f, int chave){
	No *novo = (No *) malloc (sizeof (No));
	novo->chave = chave;
	novo->prox = NULL;
	if (f->fim != NULL) f->fim->prox = novo;
	else f->inicio = novo;
	f->fim = novo;
	f->tamanho++;
	return f;
}

int retira(Fila *f){
	No *aux;
	int chave;
	if (f->tamanho == 0) {
		printf("Fila vazia. \n");
		exit (1);
	}
	aux = f->inicio;
	chave = aux->chave;
	f->inicio = aux->prox;
	f->tamanho--;
	if (f->inicio == NULL)
		f->fim = NULL;
	free(aux);
	return chave;
}

int primeiro(Fila *f){
    return f->inicio->chave; 
}

int **alocaMatrizAdj (int r, int c, int val){
	int i, j;
	int **m = malloc(r * sizeof(int *));
	for (i = 0; i< r; i++){
		m[i] = malloc (c * sizeof (int));
	}
	for (i = 0; i < r; i++) 
		for (j = 0; j < c; j++)
			m[i][j] = val;
	return m;
}

void insereAresta (Grafo *G, int v, int w){
	if (v != w && G->adj[v][w] == 0){
		G->adj[v][w] = 1;
		G->adj[w][v] = 1;
		G->E++;
	}
}

void removeAresta (Grafo *G, int v, int w){
	if (G->adj[v][w] == 1){
		G->E--;
		G->adj[v][w] = 0;
		G->adj[w][v] = 0;
	}
}

Grafo *criaGrafo (int V){
	Grafo *G = malloc (sizeof (Grafo));
	G->V = V;
	G->E = 0;
	G->adj = alocaMatrizAdj(V, V, 0);
	return G;
}

int verificaAdj (Grafo *G, int v, int w){
	if (G->adj[v][w] == 1) return 1;
	else return 0;
}

int bipartido (Grafo *G){
	Fila *f = criaFila();
	int i, r, v, w, alc;
	int Alc[G->V], Niv[G->V];
	
	for (i=0;i<G->V;i++) Alc[i] = 0;
	r = 0;
	f = insere(f,r);
	Alc[r] = Niv[r] = alc = 1;

	while(f->tamanho > 0){
		v = primeiro(f);
		for(w=0;w<G->V;w++){
            if(verificaAdj(G,v,w)){    
                if(Alc[w]==0){
                    f = insere(f,w);
                    alc++;
                    Alc[w] = alc;
                    Niv[w] = Niv[v]+1;
                }
                if(Alc[v] < Alc[w]){   
                    if(Niv[v] == Niv[w]) return 0;
                }
            }
        }
		v = retira(f);
	}
	return 1;
}

int main (){
    int i, j, k, v;
    Grafo *g;
    
    scanf ("%d", &v);
    g = criaGrafo(v);
        
    for (i=0;i<v;i++) {
        for (j=0;j<v;j++){
            scanf("%d", &k);
            if (k == 0) insereAresta(g,i,j);
        }
    }
   
    if (bipartido(g)) printf ("Bazinga!\n");
    else printf ("Fail!\n");

    return (0);
}