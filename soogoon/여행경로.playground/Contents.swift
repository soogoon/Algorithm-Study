import Foundation

func searchTicket(current: String, tickets: [[String]], visited: inout [Bool], count: Int, path: inout [String], answer: inout [String]) -> Bool {
  path.append(current)
  if count == tickets.count {
    answer = path
    return true
  }
  for i in 0..<tickets.count {
    if tickets[i].first == current && !visited[i] {
      visited[i] = true
      let success = searchTicket(current: tickets[i].last ?? "", tickets: tickets, visited: &visited, count: count + 1, path: &path, answer: &answer)
      if success { return true }
      visited[i] = false
    }
  }
  path.removeLast()
  return false
}

func solution(_ tickets:[[String]]) -> [String] {
  let sortedTickets = tickets.sorted(by: { $0.last ?? "" <= $1.last ?? "" })
  let start: String = "ICN"
  var visited: [Bool] = Array(repeating: false, count: sortedTickets.count)
  var answer: [String] = []
  var path: [String] = []
  searchTicket(current: start, tickets: sortedTickets, visited: &visited, count: 0, path: &path, answer: &answer)
  return answer
}

let tickets = [["ICN", "SFO"], ["ICN", "ATL"], ["SFO", "ATL"], ["ATL", "ICN"], ["ATL", "SFO"]]
let tickets2 = [["ICN", "AAA"], ["ICN", "AAA"], ["AAA", "ICN"]]
let tickets3 = [["ICN", "BOO"], ["ICN", "COO"], ["COO", "DOO"], ["DOO", "COO"], ["BOO", "DOO"] ,["DOO", "BOO"], ["BOO", "ICN"], ["COO", "BOO"]]

print(solution(tickets))
