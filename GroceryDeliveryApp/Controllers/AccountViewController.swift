//
//  AccountViewController.swift
//  GroceryDeliveryApp
//
//  Created by XIANG YAN on 1/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import UIKit
import Firebase
import SDWebImage

class AccountViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    
    @IBOutlet weak var username: UILabel!
    @IBOutlet weak var profileImageView: UIImageView!
    
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    var loginUser: User?
    

    override func viewDidLoad() {
        super.viewDidLoad()
        self.hideKeyboardWhenTappedAround()

        // Do any additional setup after loading the view.
        fetchUser()
        profileImageView.layer.cornerRadius = profileImageView.frame.width/2
        profileImageView.isUserInteractionEnabled = true
        profileImageView.addGestureRecognizer(UITapGestureRecognizer(target: self, action: #selector(handleSelectprofileImageView)) )
        
    }
    
    @objc func handleSelectprofileImageView() {
        
        let picker : UIImagePickerController = UIImagePickerController()
        picker.delegate = self
        picker.allowsEditing = true
        present(picker, animated: true, completion: nil)
        
    }
    
    func fetchUser() {
        if appDelegate.isLogin {
            Database.database().reference().child("User").child(appDelegate.currentUserUid).observeSingleEvent(of: .value) {
                (snapshot) in
                if let dict = snapshot.value as? [String : Any] {
                    var tempUser = User()
                    tempUser.userEmail = dict["email"] as? String
                    tempUser.userName = dict["name"] as? String
                    tempUser.userProfileImageUrl = dict["profileUrl"] as? String
                    
                    self.loginUser = tempUser
                    self.loadUsernameAndProfileImg()
                }
            }
        }
    }
    
    func loadUsernameAndProfileImg() {
        
        username.text = loginUser?.userName
        
        if let profileImgUrl = loginUser?.userProfileImageUrl {

            let url = URL(string: profileImgUrl)
            print(url!)
            DispatchQueue.main.async {
                self.profileImageView.sd_setImage(with: url, completed: nil)
            }
        }
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        var selectedImageFromPicker : UIImage?
        
        if let editedImage = info["UIImagePickerControllerEditedImage"] {
            selectedImageFromPicker = editedImage as? UIImage
        }else if let orginalImage = info["UIImagePickerControllerOriginalImage"] {
            selectedImageFromPicker = orginalImage as? UIImage
        }
        if let selectedImage = selectedImageFromPicker {
            //repalce with selected iamge
            profileImageView.image = selectedImage
            print("repalced")
            
            //upload selected profile image to Firebase Storage
            let storageRef = Storage.storage().reference().child("users").child(appDelegate.currentUserUid).child("profile.png")
            
            if let uploadImg = UIImagePNGRepresentation(profileImageView.image!) {
                storageRef.putData(uploadImg, metadata: nil) { (metadata, error) in
                    if error != nil {
                        print (error!.localizedDescription)
                    }else{
                        storageRef.downloadURL(completion: { (url, error) in
                            if error == nil {
                                let profileUrl = ["profileUrl" : url?.absoluteString]
                                let dbRef = Database.database().reference().child("User").child(self.appDelegate.currentUserUid)
                                dbRef.updateChildValues(profileUrl as Any as! [AnyHashable : Any], withCompletionBlock: { (error, dbRef) in
                                    if error != nil {
                                        print(error!.localizedDescription)
                                    }
                                })
                            }
                        })
                    }
                }
            }
            
            
        }
        dismiss(animated: true, completion: nil)
        
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        dismiss(animated: true, completion: nil)
    }

    override func viewWillAppear(_ animated: Bool) {
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

}
