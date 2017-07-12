/*
 Dijkstra on 2D map. Graph is modeled as a simple matrix.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<int> vi;

int INF = 1000000000;

int djikstra(int rows, int columns, vector<vi> maze, ii source, ii target){
    vector<vi> sums(rows, vi(columns, INF));
    sums[source.first][source.second] = maze[source.first][source.second];
    priority_queue<int, viii, greater<iii>> queue;
    queue.push(iii(0, source));
    
    while(!queue.empty()){
        iii u = queue.top();
        queue.pop();
        int uCoordX = u.second.first;
        int uCoordY = u.second.second;
        int uValue = u.first;
    
        if(sums[uCoordX][uCoordY] >= uValue) {
            
            vector<ii> neighbours = {
                ii(uCoordX - 1, uCoordY), ii(uCoordX + 1, uCoordY),
                ii(uCoordX, uCoordY - 1), ii(uCoordX, uCoordY + 1)
            };
            for(int i = 0; i < neighbours.size(); i++) {
                int neighbourX = neighbours[i].first;
                int neighbourY = neighbours[i].second;
                
                if(neighbourY >= 0 && neighbourY < columns && 
                neighbourX >= 0 && neighbourX < rows) {
                    int neighbourValue = sums[uCoordX][uCoordY] + maze[neighbourX][neighbourY];
                    if(neighbourValue < sums[neighbourX][neighbourY]) {
                        sums[neighbourX][neighbourY] = neighbourValue;
                        queue.push(iii(neighbourValue, ii(neighbourX, neighbourY)));
                    }
                }
            }
        }
    }
    cout << sums[target.first][target.second] << endl;
    return 0;
}


int main() {
	int testCases;
	cin >> testCases;
	
	for(int i = 0; i < testCases; i++) {
	    int rows, columns;
	    cin >> rows;
	    cin >> columns;
	    
	    vector<vi> maze(rows, vi(columns));
	    for(int j = 0; j < rows; j++){
	        for(int k = 0; k < columns; k++) {
	            int value;
	            scanf("%d", &value);
	            maze[j][k] = value;
	        }
	        cin.ignore(columns, '\n'); 
	    }
	    djikstra(rows, columns, maze, ii(0, 0), ii(rows - 1, columns - 1));
	}
	return 0;
}
