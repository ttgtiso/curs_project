#include <MainWindow.h>

enum Panel_id
{
	Home_page_id,
	Login_page_id,
	Reg_page_id
};

/*
// Перечисление id кнопок.
enum ButtonId
{
    first_button_id = wxID_LAST + 1,
    second_button_id,
    first_button2_id,
    second_button2_id
};
// clang-format off.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(first_button_id, MyFrame::OnClick_first)
    EVT_BUTTON(second_button_id, MyFrame::OnClick_second)
wxEND_EVENT_TABLE()
; // clang-forman on.
*/

MyFrame1::MyFrame1(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// Настройка драйвера MySQL
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("localhost:3306", "app_user", "Password123!");
	stmt = con->createStatement();
	stmt->execute("USE autoshop");
	delete stmt;

	// Установка минимального размера окна
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );
	SimpleBookMain = new wxSimplebook(this);
	HomePage = new HomePagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	HomePage->LoginButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnLogin), NULL, this);
	HomePage->RegButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnReged), NULL, this);
	HomePage->ShopPanel1->ViewButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ViewContent), NULL, this);

	LoginPage = new LoginPagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	LoginPage->LoginingButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);

	RegPage = new RegPagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RegPage->LoginingButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);


	SimpleBookMain->AddPage(HomePage, wxT("HomePage"));
	SimpleBookMain->AddPage(LoginPage, wxT("LoginPage"));
	SimpleBookMain->AddPage(RegPage, wxT("RegPage"));

	Bind(wxEVT_SIZE, &MyFrame1::OnSize, this);

}

MyFrame1::~MyFrame1()
{
	// Отключение событий
	HomePage->LoginButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnLogin ), NULL, this );
	HomePage->RegButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnReged ), NULL, this );
	LoginPage->LoginingButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	RegPage->LoginingButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	HomePage->ShopPanel1->ViewButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ViewContent), NULL, this);
	delete con;
}

void MyFrame1::OnLogin(wxCommandEvent& event)
{
	std::cout << "Pressed button login" << std::endl;
	SimpleBookMain->ChangeSelection(Login_page_id);

	try{
		std::cout << "Выполнение подключения к базе данных..." << std::endl;
		stmt = con->createStatement();
		prep_stmt = con->prepareStatement("INSERT INTO product VALUES (?, ?, ?, ?, ?, ?, ?)");
		prep_stmt->setInt(1, 3);
		prep_stmt->setString(2, "A2");
		prep_stmt->setString(3, "App car");
		prep_stmt->setString(4, "wxWidgets");
		prep_stmt->setInt(5, 8800);
		prep_stmt->setInt(6, 0);
		prep_stmt->setInt(7, 10);
		prep_stmt->execute();
		std::cout << "Выполнение запроса завершено" << std::endl;
		delete stmt;
		delete prep_stmt;
	} 
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
	
}

void MyFrame1::OnReged(wxCommandEvent& event)
{
	std::cout << "Presed button Reged" << std::endl;
	SimpleBookMain->ChangeSelection(Reg_page_id);
	try
	{
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * from product");
		while (res->next())
		{
			std::cout << "| --------------------------------------- |" << std::endl;
			std::cout << "Id: " << res->getInt(1) << std::endl;
			std::cout << "Articul: " << res->getString(2) << std::endl; 
			std::cout << "Model: " << res->getString(3) << std::endl;
			std::cout << "Provider: " << res->getString(4) << std::endl;
			std::cout << "Price: " << res->getInt(5) << std::endl;
			std::cout << "Warranty: " << res->getInt(6) << std::endl; 
			std::cout << "Count: " << res->getInt(7) << std::endl;
		}
		delete stmt;
		delete res;
	}
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void MyFrame1::Back_main_window(wxCommandEvent& event)
{
	std::cout << "Back to main window" << std::endl;
	SimpleBookMain->ChangeSelection(Home_page_id);
}

void MyFrame1::ViewContent( wxCommandEvent& event)
{
	std::cout << "Pressed ViewButton" << std::endl;
	HomePage->ShopPanel1->updateImage();
}

void MyFrame1::OnSize(wxSizeEvent& event)
{
	if (this->IsShownOnScreen())
	{
		std::cout << "Wait" << std::endl;
		HomePage->ShopPanel1->updateImage();
		event.Skip();
	}
}
