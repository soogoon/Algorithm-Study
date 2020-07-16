//
//  main.cpp
//  moveTerrain
//
//  Created by 조윤영 on 2020/07/04.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://programmers.co.kr/learn/courses/30/lessons/62050

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

#define MAX_SIZE 301

using namespace std;

//다른 사람의 풀이를 보고 시도한 두 번째 시도..
//1.사다리가 없이 이동이 가능i한 지형끼리 묶기
//2.같은 땅덩어리로 묶이지 않은 지형들 간의 거리 구하기
//3.사다리의 설치 최소 비용 구하기

int answer = 0;
int groupCnt = 1;
int visited[MAX_SIZE][MAX_SIZE];
struct Dir {
    int y;
    int x;
};

struct Position {
    int y;
    int x;
    Position(int _y, int _x) {
        y = _y;
        x = _x;
    };
};

int N = 0;
Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};
vector<int> parent;
vector<pair<int, pair<int,int>>> edge;

bool canMove(int y, int x) {
    if(0<= y && y <N && 0<=x && x<N) return true;
    return false;
}

void bfs(int y, int x, int groupNumber, vector<vector<int>> land, int height) {

    queue<Position> q;
    q.push(Position(y,x));
    visited[y][x] = groupNumber;
    
    while(!q.empty()) {
        int currentY = q.front().y;
        int currentX = q.front().x;
        q.pop();
        
        for(int i=0; i<4; i++) {
            int nextY = currentY + moveDir[i].y;
            int nextX = currentX + moveDir[i].x;
            
            if(canMove(nextY, nextX) && visited[nextY][nextX] == 0 && abs(land[currentY][currentX] - land[nextY][nextX]) <= height) {
                visited[nextY][nextX] = groupNumber;
                q.push(Position(nextY, nextX));
            }
        }
    }
}

void makeGroup(vector<vector<int>> land, int height) {
    for(int i=0; i<land.size(); i++) {
        for(int j=0; j<land[i].size(); j++) {
            if(visited[i][j] == 0) bfs(i, j, groupCnt++, land, height);
        }
    }
}

void findDistanceBetweenGroup(vector<vector<int>> land, int height) {
    for(int y=0; y<land.size(); y++) {
        for(int x=0; x<land.size(); x++) {
            for(int h=0; h<4; h++) {
                int nextY = y+ moveDir[h].y;
                int nextX = x+ moveDir[h].x;
                
                if(canMove(nextY, nextX)){
                    if(visited[y][x] != visited[nextY][nextX]) {
                        //이동할 수 있으며 + 다른 영역일 때
                        int differ = abs(land[y][x] - land[nextY][nextX]);
                        edge.push_back(make_pair(differ, make_pair(visited[y][x], visited[nextY][nextX])));
                    }
                }
            }
        }
    }
}

int findParent(int a) {
    if(a == parent[a]) return a;
    return parent[a] = findParent(parent[a]); //부모를 찾지 못했다면, 재귀 돌리기
}

void Union(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    parent[b] = a;
}

bool isSameParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if(a == b) return true;
    return false;
}

//'MST(Minimal Spanning Tree)': 가중치의 합을 최소로 만드는 스패닝 트리
//1. 모든 간선들의 가중치를 오름차순으로 정렬
//2. 가중치가 가장 작은 간선을 선택
//3. 2에서 선택한 간선이 연결하려는 2개의 노드가 아직 서로 연결되지 않은 상태라면, 2개의 노드를 서로 연결
//4. 위의 과정 반복
//=>
//1. 서로 같은 부모를 갖는지 판단해주는 함수
//2. 1번 과정을 위해서 부모를 찾는 find 함수
//3. 서로 다른 부모일 경우, 두 개의 노드를 연결해야 하므로, 합치는 union 함수

void kruskal() {
    parent.resize(groupCnt); //resize는 공간을 n으로 변경하고, 확장되는 공간의 값을 x값으로 초기화
    for(int i=1; i<groupCnt; i++) parent[i] = i;
    //parent[1] = 1
    
    sort(edge.begin(), edge.end());//cost를 오름차순으로 정렬?
    
    for(int i=0; i<edge.size(); i++) {
        int n1 = edge[i].second.first;
        int n2 = edge[i].second.second;
        int cost = edge[i].first;

        if(!isSameParent(n1, n2)) {
            Union(n1, n2); //3. 서로 다른 부모일 경우, 두 개의 노드를 연결해야 하므로, 합치는 union 함수
            answer += cost;
        }
    }
}

int solution(vector<vector<int>> land, int height ) {
    N = land.size();
    makeGroup(land, height);//1. 사다리가 없이 이동이 가능한 지형끼리 묶기
    findDistanceBetweenGroup(land, height);//2. 같은 땅덩어리로 묶이지 않은 지형들 간의 높이 차 구하기
    kruskal();//3. 사다리의 설치 최소 비용 구하기
    
    return answer;
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> land = {{1,4,8,10},{5,5,5,5},{10,10,10,10},{10,10,10,20}};
    int height = 3;
    cout<<solution(land, height);
    return 0;
}
