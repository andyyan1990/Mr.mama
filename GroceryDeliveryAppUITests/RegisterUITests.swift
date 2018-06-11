//
//  RegisterUITests.swift
//  GroceryDeliveryAppUITests
//
//  Created by XIANG YAN on 11/6/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import XCTest

class RegisterUITests: XCTestCase {
        
    override func setUp() {
        super.setUp()
        
        // Put setup code here. This method is called before the invocation of each test method in the class.
        
        // In UI tests it is usually best to stop immediately when a failure occurs.
        continueAfterFailure = false
        // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
        XCUIApplication().launch()

        // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        // Use recording to get started writing UI tests.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }
    
    func testRegisterToLoginSegue() {
        
        let app = XCUIApplication()
        app.buttons["Register"].tap()
        app.buttons["Already an user? Click here"].tap()
    }
    
    func testInputPasswdInconsistentAlert() {
        
        let app = XCUIApplication()
        app.buttons["Register"].tap()
        
        let element = app.children(matching: .window).element(boundBy: 0).children(matching: .other).element.children(matching: .other).element
        element.children(matching: .textField).element.tap()
        
        let secureTextField = element.children(matching: .secureTextField).element(boundBy: 0)
        secureTextField.tap()
        secureTextField.tap()
        
        let secureTextField2 = element.children(matching: .secureTextField).element(boundBy: 1)
        secureTextField2.tap()
        secureTextField2.tap()
        app.buttons["sign up"].tap()
        app.alerts["Input Error"].buttons["OK"].tap()
    }
    
}
