//
//  main.cpp
//  TravelRoute
//
//  Created by 조윤영 on 2020/07/09.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://programmers.co.kr/learn/courses/30/lessons/43164

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#define source "ICN"

using namespace std;
typedef pair<int, string> TicketInfo;

vector<bool> visited;
vector<string> answer;

bool dfs(string depart, vector<vector<string>> tickets, int userTicketCnt) {

    answer.push_back(depart);
     if(userTicketCnt == tickets.size()) return true;
    
    for(int i=0; i<tickets.size(); i++) {
        if(!visited[i] && tickets[i][0] == depart) {
            visited[i] = true;
            if(dfs(tickets[i][1], tickets, userTicketCnt+1))return true;
            
            visited[i] = false;
        }
    }
    answer.pop_back();
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    visited.assign(tickets.size(), false);
    vector<TicketInfo> destination;
    sort(tickets.begin(), tickets.end());
    
    dfs(source, tickets, 0);
    
    return answer;
}

int main(int argc, const char * argv[]) {
    vector<vector<string>> tickets =
//    {{"ICN","A"},{"A","B"},{"B","A"},{"A","ICN"},{"ICN","A"}};
    {{"ICN","BOO"},{"ICN","COO"},{"COO","DOO"},{"DOO","COO"},{"BOO","DOO"},{"DOO","BOO"},{"BOO","ICN"},{"COO","BOO"}};
    solution(tickets);
    return 0;
}
