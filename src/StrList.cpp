#include "StrList.h"



StrList::StrList()
	: begin(nullptr), current(nullptr)
{
}

StrList::~StrList()
{
	while (begin != nullptr)
	{
		Node *temp = this->begin;
		this->begin = this->begin->next;
		delete temp;
	}
}

unsigned int StrList::size()
{
	return this->Size;
}

void StrList::push(sf::String line)
{
	Node *temp = this->begin;
	this->begin = new Node(line, temp);

	this->Size++;
}

void StrList::pop()
{
	if (this->begin == nullptr)
		return;
	else if (this->begin->next == nullptr)
	{
		delete this->begin;
		this->begin = nullptr;
		this->Size = 0;
		return;
	}
	Node *temp = this->begin;
	while (temp->next->next != nullptr)
	{
		temp = temp->next;
	}
	delete temp->next;
	temp->next = nullptr;

	this->Size--;
}

sf::String StrList::getCurrentString()
{
	return this->current->line;
}

void StrList::ResetCurrent()
{
	this->current = this->begin;
}

void StrList::NextCurrent()
{
	this->current = this->current->next;
}
