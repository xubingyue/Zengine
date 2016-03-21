#pragma once

#include <string>
#include <iostream>

#include <LuaHelperFunctions.h>

#include <Entity.h>
/*#include <Component.h>*/
#include <System.h>
#include <GraphicsComponent.h>
#include <NpcComponent.h>

extern "C" 
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <LuaBridge.h>




class Game 
{
	public:

		bool Initialize();

		void handleMessage(std::string message);

		void Update();

		void Close();

		//bool doOldLuaStuff();

	private:

		lua_State* luaState;
		lua_State* L;
		std::string message;

};

