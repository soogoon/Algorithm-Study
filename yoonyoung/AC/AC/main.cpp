//
//  main.cpp
//  AC
//
//  Created by 조윤영 on 2020/06/23.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/5430
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

void stringToVector(string input_array);
void solution();
void input();

int T = 0;
string calculateFunc = "";
int n = 0;
string arrays = "";
deque<int> dq;
bool isError = false;
bool isReverse = false;

void stringToVector(string input_array) {
    
    if(input_array == "[]") return;

    
    string temp = "";
    for(int i=1; i<input_array.size(); i++) {
        
        if(input_array[i] == ']' || input_array[i] == ',') {
            dq.push_back(stoi(temp));
            temp = "";
        } else {
            temp += input_array[i];
        }

    }
}

void input() {
    cin>>T;
    for(int i=0; i<T; i++) {
        dq.clear();
        isError = false;
        isReverse = false;
        
        cin>>calculateFunc;
        cin>>n;
        cin>>arrays;
        
        stringToVector(arrays);
        solution();
    }
}

void printOutput() {
    if(dq.empty()) {
        cout<<"[]\n";
        return;
    }
    string output = "[";
    if(isReverse) {
        while(!dq.empty()) {
            output += to_string(dq.back());
            dq.pop_back();
            if(!dq.empty())output += ',';
        }
    }else  {
        while(!dq.empty()) {
               output += to_string(dq.front());
               dq.pop_front();
               if(!dq.empty())output += ',';
           }
    }
   
    output +=']';
    cout<<output<<"\n";
}
void deleteArray() {
    if(dq.empty()) {
        isError = true;
        return;
    }
    
    if(isReverse) dq.pop_back();
    else dq.pop_front();
}

void solution() {
    for(int i=0; i<calculateFunc.size(); i++) {
        if(calculateFunc[i] == 'R') isReverse = !isReverse;
        else if(calculateFunc[i] == 'D') deleteArray();
        
        if(isError) {
            cout<<"error"<<"\n";
            return;
        }
    }
    printOutput();
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    input();
    return 0;
}
