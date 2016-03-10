#include <GraphicsComponent.h>

void GraphicsComponent::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
	printf("This is called from GraphicsComponent.setFileName()\n");
}

std::string GraphicsComponent::getFileName()
{

	printf("This is called from GraphicsComponent.getFilename()\n");

	return fileName;
}