//
//  DateFormatter.swift
//  ZiggeoDemo
//
//  Created by Severyn-Wsevolod on 13.05.2024.
//

import Foundation

extension DateFormatter {
    static var dateTime: DateFormatter { .init(format: "yyyy-MM-dd HH:mm:ss") }
    
    convenience init(format: String) {
        self.init()
        self.dateFormat = format
    }
}
