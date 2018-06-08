//
//  ShopViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 13/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import Firebase
import CoreLocation
import SDWebImage

class ShopViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, CLLocationManagerDelegate, UISearchBarDelegate{
    
    @IBOutlet weak var categoryTableView: UITableView!
    @IBOutlet weak var itemTableView: UITableView!
    
    @IBOutlet weak var searchInShop: UISearchBar!
    
    //Declare Variable
    let locationManager = CLLocationManager()
    var itemDataSource:UITableViewDataSource?
    var categoryList = [Category]()
    var itemList = [String : Any]()
    
    var selectedItem: OrderItem?
    
    //create sample datasource
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        //setup tableView delegate and datasource
        categoryTableView.delegate = self
        itemTableView.delegate = self
        itemTableView.dataSource = self
        
        //setup searchBar delegate
        searchInShop.delegate = self
        
        //register nib for customised cells
        categoryTableView.register(UINib(nibName: "CategoryTableViewCell", bundle: nil), forCellReuseIdentifier: "CustomCategoryCell")
        itemTableView.register(UINib(nibName: "ItemTableViewCell", bundle: nil), forCellReuseIdentifier: "CustomItemCell")
        
        //
        fetchCategoryList()
        fetchItemList()
        
        // Location Service setup
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        //self.categoryTableView.reloadData()
        self.itemTableView.reloadData()
        
    }
    
    
    override func viewWillDisappear(_ animated: Bool) {
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    


    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
        if segue.identifier == "popUpShowItemSegue" {
            if let indexPath = itemTableView.indexPathForSelectedRow {
                let cell = itemTableView.cellForRow(at: indexPath) as! ItemTableViewCell
                let tempItem = OrderItem()
                tempItem.itemImage = cell.itemImage.image!
                tempItem.itemName = cell.itemLabel.text!
                if let destVC = segue.destination as? ItemViewController {
                    //destVC.itemImageView.image = cell.itemImage.image
                    //destVC.itemLabel.text = cell.itemLabel.text
                    destVC.selectedItem = tempItem
                }
            }
        }
    }

    // MARK: - TableView
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        if tableView == categoryTableView {
            return categoryList.count
        }else{
            return 5
        }
    }
    
    
    //
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        if tableView == categoryTableView {
            
            let cell = tableView.dequeueReusableCell(withIdentifier: "CustomCategoryCell", for: indexPath) as! CategoryTableViewCell
            cell.categoryLabel.text = categoryList[indexPath.row].categoryName!
            return cell
            
        }else{
            
            let cell = tableView.dequeueReusableCell(withIdentifier: "CustomItemCell", for: indexPath) as! ItemTableViewCell
            
            cell.itemPrice.text = "0.0"
            let itemDBRef = Database.database().reference().child("Stock")
            cell.itemNumber.text = String(Int(cell.itemCounter.value))
            cell.itemLabel.text = "Item \(indexPath.row)"
            return cell
        }
    }
    
    //configure tableViews Cell Height
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if tableView == categoryTableView {
            return 80
        }else{
            return 120
        }
    }
    
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        if tableView == itemTableView {
            //tableView.deselectRow(at: indexPath, animated: false)
            performSegue(withIdentifier: "popUpShowItemSegue", sender: nil)
        }
        
        if tableView == categoryTableView {
            let cell = tableView.cellForRow(at: indexPath) as! CategoryTableViewCell
            switch cell.categoryLabel.text {
            case "Diary":
                itemDataSource = SampleDataSource(wholeList: itemList, selectedCategory: "Diary")
                itemTableView.dataSource = itemDataSource
                itemTableView.reloadData()
                break
            case "Beverage":
                itemDataSource = SampleDataSource(wholeList: itemList, selectedCategory: "Beverage")
                itemTableView.dataSource = itemDataSource
                itemTableView.reloadData()
                break
            case "Can Food":
                itemDataSource = SampleDataSource(wholeList: itemList, selectedCategory: "Can Food")
                itemTableView.dataSource = itemDataSource
                itemTableView.reloadData()
                break
            case "Bakery":
                itemDataSource = SampleDataSource(wholeList: itemList, selectedCategory: "Bakery")
                itemTableView.dataSource = itemDataSource
                itemTableView.reloadData()
                break
            default:
                itemTableView.dataSource = self
                itemTableView.reloadData()
                break
            }
        }
        
        
    }
    
    // MARK: - Fetch Category List from Firebase Database
    func fetchCategoryList() {
        
        Database.database().reference().child("Stock").observeSingleEvent(of: .value) { (snapshot) in
            if let categoryDict = snapshot.value as? [String : Any] {
                for key in categoryDict.keys {
                    let cat = Category()
                    cat.categoryName = key
                    self.categoryList.append(cat)
                }
                DispatchQueue.main.async {
                    self.categoryTableView.reloadData()
                }
                
            }
        }
        
        
//        Database.database().reference().child("Stock").observe(DataEventType.value) { (snapshot) in
//            if let categoryDict = snapshot.value as? [String : Any] {
//                for key in categoryDict.keys {
//                    let cat = Category()
//                    cat.categoryName = key
//                    self.categoryList.append(cat)
//                }
//                DispatchQueue.main.async {
//                    self.categoryTableView.reloadData()
//                }
//
//            }
//        }
    }
    
    func fetchItemList() {
        Database.database().reference().child("Stock").observe(.value) { (snapshot) in
            if let dict = snapshot.value as? [String : Any] {
                self.itemList = dict
            }
        }
    }
    
    // MARK: - Download images from Firebase Storage
    //before doing anything, make sure have reference of Firebase storage reference in ViewDidLoad

    
    
    
    // MARK: - Location Manager Delegate Methods
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let location = locations[locations.count - 1]
        if location.horizontalAccuracy > 0 {
            
            locationManager.stopUpdatingLocation()
//            for simulator, can set customised location data in the debug menu
            let lat = location.coordinate.latitude
            let lon = location.coordinate.longitude
            let params : [String : String] = ["lat" : String(lat), "lon" : String(lon)]
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print(error)
        let alert = UIAlertController(title: "Location Undefined", message: "this is a location alert", preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.cancel, handler: nil))
        self.present(alert, animated: true, completion: nil)
        
        
    }
    

}
