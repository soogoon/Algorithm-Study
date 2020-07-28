//
//  main.cpp
//  Lotto
//
//  Created by 조윤영 on 2020/07/27.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/6603
//

#include <iostream>
#include <vector>
#include <queue>
#define LottoCnt 6

using namespace std;
void solution();

vector<int> numbs;
vector<bool> visited;
int answer = 0;
int k = -1;

void input() {
    while(k != 0) {
        cin>>k;
        numbs.assign(k, 0);
        visited.assign(k, false);
        for(int i=0; i<k; i++) {
            cin>> numbs[i];
        }
        
        solution();
        cout<<"\n";
    }
}


struct Collections {
    int index;
    int cnt;
    
    Collections(int _index, int _cnt) {
        index = _index;
        cnt = _cnt;
    };
};

void DFS(int index, int cnt) {
    if(cnt == LottoCnt) {
        for(int i=0; i<k; i++) {
            if(visited[i])cout<<numbs[i]<<" ";
        }
        cout<<"\n";
        return;
    }
    for(int i=index+1; i<k; i++) {
        visited[i] = true;
        DFS(i,cnt+1);
        visited[i] = false;
    }
}

void solution() {
    //DFS
    for(int i=0; i<k-LottoCnt+1; i++) {
        visited[i] = true;
        DFS(i, 1);
        visited[i] = false;
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    input();
    
    return 0;
}
