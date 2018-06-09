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

class MapViewController: UIViewController, MKMapViewDelegate, CLLocationManagerDelegate, MKLocalSearchCompleterDelegate, SetAddressDelegate {

    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var searchAddressView: UIView!
    @IBOutlet weak var addressField: UITextField!
    @IBOutlet weak var mapBtn: UIButton!
    @IBOutlet weak var centerUserLocationBtn: UIButton!
    
    let locationManager = CLLocationManager()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.hideKeyboardWhenTappedAround()

        // Do any additional setup after loading the view.
        searchAddressView.layer.cornerRadius = 10
        searchAddressView.layer.shadowOpacity = 0.3
        searchAddressView.layer.shadowRadius = 5
        searchAddressView.layer.shadowOffset = CGSize(width: 0, height: 4)
        mapBtn.layer.cornerRadius = 8
        mapBtn.layer.shadowOpacity = 0.3
        mapBtn.layer.shadowRadius = 5
        mapBtn.layer.shadowOffset = CGSize(width: 0, height: 3)
        centerUserLocationBtn.layer.shadowOpacity = 0.3
        centerUserLocationBtn.layer.shadowRadius = 3
        
        //setup location and map
        setUpLocationAndMapView()
    }
    
    func setUpLocationAndMapView() {
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
        mapView.showsUserLocation = true
        mapView.userTrackingMode = .follow
        centerMapOnUserLocation(regionRadiousLevel: 2.0)
    }
    
    func centerMapOnUserLocation(regionRadiousLevel : Double) {
        let regionRadious:CLLocationDistance = 1000
        let coordinateRegion = MKCoordinateRegionMakeWithDistance(mapView.userLocation.coordinate, regionRadious * regionRadiousLevel, regionRadious * regionRadiousLevel)
        mapView.setRegion(coordinateRegion, animated: true)
    }

    @IBAction func centerUserLocation(_ sender: Any) {
        centerMapOnUserLocation(regionRadiousLevel: 2.0)
    }
    
    @IBAction func searchLocation(_ sender: Any) {
        let searchRequest = MKLocalSearchRequest()
        searchRequest.naturalLanguageQuery = addressField.text
        let activeSearch = MKLocalSearch(request: searchRequest)
        activeSearch.start { (response, error) in
            if error == nil {
                let annotations = self.mapView.annotations
                self.mapView.removeAnnotations(annotations)
                
                let latitude = response?.boundingRegion.center.latitude
                let longitude = response?.boundingRegion.center.longitude
                
                let annotation = MKPointAnnotation()
                
            }
        }
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
        return "test"
    }
    

}
