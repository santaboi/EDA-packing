#ifndef MODULE_H
#define MODULE_H
#include <iostream>
//#include"Btree.h"

class Module
{
    //friend class Btree;
private:
public:
    char* name=new char[10];
    char* l_name=new char[10];
    char* r_name=new char[10];
    double x;//module 左側的x
    double y;//module 下底的y
    double width;
    double height;
    double pin_x;
    double pin_y;
    Module *leftPtr;
    Module *rightPtr;
    /*Module();//default ctor
    Module(int x1,int width1,int height1,Module* left1,Module *right1);//normal ctor
    ~Module();
    */
};
#endif


/*
Module::Module()
{
}

Module::~Module()
{
    delete [] name;
    delete [] l_name;
    delete [] r_name;

}
*/


