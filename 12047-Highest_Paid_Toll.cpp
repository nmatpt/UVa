/*
 Clever usage of Dijkstra, run from source and from destination; 
 try all edge (u,v) if dist[source][u]+ weight(u,v)+dist[v][destination] ≤ p; 
 record the largest edge weight found. 
 Beware of overflows
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
ll INF = 2e18;

vll dijkstra(int nrNodes, vector<vii> adjList, int source, int money) {
    priority_queue<pll, vpll, greater<pll> > queue;
    queue.push(pll(0, source));
    vll distance(nrNodes, INF);
    distance[source] = 0;
    
    while(!queue.empty()){
        pll u = queue.top();
        queue.pop();
        
        ll uNode = u.second;
        ll uCost = u.first;
        
        if(uCost <= distance[uNode]) {
            for(int j = 0; j < adjList[uNode].size(); j++){
                pll v = adjList[uNode][j];
                ll vNode = v.first;
                ll vCost = v.second;
                
                ll newCost = distance[uNode] + vCost;
                if(newCost < distance[vNode]) {
                    distance[vNode] = newCost;
                    queue.push(ii(newCost, vNode));
                }
            }
        }
    }
    return distance;
}

ll max_toll(int nrVertices, vector<vii> adjList, vll distances, vll reverseDistances, int target, int money) {
    ll max = -1;
    
    for(int u = 0; u < nrVertices; u++) {
        for(int i = 0; i < adjList[u].size(); i++) {
            ll v = adjList[u][i].first;
            ll edgeCost = adjList[u][i].second;
            if(distances[u] + reverseDistances[v] + edgeCost <= money && edgeCost > max) {
                max = edgeCost;
            }
        }
    }
    return max;
}

int main(){
    int testCases;
    cin >> testCases;
    
    while(testCases--){
        int nrVertices, nrEdges, source, target, money;
        scanf("%d %d %d %d %d\n", &nrVertices, &nrEdges, &source, &target, &money);
        source--; target--;
        
        vector<vii> adjList(nrVertices, vii());
        vector<vii> reverseAdjList(nrVertices, vii());
        for(int i=0; i < nrEdges; i++) {
            int u, v, cost;
            scanf("%d %d %d\n", &u, &v, &cost);
            u--; v--;
            adjList[u].push_back(ii(v, cost));
            reverseAdjList[v].push_back(ii(u, cost));
        }
        vll distances = dijkstra(nrVertices, adjList, source, money);
        vll reverseDistances = dijkstra(nrVertices, reverseAdjList, target, money);

        int result = max_toll(nrVertices, adjList, distances, reverseDistances, target, money);
        cout << result << endl;
    }
    return 0;
}
