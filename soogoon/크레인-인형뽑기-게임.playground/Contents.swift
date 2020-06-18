import Foundation

func boom(_ stack: inout [Int]) -> Int {
  guard stack.count >= 2 else { return 0 }
  var count = 0
  if stack[stack.count - 1] == stack[stack.count - 2] {
    stack.removeLast()
    stack.removeLast()
    count += 2
    return boom(&stack) + count
  } else {
    return 0
  }
}

func solution(_ board:[[Int]], _ moves:[Int]) -> Int {
  var storedBoard: [[Int]] = board
  var stack: [Int] = []
  var count = 0
  moves.forEach { move in
    for board in 0..<storedBoard.count {
      if storedBoard[board][move - 1] != 0 {
        let doll = storedBoard[board][move - 1]
        storedBoard[board][move - 1] = 0
        stack.append(doll)
        count += boom(&stack)
        break
      }
    }
  }
  return count
}
