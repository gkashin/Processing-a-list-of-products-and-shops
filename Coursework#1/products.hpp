//
//  products.hpp
//  Coursework#1
//
//  Created by Георгий Кашин on 11/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#ifndef Products_hpp
#define Products_hpp

#include <vector>

class Product;

using namespace std;

class Products
{
public:
    
    void addProduct(Product &product);
    const string showTheMostExpensiveProduct();
    void sort();
    int size();
    
    friend void operator>>(ifstream& input, Products &productsList);
    friend void operator<<(ofstream& output, Products &productsList);
    
    Product& operator[](int index);
    
private:
    
    vector<Product> productsList;
};

#endif /* products_hpp */
