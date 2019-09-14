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

	//degree of interpolation
	unsigned int m;

	double l(int &i, double &j, int &begin_index, int &end_index);
	void fillAdditional();
	std::vector<double> getAnswerVector();
	void getBeginEnd(double &j, int &begin, int &end);
public:
	Interpol();
	virtual ~Interpol();
	int openFilesAndRead(const char *pathIn, const char *pathOut);

	void outFileAnswer();
};

#endif
