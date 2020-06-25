import Foundation

func checkNetwork(_ visited: inout [Bool], _ computers: [[Int]], _ nextIndex: Int) -> Int {
  guard !visited[nextIndex] else { return 0 }
  var queue: [Int] = []
  queue.append(nextIndex)
  visited[nextIndex] = true
  while !queue.isEmpty {
    if let current = queue.first {
      queue.removeFirst()
      (0..<computers[current].count).forEach {
        if !visited[$0] && computers[current][$0] == 1 {
          visited[$0] = true
          queue.append($0)
        }
      }
    }
  }
  return 1
}

func solution(_ n:Int, _ computers:[[Int]]) -> Int {
  var visited: [Bool] = (0..<n).map({ _ in return false })
  var count: Int = 0
  (0..<n).forEach { i in
    count += checkNetwork(&visited, computers, i)
  }
  return count
}

//let n1 = 3
//let computers1 = [[1, 1, 0], [1, 1, 0], [0, 0, 1]]
//print(solution(n1, computers1))

let n2 = 3
let computers2 = [[1, 1, 0], [1, 1, 1], [0, 1, 1]]
print(solution(n2, computers2))
