//
//  main.cpp
//  DrawingDoll
//
//  Created by 조윤영 on 2020/06/19.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> board = {{0,0,0,0,0},{0,0,1,0,3},{0,2,5,0,1},{4,2,4,4,2},{3,5,1,3,1}};
    vector<int> moves = {1,5,3,5,1,2,1,4};
    solution(board, moves);
    return 0;
}
