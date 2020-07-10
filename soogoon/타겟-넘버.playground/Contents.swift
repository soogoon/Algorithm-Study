import Foundation

func dfs(numbers: [Int], _ currentIndex: Int, targetNumber: Int, previousNumber: Int) -> Int {
  guard currentIndex < numbers.count else {
    return previousNumber == targetNumber ? 1 : 0
  }
  let minusCase = previousNumber - numbers[currentIndex]
  let plusCase = previousNumber + numbers[currentIndex]
  return dfs(numbers: numbers, currentIndex + 1, targetNumber: targetNumber, previousNumber: minusCase) + dfs(numbers: numbers, currentIndex + 1, targetNumber: targetNumber, previousNumber: plusCase)
}

func solution(_ numbers:[Int], _ target:Int) -> Int {
  return dfs(numbers: numbers, 0, targetNumber: target, previousNumber: 0)
}

solution([1,1,1,1,1], 3)
