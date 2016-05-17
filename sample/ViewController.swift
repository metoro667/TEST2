//
//  ViewController.swift
//  sample
//
//  Created by 渡辺寛太 on 2016/05/09.
//  Copyright © 2016年 渡辺寛太. All rights reserved.
//
// TEST 追加
// 1
// 2

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var webview: UIWebView!
    
    var url:String = "https://www.google.co.jp"
    
    @IBAction func unipa(sender: AnyObject) {
        
        // 入力されたURLを取得
        url = "https://portal.sa.dendai.ac.jp/up/faces/login/Com00505A.jsp"
        
        // loadURL関数を実行
        loadURL()
    }
    @IBAction func mail(sender: AnyObject) {
        
        url = "http://mail.ms.dendai.ac.jp/cgi-bin/index.cgi"
        
        loadURL()
    }
    @IBAction func google(sender: AnyObject) {
        
        url = "https://www.google.co.jp"
        
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

