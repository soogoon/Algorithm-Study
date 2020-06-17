# 정렬 알고리즘(Sorting)

### 참고

- [Swift Algorithm Club](https://github.com/raywenderlich/swift-algorithm-club) 에서 영어 원문을 번역한 내용입니다.

## 퀵 정렬 (Quick Sort)

퀵 정렬은 정렬 알고리즘 중에서 가장 유명한 정렬 중 하나이다. 재귀 호출이 아직 모호한 개념이었던 때인 1959년에, 토니 호어(Tony Hoare)에 의해 발명되었고 이후 많은 사람에 의해 수정, 보완되어 만들어진 알고리즘이다.

빠른속도는 물론 구현하기도 단순하며 메모리 사용량도 적어 정렬 알고리즘을 사용한다고 하면 보통 퀵 정렬 알고리즘을 사용한다고 봐도 무방하다.

하지만 약점은 있다. 먼저 퀵 정렬이 어떻게 정렬을 진행하는지 알아보자.

우선 Swift로 작성된 이해하기 쉽게 구현된 코드를 보자.

```swift
func quicksort<T: Comparable>(_ a: [T]) -> [T] {
  guard a.count > 1 else { return a }

  let pivot = a[a.count / 2]
  let less = a.filter { $0 < pivot }
  let equal = a.filter { $0 == pivot }
  let greater = a.filter { $0 > pivot }

  return quicksort(less) + equal + quicksort(greater)
}
```

여기에 아래의 테스트를 돌려보면,

```swift
let list = [10, 0, 3, 9, 2, 14, 8, 27, 1, 5, 8, -1, 26]
quicksort(list)
```

아마 잘 작동할 것이다.

 `quicksort()` 는 배열이 주어지면 pivot 변수를 기준으로 우선 세부분으로 나눈다. 여기서 pivot 변수는 배열의 중간 인덱스의 요소로 정해진다. (이 pivot 을 선택하는 기준이 퀵 정렬의 가장 큰 핵심이다. 후에 더 알아보도록 하자.)

pivot 보다 작은 값을 가지면 새로운 `less` 배열로 들어가고, 같은 값이면 `equal` 배열, 더 큰 값은 `greater` 배열로 들어간다. 값의 비교를 위해 `T` 타입은 `Comparable` 을 채택하고 있어야 한다.( `<`, `==`, `>` 을 사용하여 비교가 가능하다는 뜻.) (여기서 `Comparable`은 Swift의 protocol 이다.) 

일단 이렇게 세 개의 배열을 갖게 되면, `quicksort()` 는 `less` 배열과 `greater` 배열을 다시 재귀적으로 호출하여 같은 과정을 반복하게 하고 모든 정렬된 부분 배열을 결합시켜 최종 정렬된 배열을 얻게 된다.

### 예시

![https://github.com/raywenderlich/swift-algorithm-club/raw/master/Quicksort/Images/Example.png](https://github.com/raywenderlich/swift-algorithm-club/raw/master/Quicksort/Images/Example.png)

위의 예시 이미지와 같은 과정을 거치게 되면 정렬이 완료된다.

처음에 정해진 pivot 인 `8` 은 배열을 거의 둘로 나눌 수 있었기에 좋은 pivot 이 되었다. 여기서 알 수 있는 것은 pivot 을 기준으로 항상 배열의 크기가 정확히 둘로 나뉘어야 퀵 정렬의 가장 최고의 성능을 낼 수 있다는 것이다.

아쉽지만, 처음에 예시로 구현한 `quicksort()` 는 그렇게 빠르지 않다. 왜냐하면 같은 배열에서 세번의 `filter` 를 거치기 때문이다.

### Partitioning

pivot 기준으로 배열을 나누는 것을 *patitioning (분할)* 이라고 하며 몇 가지 다른 분할 방식이 있다.

이러한 배열이 있고,

```swift
[ 10, 0, 3, 9, 2, 14, 8, 27, 1, 5, 8, -1, 26 ]
```

중간 인덱스의 요소인 `8` 을 pivot 으로 선택하고 배열을 분할하면,

```swift
[ 0, 3, 2, 1, 5, -1, 8, 8, 10, 9, 14, 27, 26 ]
  -----------------        -----------------
  all elements < 8         all elements > 8
```

여기서 핵심은 분할하고 나면 pivot 요소가 이미 최종 정렬된 위치에 있어야 한다는 것이다. 나머지 요소는 아직 정렬되지 않고 pivot 값을 중심으로 분할된다. 퀵 정렬은 모든 값이 최종 위치에 있을때까지 배열을 여러 번 분할한다.

분할 할때 각 요소가 동일한 상대적 순서로 유지된다는 보장은 없다. 그러므로 pivot `8` 을 중심으로 다음과 같이 끝날 수도 있다.

```swift
[ 3, 0, 5, 2, -1, 1, 8, 8, 14, 26, 10, 27, 9 ]
```

유일한 보장은 pivot의 왼쪽에는 모두 작은 원소가 있고 오른쪽에는 큰 원소가 있다는 것이다. 이러한 분할은 동일한 요소의 원래 순서를 변경할 수 있기 때문에 여기서의 퀵 정렬은 안정적인 정렬을 보장하지 않는다.

### Lomuto's partitioning

위에서 첫번째 예시로 나왔던 Swift의 `filter()` 함수를 세번 불러 분할을 하는 것은 매우 효율적이지 않다. 원래의 배열을 수정하여 제자리에서 작동하는 보다 똑똑한 분할 방법을 살펴보자.

Swift로 구현된 Lomuto의 분할 방법이다.

```swift
func partitionLomuto<T: Comparable>(_ a: inout [T], low: Int, high: Int) -> Int {
  let pivot = a[high]

  var i = low
  for j in low..<high {
    if a[j] <= pivot {
		  a.swapAt(i, j)
      i += 1
    }
  }

  a.swapAt(i, high)
  return i
}
```

이것을 한번 테스트 해보면,

```swift
var list = [10, 0, 3, 9, 2, 14, 26, 27, 1, 5, 8, -1, 8]
let p = partitionLomuto(&list, low: 0, high: list.count - 1)
list  // show the results
```

참고로 여기서 배열의 내용을 직접 변경하므로(`inout` 매개변수로 전달됨) 배열은 변수여야 한다. 이것은 새로운 배열을 여러개 할당하는 것보다 더 효율적이다.

이 방법에서의 퀵 정렬은 전체 배열을 재분할하는 것을 막기 위해 `low` 와 `high` 매개변수를 필요로 한다. 이것은 점점 더 작아지는 제한된 범위로 사용된다.

이전에는 중간 배열 요소를 pivot 으로 사용했지만, Lomuto 알고리즘은 항상 pivot 을 위해 마지막 요소인 `a[high]` 를 사용한다는 것을 알아야한다. 지금까지 `8`  을 중심으로 선회해왔기 때문에, 예제에서 `8` 과 `26` 의 위치를 바꾸어서 `8` 이 배열의 끝에 있고 여기서도 pivot 값으로 사용된다.

분할이 끝나면 배열의 상태는 이렇게 된다.

```swift
[ 0, 3, 2, 1, 5, 8, -1, 8, 9, 10, 14, 26, 27 ]
                        *
```

변수 p 는 `patitionLomuto()` 에 대한 반환 값을 저장하며 여기서는 7이다. 방금 과정으로 변화된 배열에서 pivot 의 인덱스를 나타낸다.

왼쪽 파티션은 0 부터 `p-1` 의 인덱스를 가지는 `[ 0, 3, 2, 1, 5, 8, -1 ]` 이고, 오른쪽 파티션은 `p+1` 부터 끝의 인덱스를 가지는 `[ 9, 10, 14, 26, 27 ]` 이다. (오른쪽 파티션이 이미 정렬되어 있는 것은 우연이다.)

여기서 알수있는 Lomuto 알고리즘의 단점은 현재 pivot인 `8` 과 동일한 또 하나의 `8` 은 가운데 있는 것이 아니라 왼쪽 파티션에 속해 있다는 것이다. 이런 중복 요소들이 많아지면 퀵 정렬을 느리게 하는 단점이 된다.

그럼 정확히 어떻게 동작하는 것일까? 위에서 `for` 루프에서는 배열을 4개의 영역으로 나눈다.

1. `a[low..i]` 는 "values`<=`pivot" 의 영역이다.
2. `a[i+1...j-1]` 는 "values `>` pivot" 의 영역이다.
3. `a[j...high-1]` 는 "아직 확인하지 않은" 영역이다.
4. `a[high]` 는 pivot 이다.

ASCII art 로 도식화 해보면 (ASCII art 가 뭔지 잘 모르겠네요ㅎㅎ..) 이렇다.

```swift
[ values <= pivot | values > pivot | not looked at yet | pivot ]
  low           i   i+1        j-1   j          high-1   high
```

루프에서는 각 요소들을 `low` 에서 `high-1` 까지 차례로 확인한다. 현재 인덱스의 값이 pivot 보다 작거나 같으면 swap 을 통해 첫번째 영역으로 이동시킨다.

→ Note: Swift에서 `(x, y) = (y, x)` 는 `x`, `y` 의 값을 교환하는 편한 방법이다. `swap(&x, &y)` 도 가능하다.

루프가 끝난 후에도 pivot 은 여전히 배열의 마지막 요소이다. 그래서 pivot 보다 큰 파티션의 첫 번째 원소와 교환한다. 이제 pivot 은 `<=` 와 `>` 영역 사이에 위치하며 배열은 적절하게 분할되어 있다.

예시를 통해 하나씩 살펴보자. 배열의 시작은 이렇다.

```swift
[| 10, 0, 3, 9, 2, 14, 26, 27, 1, 5, 8, -1 | 8 ]
   low                                       high
   i
   j
```

처음에는 "아직 확인하지 않은" 영역이 인덱스 0에서 11까지 이어지고 pivot은 인덱스 12에 있다. "values `<=` pivot" 영역과 "values `>` pivot" 영역은 아직 어떤 값도 확인하지 않았기에 비어있다.

먼저 첫번째 값인 10을 보면, pivot 인 8 보다 작지않으므로 다음으로 넘어간다.

```swift
[| 10 | 0, 3, 9, 2, 14, 26, 27, 1, 5, 8, -1 | 8 ]
   low                                        high
   i
       j
```

그러면 "아직 확인하지 않은" 영역은 인덱스 1에서 11이고,  "values `>` pivot" 영역은 숫자 10을 포함하며, "values`<=`pivot" 영역은 여전히 비어있다.

두번째로 0을 보자. pivot 8 보다 작으므로 현재 0의 인덱스인 j와 인덱스 i (값 10) 을 swap 한다.

```
[ 0 | 10 | 3, 9, 2, 14, 26, 27, 1, 5, 8, -1 | 8 ]
  low                                         high
      i
           j
```

이제 "아직 확인하지 않은" 영역은 인덱스 2에서 11이고,  "values `>` pivot" 영역은 여전히 숫자 10만 포함하며, "values`<=`pivot" 영역은 0을 포함한다.

세번째로 3을 보자. pivot 보다 작으므로 10과 swap 한다.

```
[ 0, 3 | 10 | 9, 2, 14, 26, 27, 1, 5, 8, -1 | 8 ]
  low                                         high
         i
              j
```

"values`<=`pivot" 영역은 이제 `[0, 3]` 이다.

한번 더 해보자. 9는 pivot 보다 크므로 그대로 진행한다.

```
[ 0, 3 | 10, 9 | 2, 14, 26, 27, 1, 5, 8, -1 | 8 ]
  low                                         high
         i
                 j
```

이제 "values `>` pivot" 영역은 `[10, 9]` 이다. 이 과정을 계속 거치면 결과적으로는 이렇게 된다.

```
[ 0, 3, 2, 1, 5, 8, -1 | 27, 9, 10, 14, 26 | 8 ]
  low                                        high
                         i                   j
```

마지막으로 `a[i]` 와 `a[high]` 를 swap 한다.

```
[ 0, 3, 2, 1, 5, 8, -1 | 8 | 9, 10, 14, 26, 27 ]
  low                                       high
                         i                  j
```

그리고 pivot 인덱스인 `i` 를 반환한다. 

이러한 분할 과정으로 퀵 정렬을 구현해보면,

```swift
func quicksortLomuto<T: Comparable>(_ a: inout [T], low: Int, high: Int) {
  if low < high {
    let p = partitionLomuto(&a, low: low, high: high)
    quicksortLomuto(&a, low: low, high: p - 1)
    quicksortLomuto(&a, low: p + 1, high: high)
  }
}
```

아주 간단하다. 먼저 `partitionLomuto()` 를 불러 pivot 기준으로 배열을 정렬한다. 그리고 `partitionLomuto()` 를 재귀 호출하여 다시 좌, 우의 배열을 정렬한다.

```swift
var list = [ 10, 0, 3, 9, 2, 14, 26, 27, 1, 5, 8, -1, 8 ]
quicksortLomuto(&list, low: 0, high: list.count - 1)
```

Lomuto *Partitioning* 방법은 이해하기 쉬운 방법이지만 swap 과정이 많다.

*Partitioning* 방법을 또 하나 알아보자.

### Hoare's partitioning

이 *Partitioning* 방법은 퀵 정렬을 발명한 Hoare의 방법이다.

```swift
func partitionHoare<T: Comparable>(_ a: inout [T], low: Int, high: Int) -> Int {
  let pivot = a[low]
  var i = low - 1
  var j = high + 1

  while true {
    repeat { j -= 1 } while a[j] > pivot
    repeat { i += 1 } while a[i] < pivot

    if i < j {
      a.swapAt(i, j)
    } else {
      return j
    }
  }
}
```

이것을 실행해보자.

```swift
var list = [ 8, 0, 3, 9, 2, 14, 10, 27, 1, 5, 8, -1, 26 ]
let p = partitionHoare(&list, low: 0, high: list.count - 1)
list  // show the results
```

Hoare의 방법은 pivot은 항상 배열의 첫번째 요소인 `a[low]` 가 된다. 여기서 다시 한번 더 8을 pivot으로 사용한다.

결과는 이렇게 된다.

```swift
[ -1, 0, 3, 8, 2, 5, 1, 27, 10, 14, 9, 8, 26 ]
```

이번에는 Lomuto의 방법과 달리 pivot 이 반드시 중앙 인덱스에 있지 않다.

대신 배열은 `[low...p]` 와 `[p+1...high]` 영역으로 분할된다. 여기서 반환된 인덱스 `p` 는 6이고, 두 영역은 `[ -1, 0, 3, 8, 2, 5, 1 ]` 와 `[ 27, 10, 14, 9, 8, 26 ]` 이다.

pivot 은 두 영역 중 한 쪽에 위치하지만 이 알고리즘에서는 어디인지 알 수 없다. pivot이 중복이라면(같은 값이 존재) 일부 값은 왼쪽 영역에, 다른 값은 오른쪽 영역에 나타날 수 있다.

이러한 차이 때문에 Hoare의 퀵 정렬 방법은 약간 다르다.

```swift
func quicksortHoare<T: Comparable>(_ a: inout [T], low: Int, high: Int) {
  if low < high {
    let p = partitionHoare(&a, low: low, high: high)
    quicksortHoare(&a, low: low, high: p)
    quicksortHoare(&a, low: p + 1, high: high)
  }
}
```

### 좋은 pivot 선택하기

Lomuto나 Hoare의 방식은 그저 배열의 마지막이나 첫번째 요소를 pivot으로 사용할 뿐이다. 이러한 pivot이 좋다는 보장은 없다.

안 좋은 pivot을 선택하면 다음과 같이 된다.

이러한 배열이 있다.

```swift
[ 7, 6, 5, 4, 3, 2, 1 ]
```

Lomuto 방식을 사용하여 pivot을 마지막 요소인 1 을 선택해보자.

```
   less than pivot: [ ]
    equal to pivot: [ 1 ]
greater than pivot: [ 7, 6, 5, 4, 3, 2 ]
```

반복적으로 진행해보면,

```
   less than pivot: [ ]
    equal to pivot: [ 2 ]
greater than pivot: [ 7, 6, 5, 4, 3 ]
```

```
   less than pivot: [ ]
    equal to pivot: [ 3 ]
greater than pivot: [ 7, 6, 5, 4 ]
```

생략...

아주 좋지않다. 이것은 삽입 정렬보다 느린 결과를 초래한다. 퀵 정렬이 효율적이려면, 배열을 두개로 나눠야 한다.

이 예제의 최적의 pivot은 4이다.

```
   less than pivot: [ 3, 2, 1 ]
    equal to pivot: [ 4 ]
greater than pivot: [ 7, 6, 5 ]
```

그렇다고 이것이 항상 첫번째나 마지막 요소가 아니라 중간 요소를 pivot으로 선택행 한다고 의미할 수 있다. 하지만 다음 상황을 보자.

```swift
[ 7, 6, 5, 1, 4, 3, 2 ]
```

이제 여기서 pivot을 중간 요소로 선택한다면, 앞의 예시와 똑같은 형편없는 결과가 나타난다.

이상적으로 pivot은 분할하는 배열의 중앙 요소. 즉, 정렬된 배열의 중간에 있는 요소이다. 물론 배열을 정렬한 후에야 중앙값을 알 수 있다. 하지만, 이상적이지는 않아도 그나마 좋은 것을 선택하는 몇가지 트릭이 있다.

하나는 배열의 첫번째, 중간, 마지막 요소의 세가지 값 중에서 중간 값을 가지는 것을 선택하는 "median of three" 방법이다. 이론상으로 정확한 중앙값의 근사치를 얻을 수 있다.

또 다른 일반적인 방법은 무작위로 pivot을 선택하는 것이다. 최적의 pivot을 선택할 확률은 적지만, 그래도 평균적으로 좋은 결과를 보여준다.

```swift
func quicksortRandom<T: Comparable>(_ a: inout [T], low: Int, high: Int) {
  if low < high {
    let pivotIndex = random(min: low, max: high)         // 1

    (a[pivotIndex], a[high]) = (a[high], a[pivotIndex])  // 2

    let p = partitionLomuto(&a, low: low, high: high)
    quicksortRandom(&a, low: low, high: p - 1)
    quicksortRandom(&a, low: p + 1, high: high)
  }
}
```

두가지 다른 점이 있다면,

1. `random(min:max:)` 함수는 `min...max` 의 범위에서 랜덤 값을 pivot 으로 선택하게 되고
2. Lomuto 의 방식은 `a[high]` 를 pivot 으로 하기 때문에 `partitionLomuto()` 를 호출하기 전에 `a[pivotIndex]` 와 `a[high]` 를 swap한다.

정렬 함수에서 랜덤 숫자를 활용하는 것이 이상하게 보일 수도 있지만, 모든 상항에서 퀵 정렬이 효율적으로 작동해야한다. pivot이 나쁘면 퀵 정렬은 O(n^2) 의 성능을 가질 수 있다. 그러나 랜덤으로 평균적으로 양호한 pivot을 선택하면 예상 실행 시간은 O(n log n)이 되고, 이는 좋은 정렬 알고리즘 이라 할 수 있다.

### Dutch national flag partitioning

추 후 작성
