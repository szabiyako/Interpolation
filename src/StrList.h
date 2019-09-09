#ifndef STRLIST_H
#define STRLIST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class StrList
{
private:
	unsigned int Size;
	struct Node
	{
		sf::String line;
		Node *next;
		Node(sf::String str)
			: next(nullptr), line(str)
		{
		}
		Node(sf::String str, Node *ptr)
			: next(ptr), line(str)
		{
		}
	};
	Node *begin;
	Node *current;
public:
	StrList();
	virtual ~StrList();
	unsigned int size();
	void push(sf::String);
	void pop();
	sf::String getCurrentString();
	void ResetCurrent();
	void NextCurrent();
};

#endif
