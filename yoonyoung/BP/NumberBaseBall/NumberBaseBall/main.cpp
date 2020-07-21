//
//  main.cpp
//  NumberBaseBall
//
//  Created by 조윤영 on 2020/07/15.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://programmers.co.kr/learn/courses/30/lessons/42841

#include <string>
#include <vector>
#include <iostream>

bool isStrike(int i, int numb, int cnt);
bool isBall(int i, int numb, int cnt);
using namespace std;

int solution(vector<vector<int>> baseball) {
    int answer = 0;

    //특정 조건을 만족하는 숫자"들"을 구할 때, 완전탐색이 유리한 경우도 있다.
    //완탐을 쓰는 문제의 종류는 문제를 많이 풀어보면서 감을 잡아가자.
    
    for(int i=123; i<=987; i++) { //각자 서로 다른 3자리 임의의 숫자이기 때문에 나올 수 있는 최솟값은 123, 최대값은 987인 것을 알 수 있다!
        
        string temp = to_string(i);
        //제1규칙: 추리해야하는 숫자가 0을 포함해서는 안된다: 왜냐하면 1~9까지의 3자리 임의의 숫자가 만들어지는데, 숫자0카드를 포함하지는 않기 때문.
        if(temp.at(0) == '0' || temp.at(1) == '0' || temp.at(2) == '0') {
            continue;
        }
        
        //제2규칙: 같은 숫자가 나오면 안된다.
        if(temp.at(0) == temp.at(1) || temp.at(1) == temp.at(2) || temp.at(0) == temp.at(2)) {
            continue;
        }
        
        int check = 1; //Check 초기화
        //해당 숫자가 strike와 ball을 만족하는 숫자인지 확인
        for(int j=0; j<baseball.size(); j++) {
            if((!isStrike(i, baseball[j][0], baseball[j][1])) || (!isBall(i, baseball[j][0], baseball[j][2]))) { //어떤 스트라이크와 볼을 만족하지 못할 때,
                check =0; //조건에 맞지 않는 숫자로 판단.
            }
        }
        
        if(check !=0) answer++; //조건에 맞다면 정답추가
    }
    
    return answer;
}

bool isStrike(int i, int numb, int strike) {
    int num = 0;
    string si = to_string(i);
    string sNumb = to_string(numb);
    
    for(int j=0; j<si.size(); j++) {
        if(si[j] == sNumb[j]) num++;
    }
    if(num == strike)return true;
    else return false;
}

bool isBall(int i, int numb, int ball) {
    int num = 0;
    string si = to_string(i);
    string sNumb = to_string(numb);
    
    for(int j=0; j<si.size(); j++) {
        for(int k=0; k<sNumb.size(); k++) {
            if((j!=k)&&(si[j] == sNumb[k]))num++;
        }
    }
    
    if(num == ball)return true;
    else return false;
}

int main(int argc, const char * argv[]) {
    vector<vector<int>> vec{{123,1,1},{356,1,0},{327,2,0},{489,0,1}};
    cout<<solution(vec);
    return 0;
}
