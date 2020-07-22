//
//  main.swift
//  MaximumDiff-10819
//
//  Created by LeeSeungsoo on 2020/07/15.
//  Copyright © 2020 soogoon. All rights reserved.
//

import Foundation

let n = Int(readLine() ?? "") ?? 0
let arr: [Int] = (readLine() ?? "").split(separator: " ").map { Int($0) ?? 0 }
var visited: [Bool] = Array(repeating: false, count: n)
var storedArr: [Int] = []

func sum(arr: [Int]) -> Int {
  var sum: Int = 0
  for i in 0..<arr.count-1 {
    sum += abs(arr[i] - arr[i+1])
  }
  return sum
}

func dfs(answer: inout Int, count: Int) {
  if count == n {
    answer = max(answer, sum(arr: storedArr))
    return
  }
  for i in 0..<n {
    if visited[i] { continue }
    visited[i] = true
    storedArr.append(arr[i])
    dfs(answer: &answer, count: count + 1)
    storedArr.removeLast()
    visited[i] = false
  }
}

func solution(_ n: Int, _ arr: [Int]) -> Int {
  var answer: Int = 0
  dfs(answer: &answer, count: 0)
  return answer
}

print(solution(n, arr))
