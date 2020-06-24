//
//  main.cpp
//  DrawingDoll
//
//  Created by 조윤영 on 2020/06/19.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#define MAX_SIZE 31

using namespace std;

bool visited[MAX_SIZE][MAX_SIZE];

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> s;
    
    for(int i=0; i<moves.size(); i++) {
        int index = moves[i]-1;
        
        for(int j=0; j<board.size(); j++) {
            if(board[j][index] !=0 && !visited[j][index]) {
                visited[j][index] = true;
                if(!s.empty() && s.top() == board[j][index]){
                    s.pop();
                    answer += 2;
                }else {
                    s.push(board[j][index]);
                }
                break;
            }
        }
    }
    return answer;
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> board = {{0,0,0,0,0},{0,0,1,0,3},{0,2,5,0,1},{4,2,4,4,2},{3,5,1,3,1}};
    vector<int> moves = {1,5,3,5,1,2,1,4};
    cout<<solution(board, moves);
    return 0;
}
