#include <Entity.h>
#include <Component.h>

Entity::~Entity()
{
	for(auto & currentComponent : componentMap)
	{
		delete currentComponent.second;
	}
}

template <typename componentType>
componentType* Entity::get()
{
	auto it = componentMap.find(std::type_index(typeid(componentType)));
	if (it != componentMap.end())
	{
		return dynamic_cast<componentType*>(it->second);
	}
	return nullptr;
}

void Entity::addComponent(std::type_index type, Component* component)
{
	componentMap[type] = component;
}

void Entity::setType(const std::string& type)
{
	this->type = type;
}

std::string Entity::getType()
{
	return type;
}