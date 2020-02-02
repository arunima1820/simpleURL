#ifndef PARSE_H
#define PARSE_H

#include<string>
#include<iostream>

using namespace std;

class parse {
    private:
        string url;
        string protocol;
        string domain;
        string port;
        string filePath;
        string param;

    public:
        parse(string const &);
        parse();

        //checks for syntax errors and assigns each url segment
        bool assign();      
        void printErrors();
        bool checkURL(int);
        void print();
        void printErrors(int);
};

#endif