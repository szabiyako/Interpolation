#ifndef INTERPOL_H
#define INTERPOL_H

#include <vector>
#include <fstream>
#include "Console.h"

class Interpol
{
private:
	std::vector<double> *y;
	std::vector<double> *yAdditional;

	std::ifstream *input;
	std::ofstream *output;

	double l(int i, double j);
	void fillAdditional();
	std::vector<double> getAnswerVector();
public:
	Interpol();
	virtual ~Interpol();
	int openFilesAndRead(const char *pathIn, const char *pathOut);

	void outFileAnswer();
};

#endif
