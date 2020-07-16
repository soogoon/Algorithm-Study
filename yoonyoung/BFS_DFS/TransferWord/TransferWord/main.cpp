//
//  main.cpp
//  TransferWord
//
//  Created by 조윤영 on 2020/07/08.
//  Copyright © 2020 조윤영. All rights reserved.
//
//https://programmers.co.kr/learn/courses/30/lessons/43163

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <queue>

#define MAX_SIZE 1000000

using namespace std;

struct WordInfo {
    int index;
    string word;
    int cnt;
    
    WordInfo(int _index, string _word, int _cnt) {
        index = _index;
        word = _word;
        cnt = _cnt;
    };
};

int answer = MAX_SIZE;
vector<bool> visited;
queue<WordInfo> q;



void dfs(string currentWord, string target, vector<string> words, int cnt) {
    if(currentWord == target) {
        answer = min(answer, cnt);
    }
    
    for(int i=0; i<words.size(); i++) {
        if(!visited[i]) {
            int diff = 0;
            for(int j=0; j<words[i].size(); j++) {
                if(words[i][j] != currentWord[j]) diff++;
                if(diff >1) break;
            }
            if(diff == 1) {
                visited[i] = true;
                dfs(words[i], target, words, cnt+1);
                visited[i] = false;
            }
        }
    }
}

void bfs(string target, vector<string> words) {
    while(!q.empty()) {
        int index = q.front().index;
        string word = q.front().word;
        int cnt = q.front().cnt;
        q.pop();
        visited[index] = true;
        
        if(word == target) {
            answer = min(answer, cnt);
            continue;
        }
        
        for(int i=0; i<words.size(); i++) {
            if(!visited[i]) {
                int diff = 0;
                for(int j=0; j<words[i].size(); j++) {
                    if(words[i][j] != word[j]) diff++;
                    if(diff >1) break;
                }
                if(diff == 1) {
                    q.push(WordInfo(i, words[i], cnt+1));
                }
            }
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    visited.assign(words.size(), false);
    
    //dfs를 이용한 풀이
    dfs(begin, target, words, 0);
    
    //bfs를 이용한 풀이
    q.push(WordInfo(MAX_SIZE, begin, 0));
    bfs(target, words);
    
    if(answer == MAX_SIZE) return 0;
    return answer;
}

int main(int argc, const char * argv[]) {
    vector<string> words = {"hot","dot","dog","lot","log","cog"};
    string begin = "hit";
    string target = "cog";
    
    cout<<solution(begin, target, words);
    return 0;
}
