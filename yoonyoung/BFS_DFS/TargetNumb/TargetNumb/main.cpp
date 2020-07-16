//
//  main.cpp
//  TargetNumb
//
//  Created by 조윤영 on 2020/06/24.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int answer =  0;

void dfs(vector<int> numbers, int index, int sum, int target, int doAction) {
    sum += numbers[index]*doAction;
    
    if(index == numbers.size()-1) {
        if(sum == target) answer++;
        return;
    }
    
    dfs(numbers, index+1, sum, target, 1);
    dfs(numbers, index+1, sum, target, -1);
}

int solution(vector<int> numbers, int target) {
    
    dfs(numbers, 0, 0, target, 1);
    dfs(numbers, 0, 0, target, -1);
    
    return answer;
}

int main(int argc, const char * argv[]) {
    vector<int> numbers = {1,1,1,1,1};
    int target = 3;
    
    cout<<solution(numbers, target);
    return 0;
}
