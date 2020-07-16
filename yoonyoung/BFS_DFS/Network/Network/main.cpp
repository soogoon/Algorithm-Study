//
//  main.cpp
//  Network
//
//  Created by 조윤영 on 2020/06/28.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<bool> visited;

void dfs(int index, vector<vector<int>>& computers) {
    visited[index] = true;
    
    for(int i=0; i<computers[index].size(); i++) {
        if(computers[index][i] == 1 && !visited[i]) dfs(i, computers);
        //관련 있는 컴퓨터이며, 방문한 적이 없다면 재귀호출
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    visited.assign(computers.size(), false); //방문 체크를 위한 초기화
    
    for(int i=0; i<computers.size(); i++) {
        if(!visited[i]) {//방문하지 않은 컴퓨터라면,
            answer++;//이 컴퓨터를 기준으로 네트워크가 형성되기 때문에 네트워크 수 증가
            dfs(i, computers);
        }
    }
    return answer;
}

int main() {
    vector<vector<int>> computers = {{1,1,0},{1,1,1},{0,1,1}};
    int n = 3;
    cout<<solution(n, computers);
    
    return 0;
}
