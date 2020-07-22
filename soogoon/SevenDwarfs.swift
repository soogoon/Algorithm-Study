//
//  main.swift
//  SevenDwarfs-2309
//
//  Created by LeeSeungsoo on 2020/07/15.
//  Copyright © 2020 soogoon. All rights reserved.
//

import Foundation

var dwarfs: [Int] = []

for _ in 0..<9 {
  dwarfs.append(Int(readLine() ?? "") ?? 0)
}

func solution(_ dwarfs: [Int]) {
  let sorted: [Int] = dwarfs.sorted(by: <)
  var firstIndex: Int = 0
  var secondIndex: Int = 0
  for i in (0..<9) {
    for j in (0..<9) {
      if i == j { continue }
      let sum = sorted.reduce(0, +) - sorted[i] - sorted[j]
      if sum == 100 {
        firstIndex = i
        secondIndex = j
      }
    }
  }
  for i in (0..<9) {
    if i == firstIndex || i == secondIndex { continue }
    print(sorted[i])
  }
}

solution(dwarfs)
