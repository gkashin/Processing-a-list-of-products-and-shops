//
//  errorHandling.hpp
//  Coursework#1
//
//  Created by Георгий Кашин on 07/04/2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#ifndef errorHandling_hpp
#define errorHandling_hpp

#include "errorsType.h"

typedef ErrorsType::StringDataErrors stringDataErrors;
typedef ErrorsType::NumericDataErrors numericDataErrors;
typedef ErrorsType::FileErrors fileErrors;

class ErrorHandling
{
public:
    bool isValidString(std::string handleString); // метод, проверяющий строку на соответствие определенным требованиям
    void removeSpaces(std::string& handleString); // метод, удаляющий из строки все лишние пробелы и табуляции
    static bool isValidField(const std::string handleString);
    
    static void outputError();
    std::string operator[](int index);
    
    static void addError(std::string error);
    
    static std::string createStringDataErrorDescription(const stringDataErrors &errorType, const int &lineNumber);
    static std::string createNumericDataErrorDescription(const numericDataErrors &errorType, const int &lineNumber);
    static std::string createFileErrorDescription(const fileErrors &errorType, const std::string &fileName);
    
private:
    
    static std::vector<std::string> errorList;
};

#endif /* errorHandling_hpp */
