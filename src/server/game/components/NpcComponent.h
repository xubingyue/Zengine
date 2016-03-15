#include <string>
#include "Component.h"

class NpcComponent : public Component 
{
	public:

		NpcComponent() {};

		void setPhrase(const std::string& phrase);

		std::string getPhrase();

	private:

		std::string phrase;
};