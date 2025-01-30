#include "TestLuaFunctions.h"

#include <iostream>
#include "LuaSystem.h"

TestLuaFunctions::TestLuaFunctions(ArksEngine::LuaSystem* pOwner)
	:m_pOwner(pOwner)
{
}

void TestLuaFunctions::TestLua()
{

    // Load the test.lua script
    m_pOwner->LoadScript("Assets/TestScript.lua");

    // Test GetGlobalVariable
    int var1 = m_pOwner->GetGlobalVariable<int>("var1");
    std::cout << "var1 = " << var1 << std::endl;

    int var2 = m_pOwner->GetGlobalVariable<int>("var2");
    std::cout << "var2 = " << var2 << std::endl;

    // Test SetGlobalVariable
    m_pOwner->SetGlobalVariable("var2", 50);
    var2 = m_pOwner->GetGlobalVariable<int>("var2");
    std::cout << "var2 (after SetGlobalVariable) = " << var2 << std::endl;

    // Test GetArrayElement
    int arr1_2 = m_pOwner->GetArrayElement<int>("arr1", 2);
    std::cout << "arr1[2] = " << arr1_2 << std::endl;

    // Test SetArrayElement
    m_pOwner->SetArrayElement("arr1", 2, 40);
    arr1_2 = m_pOwner->GetArrayElement<int>("arr1", 2);
    std::cout << "arr1[2] (after SetArrayElement) = " << arr1_2 << std::endl;

    // Test GetTableElement
    int tbl1_key1 = m_pOwner->GetTableElement<int>("tbl1", "key1");
    std::cout << "tbl1.key1 = " << tbl1_key1 << std::endl;

    // Test SetTableElement
    m_pOwner->SetTableElement("tbl1", "key1", 150);
    tbl1_key1 = m_pOwner->GetTableElement<int>("tbl1", "key1");
    std::cout << "tbl1.key1 (after SetTableElement) = " << tbl1_key1 << std::endl;

}
