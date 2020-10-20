#include<iostream> 
#include <list> 

using namespace std; 

class Grafo { 
	int V; 
	list<int> *adj;
public: 
	Grafo(int V); 
	void addAresta(int v, int w);
	int encontraPontes(int v, bool visited[], int disc[], int low[], int parent[]); 
	int pontes();
}; 

Grafo::Grafo(int V) { 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Grafo::addAresta(int v, int w){ 
	adj[v].push_back(w); 
	adj[w].push_back(v);
} 

int Grafo::encontraPontes(int u, bool visited[], int disc[], int low[], int parent[]) { 
	int encontradas = 0;
	static int time = 0; 
	visited[u] = true; 
 
	disc[u] = low[u] = ++time; 
 
	list<int>::iterator i; 
	for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
		int v = *i; 
		if (!visited[v]) { 
			parent[v] = u; 
			encontradas += encontraPontes(v, visited, disc, low, parent); 
			low[u] = min(low[u], low[v]);
			if (low[v] > disc[u]) encontradas++; 
		} 
		else 
			if (v != parent[u]) low[u] = min(low[u], disc[v]); 
	}
	return encontradas; 
} 

int Grafo::pontes() {
	int resp = 0;
	bool *visited = new bool[V]; 
	int *disc = new int[V]; 
	int *low = new int[V]; 
	int *parent = new int[V]; 

	for (int i = 0; i < V; i++) { 
		parent[i] = -1; 
		visited[i] = false; 
	} 

	for (int i = 0; i < V; i++) 
		if (visited[i] == false) 
			resp += encontraPontes(i, visited, disc, low, parent);
	return resp;
} 

int main() {
	int c, p, a, b;
	while (scanf("%d %d", &c, &p) != EOF){
		Grafo G(c);
		for (int i = 0; i < p; i++){
			cin >> a;
			cin >> b;
			G.addAresta(a-1,b-1);
		}
		cout << G.pontes() << endl;
	} 
	return 0; 
}
