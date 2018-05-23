//
//  ItemTableViewCell.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 13/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit

class ItemTableViewCell: UITableViewCell {

    @IBOutlet weak var itemImage: UIView!
    @IBOutlet weak var itemLabel: UILabel!
    @IBOutlet weak var itemNumber: UILabel!
    @IBOutlet weak var itemCounter: UIStepper!
    
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}
