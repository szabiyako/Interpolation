#ifndef MULTISTORAGE_H
#define MULTISTORAGE_H

#include <vector>
#include <string>

class MultiStorage
{
private:
	std::vector<int> *vectorInt;
	std::vector<double> *vectorDouble;
	std::vector<std::string> *vectorString;

public:
	MultiStorage();
	virtual ~MultiStorage();

	void CreateVectorInt();
	void CreateVectorDouble();
	void CreateVectorString();

	std::vector<int> *getVectorInt();
	std::vector<double> *getVectorDouble();
	std::vector<std::string> *getVectorString();
};

#endif