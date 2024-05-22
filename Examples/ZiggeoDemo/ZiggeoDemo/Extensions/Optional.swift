//
//  Optional.swift
//  ZiggeoDemo
//
//  Created by Severyn-Wsevolod on 20.05.2024.
//

import Foundation

// MARK: - Timer
extension Optional where Wrapped == Timer {
    mutating func kill() {
        self?.invalidate()
        self = nil
    }
}

// MARK: - NSKeyValueObservation
extension Optional where Wrapped == NSKeyValueObservation {
    mutating func kill() {
        self?.invalidate()
        self = nil
    }
}
