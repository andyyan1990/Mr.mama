//
//  ConfirmOrderViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 8/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit

protocol SetAddressDelegate {
    func getAddress() -> String
}

class ConfirmOrderViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {

    var appDelegate = UIApplication.shared.delegate as! AppDelegate
    var totalPrice:Double?
    var setAddrDelegate:SetAddressDelegate?
    
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
        if let addr = setAddrDelegate?.getAddress() {
            deliveryAddrBtn.titleLabel?.text = addr
        }
    }


    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
        if segue.identifier == "toMapView" {
            let destVC = segue.destination as! MapViewController
            setAddrDelegate = destVC
        }
    }
    
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
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 80
    }
    
    @IBAction func backClicked(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBAction func submitOrder(_ sender: Any) {
        let alert = UIAlertController(title: "Order submitted", message: "Your order has been submitted", preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.cancel, handler: {
            action in
            self.dismiss(animated: true, completion: nil)
        }))
        self.present(alert, animated: true) {
            self.appDelegate.Order.removeAll()
        }
    }
    
    func getTotalPrice() -> String {
        totalPrice = 0
        for orderItem in appDelegate.Order {
            totalPrice = totalPrice! + Double(orderItem.quantity) * Double(orderItem.itemPrice)!
        }
        return "Total Price: \(totalPrice!)"
    }
}
