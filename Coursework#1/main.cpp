//
//  main.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#include "product.hpp"
#include "products.hpp"
#include "shops.hpp"
#include "errorHandling.hpp"

using namespace std;

Shops shopsList;

int main()
{
    try
    {
        string inputFileName;
        ifstream input;
        ofstream output;
        ofstream outputShopsList;
        
        cout << "Enter input file name: ";
        cin >> inputFileName;
        
        input.open(inputFileName);
        if (!input.is_open())
        {
            std::string error = ErrorHandling::createFileErrorDescription(fileErrors::didNotOpen, inputFileName);
            throw invalid_argument(error);
        }
        
        string outputFileName = "output.txt";
        output.open(outputFileName);
        if (!output.is_open())
        {
            std::string error = ErrorHandling::createFileErrorDescription(fileErrors::didNotOpen, outputFileName);
            throw invalid_argument(error);
        }
        
        string shopsListFileName = "outputShopsList.txt";
        outputShopsList.open(shopsListFileName);
        if (!outputShopsList.is_open())
        {
            std::string error = ErrorHandling::createFileErrorDescription(fileErrors::didNotOpen, shopsListFileName);
            throw invalid_argument(error);
        }
        
        Products productsList;
        
        input >> productsList;
    
        productsList.sort();
        cout << productsList.showTheMostExpensiveProduct() << endl;
        
        output << productsList;
        outputShopsList << shopsList;
        
        ErrorHandling::outputError();
        
        input.close();
        output.close();
        outputShopsList.close();
    }
    
    catch(invalid_argument &error)
    {
        cout << error.what() << endl;
        return -1;
    }
    
    return 0;
}
