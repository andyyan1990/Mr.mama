//
//  WelcomeViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 31/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import Firebase

class WelcomeViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
    }
    
    override func viewDidAppear(_ animated: Bool) {
        if let uid = Auth.auth().currentUser?.uid {
            print(uid)
            performSegue(withIdentifier: "skipToShop", sender: self)
        }else{
            print("no user login")
        }
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
