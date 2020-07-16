# 완전탐색
말 그대로 가능한 모든 경우의 수를 다 시도해 답을 찾는 방법. 
정확하고 확실하게 답을 찾을 수 있다는 장점이 있지만, 시간이 오래 걸린다는 단점이 있다.


## 깊이 우선 탐색(DFS, Depth-First Search)
루트노드(혹은 다른 임의의 노드)에서 시작해서 다음 분기로 넘어가기 전에 해당 분기를 완벽하게 탐색하는 방법   
쉽게 풀어 말하자면, 탐색에 있어 ```형제 노드 탐색의 우선순위```보다 ```자식 노드 탐색의 우선순위```가 높은 탐색 방법을 뜻한다.  

![](ReadmeResource/dfs.gif)

- 동작방식: 갈 수 있는 만큼 최대한 깊이 가고, 더 이상 갈 곳이 없다면 이전 정점으로 돌아간다.  
- 이러한 DFS를 구현하기 위한 방법으로는  ```재귀```와 ```스택```이 있다.  

#### ☝🏻재귀 함수를 이용한 DFS 풀이
잠깐! 인접 행렬과 리스트에 대해서 기억나지 않으시는 분들을 위해(https://sarah950716.tistory.com/12)  

- 인접 행렬을 이용한 구현
```
// DFS - Recursion + 인접 행렬
void dfs_recursion(int index, int y) {
  visited[index] = true; 
  for (int i=1; i<=n; i++) {
    if (a[inedx][i] == 1 && visited[i] == false) {
      dfs(i); 
     }
   }
}
```
- 인접 리스트를 이용한 구현
```
void dfs(int x) { 
  visited[x] = true;
  for (int i=0; i<a[x].size(); i++) { 
    int y = a[x][i];
    if (visited[y] == false) { 
      dfs(y);
    } 
   }
}

```

### ✌🏻Stack을 이용한 DFS 풀이
그림으로 이해해요 -> https://palpit.tistory.com/898
```
void dfsWithStack(int start, vector<int> graph[], bool check[]){

	stack<int> s;
	s.push(start);
	visited[start] = true;

	while(!s.empty()){

		int current_node = s.top();
		s.pop();
		for(int i=0; i<graph[current_node].size(); i++){

			int next_node = graph[current_node][i];

			if(visited[next_node]==false){
				visited[next_node] = true;
				// pop()을 했었기 때문에 현재 current_node도 넣어줘야한다.
				s.push(current_node);
				s.push(next_node);
				break;
			}
		}
	}
}
```

### DFS 구현 시 주의해야할 점
- 이러한 DFS를 ```사이클 있는 그래프```탐색에 적용하여 풀이할 때에는, 어떤 노드를 방문했었는지 여부를 반드시 체크해야한다. 검사하지 않을 경우, 무한루프에 빠져  ```런타임 에러```가 발생하게 된다.

### DFS 장점👍🏻
- 찾으려는 노드가 깊은 단계에 있는 경우 BFS 보다 빠르게 찾을 수 있다.
- 현 경로상의 노드를 기억하기 때문에 ```적은 메모리```를 사용한다.

### DFS 단점👎🏻
- 목표 노드가 없는 경로에 깊게 빠질 수 있다.
- DFS를 통해서 얻어진 해가 최단 경로라는 보장이 없다. DFS는 해에 도착하면 탐색을 종료하기 때문이다.

### DFS의 Time Complexity
- DFS는 그래프(정점의 수:N, 간선의 수:E)의 모든 간선을 조회한다.
- 인접 행렬의 경우 ```O(N^2)```, 인접 리스트의 경우 ```O(N+E)```의 시간 복잡도를 가진다.

### DFS, 그래서 어떤 문제 유형에 적용될까?
- 사이클 탐지(Cycle Detection), 위상 정렬(Topological Sorting)

### 짧은 시간 내에 감잡기 좋은 문제
- 타겟 넘버: https://programmers.co.kr/learn/courses/30/lessons/43165
- 네트워크: https://programmers.co.kr/learn/courses/30/lessons/43162


## BFS
루트 노드(혹은 다른 임의의 노드)에서 시작해서 인접한 노드를 먼저 탐색하는 방법.  
쉽게 풀어 말하자면, 탐색에 있어 ```자식 노드 탐색의 우선순위```보다 ```형제 노드 탐색의 우선순위```가 더 높은 탐색 방법을 뜻한다.  

- 이러한 DFS를 구현하기 위한 방법으로는  ```Queue```가 있다.  

![](ReadmeResource/bfs.gif)
### Queue을 이용한 BFS 풀이
그림으로 이해해요 -> https://sarah950716.tistory.com/13

-인접 행렬을 이용한 풀이
```
queue<int> q;
visited[1] = true; 
q.push(1); 

while (!q.empty()) {
  int x = q.front(); 
  q.pop();
  for (int i=1; i<=n; i++) {
    if (a[x][i] == 1 && check[i] == false) { 
      check[i] = true;
      q.push(i); 
    }
  } 
}
```
-인접 리스트를 이용한 풀이
```
queue<int> q;
check[1] = true; q.push(1); 

while (!q.empty()) {
  int x = q.front(); 
  q.pop();
  
  for (int i=0; i<a[x].size(); i++) {
    int y = a[x][i];
    if (check[y] == false) {
      check[y] = true; q.push(y); 
     }
   } 
}
```
### BFS 장점👍🏻
- 너비를 우선으로 탐색하기 때문에 답이 되는 경로가 여러 개인 경우에도 최단 경로임을 보장한다.
- 노드의 수가 적고 깊이가 얕은 해가 존재할 때 유리하다.

### BFS 단점👎🏻
- 재귀호출을 사용하는 DFS와 달리 Queue를 이용해 다음에 탐색할 노드들을 저장하기 때문에 노드의 수가 많을수록 필요없는 노드들까지 저장행야하기 때문에 더 큰 저장공간이 필요하다.
- 노드의 수가 늘어나면 탐색해야 하는 노드 또한 많아지기  비현실적이다.

### BFS의 Time Complexity
- 너비 우선 탐색의 시간복잡도는 깊이 우선 탐색과 다를 것이 없다..!
- 따라서 인접 리스트로 구현된 경우에는 ```O(N+E)```, 인접 행렬로 구현했을 경우 ```O(N^2)```의 시간복잡도를 갖게 된다.

### BFS, 그래서 어떤 문제 유형에 적용될까?
- 최소신장트리(Minimum Spanning Trees), 최단경로(Shortest Paths)

### 짧은 시간 내에 감잡기 좋은 문제
- 안전영역: https://www.acmicpc.net/problem/2468
- 토마토: https://www.acmicpc.net/problem/7569
