//
//  ConfirmOrderViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 8/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit

class ConfirmOrderViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {

    var appDelegate = UIApplication.shared.delegate as! AppDelegate
    var totalPrice:Double?
    @IBOutlet weak var deliveryAddrBtn: UIButton!
    @IBOutlet weak var totalPriceLabel: UIBarButtonItem!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.hideKeyboardWhenTappedAround()

        // Do any additional setup after loading the view.
        totalPrice = 0
        deliveryAddrBtn.layer.cornerRadius = 5
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        totalPriceLabel.title = getTotalPrice()
    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return appDelegate.Order.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "orderSummary", for: indexPath)
        let orderItem = appDelegate.Order[indexPath.row]
        cell.textLabel?.text = orderItem.itemName
        cell.detailTextLabel?.text = "Qtn: \(orderItem.quantity) Price: \(Double(orderItem.quantity) * Double(orderItem.itemPrice)!)"
        cell.imageView?.layer.cornerRadius = (cell.imageView?.frame.width)!
        cell.imageView?.image = orderItem.itemImage
        return cell
    }
    
    func tableView(_ tableView: UITableView, didDeselectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
    }
    
    
    @IBAction func backClicked(_ sender: Any) {
        print(totalPrice)
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBAction func submitOrder(_ sender: Any) {
        let alert = UIAlertController(title: "Order confrimed", message: "Your order has been confirmed", preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.cancel, handler: nil))
        self.present(alert, animated: true)
    }
    
    func getTotalPrice() -> String {
        for orderItem in appDelegate.Order {
            totalPrice = totalPrice! + Double(orderItem.quantity) * Double(orderItem.itemPrice)!
        }
        return "Total Price: \(totalPrice!)"
    }
}
