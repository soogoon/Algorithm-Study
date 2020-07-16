//
//  main.cpp
//  Study0617_Stack_Printer
//
//  Created by 조윤영 on 2020/06/17.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Printer {
    int location;
    int priority;
    
    Printer(int _location, int _priority) {
        location = _location;
        priority = _priority;
    };
};

int solution(vector<int> priorities,  int location) {

    int answer = 0;
    
    queue<Printer> q; //(index, index의 값)
    priority_queue<int> pq;//우선순위큐
    
    for(int i=0; i<priorities.size(); i++) {
        q.push({i, priorities[i]});
        pq.push({priorities[i]});
    }
    
    while(!q.empty()) {//대기 목록이 빌 때까지 똘린다
        if(q.front().priority == pq.top()) { //해당 값이 배열에 존재하는 수 중 가장 큰 값일 때
            if(q.front().location == location)return ++answer; //출력될 순서의 작업이 찾고자 했던 location의 원소일 때
            else {//해당 location의 원소는 아니지만 가장 큰 수일 경우에는 출력해버리고, 순번 미루기
                answer++;
                q.pop();
                pq.pop();
            }
        } else {//현재 가장 큰 숫자가 아닐 경우, 뒤로 돌아가서 대기하기
            q.push(q.front());
            q.pop();
        }
    }
       return answer;
}

int main(int argc, const char * argv[]) {
    
    vector<int> priorities = {2,1,3,2};
    int location = 2;
    cout<<solution(priorities, location);
    
    return 0;
}
