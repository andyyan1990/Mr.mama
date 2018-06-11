//
//  RegisterViewControllerTest.swift
//  GroceryDeliveryAppTests
//
//  Created by XIANG YAN on 8/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import XCTest
@testable import GroceryDeliveryApp

class RegisterViewControllerTest: XCTestCase {

    var registerVC:RegisterViewController?
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
        registerVC = RegisterViewController()
        
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
        registerVC = nil
    }
    
    func testInputEmailValid() {
        
        let inputEmail = "abc"
        let inputPasswd = "password"
        let isValid = registerVC?.isInputValid(inputEmail: inputEmail, inputPasswd: inputPasswd)
        XCTAssertTrue(isValid!)
    }
    
    func testPasswordSame() {
        let inputPassewd = "password"
        let confirmPasswd = "password"
        XCTAssert((registerVC?.isPasswordSame(passwd: inputPassewd, confirmPasswd: confirmPasswd))!)
    }
}
