#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <fstream>

using namespace std;

void FW(vector<vector<int>>& Dist, vector<vector<int>>& Next, int k, int r1, int r2, int c1, int c2);
//main function
int main() {
	//initializing nodes
	int Nodes, Edges;
	ifstream In("graph1.txt");
	//Enter the nodes and edges
	In >> Nodes >> Edges;
	vector < list<pair<int, int>>> Graph(Nodes);
	for (int i = 0; i < Edges; ++i) {
		int a, b, c;
		In >> a >> b >> c;
		Graph[a].push_back({ b,c });
	}
	//Close the input stream
	In.close();
	//Initialize a distance and next node matrix
	vector<vector<int>> Dist(Nodes, vector<int>(Nodes, 9999));
	vector<vector<int>> Next(Nodes, vector<int>(Nodes, -1));
	for (int i = 0; i < Nodes; ++i) {
		Dist[i][i] = 0;
		Next[i][i] = i;
	}
	for (int i = 0; i < Nodes; ++i) {
		for (auto& j : Graph[i]) {
			if (Dist[i][j.first] > j.second) {
				Dist[i][j.first] = j.second;
				Next[i][j.first] = j.first;

			}
		}
	}
	int n{ Nodes };
	vector<thread> T;
	for (int k = 0; k < Nodes; ++k) {
		T.emplace_back(FW, ref(Dist), ref(Next), k, 0, n / 2 - 1, 0, n / 2 - 1);
		T.emplace_back(FW, ref(Dist), ref(Next), k,  n / 2, n - 1, 0, n / 2 - 1);
		T.emplace_back(FW, ref(Dist), ref(Next), k, 0, n / 2 - 1, n / 2, n - 1);
		FW(Dist, Next, k, n / 2, n - 1, n / 2, n - 1);
		for (auto& i : T) i.join();
		T.clear();
	}
	cout << "Dist Matrix" << endl;
	for (auto& i : Dist) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Next Matrix" << endl;

	for (auto& i : Next) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	return 0;
}
// Main Floyd-Warshall function
void FW(vector<vector<int>>& Dist, vector<vector<int>>& Next, int k, int r1, int r2, int c1, int c2) {
		for (int i = r1; i <= r2; ++i) {
			for (int j = c1; j <= c2; ++j) {
				if (Dist[i][j] > Dist[i][k] + Dist[k][j]) {
					Dist[i][j] = Dist[i][k] + Dist[k][j];
					Next[i][j] = Next[i][k];
				}
			}
		}
}
