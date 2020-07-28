//
//  main.cpp
//  RemoteControl
//
//  Created by 조윤영 on 2020/07/28.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://www.acmicpc.net/problem/1107
//
//음.. https://jaimemin.tistory.com/659
//

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#define INF 987654321
#define MAX_SIZE 500001

using namespace std;

int N, M;
vector<int> buttons;
map<int,bool> is_broken;

void input() {
    cin>> N;
    cin>>M;
    buttons.assign(M, 0);
    int button = 0;
    for(int  i=0; i<M; i++) {
        
        cin>> button;
        is_broken[button] = true;
    }
}



bool possible(int num) {
    if(num == 0) {
        if(!is_broken[0]) return true;
        else return false;
    }
    
    while(num) {
        if(is_broken[num%10]) return false;
        
        num /= 10;
    }
    
    return true;
}

int length(int num) {
    //0이면 길이 1(중요한 예외처리)
    if (num == 0) return 1;
    
    int result = 0;
    while (num) {
        num /= 10;
        result++;
    }
    
    return result;

}

//현재 채널100에서 바꾸는 경우 조작해야하는 횟수
int changeFromHundred() {
    return abs(N-100);
}

int changeEntirely() {
    int result = INF;
    int similar = 0;
    
    for(int i=0; i<MAX_SIZE; i++) {
        if(possible(i)) {
            int click = abs(N - i);
            if(result >click) {
                result = click;
                similar = i;
            }
        }
    }
    return result + length(similar);
}

void solution() {
    cout<<min(changeFromHundred(), changeEntirely())<<"\n";
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    input();
    solution();
    
    return 0;
}

//int minNumb = 0;
//int maxNumb = 0;
//int findPrevNumb(int target) {
//    for(int i = target-1; i>=0; i--) {
//        if(!is_broken[i]) return i;
//    }
//
//    return -1;
//}
//
//int findNextNumb(int target) {
//    int nextN = target+1;
//
//    while(true) {
//        if(!is_broken[nextN]) return nextN;
//        else nextN++;
//    }
//
//    return -1;
//}
//
//int findMinNumb() {
//    for(int i=0; i<10; i++) {
//        if(!is_broken[i]) return i;
//    }
//
//    return -1;
//}
//
//int findMaxNumb() {
//    for(int i=9; i>=0; i--) {
//        if(!is_broken[i]) return i;
//    }
//
//    return -1;
//}
//
//string initNumb() {
//    string s_currentChannel;
//
//    for(int i=0; i<N.size(); i++) {
//        char n = N[i];
//        int numb = n - '0';
//
//        if(is_broken[numb]) { //고장난 버튼이라면?
//
//            int prevN = findPrevNumb(numb);
//            int nextN = findNextNumb(numb);
////            cout<<stoi(s_currentChannel+to_string(prevN))<<","<<stoi(s_currentChannel+ to_string(nextN))<<endl;
////            cout<<stoi(N)-stoi(s_currentChannel+to_string(prevN))<<","<<stoi(s_currentChannel+ to_string(nextN)) - stoi(N)<<endl;
////
//
//            if(prevN == -1 || stoi(N) - (stoi(s_currentChannel+to_string(prevN))) >= (stoi(s_currentChannel+ to_string(nextN)) - stoi(N))) {
//                //예를 들어서 고장난 버튼이 0이거나 이전 버튼이 모두 고장이 나서 대체할 버튼이 없는 경우
//                //=> nextN으로 해야함
//                s_currentChannel+= to_string(nextN);
//
//                for(int j=i+1; j<N.size(); j++) s_currentChannel+= to_string(minNumb);
//
//                return s_currentChannel;
//            } else {
//                s_currentChannel+= to_string(prevN);
//
//                for(int j=i+1; j<N.size(); j++) s_currentChannel+= to_string(maxNumb);
//
//                return s_currentChannel;
//            }
//        } else {//고장나지 않은 버튼이라면?
//            s_currentChannel+= n;
//        }
//    }
//
//    return s_currentChannel;
//}
//
//void solution() {
//    int answer = 0;
//
//    minNumb = findMinNumb();
//    maxNumb = findMaxNumb();
//
//    int targetNumb = stoi(initNumb());
//
//    if(abs(stoi(N) - 100) > abs(stoi(N) - targetNumb)) {
//        answer = N.size() + abs(stoi(N) - targetNumb);
//    } else {
//        answer = abs(stoi(N) - 100);
//    }
//
//
//    cout<<answer<<"\n";
//}
