//
// Created by itamarq on 27/03/2022.
//

#include "Notebook.hpp"
#include <iostream>
#include <map>
#include <string>
#include "Page.hpp"
#include "Direction.hpp"

const int ROW_MAX_LENGTH = 100;
const int ROWS_NUM_TO_SHOW = 50;
using namespace ariel;

namespace ariel {
    void Notebook::write(int page, int row, int col, ariel::Direction direction, std::string toWrite) {
        validateInput(page, row, col, direction, toWrite.size());
        validateInputChars(toWrite);
        unsigned int pageNum = unsigned(page);
        unsigned int rowNum = unsigned(row);
        unsigned int colNum = unsigned(col);
        this->validatePageExist(pageNum);
        this->validateLinesExist(pageNum, rowNum, colNum, direction, toWrite.size());
        this->validateCanWrite(pageNum, rowNum, colNum, direction, toWrite.size());
        if (direction == Direction::Horizontal) {
            char *currRow = this->notebook->at(pageNum)->at(rowNum);
            for (unsigned int i = 0; i < toWrite.size(); ++i) {
                currRow[colNum + i] = toWrite[i];
            }
        } else {
            for (unsigned int i = 0; i < toWrite.size(); ++i) {
                char *currRow = this->notebook->at(pageNum)->at(rowNum + i);
                currRow[colNum] = toWrite[i];
            }
        }
    }

    std::string Notebook::read(int page, int row, int col, ariel::Direction direction, int len) {
        validateInput(page, row, col, direction, len);
        unsigned int pageNum = unsigned(page);
        unsigned int rowNum = unsigned(row);
        unsigned int colNum = unsigned(col);
        this->validatePageExist(pageNum);
        this->validateLinesExist(pageNum, rowNum, colNum, direction, len);
        std::string output;
        if (direction == Direction::Horizontal) {
            char *currRow = this->notebook->at(pageNum)->at(rowNum);
            for (unsigned int i = 0; i < len; ++i) {
                output += currRow[colNum + i];
            }
        } else {
            for (unsigned int i = 0; i < len; ++i) {
                char *currRow = this->notebook->at(pageNum)->at(rowNum + i);
                output += currRow[colNum];
            }
        }
        return output;
    }

    void Notebook::erase(int page, int row, int col, ariel::Direction direction, int len) {
        validateInput(page, row, col, direction, len);
        unsigned int pageNum = unsigned(page);
        unsigned int rowNum = unsigned(row);
        unsigned int colNum = unsigned(col);
        this->validatePageExist(pageNum);
        this->validateLinesExist(pageNum, rowNum, colNum, direction, len);
        if (direction == Direction::Horizontal) {
            char *currRow = this->notebook->at(pageNum)->at(rowNum);
            for (unsigned int i = 0; i < len; ++i) {
                currRow[colNum + i] = '~';
            }
        } else {
            for (unsigned int i = 0; i < len; ++i) {
                char *currRow = this->notebook->at(pageNum)->at(rowNum + i);
                currRow[colNum] = '~';
            }
        }
    }

    void Notebook::show(int page) {
        if(page < 0){
            throw std::invalid_argument("page number must be a positive integer!\n");
        }
        unsigned int pageNum = unsigned (page);
        this->validatePageExist(pageNum);
        std::map<unsigned int, char*>* currPage = this->notebook->at(pageNum);
        this->validateLinesExist(pageNum, 0, 0, Direction::Vertical, ROW_MAX_LENGTH);
        for (unsigned int i = 0; i < ROW_MAX_LENGTH; ++i) {
            char* currRow = currPage->at(i);
            for (int j = 0; j < ROW_MAX_LENGTH; ++j) {
                std::cout << currRow[j];
            }
            std::cout << std::endl;
        }
    }

    void Notebook::validatePageExist(unsigned int pageNUm) {
        if (notebook->count(pageNUm) == 0) {
            std::map<unsigned int, char *> *pageToAdd = new std::map<unsigned int, char *>();
            notebook->emplace(pageNUm, pageToAdd);
        }
    }

    void
    Notebook::validateLinesExist(unsigned int pageNum, unsigned int rowNum, unsigned int colNum, Direction direction,
                                 int len) {
        std::map<unsigned int, char *> *currPage = notebook->at(pageNum);
        if (direction == Direction::Horizontal) {
            if (currPage->count(rowNum) == 0) {
                char *lineToAdd = createNewLine();
                currPage->emplace(rowNum, lineToAdd);
            }
        } else {
            for (unsigned int i = 0; i <= len; ++i) {
                if (currPage->count(rowNum + i) == 0) {
                    char *lineToAdd = createNewLine();
                    currPage->emplace(rowNum + i, lineToAdd);
                }
            }
        }
    }

    void Notebook::validateCanWrite(unsigned int pageNum, unsigned int rowNum, unsigned int colNum, Direction direction,
                                    int len) {
        std::map<unsigned int, char *> *currPage = notebook->at(pageNum);
        if (direction == Direction::Horizontal) {
            char *currRow = currPage->at(rowNum);
            for (unsigned int i = 0; i < len; ++i) {
                if (currRow[colNum + i] != '_') {
                    throw std::invalid_argument("you can't write to the same place twice!\n");
                }
            }
        } else {
            for (unsigned int i = 0; i < len; ++i) {
                char *currRow = currPage->at(rowNum + i);
                if (currRow[colNum] != '_') {
                    throw std::invalid_argument("you can't write to the same place twice!\n");
                }
            }
        }
    }

    char *createNewLine() {
        char *newLine = new char[ROW_MAX_LENGTH];
        for (int i = 0; i < ROW_MAX_LENGTH; ++i) {
            newLine[i] = '_';
        }
        return newLine;
    }

    void validateInput(int page, int row, int col, ariel::Direction direction, int len) {
        validateInputNums(page, row, col, len);
        if (direction == Direction::Horizontal) {
            validateNoOverflow(col, len);
        }

    }

    void validateInputNums(int page, int row, int col, int len) {
        if (page < 0) {
            throw std::invalid_argument("page number must be an integer greater or equal to zero!\n");
        }
        if (row < 0) {
            throw std::invalid_argument("row number must be an integer greater or equal to zero!\n");
        }
        if (col < 0 || col >= ROW_MAX_LENGTH) {
            throw std::invalid_argument("row number must be an integer greater or equal to zero and lesser than 99!\n");
        }
        if (len < 0) {
            throw std::invalid_argument("length of input text or length of read/erase can't be negative!\n");
        }
    }

    void validateNoOverflow(int col, int len) {
        if (col + len > ROW_MAX_LENGTH) {
            throw std::invalid_argument("current given values cause out of bounds exception\n");
        }
    }

    void validateInputChars(std::string inputText) {
        for (unsigned int i = 0; i < inputText.size(); ++i) {
            char currChar = inputText.at(i);
            if (std::isprint(currChar) == 0 || currChar == '~' || currChar == '\n') {
                throw std::invalid_argument("given text contains illegal characters!\n");
            }
        }
    }

    Notebook::~Notebook() {
        for (auto const &notebookPair: *this->notebook) {
            unsigned int currPageNum = notebookPair.first;
            std::map<unsigned int, char*>* currPage = this->notebook->at(currPageNum);
            for (auto const &pagePair: *currPage){
                unsigned int currRowNum = pagePair.first;
                char* currRow = currPage->at(currRowNum);
                delete [] currRow;
                currRow = NULL;
            }
            currPage->clear();
            currPage = NULL;
        }
        this->notebook->clear();
        this->notebook = NULL;
    }


}