//
//  IBDesignableButton.swift
//  実習
//
//  Created by 大木一輝 on 2016/05/14.
//  Copyright © 2016年 mycompany. All rights reserved.
//
import UIKit

// 右カラムのAttributes Inspectorで設定した値がリアルタイムで適用される
// classの前のここに書く
@IBDesignable

class IBDesignableButton: UIButton {
    
    // 今回はボタンの枠線の色，太さ，ボタンの角を丸める設定をいじってみる
    // 以下の変数宣言でこれらがデフォルトの値になる
    @IBInspectable var borderColor :  UIColor = UIColor.blackColor()
    @IBInspectable var borderWidth : CGFloat = 1.0
    @IBInspectable var cornerRadius : CGFloat = 5.0
    
    
    // Attributes Inspectorで設定した値を反映
    override func drawRect(rect: CGRect) {
        self.layer.borderColor = borderColor.CGColor
        self.layer.borderWidth = borderWidth
        self.layer.cornerRadius = cornerRadius
    }
}