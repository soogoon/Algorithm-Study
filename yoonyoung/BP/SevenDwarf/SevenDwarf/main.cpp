//
//  main.cpp
//  SevenDwarf
//
//  Created by 조윤영 on 2020/07/21.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/2309

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> dwarfs(9, 0);
vector<bool> visited(9, false);
bool findDwarfs = false;

void input() {
    for(int i=0; i<9; i++) cin>>dwarfs[i];
}

void dfs(int cnt, int sum) {
    if (sum> 100) return;
    else if(sum == 100 && cnt == 7) {
        findDwarfs = true;
        return;
    }
        
    for(int i=0; i<dwarfs.size(); i++) {
        if(!visited[i]) {
            visited[i] = true;
            dfs(cnt+1, sum+dwarfs[i]);
            if(!findDwarfs) visited[i] = false;
            else return;
        }
    }
    return;
}

//DFS
void solution()  {
    vector<int> answer;
    
    for(int i=0; i<dwarfs.size(); i++) {
        visited[i] = true;
        dfs(1, dwarfs[i]);
        
        if(findDwarfs) {
            for(int j=0; j<dwarfs.size(); j++) {
                if(visited[j])  answer.push_back(dwarfs[j]);
            }
            
            sort(answer.begin(), answer.end());
            for(int a: answer) cout<<a<<"\n";
            return;
        }
        
        visited[i] = false;
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    solution();
    return 0;
}
