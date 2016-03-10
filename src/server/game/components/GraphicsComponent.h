#include <string>
#include <stdio.h>
#include <Component.h>

class GraphicsComponent : public Component 
{
	public:

		GraphicsComponent() {};

		void setFileName(const std::string& fileName);

		std::string getFileName();

	private:

		std::string fileName;	

};