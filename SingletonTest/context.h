#pragma once


#include <vector>
#include <string>
#include <iostream>
#include "CustomException.h"

using namespace std;

struct var_info
{
    char name_var;
    string val_var;
};

class Context
{
    vector<var_info> check;
    int level;
    static Context* ptrContext;
protected:
    Context();
    ~Context();
public:
    static Context* GetInstance();
    void SetVarible(char, const string&);
    const string& Varification(char) const;
    void AddBrackLevel();
    void SubBrackLevel();
    int GetLevel() const;
};

struct TestContext:Context
{
    TestContext *pTest;
    TestContext();
    ~TestContext();
};


