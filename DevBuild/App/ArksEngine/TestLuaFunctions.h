#pragma once


namespace ArksEngine
{
	class LuaSystem;
}

class TestLuaFunctions
{
	ArksEngine::LuaSystem* m_pOwner;

public:
	TestLuaFunctions(ArksEngine::LuaSystem* pOwner);
	void TestLua();
};

