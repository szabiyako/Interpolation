#include "Main_Menu.h"



void Main_Menu::InitText()
{
	sf::String label = L"��������� �������� 3-�� ����� ���� 61�� ������� ����������\n";
	label += L"������� 14) ���������� � ��� ���� ������� �������� ������� � ���������������\n";
	label += L"            ���������� ���������.\n";
	label += L"����        �� ������� ���� ��������������� ��������\n";
	label += L"            ���������� �������� �������, ������� ������������\n";
	label += L"            � ���� �������� �������";
	this->text = new sf::Text(label, *this->resource_manager->getFontSystem());
	this->text->setPosition(sf::Vector2f(20.f, 20.f));
	this->log = new sf::Text(L"", *this->resource_manager->getFontSystem());
	this->log->setPosition(sf::Vector2f(735.f, 530.f));
	this->log->setOutlineColor(sf::Color::Black);
}

void Main_Menu::InitTexture()
{
	this->resource_manager->setTexture("resources/textures/Menu.jpg");
}

void Main_Menu::InitBackground()
{
	this->background = new sf::Sprite();
	this->background->setTexture(*this->resource_manager->getTexture());
	this->background->setTextureRect(sf::IntRect(0, 0, 1280, 720));
	this->background->setPosition(0.f, 0.f);
	
	this->backText = new sf::RectangleShape(sf::Vector2f(1280.f, 235.f));
	this->backText->setFillColor(sf::Color(40, 40, 40, 125));
}

void Main_Menu::InitButtons()
{
	this->button_exit = new UI::ButtonText(this->resource_manager->getFontSystem(), L"�����", sf::Vector2f(120.f, 60.f), 40);
	this->button_start = new UI::ButtonText(this->resource_manager->getFontSystem(), L"������", sf::Vector2f(120.f, 60.f), 40);
	this->button_start->setPosition(sf::Vector2f(550.f, 520.f));
	this->button_exit->setPosition(sf::Vector2f(550.f, 620.f));
}


Main_Menu::Main_Menu(Resource_Manager * resource_manager) : Scene(resource_manager)
{
	this->InitText();
	this->InitTexture();
	this->InitBackground();
	this->InitButtons();
}


Main_Menu::~Main_Menu()
{
	delete this->background;
	delete this->backText;

	delete this->button_start;
	delete this->button_exit;

	delete this->text;
	delete this->log;
}

void Main_Menu::update(float & dt, int &current_scene, sf::RenderWindow &window)
{
	if (this->button_start->isClicked(window))
	{
		Interpol ip;
		int t = ip.openFilesAndRead("input.txt", "output.txt");
		if (t == -1)
		{
			this->log->setFillColor(sf::Color::Red);
			this->log->setOutlineThickness(5.f);
			this->log->setString(L"�� ������ ������� ���� \"input.txt\"");
			Console::addLine(L"ERROR: �� ������ ������� ���� \"input.txt\"");
		}
		else if (t == -2)
		{
			this->log->setFillColor(sf::Color::Red);
			this->log->setOutlineThickness(5.f);
			this->log->setString(L"�� ������ ������� ���� \"output.txt\"");
			Console::addLine(L"ERROR: �� ������ ������� ���� \"output.txt\"");
		}
		else if (t == -3)
		{
			this->log->setFillColor(sf::Color::Red);
			this->log->setOutlineThickness(5.f);
			this->log->setString(L"������� ������������ �������\n��� ����� ����� �����");
			Console::addLine(L"ERROR: ������� ������������ ������� ��� ����� ����� �����");
		}
		else
		{
			Console::addLine(L"---------------------");
			Console::addLine(L"LOG: ������ ���������");
			Console::addLine(L"---------------------");
			ip.outFileAnswer();
			this->log->setFillColor(sf::Color::White);
			this->log->setOutlineThickness(0.f);
			this->log->setString(L"������");
			Console::addLine(L"---------------------");
			Console::addLine(L"LOG: ������� ��������");
			Console::addLine(L"---------------------");
		}
	}

	if (this->button_exit->isClicked(window))
		current_scene--;
}

void Main_Menu::render(sf::RenderTarget & window)
{
	window.draw(*this->background);

	window.draw(*this->backText);
	window.draw(*this->text);
	window.draw(*this->log);

	this->button_exit->render(window);
	this->button_start->render(window);
}
