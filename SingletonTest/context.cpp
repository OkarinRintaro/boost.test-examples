#include "context.h"

Context::Context():level(0)
{
}

Context::~Context()
{
    if(ptrContext)
    {
        Context* temp = ptrContext;
        ptrContext = nullptr;
        delete temp;
    }
}


Context* Context::GetInstance()
{
    if(!ptrContext)
    {
        cout<<"GetInstance()"<<endl;
        ptrContext = new Context();
    }
    return ptrContext;
}

const string& Context::Varification(char ch) const
{
    int temp_level = level;
    while (temp_level)
    {
        if(!check.empty())
            if (check[temp_level].name_var == ch)
                return check[temp_level].val_var;
        temp_level--;
    }
    throw CustomException(2);
}

void Context::SetVarible(char ch, const string& num)
{
    if (level >= check.size())
        check.resize(2 * level);
    if(level)
    {
        check[level].name_var = ch;
        check[level].val_var = num;
    }
}

void Context::AddBrackLevel()
{
    level++;
}

void Context::SubBrackLevel()
{
    if(level)
        level--;
    else
      throw CustomException(4);
}

int Context::GetLevel() const
{
    return level;
}

TestContext::TestContext()
{
    pTest = (TestContext*)operator new(sizeof(TestContext));
    cout<<"Setup()"<<endl;
}

TestContext::~TestContext()
{
    operator delete(pTest);
    pTest = nullptr;
    cout<<"Teardown()"<<endl;
}
