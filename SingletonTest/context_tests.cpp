
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ClassContextTest
#include <boost/test/unit_test.hpp>
#include "context.h"

Context* Context::ptrContext = nullptr;

BOOST_AUTO_TEST_SUITE(GetInstanceTest)

    BOOST_FIXTURE_TEST_CASE(GetInstance_Context,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        BOOST_REQUIRE(ptr_context->GetLevel()==0);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AddBrackLevelTest)

    BOOST_FIXTURE_TEST_CASE(LevelEqualOne,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        BOOST_CHECK(ptr_context->GetLevel()==1);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SubBrackLevelTest)

    BOOST_FIXTURE_TEST_CASE(Level_Below_Zero,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        BOOST_CHECK_THROW(ptr_context->SubBrackLevel(),CustomException);
    }

    BOOST_FIXTURE_TEST_CASE(Level_Equal_Zero,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        ptr_context->SubBrackLevel();
        BOOST_CHECK(ptr_context->GetLevel()==0);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(VarificationTest)

    BOOST_FIXTURE_TEST_CASE(Varification_Exception_LevelZero,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        char ch =' ';
        BOOST_CHECK_THROW(ptr_context->Varification(ch),CustomException);
    }
    BOOST_FIXTURE_TEST_CASE(Varification_Exception_LevelOne_VectorEmpty,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        char ch =' ';
        BOOST_CHECK_THROW(ptr_context->Varification(ch),CustomException);
    }
    BOOST_FIXTURE_TEST_CASE(Varification_LevelOne_VectorNotEmpty,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        char ch ='a';
        ptr_context->SetVarible(ch,"5.5");
        BOOST_CHECK_EQUAL(ptr_context->Varification(ch),"5.5");
    }
    BOOST_FIXTURE_TEST_CASE(Varification_Exception_LevelOne_VectorNotEmpty,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        char ch ='a';
        ptr_context->SetVarible(ch,"5.5");
        ch = 'b';
        BOOST_CHECK_THROW(ptr_context->Varification(ch),CustomException);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SetVaribleTest)
    BOOST_FIXTURE_TEST_CASE(SetVarible_LevelOne,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        char ch ='c';
        ptr_context->SetVarible(ch,"6");
        BOOST_CHECK_EQUAL(ptr_context->Varification(ch),"6");
    }
    BOOST_FIXTURE_TEST_CASE(SetVarible_LevelTwo,TestContext)
    {
        Context *ptr_context = Context::GetInstance();
        ptr_context->AddBrackLevel();
        ptr_context->AddBrackLevel();
        ptr_context->AddBrackLevel();
        ptr_context->SubBrackLevel();
        char ch ='b';
        ptr_context->SetVarible(ch,"-9.7");
        BOOST_CHECK_EQUAL(ptr_context->Varification(ch),"-9.7");
    }
BOOST_AUTO_TEST_SUITE_END()
