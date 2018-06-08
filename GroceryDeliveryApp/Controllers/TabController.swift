//
//  TabController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 24/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit

class TabController: UITabBarController {

    //create
    var Order = [OrderItem]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
