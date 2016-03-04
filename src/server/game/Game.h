#include <LuaBridge.h>
#include <iostream>
#include <lua.h>
#include <string>
//#include <lauxlib.h>
//#include <lualib.h>

using namespace luabridge;

class Game 
{
	public:

		bool Initialize();

		void handleMessage(std::string message);

		void Update();

		void Close();

	private:

		lua_State* luaState;
		std::string message;

};