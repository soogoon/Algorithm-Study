//
//  main.cpp
//  Carpet
//
//  Created by 조윤영 on 27/11/2019.
//  Copyright © 2019 조윤영. All rights reserved.
//
//https://programmers.co.kr/learn/courses/30/lessons/42842
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//2020.07.20
vector<int> solution2(int brown, int yellow) {
    vector<int> answer;
    
    int area = brown + yellow;
    int height = 0;
    int maxWidth = (brown-2)/2;
    
    for(int width=3; width<maxWidth+1; width++) {
        
        height = (brown - width *2)/2+2;
        int yellowCnt = (width-2) * (height-2);
        if((yellowCnt == yellow) && (width >= height)) {
            answer.push_back(width);
            answer.push_back(height);
            break;
        }
    }
    
    return answer;
}


vector<int> solution(int brown, int red) {
    vector<int> answer;
    int area = brown+ red; //카펫의 넓이
    int width = 0;
    
    int limit = (int)sqrt(area);
    for(int i=3; i<=limit; i++) {
        width = area/i;
        
        if(area%i == 0 && width >= i) { //가로 길이가 정수로 나누어 떨어지는지 & 세로 길이보다 큰지 확인
            if((width-2)*(i-2) == red){
                cout<<width<<","<<i<<endl;
                answer.push_back(width);//가로 길이 집어넣고
                answer.push_back(i);//세로 길이 집어넣고
            }
            
        }
    }
    
    return answer;
}

int main(int argc, const char * argv[]) {
    solution2(24,24);
    return 0;
}
