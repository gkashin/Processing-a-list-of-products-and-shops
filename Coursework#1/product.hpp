//
//  product.hpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#ifndef product_hpp
#define product_hpp

#include "shop.hpp"

using namespace std;

class Product
{
public:
    
    Product();
    Product(string name, Shop shop, int price);
    Product(const Product& otherProduct);
    
    bool operator==(const Product& otherProduct);
    bool operator>(const Product& otherProduct);
    void operator=(const Product& otherProduct);
    
    Product& operator++();
    friend Product operator++(Product& product, int value);
    
    friend bool operator==(const Product& firstProduct, const Product& secondProduct);
    friend bool operator>(const Product& firstProduct, const Product& secondProduct);
    
    friend ostream& operator<<(ostream& output, const Product& product);
    friend istream& operator>>(istream& input, Product& product);
    
    string getShopName();
    string getProductName();
    int getProductPrice();
    
    static bool isValidProduct(const string product);
    
    ~Product();
    
private:
    
    string name_;
    int price_;
    Shop shop_;
};


#endif /* product_hpp */
