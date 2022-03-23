#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <queue>
#include <list>

using namespace std;
const int VMAX = 1e5;
const int INF = 1e7;

struct edge {
	int src, dest, weight;
};

class Graph {
	char* infile;
	char* outfile;
	int V;
	int E;
	vector<edge> edges;
	list<pair<int, int>>* adj;

public:
	Graph(char* in, char* out);
	void dijkstra(int src);
	bool bellmanFord();
	void johnson();
	~Graph();
};

Graph::Graph(char* in, char* out) {
	this->infile = new char[strlen(in) + 1];
	this->outfile = new char[strlen(out) + 1];
	strcpy(this->infile, in);
	strcpy(this->outfile, out);
	
	ifstream fin(this->infile);
	if (!fin) {
		cout << "Fisierul de intrare nu a putut fi deschis!\n";
		exit(-1);
	}
	int V, E;
	fin >> V >> E;
	this->adj = new list<pair<int, int>>[V];
	this->V = V;
	this->E = E;
	for(int u, v, w; fin >> u >> v >> w; adj[u].push_back({ v, w }), edges.push_back({ u, v, w }));
	fin.close();
}

void Graph::dijkstra(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pcoada;
	vector<int> dist(V, INF);

	pcoada.push({ 0, src });		
	dist[src] = 0;
	while(!pcoada.empty()) {
		int u = pcoada.top().second;
		pcoada.pop();
		for (auto i : adj[u]) {
			int v = i.first;
			int w = i.second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pcoada.push({ dist[v], v });
			}
		}
	}

	ofstream fout;
	fout.open(this->outfile, ios_base::app);
	for (int i = 0; i < V; ++i) {
		if (dist[i] == INF) {
			fout << "INF ";
		}
		else {
			fout << dist[i] << " ";
		}
	}
	fout << "\n";
}

bool Graph::bellmanFord() {
	vector<int> dist(V + 1, INF);
	dist[V] = 0;

	for (int i = 0; i < V; ++i) {
		edges.push_back({ V, i, 0 });
	}

	for (int i = 0; i < V; ++i) {
		for (auto j : edges) {
			if (dist[j.src] != INF && dist[j.dest] > dist[j.src] + j.weight) {
				dist[j.dest] = dist[j.src] + j.weight;
			}
		}
	}
	
	for (int i = 0; i < V; ++i) {
		edges.pop_back();
	}

	ofstream fout(this->outfile);

	for (auto j : edges) {
		if (dist[j.src] + j.weight < dist[j.dest]) {
			return false;
		}
	}

	for (auto j : edges) {
		j.weight += dist[j.src] - dist[j.dest];
		fout << j.src << " " << j.dest << " " << j.weight << "\n";
	}
	for (int i = 0; i < V; ++i) {
		for (auto j : adj[i]) {
			j.second += dist[i] - dist[j.first];
		}
	}
	
	fout.close();
	return true;
}

void Graph::johnson() {
	if (this->bellmanFord() == false) {
		ofstream fout(outfile);
		fout << "-1\n";
		fout.close();
		return;
	}
	for (int i = 0; i < V; ++i) {
		this->dijkstra(i);
	}
}

Graph::~Graph() {
	delete[] adj;
	delete[] infile;
	delete[] outfile;
}


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Numar invalid de argumente!\n";
		cout << " Utilizare: ./p2.exe fisier1 fisier2\n";
		exit(-1);
	}

	Graph G(argv[1], argv[2]);
	G.johnson();

	return 0;
}

