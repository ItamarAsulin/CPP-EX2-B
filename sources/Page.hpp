//
// Created by itamarq on 26/03/2022.
//

#ifndef NOTEBOOK_B_PAGE_HPP
#define NOTEBOOK_B_PAGE_HPP

#include <iostream>
#include <map>
#include <string>
#include "Direction.hpp"

class Page
{
private:
    std::map<unsigned int, char *> page;

    void validateLinesExist( unsigned int rowNum, unsigned int colNum,
                            ariel::Direction direction, int len);



public:
    Page(){};
    void validateCanWrite( unsigned int rowNum, unsigned int colNum,
                           ariel::Direction direction, std::string &toWrite);
    void writeToPage(unsigned int rowNum, unsigned int colNum, ariel::Direction direction, std::string toWrite);

    std::string readFromPage(unsigned int rowNum, unsigned int colNum, ariel::Direction direction, int len);

    void eraseFromPage(unsigned int rowNum, unsigned int colNum, ariel::Direction direction, int len);

    void showPage();
};

#endif // NOTEBOOK_B_PAGE_HPP
