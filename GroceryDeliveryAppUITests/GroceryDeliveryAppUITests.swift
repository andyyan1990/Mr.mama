//
//  GroceryDeliveryAppUITests.swift
//  GroceryDeliveryAppUITests
//
//  Created by XIANG YAN on 12/5/18.
//  Copyright © 2018 XIANG YAN. All rights reserved.
//

import XCTest

class GroceryDeliveryAppUITests: XCTestCase {
    
    var app: XCUIApplication?
    
    override func setUp() {
        super.setUp()
        
        // Put setup code here. This method is called before the invocation of each test method in the class.
        
        // In UI tests it is usually best to stop immediately when a failure occurs.
        continueAfterFailure = false
        // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
        app = XCUIApplication()
        app?.launch()

        // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        // Use recording to get started writing UI tests.
        
        let app = XCUIApplication()
        let tablesQuery = app.tables
        tablesQuery/*@START_MENU_TOKEN@*/.staticTexts["Diary"]/*[[".cells.staticTexts[\"Diary\"]",".staticTexts[\"Diary\"]"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/.tap()
        tablesQuery.cells.containing(.staticText, identifier:"pure milk 1").buttons["Increment"].tap()
        
        let incrementButton = tablesQuery/*@START_MENU_TOKEN@*/.cells.containing(.staticText, identifier:"1")/*[[".cells.containing(.staticText, identifier:\"pure milk 1\")",".cells.containing(.staticText, identifier:\"1\")"],[[[-1,1],[-1,0]]],[0]]@END_MENU_TOKEN@*/.buttons["Increment"]
        incrementButton.tap()
        app.navigationBars["pure milk 1"].buttons["Back"].tap()
        incrementButton.tap()
        
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }
    
}
