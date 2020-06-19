import Foundation

func solution(_ citations:[Int]) -> Int {
  let sorted = citations.sorted(by: >)
  return sorted.enumerated()
    .map({ min($0.offset + 1, $0.element) })
    .sorted(by: >).first ?? 0
}
