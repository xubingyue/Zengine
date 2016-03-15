

#include <map>
#include <string>
#include <typeindex>

class Component;

class Entity
{
	public: 

		~Entity();

		void addComponent(std::type_index type, Component* component);

		template <typename componentType>
		componentType* get();

		void setType(const std::string& type);

		std::string getType();

	private:

		std::string type;
		std::map<std::type_index, Component*> componentMap;

};
