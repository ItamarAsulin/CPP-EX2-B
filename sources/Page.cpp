////
//// Created by itamarq on 26/03/2022.
////
//
//#include "Page.hpp"
//#include "Direction.hpp"
//#include <map>
//#include <iostream>
//#include <string>
//#include <vector>
//
//const int ROW_MAX_LENGTH = 100;
//const std::vector<char> badChars = {'~'};
//const int MIN_LEGAL_CHAR = 33;
//const int MAX_LEGAL_CHAR = 125;
//
//using namespace ariel;
//
//void Page::writeToPage(unsigned int rowNum, unsigned int colNum, ariel::Direction direction, std::string toWrite) {
//    this->validateCanWrite(rowNum, colNum, direction, toWrite);
//    if (direction == ariel::Direction::Horizontal) {
//        int textLen = toWrite.size();
//        char* currRow = this->page.at(rowNum);
//        for (unsigned int i = 0; i < textLen; i++) {
//            char currChar = toWrite.at(i);
//            currRow[colNum + i] = currChar;
//        }
//    } else {
//        int textLen = toWrite.size();
//        for (unsigned int i = 0; i < textLen; i++) {
//            char* currRow = this->page.at(rowNum + i);
//            char currChar = toWrite.at(i);
//            currRow[colNum] = currChar;
//
//        }
//    }
//}
//
//
//std::string Page::readFromPage(unsigned int rowNum, unsigned int colNum, ariel::Direction direction, int len) {
//    this->validateLinesExist(rowNum, colNum, direction, len);
//    std::string output;
//    if (direction == ariel::Direction::Horizontal) {
//        char* currRow = this->page.at(rowNum);
//        for (unsigned int i = 0; i < len; i++) {
//            char currChar = currRow[colNum + i];
//            output += currChar;
//        }
//    } else {
//        for (unsigned int i = 0; i < len; i++) {
//            char* currRow = this->page.at(rowNum + i);
//            char currChar = currRow[colNum];
//            output += currChar;
//        }
//    }
//    return output;
//}
//
//void Page::eraseFromPage(unsigned int rowNum, unsigned int colNum, ariel::Direction direction, int len) {
//    this->validateLinesExist(rowNum, colNum, direction, len);
//    if (direction == ariel::Direction::Horizontal) {
//        char* currRow = this->page.at(rowNum);
//        for (unsigned int i = 0; i < len; ++i) {
//            currRow[colNum + i] = '~';
//        }
//    } else {
//        for (unsigned int i = 0; i < len; i++) {
//            char* currRow = this->page.at(rowNum + i);
//            currRow[colNum] = '~';
//        }
//    }
//}
//
//
//
//void Page::showPage() {
//    this->validateLinesExist(0, 0, Direction::Vertical, 50);
//    for (unsigned int i = 0; i < 50; i++) {
//        std::cout << "" << i << ": ";
//        for (int j = 0; j < 100; j++) {
//            std::cout << this->page[i][j];
//        }
//        std::cout << std::endl;
//
//    }
//
//}
//
//char *createNewLine() {
//    char *newLine = new char[100];
//    for (int i = 0; i < 100; i++) {
//        newLine[i] = '_';
//    }
//    return newLine;
//}
//
//void validateText(std::string &toWrite) {
//    for (unsigned int i = 0; i < toWrite.size(); i++) {
//        char currChar = toWrite.at(i);
//        if (currChar < MIN_LEGAL_CHAR || currChar > MAX_LEGAL_CHAR || isprint(currChar) == 0) {
//            throw std::invalid_argument("the string you gave contains illegal characters!\n");
//        }
//    }
//}
//
//
//void Page::validateLinesExist(unsigned int rowNum, unsigned int colNum,
//                              ariel::Direction direction, int len) {
//    if (direction == ariel::Direction::Horizontal) {
//        if (this->page.count(rowNum) == 0) {
//            char* lineToInsert = createNewLine();
//            this->page.emplace(rowNum, lineToInsert);
//        }
//    } else {
//        for (unsigned int i = 0; i < len; i++) {
//            if (this->page.count(rowNum + i) == 0) {
//                char* lineToInsert = createNewLine();
//                this->page.emplace(rowNum + i, lineToInsert);
//            }
//        }
//    }
//}
//
//void Page::validateCanWrite(unsigned int rowNum, unsigned int colNum,
//                            ariel::Direction direction, std::string &toWrite) {
//    this->validateLinesExist(rowNum, colNum, direction, toWrite.size());
//    if (direction == ariel::Direction::Horizontal) {
//        char* currRow = this->page.at(rowNum);
//        for (unsigned int i = 0; i < toWrite.size(); i++) {
//            if (currRow[colNum + i] != '_') {
//                throw std::invalid_argument("you can't write in a place you've written to or erased before!\n");
//            }
//        }
//    } else {
//        for (unsigned int i = 0; i < toWrite.size(); i++) {
//            char* currRow = this->page.at(rowNum+i);
//            if (currRow[colNum] != '_') {
//                throw std::invalid_argument("you can't write in a place you've written to or erased before!\n");
//            }
//        }
//    }
//}
//
//
