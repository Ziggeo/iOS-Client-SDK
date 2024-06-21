//
//  UIWindowScene.swift
//  ZiggeoDemo
//
//  Created by Severyn-Wsevolod on 13.05.2024.
//

import UIKit

extension UIWindowScene {
    static var foregroundActive: UIWindowScene? {
        let windowScenes = UIApplication.shared.connectedScenes.compactMap { $0 as? UIWindowScene }
        
        return windowScenes.first(where: { $0.activationState == .foregroundActive }) ??
        windowScenes.first(where: { $0.activationState == .foregroundInactive })
    }
}
