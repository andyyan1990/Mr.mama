//
//  SampleDataSource.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 30/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import Firebase
import SDWebImage

class SampleDataSource: NSObject, UITableViewDataSource {
    
    var items : [String : Any]?
    var nameArray = [String]()
    var priceArray = [String]()
    var urlArray = [String]()
    
    init(wholeList:[String : Any], selectedCategory: String) {
        super.init()
        print("reaching in init")
        items = wholeList[selectedCategory] as? [String : Any]
        
        for value in Array(items!.values){
            
            let castValue = value as! [String : Any]
            let name = castValue["name"] as! String
            nameArray.append(name)
            let price = String(castValue["price"] as! Double)
            priceArray.append(price)
            let url = castValue["imgUrl"] as! String
            urlArray.append(url)
        }
        
        
    }
    
    func fetchItemList(selectedCategory:String) {

//            self.itemDBRef.child(selectedCategory).observeSingleEvent(of: .childAdded, with: { (snapshot) in
//                if let dict = snapshot.value as? [String : Any] {
//                    self.items = dict
//                    print(self.items!)
//                }
//            })

        
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.items!.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "CustomItemCell", for: indexPath) as! ItemTableViewCell
   
        cell.itemImage.sd_setImage(with: URL(string: urlArray[indexPath.row]), completed: nil)
        cell.itemPrice.text = priceArray[indexPath.row]
        cell.itemLabel.text = nameArray[indexPath.row]
        let appDelegate = UIApplication.shared.delegate as! AppDelegate
        var isInOrder = false;
        for orderItem in appDelegate.Order {
            if nameArray[indexPath.row] == orderItem.itemName {
                isInOrder = true
                cell.itemNumber.text = String(orderItem.quantity)
                break
            }
        }
        if !isInOrder {
            cell.itemNumber.text = "0"
        }
        
        return cell
    }
    
    
    
}
