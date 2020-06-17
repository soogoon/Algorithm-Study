# Stack

스택은 후입 선출/LIFO(Last In - First Out)으로 데이터에 접근하는 자료구조입니다.

따라서 일반적으로 TOP이라 부르는 위치에서만 데이터를 입력, 출력, 삭제를 할 수 있는 구조로 구현되어있습니다. 

![img](https://k.kakaocdn.net/dn/bhG6Aw/btqESoVmtYh/xLIVFZbhZEmjpkdYIMsne0/img.png)

따라서 이런 구조를 가진 Stack을 만들어볼게요~

```swift
public struct Stack<T> {

    private var storage: [T] = []
    
    public init() { }
    
    public init(_ elements: [T]){
        storage = elements
    }
    
    public mutating func push(_ element: T) {
        storage.append(element)
    }
    
    @discardableResult
    public mutating func pop() -> T? {
        return storage.popLast()
    }

    public func peek() -> T? {
        return storage.last
    }
    
    // MARK: - 스택이 비어있는지
    public var isEmpty: Bool {
        return peek() == nil
    }

    // MARK: - 스택의 원소 갯수
    public var count: Int? {
        return storage.count
    }
}
```

 

```swift
// MARK: -스택 전체를 읽기 위한 Custom String description
extension Stack: CustomStringConvertible {

	public var description: String {
    	let top = "---top---\n"
        let bottom = "\n--------"
        
        let stackElements = storage.map { "\($0)" }.reversed().joined(separator: "\n")
        return top + stackElements + bottom
    }
}
```



# Queue

큐는 스택과 달리 선입선출 / FIFO(First in - First Out)으로 데이터에 접근하고, 

Back(Rear)이라는 위치에서 Enqueue라는 메소드로 데이터를 입력,

 

Front라는 위치에서 Dequeue라는 메소드로 데이터를 출력, 삭제하는 구조로 구현되는 자료구조입니다.

 



![img](https://k.kakaocdn.net/dn/bp7mXC/btqEShDd36M/yC80pBj4ooyVtXEzpmNgIk/img.png)



 

일반적으로 정의된 자료구조에 따라서 Swift로 코드를 작성해보자면!!

 

```swift
public struct Queue<T> {
    
    private var storage: [T] = []

    // 비어있는 Queue로 생성
    public init() {}
    
    // Queue 생성과 함께 데이터 입력
    public init(_ elements: [T]){
        storage = elements
    }
    
    // Back에서 데이터 입력
    public mutating func enqueue(_ element: T) -> Bool {
        storage.append(element)
        return true
    }
    
    // Front에서 데이터 출력, 삭제 
    public mutating func dequque() -> T? {
        return isEmpty ? nil : storage.removeFirst()
    }
    
    public var isEmpty: Bool {
        return storage.isEmpty
    }
    
    public var peek: T? {
        return storage.first ?? T.self as! T
    }

    public var count: Int? {
        return storage.count
    }
}
```

와 같이 구현할수가 있습니다. 

 

그리고 Stack과 같이

```swift
extension Queue: CustomStringConvertible {
    public var description: String {
        return storage.description
    }
}
```

private로 선언된 storage를 그려줄수있는 desription을 작성해주었습니다.

## 

그리고 

# Deque

우선 덱에 대한 기본적인 구조를 알아보겠습니다. 

덱에서는 앞에서 다루었던 스택. 큐와 다르게 양쪽 끝에서 모두 삽입과 삭제가 가능한 자료구조입니다.

 



![img](https://k.kakaocdn.net/dn/qRGUD/btqETLQDm4x/v8rWjayzQlnTm5BS9AwDpK/img.png)



우선 간단하게 덱의 구조를 파악했으니 Swift로 간단하게 코드를 작성해 볼까요??

 

```swift
public struct Deque<T> {
    private var storage: [T] = []
    
    public init() {}
    
    public init(_ elements: [T]){
        storage = elements
    }
    
   // Front로 데이터 입력
    public mutating func frontEnqueue(_ element: T) -> Bool{
        storage.insert(element, at: 0)
        return true
    }
   // Back(rear)로 데이터를 입력 
    public mutating func backEnqueue(_ element: T) -> Bool{
        storage.append(element)
        return true
    }
   // Front로 데이터 출력, 삭제 
    public mutating func frontDequeue() -> T? {
        return isEmpty ? nil : storage.removeFirst()
    }
   // Back(rear)로 데이터 출력, 삭제 
    public mutating func backDequeue() -> T? {
        return isEmpty ? nil : storage.remove(at: storage.count - 1)
    }
    
    public var isEmpty: Bool {
        return storage.isEmpty
    }
   // Front에 있는 데이터 출력
    public var frontPeek: T? {
        return storage.first
    }
   // Back에 있는 데이터 출력   
    public var backPeek: T? {
        return storage.last
    }
}
```

와 같이 구현할 수가 있습니다.

 하지만 위 코드처럼 양쪽에서 입력과 출력 모두 사용하는 경우는 없으며 한쪽에서 삽입, 삭제 기능중 하나가 제한 되어 있어야 합니다.

삽입이 제한된경우는 입력 제한 덱, 삭제가 제한된 경우 출력 제한 덱이라 불립니다.

그리고 Stack, Queue와 같이 

```swift
extension Deque: CustomStringConvertible {
    public var description: String {
        return storage.description
    }
}
```

private로 선언된 storage를 그려줄수있는 desription을 작성해주었습니다.

위 내용을 정리해보면 아래 표와 같은 차이점을 알수가 있습니다.

|      | 스택 | 큐         | 덱                |
| ---- | ---- | ---------- | ----------------- |
| 입력 | Top  | Back(rear) | Front, Back(rear) |
| 출력 | Top  | Front      | Front, Back(rear) |



이런 차이점을 가지고 문제에서는 어떻게 스택, 큐, 덱으로 접근해야하는지 알아볼게요~!

## 문제

[2019 카카오 개발자 겨울 인턴십 1번 문제](https://programmers.co.kr/learn/courses/30/lessons/64061)

[프로그래머스 프린터 문제](https://programmers.co.kr/learn/courses/30/lessons/42587)

[백준 5430번 문제](https://www.acmicpc.net/problem/5430)