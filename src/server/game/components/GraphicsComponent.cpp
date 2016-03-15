#include <GraphicsComponent.h>

void GraphicsComponent::setFileName(const std::string& fileName)
{
	this->fileName = fileName;
	printf("File name has been set.\n");
}

std::string GraphicsComponent::getFileName()
{

	printf("File name: %s\n", fileName.c_str());

	return fileName;
}