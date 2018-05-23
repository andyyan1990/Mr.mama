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

class ShopViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, CLLocationManagerDelegate, UISearchBarDelegate{
    
    @IBOutlet weak var categoryTableView: UITableView!
    @IBOutlet weak var itemTableView: UITableView!
    
    @IBOutlet weak var searchInShop: UISearchBar!
    
    //Declare Variable
    let locationManager = CLLocationManager()
    
    //create reference of Firebase Storage reference
    
    override func viewDidLoad() {
        super.viewDidLoad()

        //setup tableView delegate and datasource
        categoryTableView.delegate = self
        itemTableView.delegate = self
        
        //setup searchBar delegate
        searchInShop.delegate = self
        
        //register nib for customised cells
        categoryTableView.register(UINib(nibName: "CategoryTableViewCell", bundle: nil), forCellReuseIdentifier: "CustomCategoryCell")
        itemTableView.register(UINib(nibName: "ItemTableViewCell", bundle: nil), forCellReuseIdentifier: "CustomItemCell")
        
        downloadBakeryImages()
        
        // Location Service setup
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        self.categoryTableView.reloadData()
        self.itemTableView.reloadData()
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
    
    // MARK: - TableView
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 3
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        if tableView == categoryTableView {
            
            let cell = tableView.dequeueReusableCell(withIdentifier: "CustomCategoryCell", for: indexPath) as! CategoryTableViewCell
            cell.categoryLabel.text = "category one"
            //cell.categoryImage.image = UIImage(data: <#T##Data#>)
            return cell
            
        }else{
            
            let cell = tableView.dequeueReusableCell(withIdentifier: "CustomItemCell", for: indexPath) as! ItemTableViewCell
            cell.itemLabel.text = "item one"
            return cell
            
        }
        
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if tableView == categoryTableView {
            return 80
        }else{
            return 120
        }
    }
    
//    func tableView(_ tableView: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath) {
//        <#code#>
//    }
    
    //configure tableViews
    func configureTableView() {
        categoryTableView.rowHeight = UITableViewAutomaticDimension
        categoryTableView.estimatedRowHeight = 60.0
        itemTableView.rowHeight = UITableViewAutomaticDimension
        itemTableView.estimatedRowHeight = 109.0
    }
    
    
    // MARK: - Download images from Firebase Storage
    //before doing anything, make sure have reference of Firebase storage reference in ViewDidLoad
    func downloadImage() -> Void {
        
        print("function called")
        let storage = Storage.storage()
        let itemImagesStorageRef:StorageReference = storage.reference(withPath: "items/bakery/baguette.png")
        
        var imageArray = [UIImage]()
        var test = itemImagesStorageRef.getData(maxSize: 1 * 1024 * 1024) { (data, error) in
            if error == nil {
                print("type of downloaded data ")
                print(type(of: data!))
            }else{
                print("error message: ")
                print (error!.localizedDescription)
            }
        }
    }
    
    
    
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
