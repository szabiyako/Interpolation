#include "MultiStorage.h"



MultiStorage::MultiStorage()
	: vectorInt(nullptr), vectorDouble(nullptr), vectorString(nullptr)
{
}


MultiStorage::~MultiStorage()
{
	if (this->vectorInt != nullptr)
		delete this->vectorInt;
	if (this->vectorDouble != nullptr)
		delete this->vectorDouble;
	if (this->vectorString != nullptr)
		delete this->vectorString;
}

void MultiStorage::CreateVectorInt()
{
	if (this->vectorInt != nullptr)
		delete this->vectorInt;
	this->vectorInt = new std::vector<int>();
}

void MultiStorage::CreateVectorDouble()
{
	if (this->vectorDouble != nullptr)
		delete this->vectorDouble;
	this->vectorDouble = new std::vector<double>();
}

void MultiStorage::CreateVectorString()
{
	if (this->vectorString != nullptr)
		delete this->vectorString;
	this->vectorString = new std::vector<std::string>();
}

std::vector<int>* MultiStorage::getVectorInt()
{
	return this->vectorInt;
}

std::vector<double>* MultiStorage::getVectorDouble()
{
	return this->vectorDouble;
}

std::vector<std::string>* MultiStorage::getVectorString()
{
	return this->vectorString;
}
