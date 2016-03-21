#include <EcsHelperFunctions.h>
#include <LuaBridge.h>

template <typename T>
void ecsh::addComponent(Entity* e)
{
	e->addComponent(std::type_index(typeid(T)), new T());	
}

Entity* ecsh::xloadEntity(luabridge::lua_State* L, const std::string& type)
{
	auto e = new Entity();
    e->setType(type);
    auto v = luah::getTableKeys(L, type);
    for (auto& componentName : v) {
        if (componentName == "GraphicsComponent") {
            addComponent<GraphicsComponent>(e);
        } else if (componentName == "NpcComponent") {
            addComponent<NpcComponent>(e);
        }
 
        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}