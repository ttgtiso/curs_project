#include <HomePage.h>

HomePagePanel::HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
    DownPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	DownPanel->SetBackgroundColour(wxColor(100, 100, 200));

	// Логин панель и её элементы
	LoginPanel = new wxStaticBox(this, wxID_ANY, wxT("Current User"), wxDefaultPosition, wxSize(200, 100));
	LoginPanelSizer = new wxStaticBoxSizer(LoginPanel, wxVERTICAL);

	LoginLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("Аунтифицируйтесь в системе"));
	LoginButton = new wxButton(LoginPanel, wxID_ANY, wxT("Войти"));
	RegLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("Нет аккаунта?"));
	RegButton = new wxButton(LoginPanel, wxID_ANY, wxT("Зарегестрироваться"));

	LoginPanelSizer->Add(LoginLabel, 0, wxEXPAND | wxRIGHT | wxLEFT, 5);
	LoginPanelSizer->Add(LoginButton, 0, wxEXPAND | wxALL, 10);
	LoginPanelSizer->Add(RegLabel, 0, wxEXPAND | wxRIGHT | wxLEFT, 5);
	LoginPanelSizer->Add(RegButton, 0, wxEXPAND | wxALL, 10);

	// Верхняя часть приложения
	UpPanelSizer = new wxBoxSizer(wxHORIZONTAL);

	// Пустой элемент для управлением BoxSizer

	UpPanelSizer->Add(0, 0, 1, wxEXPAND, 5);
	UpPanelSizer->Add(LoginPanelSizer);

	// Нижняя часть приложения
	DownPanelSizer = new wxBoxSizer(wxVERTICAL);
	DownPanelSizer->Add(DownPanel, 1, wxEXPAND | wxALL);

	// Главный Sizer приложения
	MainPanelSizer = new wxBoxSizer(wxVERTICAL);
	MainPanelSizer->Add(UpPanelSizer, 0, wxEXPAND | wxALL, 5);
	MainPanelSizer->Add(DownPanelSizer, 1, wxEXPAND | wxALL, 5);

	this->SetSizerAndFit(MainPanelSizer);
}
