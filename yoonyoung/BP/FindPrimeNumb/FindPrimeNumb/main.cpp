//
//  main.cpp
//  FindPrimeNumb
//
//  Created by 조윤영 on 25/11/2019.
//  Copyright © 2019 조윤영. All rights reserved.
//

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#define MAX_SIZE 10000000
using namespace std;
bool checkNumber(int i, string numbers);
//상단에 명시해주면 함수의 위치에 관계없이 참조할 수 있음

int solution(string numbers) {
    int answer = 0;
    sort(numbers.begin(), numbers.end(), greater<int>());
    //내림차순으로 정렬한 후 stoi를 통해 int형으로 변환을 하면 가장 높은 값을 뽑아낼 수 있다.

    vector<bool> temp(stoi(numbers)+1);//가장 큰 수 +1만큼의 bool값 생성->visit배열을 만든 것

    //2~나올 수 있는 가장 큰 수 까지의 수를 하나씩 확인
    for (int i = 2; i <= stoi(numbers); i++) {

        //해당 수를 방문한 적이 없으며 에라토네스의 체에 걸러지지 않았을 경우
        //&& 소수일 경우
        if (temp[i]==false && checkNumber(i,numbers)) {
            answer++;
        }

        if (temp[i] == false) {

            //checkNumbe 호출 횟수를 줄이기 위해
            //에라토네스의 체를 적용하여 배수를 거두는 방식
            for (int j = i; j <= stoi(numbers); j += i) {
                temp[j] = true;
            }
        }
    }

    return answer;
}

bool checkNumber(int i,string numbers) {
    bool flag = false;
    vector<bool> visit(numbers.length());

    while (i != 0) {//i가 0만큼 작아지기 전까지 계속 반복
        flag = false;
        int temp = i % 10;//확인하고자 하는 수를 10으로 나눈 나머지
        //자리 수 하나씩 하나씩 확인해보려는 것(각 자리의 수가 조각의 숫자와 일치하는지 확인해보기 위해)

        for (int j = 0; j <= numbers.length(); j++) {//numbers의 길이만큼 반복
            //현재 숫자를 10으로 나눈 나머지가 주어진 조각의 숫자와 일치할 뿐만 아니라,방문한 적이 없다면?
            //여기서 0은 false를 뜻하고, 1은 true를 뜻한다.
            if (temp == numbers[j]-'0'&&visit[j]==0) {
                flag = true;
                visit[j] = 1;
                break;//일치하는 숫자가 있으면, 해당 숫자 visit한 걸로 표시하고 for문 빠져나오기
            }

        }
        if (flag == false) //해당 자리가 조각 숫자와 일치하는 경우가 없었다면
            return false;//그것은 숫자 조각을 이용해서 나온 소수가 아님을 알린다.

        i /= 10;//다음 작은 자리수로 이동한다.
    }

    return true;//이 모든걸 통과해야 true를 반환하므로, 즉 한 자리라도 조각 숫자와 일치하지 않는다면 false를 반환하는 것임을 알 수 있음.
}
int main(int argc, const char * argv[]) {
    // insert code here...
    cout<<solution("17");
    return 0;
}
