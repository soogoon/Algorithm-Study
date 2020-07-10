import Foundation

func check(_ begin: String, _ target: String, _ words: [String]) -> Int {
  var visited: [Bool] = (0..<words.count).map({ _ in return false })
  var dist: [Int] = (0..<words.count).map({ _ in return 0 })
  var queue: [String] = []
  queue.append(begin)
  while !queue.isEmpty {
    let current = queue.removeFirst()
    words.filter { word in
      return zip(word, current)
        .filter({ $0.0 == $0.1})
        .count == (word.count - 1)
    }.forEach { word in
      let currentIndex = words.firstIndex(of: current) ?? -1
      let nextIndex = words.firstIndex(of: word) ?? 0
      if !visited[nextIndex] {
        visited[nextIndex] = true
        dist[nextIndex] = currentIndex == -1 ? 1 : dist[currentIndex] + 1
        queue.append(word)
      }
    }
  }
  let targetIndex = words.firstIndex(of: target) ?? 0
  return dist[targetIndex]
}

func solution(_ begin: String, _ target: String, _ words: [String]) -> Int {
  guard words.contains(target) else { return 0 }
  return check(begin, target, words)
}
