#include <LuaBridge.h>
#include <iostream>
#include <lua.h>
#include <string>

#include <Entity.h>
/*#include <Component.h>*/
#include <System.h>
#include <GraphicsComponent.h>
#include <NpcComponent.h>

//#include <lauxlib.h>
//#include <lualib.h>

//using namespace luabridge;

class Game 
{
	public:

		bool Initialize();

		void handleMessage(std::string message);

		void Update();

		void Close();

	private:

		luabridge::lua_State* luaState;
		std::string message;

};