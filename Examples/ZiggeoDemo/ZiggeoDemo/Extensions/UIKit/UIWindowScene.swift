//
//  UIWindowScene.swift
//  ZiggeoDemo
//
//  Created by Severyn-Wsevolod on 13.05.2024.
//

import UIKit

extension UIWindowScene {
    static var foregroundActive: UIWindowScene? {
        UIApplication.shared.connectedScenes
            .first(where: { $0.activationState == .foregroundActive && $0 is UIWindowScene })
            .flatMap({ $0 as? UIWindowScene })
    }
}
