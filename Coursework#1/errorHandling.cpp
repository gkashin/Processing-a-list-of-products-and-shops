//
//  errorHandling.cpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <vector>
#include <string>
#include <fstream>

#include "errorHandling.hpp"
#include "isIntegerNumber.hpp"
#include "product.hpp"
#include "errorsType.h"

using namespace std;

int maxProductLength = 0; // объявляем максимальные значения длин каждого поля для дальнейшего вывода таблицы
int maxShopLength = 0;
int maxPriceLength = 0;

int lineNumber = 0; // счетчик строки, увеличивается после каждого вызова функции

bool ErrorHandling::isValidString(string handleString)
{
    lineNumber++;
    
    if (handleString.find(';', 0) != string::npos &&                                        // проверяем строку на содержание двух точек с запятой
        handleString.find(';', handleString.find(';', 0) + 1) != string::npos &&            // программа предусматривает жесткое разделение полей точками
        handleString.find(';', handleString.find(';', handleString.find(';', 0) + 1) + 1) == string::npos)  // с запятой, поэтому их должно быть именно две, иначе пропускаем строку
    {
        bool isValidProductField = false; // переменные, определяющие правильность полей
        bool isValidShopField = false;
        bool isValidPriceField = false;
        
        string handleField; // подстрока строки handleString, содержит нужное нам поле
        
        handleField = handleString.substr(0, handleString.find(';', 0));
        isValidProductField = Product::isValidProduct(handleField);
        
        if (!isValidProductField) { return false; }
        
        handleString = handleString.substr(handleString.find(';', 0) + 1, handleString.find('\n', 0)); // обрезаем handleString на одно, уже обработанное, поле
        handleField = handleString.substr(0, handleString.find(';', 0));
        
        isValidShopField = Shop::isValidShop(handleField);
        
        if (!isValidShopField) { return false; }
        
        handleString = handleString.substr(handleString.find(';', 0) + 1, handleString.find('\n', 0)); // обрезаем handleString на одно, уже обработанное, поле
        
        handleField = handleString; // сюда программа придет, когда будет считываться последнее поле
        
        // далее удаляются все пробелы и табуляции из начала и конца productPrice
        
        int priceLength = static_cast<int>(handleField.length());
        while (handleField[0] == ' ' || handleField[0] == '\t')
        {
            if (handleField[0] == ' ')
            {
                handleField.erase(0, handleField.find_first_not_of(' '));
            }
            
            if (handleField[0] == '\t')
            {
                handleField.erase(0, handleField.find_first_not_of('\t'));
            }
        }
        
        priceLength = static_cast<int>(handleField.length());
        
        while (handleField[priceLength - 1] == ' ' || handleField[priceLength - 1] == '\t')
        {
            auto lastNotSpacePos = handleField.find_last_not_of(' ');
            
            if (handleField[priceLength - 1] == ' ')
            {
                handleField.erase(lastNotSpacePos + 1, priceLength - lastNotSpacePos);
                priceLength = static_cast<int>(handleField.length());
            }
            
            auto lastNotTabPos = handleField.find_last_not_of('\t');
            
            if (handleField[priceLength - 1] == '\t')
            {
                handleField.erase(lastNotTabPos + 1, priceLength - lastNotTabPos);
                priceLength = static_cast<int>(handleField.length());
            }
        }
        
        string error;
        if (handleField == "" || handleField.find_first_not_of(" ") == string::npos || handleField.find_first_not_of('\t') == string::npos) // поле не должно быть пустым
        {
            stringDataErrors errorType = stringDataErrors::isFieldEmpty;
            
            error = createStringDataErrorDescription(errorType, lineNumber);
            ErrorHandling::addError(error);
        }
        else if (!isIntegerNumber(handleField)) // цена продукта должна быть задана числом
        {
            numericDataErrors errorType = numericDataErrors::nonInteger;
            error = createNumericDataErrorDescription(errorType, lineNumber);
            ErrorHandling::addError(error);
        }
        else if (stoi(handleField) <= 0) // если задано числом, то проверяем, чтобы это число было положительным
        {
            numericDataErrors errorType = numericDataErrors::nonPositive;
            error = createNumericDataErrorDescription(errorType, lineNumber);
            ErrorHandling::addError(error);
        }
        else
        {
            isValidPriceField = true;
        }
        
        return isValidPriceField;
    }
    return false;
}



void ErrorHandling::removeSpaces(string& handleString)
{
    string productName;
    string productPrice;
    string shopName;
    
    string workingString = handleString;
    
    int productLength;
    int shopLength;
    int priceLength;
    
    productName = workingString.substr(0, workingString.find(';', 0)); // выделяем название товара
    productLength = static_cast<int>(productName.length());
    
    // цикл, удялающий пробелы и табуляции перед названием товара
    
    while (productName[0] == ' ' || productName[0] == '\t')
    {
        if (productName[0] == ' ')
        {
            productName.erase(0, productName.find_first_not_of(' '));
        }
        
        if (productName[0] == '\t')
        {
            productName.erase(0, productName.find_first_not_of('\t'));
        }
    }
    
    // цикл, удаляющий пробелы и табуляции после названия товара
    
    productLength = static_cast<int>(productName.length()); // заново определяем длину, так как она могла измениться
    while (productName[productLength - 1] == ' ' || productName[productLength - 1] == '\t')
    {
        auto lastNotSpacePos = productName.find_last_not_of(' '); // позиция последнего не пробела
        
        if (productName[productLength - 1] == ' ') // если последний символ названия товара - пробел
        {
            productName.erase(lastNotSpacePos + 1, productLength - lastNotSpacePos); // то удаляем все найденные в конце пробелы
            productLength = static_cast<int>(productName.length()); // обновляем длину
        }
        
        auto lastNotTabPos = productName.find_last_not_of('\t'); // позиция последней не табуляции
        
        if (productName[productLength - 1] == '\t') // если последний символ названия товара - табуляция
        {
            productName.erase(lastNotTabPos + 1, productLength - lastNotTabPos); // то удялаем все найденные в конце табуляции
            productLength = static_cast<int>(productName.length()); // обновляем длину
        }
    }
    
    if (productLength > maxProductLength) // обновляем максимальную длину для последующего вывода в таблицу
    {
        maxProductLength = productLength;
    }
    
    workingString = workingString.substr(workingString.find(';', 0) + 1, workingString.find('\n', 0)); // обрезаем строку на одно, уже обработанное, поле
    
    // далее все аналогично первому циклу
    
    shopName = workingString.substr(0, workingString.find(';', 0));
    shopLength = static_cast<int>(shopName.length());
    
    while (shopName[0] == ' ' || shopName[0] == '\t')
    {
        if (shopName[0] == ' ')
        {
            shopName.erase(0, shopName.find_first_not_of(' '));
        }
        
        if (shopName[0] == '\t')
        {
            shopName.erase(0, shopName.find_first_not_of('\t'));
        }
    }
    
    shopLength = static_cast<int>(shopName.length());
    
    while (shopName[shopLength - 1] == ' ' || shopName[shopLength - 1] == '\t')
    {
        auto lastNotSpacePos = shopName.find_last_not_of(' ');
        
        if (shopName[shopLength - 1] == ' ')
        {
            shopName.erase(lastNotSpacePos + 1, shopLength - lastNotSpacePos);
            shopLength = static_cast<int>(shopName.length());
        }
        
        auto lastNotTabPos = shopName.find_last_not_of('\t');
        
        if (shopName[shopLength - 1] == '\t')
        {
            shopName.erase(lastNotTabPos + 1, shopLength - lastNotTabPos);
            shopLength = static_cast<int>(shopName.length());
        }
    }
    
    if (shopLength > maxShopLength)
    {
        maxShopLength = shopLength;
    }
    
    workingString = workingString.substr(workingString.find(';', 0) + 1, workingString.find('\n', 0)); // обрезаем строку еще на одно поле
    
    // цикл, удаляющий все пробелы и табуляции в productPrice
    
    productPrice = workingString.substr(0, workingString.find('\n', 0));
    priceLength = static_cast<int>(productPrice.length());
    while (productPrice[0] == ' ' || productPrice[0] == '\t')
    {
        if (productPrice[0] == ' ')
        {
            productPrice.erase(0, productPrice.find_first_not_of(' '));
        }
        
        if (productPrice[0] == '\t')
        {
            productPrice.erase(0, productPrice.find_first_not_of('\t'));
        }
    }
    
    priceLength = static_cast<int>(productPrice.length());
    
    while (productPrice[priceLength - 1] == ' ' || productPrice[priceLength - 1] == '\t')
    {
        auto lastNotSpacePos = productPrice.find_last_not_of(' ');
        
        if (productPrice[priceLength - 1] == ' ')
        {
            productPrice.erase(lastNotSpacePos + 1, priceLength - lastNotSpacePos);
            priceLength = static_cast<int>(productPrice.length());
        }
        
        auto lastNotTabPos = productPrice.find_last_not_of('\t');
        
        if (productPrice[priceLength - 1] == '\t')
        {
            productPrice.erase(lastNotTabPos + 1, priceLength - lastNotTabPos);
            priceLength = static_cast<int>(productPrice.length());
        }
    }
    
    if (priceLength > maxPriceLength)
    {
        maxPriceLength = priceLength;
    }
    
    handleString = productName + ';' + shopName + ';' + productPrice; // присваиваем принимаемой строке обработанные поля, разделенные, как и были, точками с запятой
}

string ErrorHandling::operator[](int index)
{
    if (index < 0 || index > errorList.size())
    {
        throw invalid_argument("ErrorHandling Index error");
    }
    else
    {
        return errorList[index];
    }
}

vector<string> ErrorHandling::errorList;
void ErrorHandling::outputError()
{
    ofstream outputError;
    std::string fileName = "outputErrors.txt";
    outputError.open(fileName);
    
    if (!outputError.is_open())
    {
        std::string error = createFileErrorDescription(fileErrors::didNotOpen, fileName);
        throw invalid_argument(error);
    }
    
    if (!errorList.empty())    // если массив ошибок не пустой, выводим эти ошибки в отдельный файл
    {
        for (int i = 0; i < errorList.size(); i++)
        {
            outputError << errorList[i] << endl;
        }
    }
    else
    {
        outputError << "No errors";
    }
    
    outputError.close();
}

void ErrorHandling::addError(string error)
{
    errorList.push_back(error);
}

bool ErrorHandling::isValidField(const string handleField)
{
    extern int lineNumber;
    
    string cyrillicString = "абвгдеёжзийклмнопрстуфхцчшщъыьэюьАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; // массив для проверки строки на русские символы
    string invalidSymbols = "~`!@\"#№%$:,^&.*()-+=[]{}|?\\/><'";
    string invalidUnderscores = "__";
    string error;
    
    if (handleField == "" || handleField.find_first_not_of(' ') == string::npos || handleField.find_first_not_of('\t') == string::npos) // поле не должно быть пустым
    {
        stringDataErrors errorType = stringDataErrors::isFieldEmpty;
        error = createStringDataErrorDescription(errorType, lineNumber);
        ErrorHandling::addError(error);
        return false;
    }
    else if (handleField.find_first_of(cyrillicString) != string::npos) // поле не должно содержать кириллицу
    {
        stringDataErrors errorType = stringDataErrors::incorrectKeyboardLayout;
        error = createStringDataErrorDescription(errorType, lineNumber);
        ErrorHandling::addError(error);
        return false;
    }
    else if (handleField.find_first_of(invalidSymbols) != string::npos || // поле не должно содержать некорректные символы
             handleField.find(invalidUnderscores) != string::npos)
    {
        stringDataErrors errorType = stringDataErrors::incorrectSymbols;
        error = createStringDataErrorDescription(errorType, lineNumber);
        ErrorHandling::addError(error);
        return false;
    }
    else if (handleField[0] >= 'a' && handleField[0] <= 'z') // поле должно начинаться с заглавной буквы
    {
        stringDataErrors errorType = stringDataErrors::incorrectRegister;
        error = createStringDataErrorDescription(errorType, lineNumber);
        ErrorHandling::addError(error);
        return false;
    }
    else
    {
        return true; // если все хорошо, возвращаем значение true
    }
}

std::string ErrorHandling::createStringDataErrorDescription(const stringDataErrors &errorType, const int &lineNumber)
{
    std::string error;
    
    switch (errorType) {
        case stringDataErrors::isFieldEmpty:
            error = "The line #" + to_string(lineNumber) + " has an empty field!";
            break;
        case stringDataErrors::incorrectKeyboardLayout:
            error = "The line #" + to_string(lineNumber) + " contains non-latin characters!";
            break;
        case stringDataErrors::incorrectSymbols:
            error = "The line #" + to_string(lineNumber) + " contains invalid symbols!";
            break;
        case stringDataErrors::incorrectRegister:
            error = "The line #" + to_string(lineNumber) + " contains field starting with a non-capital letter!";
            break;
        default:
            break;
    }
    return error;
}

std::string ErrorHandling::createNumericDataErrorDescription(const numericDataErrors &errorType, const int &lineNumber)
{
    std::string error;
    
    switch (errorType) {
        case numericDataErrors::nonInteger:
            error = "The product price in the line #" + to_string(lineNumber) + " must be specified by integer number";
            break;
        case numericDataErrors::nonPositive:
            error = "The product price in the line #" + to_string(lineNumber) + " must be specified by positive number";
            break;
        default:
            break;
    }
    return error;
}

std::string ErrorHandling::createFileErrorDescription(const fileErrors &errorType, const std::string &fileName)
{
    std::string error;
    switch (errorType) {
        case fileErrors::isEmpty:
            error = "ERROR! File '" + fileName + "' is empty!";
            break;
        case fileErrors::didNotOpen:
            error = "ERROR! File '" + fileName + "' did not open";
            break;
        default:
            break;
    }
    return error;
}
