//
//  ItemViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 7/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit


class ItemViewController: UIViewController {

    @IBOutlet weak var itemTitle: UINavigationItem!
    @IBOutlet weak var itemImageView: UIImageView!
    @IBOutlet weak var itemLabel: UILabel!
    @IBOutlet weak var itemDescription: UILabel!
    
    var selectedItem: OrderItem?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        itemImageView.image = selectedItem?.itemImage
        itemLabel.text = selectedItem?.itemName
        itemTitle.title = selectedItem?.itemName
    }

    @IBAction func dismissView(_ sender: Any) {
        dismiss(animated: true, completion: nil)
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
