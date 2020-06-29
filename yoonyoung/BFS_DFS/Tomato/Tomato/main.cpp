//
//  main.cpp
//  Tomato
//
//  Created by 조윤영 on 2020/06/24.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/7569
//

#include <iostream>
#include <queue>
#define MAX_SIZE 101

using namespace std;

int M = 0;
int N = 0;
int H = 0;
int room[MAX_SIZE][MAX_SIZE][MAX_SIZE];

struct Dir {
    int h;
    int y;
    int x;
};
Dir moveDir[6] = {{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}};

struct Tomato {
    int box;
    int y;
    int x;
    Tomato(int _box, int _y, int _x) {
        box = _box;
        y = _y;
        x = _x;
    };
};
queue<Tomato> ripen_tomato;
int tomatoSum = 0;
int ripenTomatoSum = 0;

void input() {
    cin>> M >> N >> H;
    
    for(int h=0; h<H; h++) {
        for(int i=0; i<N;  i++) {
            for(int j=0; j<M; j++) {
                cin>> room[h][i][j];
                if(room[h][i][j] == 1) {
                    ripen_tomato.push(Tomato(h, i, j));
                    tomatoSum++;
                    ripenTomatoSum++;
                }else if (room[h][i][j] == 0) tomatoSum++;
            }
        }
    }
}

bool isInBoundary(int box, int y, int x) {
    if(0<= y && y<N && 0<=x && x<M && 0<=box && box<H) return true;
    return false;
}

int solution() {
    int answer = 0;
    
    while(!ripen_tomato.empty()) {
        bool isRipen = false;
        int tomatoCnt = ripen_tomato.size();
        
        
        for(int i=0; i<tomatoCnt; i++) {
            int tomatoBox = ripen_tomato.front().box;
            int tomatoY = ripen_tomato.front().y;
            int tomatoX = ripen_tomato.front().x;
            ripen_tomato.pop();
            
            for(int i=0; i<6; i++) {
                int nextTomatoBox = tomatoBox + moveDir[i].h;
                int nextTomatoY = tomatoY + moveDir[i].y;
                int nextTomatoX = tomatoX + moveDir[i].x;
                
                if(isInBoundary(nextTomatoBox, nextTomatoY, nextTomatoX)) {
                    int nextTomato = room[nextTomatoBox][nextTomatoY][nextTomatoX];
                    
                    if (nextTomato == 0) {//익지 않은 토마토라면,
                         isRipen = true;
                        room[nextTomatoBox][nextTomatoY][nextTomatoX] = 1;
                        ripen_tomato.push(Tomato(nextTomatoBox, nextTomatoY, nextTomatoX));
                        ripenTomatoSum++;
                    }
                }
            }
        }
        if(isRipen)answer++;
    }
    
    if(ripenTomatoSum < tomatoSum) answer = -1;
    
    return answer;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    cout<<solution()<<"\n";
    return 0;
}
