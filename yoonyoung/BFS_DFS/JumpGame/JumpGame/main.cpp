//
//  main.cpp
//  JumpGame
//
//  Created by 조윤영 on 2020/07/10.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/15558
//

#include <iostream>
#include <queue>
#define MAX_SIZE 100001
using namespace std;

int N = 0;
int K = 0;
char map[2][MAX_SIZE];
int answer = 0;
int cnt = 0;


void input() {
    cin>> N>> K;
    for(int i=0; i<N; i++) cin>>map[0][i];
    for(int i=0; i<N; i++) cin>>map[1][i];
}

int solution() {
    queue<pair<int,int>> q;
    q.push({0,0});
    
    while(!q.empty()) {

        int qSize = q.size();
        for(int i=0; i<qSize; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
        
            if(y <cnt) continue;
            
            if(y>=N) return 1;
            if(cnt>=N) return 0;
            if(map[x][y] == '0') continue;
            
            //1.전진
            q.push({x, y+1});
            //2.후진
            q.push({x, y-1});
            //3.점프 +k
            if(x == 0) q.push({1, y+K});
            else q.push({0, y+K});
        }
        cnt++;
    }
    
    return 0;
}


int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    input();
    cout<<solution()<<"\n";
    
    return 0;
}
