# 동적 계획법 (Dynamic Programming)

동적 계획법(이하 DP)은 간단히 말하자면 큰 문제를 작은 문제로 나눠서 푸는 알고리즘이다.

DP로 풀어 낼 수 있는 문제는 다음 두가지 속성을 만족해야 한다.

- Overlapping Subproblem
- Optimal Substructure

### Overlapping Subproblem

분할 정복처럼, DP는 하위 문제에 대한 솔루션을 결합한다. DP는 주로 동일한 하위 문제의 솔루션이 계속해서 필요할 때 사용된다. DP에서 하위 문제에서 계산된 솔루션은 테이블에 저장되므로 이러한 솔루션은 다시 계산할 필요가 없다. 따라서 하위 문제가 다시 필요하지 않으면 솔루션을 저장하는 포인트가 없기 때문에 공통된 하위 문제(Overlapping Subproblem)가 없을 때에는 효율적이지 않다. 예를 들어, 바이너리 서치에서는 공통 하위 문제가 없다.

예시로 피보나치에 대한 재귀 함수를 살펴보면, 몇번이고 계산되는 하위 문제들이 있다.

```c++
int fib(int n) { 
   if ( n <= 1 ) 
      return n;
   return fib(n-1) + fib(n-2); 
}
```

위의 함수를 리커젼 트리로 살펴보자.

```
                          fib(5)
                     /             \
               fib(4)                fib(3)
             /      \                /     	\
         fib(3)      fib(2)         fib(2)    fib(1)
        /     \        /    \       /    \
  fib(2)   fib(1)  fib(1) fib(0) fib(1) fib(0)
  /    \
fib(1) fib(0)
```

함수 fib(3)가 2번 호출되고 fib(2)는 3번이나 호출 된다. 만약 fib(3), fib(2)의 값을 저장한다면, 다시 계산하는 대신에 저장된 값을 재사용할 수 있다. 이러한 값을 재사용할 수 있도록 저장하는 방법에는 다음과 같은 두 가지가 있다.

- Memoization (Top Down)
- Tabluation (Bottom Up)

---

#### Memoization

Memoization 은 재귀호출과 비슷하지만, 값을 계산하기전에 미리 저장된 값을 살펴본다는 차이점이 있다. 

초기 값을 모두 Null로 하여 조회 배열을 초기화한다. 하위 문제에 대한 값을 계산할 때마다 먼저 배열을 살펴본다. 사전 계산된 값이 있으면 그 값을 반환하고, 그렇지 않으면 계산하여 나중에 재사용할 수 있도록 배열에 결과를 넣는다.

다음은 memoization을 적용한 피보나치 함수이다.

```c++
/* C++ program for Memoized version 
for nth Fibonacci number */
#include <bits/stdc++.h> 
using namespace std; 
#define NIL -1  
#define MAX 100  
  
int lookup[MAX];  
  
/* Function to initialize NIL  
values in lookup table */
void _initialize()  
{  
    int i;  
    for (i = 0; i < MAX; i++)  
        lookup[i] = NIL;  
}  
  
/* function for nth Fibonacci number */
int fib(int n)  
{  
    if (lookup[n] == NIL)  
    {  
        if (n <= 1)  
            lookup[n] = n;  
        else
            lookup[n] = fib(n - 1) + fib(n - 2);  
		}  
		return lookup[n];  
}  
  
// Driver code 
int main ()  
{  
    int n = 40;  
    _initialize();  
    cout << "Fibonacci number is " << fib(n);  
    return 0;  
}  
  
// This is code is contributed by rathbhupendra 
```

#### Tabulation

 Tabulation 방식은 아래부터 테이블을 채워나가고 테이블의 마지막 항목을 반환한다.

다시 피보나치 수를 예시로 하면, 먼저 fib(0)을 계산하고 다음에 fib(1), fib(2) 계산해 나간다. 말 그대로 하위 문제를 Bottom Up 방식으로 해결한다.

```c++
/* C program for Tabulated version */
#include<stdio.h> 
int fib(int n)
{
  int f[n+1];
  int i;
  f[0] = 0;
  f[1] = 1;
  for (i = 2; i <= n; i++)
      f[i] = f[i-1] + f[i-2];
  return f[n];
} 
   
int main () 
{ 
  int n = 9;
  printf("Fibonacci number is %d ", fib(n));
  return 0; 
}
```

---

위의 두 방식 모두 하위 문제의 값을 저장한다. Memoization은 필요한 값만 테이블에서 가져오지만, Tabulation은 첫번째 요소부터 모든 요소를 저장한다. Tabulation과는 달리 lookup 테이블의 모든 요소는 memoization에서는 채워질 필요가 없다.

재귀적인 방법과 비교해서 memoization과 tabulation으로 최적화를 보려면, 꽤 큰 수의 피보나치 수열을 계산해보며 소요시간을 비교해 보면 된다. 재귀적인 방법이 두가지 다이나믹 프로그래밍 기술에 비해 더 많은 시간이 소요될 것이다.

### Optimal Substructure

두번째 속성으로, 문제의 정답을 작은 문제의 정답에서 구할 수 있어야 한다. 설명하자면 문제의 최적해를 작게 나눈 하위구조의 최적해를 구함으로서 알아낼 수 있는 경우에 최적의 하위구조(Optimal substructure)를 만족하게 된다.

최단 경로 문제로 예를 들면, 노드 x가 시작점 u에서 도착점 v로 가는 최단경로상에 있다면, 최단 경로 u-v는 최단경로 u-x와 x-v의 조합이다. 모든 최단 경로를 구하는 Floyd-Warshall, Bellman-Ford 알고리즘도 다이나믹 프로그래밍의 예제이다.

반면에 최장 경로 문제는 Optimal Substructure 속성을 가지고 있지 않다. 여기서 최장 경로란 두 노드 사이의 최장 단순 경로를 말한다.(사이클이 없는 경로).

다음 그래프를 보면,

![graph](https://user-images.githubusercontent.com/19575791/88768609-492a8d80-d1b6-11ea-9148-defc335a30c3.png)

q-t의 최장 경로가 존재한다. q-r-t, q-s-t. 최단 경로와 달리, 최장경로는 Optimal Substructure 의 특성이 없다.

예를 들어, 최장경로 q-r-t는 최장 경로 q-r과 r-t의 조합이 아니다. 왜냐하면 최장경로 q-r은 q-s-t-r 이고 최장경로 r-t는 r-q-s-t이기 때문이다.

---

지금까지 살펴본 내용을 토대로 Dynamic Programming의 핵심을 간추려보면 다음과 같다.

- 각 문제는 한 번만 풀어야 한다.
- Optimal Substructure를 만족하기 때문에, 같은 문제는 구할 때마다 정답이 같다.
- 따라서, 정답을 구했으면, 정답을 어딘가에 메모한다.
- 이것을 Memoization이라 하고, 배열에 저장하는 것으로 구현할 수 있다.

