#pragma once

#include <Entity.h>
#include <iostream>
#include <LuaHelperFunctions.h>
#include <GraphicsComponent.h>
#include <NpcComponent.h>
#include <LuaBridge.h>

struct lua_State;

namespace ecsh {



	template <typename T>
	void addComponent(Entity* e);

	Entity* xloadEntity(luabridge::lua_State* L, const std::string& type);

}