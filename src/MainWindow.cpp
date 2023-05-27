#include <MainWindow.h>

enum Panel_id
{
	Home_page_id,
	Login_page_id,
	Reg_page_id,
	Shop_page_id,
	Root_page_id,
	Root_page_view_id
};

MyFrame1::MyFrame1(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	// Настройка драйвера MySQL
	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("localhost:3306", "app_user", "Password123!");
	stmt = con->createStatement();
	stmt->execute("USE autoshop");
	userLogining = false;

	// Установка минимального размера окна
	this->SetSizeHints( wxSize( 700,600 ), wxDefaultSize );
	SimpleBookMain = new wxSimplebook(this);
	HomePage = new HomePagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	HomePage->LoginButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ShownLoginPage), NULL, this);
	HomePage->RegButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ShownRegedPage), NULL, this);

	res = stmt->executeQuery("SELECT * from product");
	HomePage->Init(res, 5);
	delete res;

	LoginPage = new LoginPagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	LoginPage->LoginingButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnLogin), NULL, this);
	LoginPage->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);

	RegPage = new RegPagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RegPage->LoginingButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnReged), NULL, this);
	RegPage->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);

	ShopPage = new ShopPagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	ShopPage->backButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ViewBack), NULL, this);

	RootPage = new RootPagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RootPage->reloginButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Relogin), NULL, this);
	RootPage->showTable->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowTable), NULL, this);

	RootPageView = new RootPageViewColumn(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RootPageView->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);

	SimpleBookMain->AddPage(HomePage, wxT("Home Page"));
	SimpleBookMain->AddPage(LoginPage, wxT("Login Page"));
	SimpleBookMain->AddPage(RegPage, wxT("Reg Page"));
	SimpleBookMain->AddPage(ShopPage, wxT("Shop Page"));
	SimpleBookMain->AddPage(RootPage, wxT("Root page"));
	SimpleBookMain->AddPage(RootPageView, wxT("Root page view"));

	ConnectEventButtonsShopPage();
}

MyFrame1::~MyFrame1()
{
	// Отключение событий
	HomePage->LoginButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::ShownLoginPage ), NULL, this );
	HomePage->RegButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::ShownRegedPage ), NULL, this );
	LoginPage->LoginingButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnLogin), NULL, this);
	LoginPage->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	RegPage->LoginingButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnReged), NULL, this);
	RegPage->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	ShopPage->backButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ViewBack), NULL, this);
	RootPage->reloginButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Relogin), NULL, this);
	RootPage->showTable->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowTable), NULL, this);
	RootPageView->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	// Удаление подключения
	delete con;
}

void MyFrame1::ShownLoginPage(wxCommandEvent& event)
{
	std::cout << "Pressed button login" << std::endl;
	SimpleBookMain->ChangeSelection(Login_page_id);
	/*
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
	*/
}

void MyFrame1::ShownRegedPage(wxCommandEvent& event)
{
	std::cout << "Presed button Reged" << std::endl;
	SimpleBookMain->ChangeSelection(Reg_page_id);
	/*
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
		delete res;
		res = stmt->executeQuery("SHOW tables");
		while (res->next())
		{
			std::cout << res->getString(1) << std::endl;
		}
		delete stmt;
		delete res;
	}
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
	*/
}

void MyFrame1::Back_main_window(wxCommandEvent& event)
{
	std::cout << "Back to main window" << std::endl;
	SimpleBookMain->ChangeSelection(Home_page_id);
}

void MyFrame1::ViewBack(wxCommandEvent& event)
{
	std::cout << "Back to main window as ShopPage" << std::endl;
	SimpleBookMain->ChangeSelection(Home_page_id);
	// Данная функция определяет, будет ли ошибка при масштабирование изображения
	// на форме покупок.
	ShopPage->UpdateImage(wxSize(10,10));
	HomePage->UpdateImage();
}

void MyFrame1::ViewContent(wxCommandEvent& event)
{
	std::cout << "Pressed ViewButton" << std::endl;
	for (auto Element : HomePage->ShopElements)
	{
		if (Element->ViewButton->GetId() == event.GetId())
		{

			std::cout << event.GetId() << std::endl;
			std::cout << "Button found!" << std::endl;
			ShopPage->UpdateData(Element);
			break;
		}
	}
	SimpleBookMain->ChangeSelection(Shop_page_id);
	ShopPage->UpdateImage();
}

void MyFrame1::OnSize(wxSizeEvent& event)
{
	if (HomePage->IsShown())
	{
		HomePage->UpdateImage();
	}
	if (ShopPage->IsShown())
	{
		std::cout << "Update ShopImage" << std::endl;
		ShopPage->UpdateImage();
	}
	if (RootPage->IsShown())
	{
		std::cout << "Root Page Update" << std::endl;
		RootPage->UpdateImage();
	}
	event.Skip();
}

void MyFrame1::ConnectEventButtonsShopPage()
{
	for (int i=0; i < HomePage->ShopElements.size(); i++)
	{
		HomePage->ShopElements.at(i)->ViewButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ViewContent), NULL, this);
	}
}

void MyFrame1::OnLogin(wxCommandEvent& event)
{
	try
	{
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT login,password,privilege_level from users");
	}
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
	res->next();
	std::string login = res->getString(1);
	std::string password = res->getString(2);
	if ( LoginPage->LoginEdit->GetValue() == login)
	{
		if (LoginPage->PasswordEdit->GetValue() == password)
		{
			userName = login;
			userPrivilege = res->getInt(3);
			userLogining = true;
			SetUser();
		}
	}
	while (res->next())
	{
		if ( LoginPage->LoginEdit->GetValue() == login)
		{
			if (LoginPage->PasswordEdit->GetValue() == password)
			{
				userName = login;
				userPrivilege = res->getInt(3);
				userLogining = true;
				SetUser();
				break;
			}
		}
	}
	if (userLogining == false)
	{
		std::cout << "Задан не верный логин или пароль." << std::endl;
	}
	delete stmt;
	delete res;
}

void MyFrame1::OnReged(wxCommandEvent& event)
{
	
}

void MyFrame1::SetUser()
{
	switch (userPrivilege)
	{
	case 0:
		HomePage->LoginPanel->SetLabel(userName);
		SimpleBookMain->ChangeSelection(Home_page_id);
		break;
	case 1:
		HomePage->LoginPanel->SetLabel(userName);
		SimpleBookMain->ChangeSelection(Home_page_id);
		break;
	case 2:
		sql::ResultSet* res_tmp = stmt->executeQuery("SHOW tables");
		RootPage->UpdateList(res_tmp);
		delete res_tmp;
		SimpleBookMain->ChangeSelection(Root_page_id);
		RootPage->Layout();
		RootPage->UpdateImage();
		break;
	}
	std::cout << "Login user " << userName << std::endl;
}

void MyFrame1::Relogin(wxCommandEvent& event)
{
	userName = wxT("");
	userLogining = false;
	userPrivilege = 0;
	RootPage->clearData();
	SimpleBookMain->ChangeSelection(Home_page_id);
}

void MyFrame1::BackRoot(wxCommandEvent& event)
{
	SimpleBookMain->ChangeSelection(Root_page_id);
}

void MyFrame1::ShowTable(wxCommandEvent& event)
{
	std::string nameTable;
	nameTable = RootPage->listTables->GetStringSelection();
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * from " + nameTable);
	data = res->getMetaData();
	RootPageView->UpdateGrid(res, data);
	SimpleBookMain->ChangeSelection(Root_page_view_id);
	delete stmt;
	delete res;
}