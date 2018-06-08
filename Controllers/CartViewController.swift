//
//  CartViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 24/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit

class CartViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    var order = [OrderItem]()
    var order1 = [OrderItem]()
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    

    @IBOutlet weak var cartTableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        cartTableView.register(UINib(nibName: "ItemTableViewCell", bundle: nil), forCellReuseIdentifier: "CustomItemCell")
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        order = appDelegate.Order
        print(order.count)
        cartTableView.reloadData()
        
    }
    
    override func viewDidAppear(_ animated: Bool) {
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        
    }
    
    // MARK: - Taking care of TableView
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return order.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "CustomItemCell", for: indexPath) as! ItemTableViewCell
        //initialise value to cell
        cell.itemLabel.text = appDelegate.Order[indexPath.row].itemName
        cell.itemNumber.text = String(appDelegate.Order[indexPath.row].quantity)
        cell.itemPrice.text = appDelegate.Order[indexPath.row].itemPrice
        cell.itemCounter.value = Double(appDelegate.Order[indexPath.row].quantity)
        cell.itemImage.image = appDelegate.Order[indexPath.row].itemImage
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {

            return 120
    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    
    @IBAction func continueBtnClicked(_ sender: Any) {
        if appDelegate.Order.count > 0 {
            performSegue(withIdentifier: "confirmOrderSegue", sender: nil)
        }
    }
    
}
