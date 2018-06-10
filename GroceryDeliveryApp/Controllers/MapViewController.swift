//
//  MapViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 8/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import MapKit
import CoreLocation

class MapViewController: UIViewController, MKMapViewDelegate, CLLocationManagerDelegate, MKLocalSearchCompleterDelegate, SetAddressDelegate, UITableViewDelegate, UITableViewDataSource, UISearchBarDelegate {
    
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var searchAddressView: UIView!
    @IBOutlet weak var searchBar: UISearchBar!
    @IBOutlet weak var mapBtn: UIButton!
    @IBOutlet weak var centerUserLocationBtn: UIButton!
    @IBOutlet weak var searchResultTableView: UITableView!
    
    let locationManager = CLLocationManager()
    var searchCompleter = MKLocalSearchCompleter()
    var searchResults = [MKLocalSearchCompletion]()
    var selectedOrSetAddress : String?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.hideKeyboardWhenTappedAround()

        // Do any additional setup after loading the view.
        searchAddressView.layer.cornerRadius = 5
        searchAddressView.layer.shadowOpacity = 0.3
        searchAddressView.layer.shadowRadius = 5
        searchAddressView.layer.shadowOffset = CGSize(width: 0, height: 4)
        mapBtn.layer.cornerRadius = 5
        mapBtn.layer.shadowOpacity = 0.3
        mapBtn.layer.shadowRadius = 5
        mapBtn.layer.shadowOffset = CGSize(width: 0, height: 3)
        centerUserLocationBtn.layer.shadowOpacity = 0.3
        centerUserLocationBtn.layer.shadowRadius = 3
        searchBar.layer.cornerRadius = 5
        
        //setup location and map
        setUpLocationAndMapView()
        searchCompleter.delegate = self
        searchResultTableView.isHidden = true
        convertCurrentLocationToPlaceName()
    }

    override func viewWillAppear(_ animated: Bool) {
        if searchResults.count == 0 {
            searchResultTableView.isHidden = true
        }
    }
    
    func setUpLocationAndMapView() {
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
        mapView.showsUserLocation = true
        mapView.userTrackingMode = .follow
        centerLocation(coordinate: mapView.userLocation.coordinate,regionRadiousLevel: 2.0)
    }
    
    func centerLocation(coordinate: CLLocationCoordinate2D,regionRadiousLevel : Double) {
        let regionRadious:CLLocationDistance = 1000
        let coordinateRegion = MKCoordinateRegionMakeWithDistance(coordinate, regionRadious * regionRadiousLevel, regionRadious * regionRadiousLevel)
        mapView.setRegion(coordinateRegion, animated: true)
    }

    @IBAction func centerUserLocation(_ sender: Any) {
        centerLocation(coordinate: mapView.userLocation.coordinate, regionRadiousLevel: 2.0)
    }
    
    //connect search bar input text with searchCompleter query
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
        searchCompleter.queryFragment = searchText
        if !searchText.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
            searchResultTableView.isHidden = false
        }
        if (searchBar.text?.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty)! {
            searchResultTableView.isHidden = true
        }
        searchResultTableView.reloadData()
    }

    
    //pass searched result list to searchResults
    func completerDidUpdateResults(_ completer: MKLocalSearchCompleter) {
        searchResults = completer.results
        print("results searched: \(searchResults.count)")
        searchResultTableView.reloadData()
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
    
    @IBAction func setAddress(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
        getAddress()
    }
    
    func getAddress() -> String {
        return self.selectedOrSetAddress!
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {

        return searchResults.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let searchResult = searchResults[indexPath.row]
        let cell = UITableViewCell(style: .subtitle, reuseIdentifier: "searchResultCell")
        cell.textLabel?.text = searchResult.title
        cell.detailTextLabel?.text = searchResult.subtitle
        return cell
    }
    
    //select specific row to set the address
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        tableView.isHidden = true
        
        print(searchResults.count, searchResults[indexPath.row])
        let completion = searchResults[indexPath.row]
        let searchRequest = MKLocalSearchRequest(completion: completion)
        let search = MKLocalSearch(request: searchRequest)
        search.start { (response, error) in
            if error == nil {
                let coordinate = response?.mapItems[0].placemark.coordinate
                let annotation = MKPointAnnotation()
                annotation.coordinate = coordinate!
                annotation.title = completion.title
                annotation.subtitle = completion.subtitle
                self.mapView.addAnnotation(annotation)
                self.centerLocation(coordinate: coordinate!, regionRadiousLevel: 2.0)
                self.selectedOrSetAddress = annotation.title! + "," + annotation.subtitle!
            }
        }
        
    }
    
    func convertCurrentLocationToPlaceName() {
        if let currentLocation = locationManager.location {
            let geoCoder = CLGeocoder()
            geoCoder.reverseGeocodeLocation(currentLocation) { (placemarks, error) in
                if error == nil {
                    self.selectedOrSetAddress = placemarks![0].name! + "," + placemarks![0].locality! + "," + placemarks![0].postalCode! + "," + placemarks![0].subLocality! + " " + placemarks![0].country!
                }
            }
        }
    }

}
