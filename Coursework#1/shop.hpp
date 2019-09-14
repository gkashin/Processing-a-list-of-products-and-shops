//
//  shop.hpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#ifndef shop_hpp
#define shop_hpp

using namespace std;

class Shop
{
public:
    
    Shop();
    Shop(string name);
    
    void operator=(const Shop &otherShop);
    bool operator==(const Shop &otherShop);
    
    friend ostream& operator<<(ostream& output, const Shop& shop);
    friend istream& operator>>(istream& input, Shop& shop);
    friend bool operator==(const Shop &firstShop, const Shop &secondShop);
    
    string getName();
    
    static bool isValidShop(const string shop);
    
private:
    
    string name_;
};

#endif /* shop_hpp */
