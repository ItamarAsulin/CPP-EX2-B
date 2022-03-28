//
// Created by itamarq on 26/03/2022.
//


#include <iostream>
#include <map>
#include <string>
#include "Page.hpp"
#include "Direction.hpp"
namespace ariel
{
    void validateInput(int page, int row, int col, ariel::Direction direction, int len);
    void validateLength(int len);
    void validateNoOverflow(int col, int len);
    void validateInputNums(int page, int row, int col, int len);
    void validateInputChars(std::string inputText);
    char* createNewLine();

    class Notebook
    {
    private:
        std::map<unsigned int, std::map<unsigned int, char*>*>* notebook;
        void validatePageExist( unsigned int pageNUm);
        void validateLinesExist(unsigned int pageNum, unsigned int rowNum, unsigned int colNum, Direction direction, int len);
        void validateCanWrite(unsigned int pageNum, unsigned int rowNum, unsigned int colNum, Direction direction, int len);


    public:
        Notebook(){
            this->notebook = new std::map<unsigned int, std::map<unsigned int, char*>*>();
        };

        void write(int page, int row, int col, ariel::Direction direction, std::string toWrite);

        std::string read(int page, int row, int col, ariel::Direction direction, int len);

        void erase(int page, int row, int col, ariel::Direction direction, int len);

        void show(int page);
        ~Notebook();
    };
}


