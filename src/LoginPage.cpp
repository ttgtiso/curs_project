#include <LoginPage.h>

LoginPagePanel::LoginPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) 
: wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);
    // Главный sizer
    LoginBoxSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    LoginBoxSizerVertical = new wxBoxSizer(wxVERTICAL);

    backButton = new wxButton(this, wxID_ANY, wxT("Вернуться"));
    // Элементы StaticBox
    LoginPanel = new wxStaticBox(this, wxID_ANY, wxT("Аунтификация"), wxDefaultPosition, wxSize(200, 200));
    LoginPanelSizer = new wxStaticBoxSizer(LoginPanel, wxVERTICAL);

    LoginLabel = new wxStaticText(this, wxID_ANY, wxT("Логин"));
    LoginEdit = new wxTextCtrl(this, wxID_ANY);
    PasswordLabel = new wxStaticText(this, wxID_ANY, wxT("Пароль"));
    PasswordEdit = new wxTextCtrl(this, wxID_ANY);
    LoginingButton = new wxButton(this, wxID_ANY, wxT("Войти"));

    LoginPanelSizer->Add(LoginLabel, 0, wxCENTER);
    LoginPanelSizer->Add(LoginEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(PasswordLabel, 0, wxCENTER);
    LoginPanelSizer->Add(PasswordEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(LoginingButton, 0, wxCENTER | wxALL, 5);

    LoginBoxSizerVertical->Add(LoginPanelSizer, 1, wxCENTER | wxALL);
    LoginBoxSizerHorizontal->Add(LoginBoxSizerVertical, 1, wxCENTER | wxALL);

    mainSizer->Add(backButton, 0, wxALL, 5);
    mainSizer->Add(LoginBoxSizerHorizontal, 1, wxEXPAND);
    this->SetSizerAndFit(mainSizer);
}