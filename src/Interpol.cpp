#include "Interpol.h"


//PRIVATE
double Interpol::l(int &i, double &j, int &begin_index, int &end_index)
{
	int size = this->y->size();

	double answer = 1;

	for (int k = begin_index; k <= end_index; k++)
	{
		if (k == i)
			continue;

		answer *= ((j - k) / (i - k));
	}
	Console::addLine(L"l(i=" + std::to_wstring(i) + L", j=" + std::to_wstring(j) + L") = " + std::to_wstring(answer));
	return answer;
}

void Interpol::fillAdditional()
{
	int size = this->y->size();

	int k = 0;

	for (double j = 0.5; j < size - 1; j += 1.0)
	{
		double answer = 0;

		int begin_index;
		int end_index;
		this->getBeginEnd(j, begin_index, end_index);

		Console::addLine(L"Вычисляем l(x" + std::to_wstring(j) + L") степени " + std::to_wstring(m)
			+ L" по точкам с x" + std::to_wstring(begin_index) + L" по x" + std::to_wstring(end_index));
		for (int i = begin_index; i <= end_index; i++)
		{
			answer += this->y->at(i) * this->l(i, j, begin_index, end_index);
		}

		this->yAdditional->at(k++) = answer;
		Console::addLine(L"Вычисляем L(x" + std::to_wstring(j) + L") степени " + std::to_wstring(m)
			+ L" по точкам с x" + std::to_wstring(begin_index) + L" по x" + std::to_wstring(end_index));
		Console::addLine(L"L(m=" + std::to_wstring(this->m) + L", j=" + std::to_wstring(j) + L") = " + std::to_wstring(answer));
		Console::addLine(L"--------------------");
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

void Interpol::getBeginEnd(double & j, int & begin, int & end)
{
	int m = (int)this->m;
	begin = (int)j;
	end = begin + 1;
	m--;

	int last = this->y->size() - 1;
	while (m != 0)
	{
		if (begin > 0)
		{
			begin--;
			m--;
		}
		if (m != 0 && end < last)
		{
			end++;
			m--;
		}
	}
}

//PUBLIC
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
	unsigned int size;
	*this->input >> size;
	*this->input >> m;
	if (m >= size || m == 0)
	{
		*this->output << 1;
		return -3;
	}

	this->y = new std::vector<double>(size);
	this->yAdditional = new std::vector<double>(size - 1);

	for (unsigned int i = 0; i < size; i++)
	{
		double temp;
		*this->input >> temp;
		this->y->at(i) = temp;
	}
	return 0;
}


void Interpol::outFileAnswer()
{
	std::vector<double> v(this->getAnswerVector());
	int size = v.size();
	Console::addLine(L"Запись ответа в файл");
	Console::addLine(L"--------------------");
	for (int i = 0; i < size; i++)
	{
		*this->output << std::fixed;
		//How many numbers will shows (EX 1.234852134000) -precision(12)
		this->output->precision(8);
		*this->output << v.at(i) << "\n";
		//LOGS
		Console::addLine(std::to_string(v.at(i)));
	}
	*this->output << "\n0";
}
