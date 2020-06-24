//
//  main.cpp
//  HIndex
//
//  Created by 조윤영 on 2020/06/23.
//  Copyright © 2020 조윤영. All rights reserved.
//

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    //6 5 3 1 0
    for (int i = 0; i < citations.size(); i++) {
        if (citations[i] <= i + 1) {
            return i;
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    vector<int> citiations = {3,0,6,1,5};
    solution(citiations);
    return 0;
}
