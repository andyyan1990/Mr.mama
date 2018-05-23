//
//  LoginViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 12/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import Firebase

class LoginViewController: UIViewController {
    
    @IBOutlet weak var emailField: UITextField!
    @IBOutlet weak var passwordField: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
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
    
    @IBAction func loginBtnClicked(_ sender: UIButton) {
        if isInputValid(inputEmail: emailField.text!, inputPasswd: passwordField.text!){
            Auth.auth().signIn(withEmail: emailField.text!, password: passwordField.text!) { (user, error) in
                if error != nil {
                    
                    //Alert with error message sent back from Firebase
                    self.alertMessage(title: "Login Error", message: error!.localizedDescription)
                    
                }else{
                    
                    self.performSegue(withIdentifier: "loginToMain", sender: sender)
                    
                }
            }
        }
        else{
            //Alert with null or empty error message
            alertMessage(title: "Check your input", message: "email and password shouldn't be null or empty.")
        }
    }
    
    // MARK: - Validation of Input
    
    func isInputValid(inputEmail:String, inputPasswd:String) -> Bool {
        if inputEmail.trimmingCharacters(in:.whitespacesAndNewlines).isEmpty || inputEmail.isEmpty || inputPasswd.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty || inputPasswd.isEmpty {
            return false
        }
        return true
    }
    
    func alertMessage(title:String, message:String) -> Void {
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.cancel, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    

}
