//
//  ItemTableViewCell.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 13/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit



class ItemTableViewCell: UITableViewCell {

    
    @IBOutlet weak var itemImage: UIImageView!
    @IBOutlet weak var itemLabel: UILabel!
    @IBOutlet weak var itemNumber: UILabel!
    @IBOutlet weak var itemCounter: UIStepper!
    @IBOutlet weak var itemPrice: UILabel!
    
    var oldValue:String?
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
        oldValue = String(Int(itemCounter.value))
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    @IBAction func itemCounterClicked(_ sender: UIStepper) {
        
        oldValue = itemNumber.text
        var clickIncrement = false
        var clickDecrement = false
        
        if Int(sender.value) > Int(oldValue!)! {
            clickIncrement = true
            itemNumber.text = String(Int(itemNumber.text!)! + 1)
        }
        if Int(sender.value) < Int(oldValue!)! && Int(sender.value) >= 0 {
            clickDecrement = true
            itemNumber.text = String(Int(itemNumber.text!)! - 1)
        }
        
        let appDelegate = UIApplication.shared.delegate as! AppDelegate
        let item = OrderItem()
        item.itemName = itemLabel.text!
        item.itemImage = itemImage.image!
        item.itemPrice = itemPrice.text!
        print(item.itemName)
        
        var hasBeenInOrder = false
        var itemPosition = 0
        for orderItem in appDelegate.Order {
            if item.itemName == orderItem.itemName{
                hasBeenInOrder = true
                if clickIncrement {
                    orderItem.quantity = orderItem.quantity + 1
                    sender.value = Double(orderItem.quantity)
                }
                if clickDecrement && orderItem.quantity > 0 {
                    orderItem.quantity = orderItem.quantity - 1
                    sender.value = Double(orderItem.quantity)
                }
                
                if orderItem.quantity == 0 {
                    appDelegate.Order.remove(at: itemPosition)
                }
            }
            itemPosition = itemPosition + 1
        }
        
        if !hasBeenInOrder && clickIncrement {
            item.quantity = 1
            appDelegate.Order.append(item)
        }
        print()
    }
    
    
}
