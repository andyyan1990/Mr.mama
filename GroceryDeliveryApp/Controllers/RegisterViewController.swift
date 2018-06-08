//
//  RegisterViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 12/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import Firebase

class RegisterViewController: UIViewController {

    @IBOutlet weak var emailField: UITextField!
    @IBOutlet weak var passwordField: UITextField!
    @IBOutlet weak var confirmPasswdField: UITextField!
    
    
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
    
    @IBAction func registerBtnClicked(_ sender: UIButton) {
        
        if isInputValid(inputEmail: emailField.text!, inputPasswd: passwordField.text!) && isPasswordSame(passwd: passwordField.text!, confirmPasswd: confirmPasswdField.text!){
            Auth.auth().createUser(withEmail: emailField.text!, password: passwordField.text!) { (user, error) in
                if error == nil {
                    print(user!)
                    user?.sendEmailVerification(completion: { (error) in
                        print(error ?? "default error")
                    })
                    
                    //persist user information into database
                    let dbRf = Database.database().reference(fromURL: "https://mr-mama-5bdee.firebaseio.com").child("User").child((user?.uid)!)
    
                    let values = ["email" : self.emailField.text!, "name" : "default user"] as [String : Any]
                    dbRf.updateChildValues(values, withCompletionBlock: { (error, dbRf) in
                        if error == nil{
                            print("user saved")
                        }else{
                            print(error!.localizedDescription)
                        }
                    })
                    self.performSegue(withIdentifier: "registerToLogin", sender: sender)
                }else{
                    self.alertMessage(title: "Signup Error", message: error!.localizedDescription)
                }
            }
        }else{
            alertMessage(title: "Input Error", message: "Plase check your input. Email and password shouldn't be null. Password and confirm Password should be the same")
            //later could be improved to be label warning below the input field
        }
        
    }
    
    
    // MARK: - Validation of Input
    
    func isInputValid(inputEmail:String, inputPasswd:String) -> Bool {
        if inputEmail.trimmingCharacters(in:.whitespacesAndNewlines).isEmpty || inputEmail.isEmpty || inputPasswd.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty || inputPasswd.isEmpty {
            return false
        }
        return true
    }
    
    func isPasswordSame(passwd:String, confirmPasswd:String) -> Bool {
        if passwd == confirmPasswd{
            return true
        }else{
            return false
        }
    }
    
    func alertMessage(title:String, message:String) -> Void {
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.cancel, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    
    @IBAction func alreadyAnUser(_ sender: Any) {
        performSegue(withIdentifier: "registerToLogin", sender: nil)
    }
    

}
