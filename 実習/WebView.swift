//
//  WebView.swift
//  実習
//
//  Created by 大木一輝 on 2016/05/13.
//  Copyright © 2016年 mycompany. All rights reserved.
//

import Foundation
import UIKit

class WebView: UIViewController {
    
    @IBOutlet weak var webview: UIWebView!
    
    var url:String = "https://www.google.co.jp"
    
    @IBAction func unipa(sender: AnyObject) {
        // 入力されたURLを取得
        url = "https://portal.sa.dendai.ac.jp/up/faces/login/Com00505A.jsp"
        
        // loadURL関数を実行
        loadURL()
    }
    
    @IBAction func google(sender: AnyObject) {
        // 入力されたURLを取得
        url = "https://www.google.co.jp"
        
        // loadURL関数を実行
        loadURL()
    }
    
    @IBAction func mail(sender: AnyObject) {
        //入力されたURLを取得
        url = "http://mail.ms.dendai.ac.jp/cgi-bin/index.cgi"
        
        // loadURL関数を実行
        loadURL()
    }
    
    
    // loadURL関数を定義
    func loadURL() {
        let requestURL = NSURL(string: url)
        let request = NSURLRequest(URL: requestURL!)
        webview.loadRequest(request)
    }

    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        loadURL()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}