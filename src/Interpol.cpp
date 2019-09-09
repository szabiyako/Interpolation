#include "Interpol.h"



double Interpol::l(int i, double j)
{
	int size = this->y->size();

	double answer = 1;

	for (int k = 0; k < size; k++)
	{
		if (k == i)
			continue;

		answer *= ((j - k) / (i - k));
	}
	return answer;
}

Interpol::Interpol()
{
	this->input = new std::ifstream();
	this->output = new std::ofstream();
}

Interpol::~Interpol()
{
	if (this->yAdditional != nullptr)
		delete this->yAdditional;
	if (this->y != nullptr)
		delete this->y;
	this->input->close();
	this->input->close();
	delete this->input;
	delete this->output;
}

int Interpol::openFilesAndRead(const char * pathIn, const char * pathOut)
{
	this->input->open(pathIn);
	if (!this->input->is_open())
	{
		return -1;
	}
	this->output->open(pathOut);
	if (!this->output->is_open())
	{
		return -2;
	}
	int size;
	*this->input >> size;
	if (size < 3)
	{
		*this->output << 1;
		return -3;
	}

	this->y = new std::vector<double>(size);
	this->yAdditional = new std::vector<double>(size - 1);

	for (int i = 0; i < size; i++)
	{
		double temp;
		*this->input >> temp;
		this->y->at(i) = temp;
	}
	return 0;
}

void Interpol::fillAdditional()
{
	int size = this->y->size();

	int k = 0;

	for (double j = 0.5; j < size - 1; j += 1.0)
	{
		double answer = 0;

		for (int i = 0; i < size; i++) 
			answer += this->y->at(i) * this->l(i, j);

		this->yAdditional->at(k++) = answer;
	}
}

std::vector<double> Interpol::getAnswerVector()
{
	this->fillAdditional();

	int size = this->y->size();
	std::vector<double> answer(2 * size - 1);
	bool first = true;

	for (int i = 0, j = 0, k = 0; i < size; k++)
	{
		if (first)
			answer[k] = this->y->at(i++);
		else
			answer[k] = this->yAdditional->at(j++);

		first = first ? false : true;
	}

	return answer;
}

void Interpol::outFileAnswer()
{
	std::vector<double> v(this->getAnswerVector());
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		*this->output << std::fixed;
		//How many numbers will shows (EX 1.234852134000)
		this->output->precision(8);
		*this->output << v.at(i) << "\n";
		//LOGS
		Console::addLine(std::to_string(v.at(i)));
	}
	*this->output << "\n0";
}
