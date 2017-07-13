/*
 Straightforward Dijkstra's application. Note that each edge is bidirectional.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int INF = 1000000000;

int dijkstra(int caseNr, vector<vii> adjList, int source, int target){
    vi latencies(adjList.size(), INF);
    latencies[source] = 0;
    priority_queue<ii, vii, greater<ii>> queue;
    queue.push(ii(0, source));

    while(!queue.empty()){
        ii u = queue.top();
        queue.pop();
        int uServer = u.second;
        int uLatency = u.first;

        if(latencies[uServer] >= uLatency) {
            for(int i = 0; i < adjList[uServer].size(); i++) {
                ii v = adjList[uServer][i];
                int vServer = v.first;
                int vLatency = v.second;
                if(latencies[uServer] + vLatency < latencies[vServer]) {
                    latencies[vServer] = latencies[uServer] + vLatency;
                    queue.push(ii(latencies[uServer] + vLatency, vServer));
                }
            }
        }
    }
    string result = latencies[target] == INF ? "unreachable" : to_string(latencies[target]);
    cout << "Case #" << caseNr << ": " << result << endl;
    return 0;
}


int main() {
    int testCases;
    cin >> testCases;
    
    for(int i = 0; i < testCases; i++) {
        int n, m, s, t;
        scanf("%d %d %d %d", &n, &m, &s, &t);
        vector<vii> servers(n, vii());
        for(int j = 0; j < m; j++){
            int server1, server2, latency;
            scanf("%d %d %d", &server1, &server2, &latency);
            servers[server1].push_back(ii(server2, latency));
            servers[server2].push_back(ii(server1, latency));
        }
        dijkstra(i + 1, servers, s, t);
    }
    return 0;
}
