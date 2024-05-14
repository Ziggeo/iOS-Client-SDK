//
//  UIWindow.swift
//  ZiggeoDemo
//
//  Created by Severyn-Wsevolod on 13.05.2024.
//

import UIKit

extension UIWindow {
    static var key: UIWindow? {
        UIWindowScene.foregroundActive?.windows.first(where: \.isKeyWindow)
    }
}
