#include <NpcComponent.h>
#include <iostream>

void NpcComponent::setPhrase(const std::string& phrase)
{
	this->phrase = phrase;
	printf("Phrase has been set.\n");
}

std::string NpcComponent::getPhrase()
{
	printf("Phrase has be returned.\n");
	return phrase;
}