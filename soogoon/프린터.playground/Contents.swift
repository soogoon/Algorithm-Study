import Foundation

public struct Queue<T: Comparable> {
  
  private var storage: [T] = []
  
  public init() {}
  
  public init(_ elements: [T]){
    storage = elements
  }
  
  public mutating func enqueue(_ element: T) -> Bool {
    storage.append(element)
    return true
  }
  
  @discardableResult
  public mutating func dequeue() -> T? {
    return isEmpty ? nil : storage.removeFirst()
  }
  
  public var isEmpty: Bool {
    return storage.isEmpty
  }
  
  public var peek: T? {
    return storage.first
  }
  
  public var count: Int? {
    return storage.count
  }
  
  public var max: T? {
    return storage.max(by: <)
  }
  
  
}

func solution(_ priorities: [Int], _ location:Int) -> Int {
  var count: Int = 0
  var locatedIndex: Int = location
  var printer = Queue<Int>(priorities)
  while true {
    if printer.peek ?? 0 == printer.max ?? 0 {
      printer.dequeue()
      count += 1
      locatedIndex -= 1
      if locatedIndex < 0 {
        break
      }
    } else {
      printer.enqueue(printer.dequeue() ?? 0)
      locatedIndex = locatedIndex == 0 ? (printer.count ?? 0) - 1 : (locatedIndex - 1)
    }
  }
  return count
}
