//
//  main.swift
//  SafetyArea
//
//  Created by LeeSeungsoo on 2020/07/01.
//  Copyright © 2020 soogoon. All rights reserved.
//

let dx = [0, 0, 1, -1]
let dy = [1, -1, 0, 0]

func dfs(map: [[Int]], visited: inout [[Bool]], height: Int, x: Int, y: Int) {
  visited[x][y] = true
  (0..<4).forEach { k in
    let nextX = x + dx[k]
    let nextY = y + dy[k]
    if nextX >= 0 && nextY >= 0 && map.count > nextX && map.count > nextY {
      if map[nextX][nextY] > height && !visited[nextX][nextY] {
        visited[nextX][nextY] = true
        dfs(map: map, visited: &visited, height: height, x: nextX, y: nextY)
      }
    }
  }
}

func main() {
  let n: Int = Int(readLine() ?? "") ?? 0
  var map: [[Int]] = []
  var count: Int = 0
  
  (0..<n).forEach { _ in
    let nums = readLine()?.split(separator: " ").map({ char in
      return Int(char) ?? 0
    }) ?? []
    map.append(nums)
  }
  
  (1...100).forEach { height in
    var visited: [[Bool]] = Array(repeating: Array(repeating: false, count: n), count: n)
    var currentCount = 1
    (0..<map.count).forEach { i in
      (0..<map.count).forEach { j in
        if map[i][j] > height && !visited[i][j] {
          dfs(map: map, visited: &visited, height: height, x: i, y: j)
          currentCount += 1
        }
      }
    }
    count = max(count, currentCount)
  }
  
  print(count)
}

main()
