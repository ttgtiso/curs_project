#include <RegPage.h>

RegPagePanel::RegPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
    // Главный sizer
    mainSizer = new wxBoxSizer(wxVERTICAL);
    LoginBoxSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    LoginBoxSizerVertical = new wxBoxSizer(wxVERTICAL);

    backButton = new wxButton(this, wxID_ANY, wxT("Назад"));
    // Элементы StaticBox
    LoginPanel = new wxStaticBox(this, wxID_ANY, wxT("Аунтификация"), wxDefaultPosition, wxSize(200, 400));
    LoginPanelSizer = new wxStaticBoxSizer(LoginPanel, wxVERTICAL);

    UserNameLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("ФИО"));
    UserNameEdit = new wxTextCtrl(LoginPanel, wxID_ANY);
    UserPhoneLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("Телефон"));
    UserPhoneEdit = new wxTextCtrl(LoginPanel, wxID_ANY);

    LoginLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("Логин"));
    LoginEdit = new wxTextCtrl(LoginPanel, wxID_ANY);
    PasswordLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("Пароль"));
    PasswordEdit = new wxTextCtrl(LoginPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    ConfirmPasswordLabel = new wxStaticText(LoginPanel, wxID_ANY, wxT("Повторите пароль"));
    ConfirmPasswordEdit = new wxTextCtrl(LoginPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    LoginingButton = new wxButton(LoginPanel, wxID_ANY, wxT("Зарегестрироваться"));

    LoginPanelSizer->Add(UserNameLabel, 0, wxCENTER); 
    LoginPanelSizer->Add(UserNameEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(UserPhoneLabel, 0, wxCENTER);
    LoginPanelSizer->Add(UserPhoneEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(LoginLabel, 0, wxCENTER);
    LoginPanelSizer->Add(LoginEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(PasswordLabel, 0, wxCENTER);
    LoginPanelSizer->Add(PasswordEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(ConfirmPasswordLabel, 0, wxCENTER);
    LoginPanelSizer->Add(ConfirmPasswordEdit, 0, wxEXPAND | wxALL, 10);
    LoginPanelSizer->Add(LoginingButton, 0, wxCENTER | wxALL, 5);
    

    LoginBoxSizerVertical->Add(LoginPanelSizer, 1, wxCENTER | wxALL);
    LoginBoxSizerHorizontal->Add(LoginBoxSizerVertical, 1, wxCENTER | wxALL);
    
    mainSizer->Add(backButton, 0, wxALL, 5);
    mainSizer->Add(LoginBoxSizerHorizontal, 1, wxEXPAND);


    this->SetSizerAndFit(mainSizer);
}