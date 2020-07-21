//
//  main.cpp
//  MaxDiffer
//
//  Created by 조윤영 on 2020/07/15.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct compare {
    bool operator() (const int &a, const int &b) {
        return abs(a)>abs(b);
    }
};


int N = 0;
vector<int> numb_list;

void input() {
    cin>> N;
    numb_list.assign(N, 0);
    for(int i=0; i<N; i++) cin>>numb_list[i];
}

void solution() {
    vector<int> answer;
    int sum = 0;
    sort(numb_list.begin(), numb_list.end(), compare());
    //20 15 10 8 4 1
    
    for(int i=0; i<numb_list.size(); i++) {
        cout<<numb_list[i]<<" ";
    }

    //-8 3 1 //(2)
    for(int i=0; i<N/2; i++) {
        answer.push_back(numb_list[N/2+i]);
        answer.push_back(numb_list[i]);
    }
    
    if(N%2 != 0) answer.push_back(numb_list[N-1]);
    
    cout<<endl;
    for(int i=0; i<answer.size(); i++) {
        cout<<answer[i]<<" ";
    }

    for(int i=0; i<answer.size()-1; i++) {
        int a = abs(answer[i]-answer[i+1]);
        sum += a;
        
    }
    cout<<endl;
    cout<<sum<<"\n";
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    solution();
    
    return 0;
}


/*
 6
 -20 1 15 8 4 10
 오름차순 정렬 1 4 8 10 15 20
 8  4  1
  20 15 10
 
=>8 20 4 15 1 10 일 때 가장 최대
 
 
 1 -8 3
 내림차순 정렬: -8 3 1
 
 
 */

/*
 6
 -5 0 -4 -3 -3 -2
 : correct = 14, wrong = 13

 5
 2 0 0 -1 3
 : correct = 12, wrong = 11

 6
 2 -4 -4 0 1 4
 : correct = 29, wrong = 28

 4
 0 -1 -4 5
 : correct = 19, wrong = 17

 6
 -5 -3 2 1 -5 5
 : correct = 38, wrong = 37

 4
 1 -3 -4 4
 : correct = 20, wrong = 19

 4
 2 3 4 -1
 : correct = 11, wrong = 10

 4
 -1 -5 2 1
 : correct = 16, wrong = 15

 4
 -2 1 -1 0
 : correct = 7, wrong = 6

 5
 -1 -1 0 -3 -4
 : correct = 12, wrong = 11
 
 */
