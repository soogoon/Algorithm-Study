//
//  main.cpp
//  SafeArea
//
//  Created by 조윤영 on 2020/06/29.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/2468

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAX_SIZE 101

using namespace std;

int room[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
bool temp_visited[MAX_SIZE][MAX_SIZE];
int N = 0;

int lowerLand = MAX_SIZE;
int highestLand = 0;

struct Location  {
    int y;
    int x;
    Location(int _y, int _x) {
        y = _y;
        x = _x;
    };
};

struct Dir {
    int y;
    int x;
};

Dir moveDir[4] = {{-1,0},{1,0},{0,-1},{0,1}};
vector<Location> wet_location;

void input() {
    cin>> N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin>>room[i][j];
            if(lowerLand > room[i][j]) {
                wet_location.clear();
                lowerLand = room[i][j];
            }
            else if(highestLand < room[i][j]) highestLand = room[i][j];
            if(lowerLand >= room[i][j]) wet_location.push_back(Location(i,j));
        }
    }
}

bool isInBoundary(int y, int x) {
    if(0<=y &&  y<N && 0<=x && x<N)return true;
    return false;
}

void findRelatedLand(int y, int x) {
    queue<Location> q;
    q.push(Location(y,x));
    
    while(!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        q.pop();
        
        for(int i=0; i<4; i++) {
            int nextY = y+ moveDir[i].y;
            int nextX = x+ moveDir[i].x;
            if(isInBoundary(nextY, nextX) && !temp_visited[nextY][nextX]) {
                temp_visited[nextY][nextX] = true;
                q.push(Location(nextY, nextX));
            }
        }
    }
}

int checkLandCnt() {
    int landCnt = 0;
    memcpy(temp_visited, visited, sizeof(visited));

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(!temp_visited[i][j]) {
                findRelatedLand(i,j);
                landCnt++;
            }
        }
    }
    return landCnt;
}

bool isCanSink(int y, int x) {
    if(isInBoundary(y, x) && !visited[y][x] && room[y][x] <=lowerLand)return true;
    return false;
}

void solution() {
    int answer = 0;
    
    for(int i=0; i<wet_location.size(); i++) {
        Location wl = wet_location[i];
        visited[wl.y][wl.x] = true;
    }

    if(lowerLand == highestLand) answer =  1;
    while(lowerLand != highestLand) {
        int landCnt = checkLandCnt();
        answer = (answer<landCnt)?landCnt:answer;
               
        lowerLand++;
        for(int i=0; i<N; i++)  {
            for(int j=0; j<N; j++) {
                if(isCanSink(i, j)) {
                    visited[i][j] = true;
                }
            }
        }
    }
    cout<<answer<<"\n";
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    input();
    solution();
    
    return 0;
}
