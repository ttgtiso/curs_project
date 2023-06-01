#include <RegPage.h>

RegPagePanel::RegPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) 
 : wxPanel(parent, wxID_ANY, pos, size)
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

void RegPagePanel::AddUser(int id, sql::PreparedStatement *prep_stmt, sql::Connection *con)
{
    std::string string1 = UserNameEdit->GetValue().ToStdString();
    std::string string2 = UserPhoneEdit->GetValue().ToStdString();
    std::string string3 = LoginEdit->GetValue().ToStdString();
    std::string string4 = PasswordEdit->GetValue().ToStdString();
    std::string string5 = ConfirmPasswordEdit->GetValue().ToStdString();

    if (string4 != string5)
    {
        wxMessageBox(wxT("Неверно потверждён пароль."), wxT("Ошибка"), wxICON_ERROR);
        return ;
    }
    try
    {
		std::cout << "Выполнение подключения к базе данных..." << std::endl;
		prep_stmt = con->prepareStatement("INSERT INTO users VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
		prep_stmt->setInt(1, id);
		prep_stmt->setString(2, string3);
		prep_stmt->setString(3, string4);
		prep_stmt->setInt(4, 0);
		prep_stmt->setString(5, string2);
		prep_stmt->setString(6, string1);
		prep_stmt->setInt(7, 0);
        prep_stmt->setString(8, "");
		prep_stmt->execute();
		std::cout << "Выполнение запроса завершено" << std::endl;
		delete prep_stmt;
	} 
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void RegPagePanel::ClearPage()
{
    UserNameEdit->SetValue(*wxEmptyString);
    UserPhoneEdit->SetValue(*wxEmptyString);
    LoginEdit->SetValue(*wxEmptyString);
    PasswordEdit->SetValue(*wxEmptyString);
    ConfirmPasswordEdit->SetValue(*wxEmptyString);
}