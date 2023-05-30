#include <MainWindow.h>

enum Panel_id
{
	Home_page_id,
	Login_page_id,
	Reg_page_id,
	Shop_page_id,
	Root_page_id,
	Root_page_view_id,
	Root_page_add_product_id,
	Root_page_add_user_id,
	Home_basket_id
};

MyFrame1::MyFrame1(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame(nullptr, wxID_ANY, title, pos, size)
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
	HomePage->BasketButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowBasketPage), NULL ,this);

	HomeBasket = new HomePageBasket(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	HomeBasket->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);

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
	RootPage->addProduct->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowAddProduct), NULL, this);
	RootPage->addUser->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowAddUser), NULL, this);

	RootPageView = new RootPageViewColumn(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RootPageView->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	RootPageView->removeButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::RemoveElement), NULL, this);

	RootPageAddPro = new RootPageAddProduct(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RootPageAddPro->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	RootPageAddPro->addButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::AddProduct), NULL, this);
	RootPageAddPro->imagePicker->Bind(wxEVT_COMMAND_FILEPICKER_CHANGED, &MyFrame1::PictureImage, this);

	RootPageAddUsr = new RootPageAddUser(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	RootPageAddUsr->backButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	RootPageAddUsr->addButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::AddUser), NULL, this);

	SimpleBookMain->AddPage(HomePage, wxT("Home Page"));
	SimpleBookMain->AddPage(LoginPage, wxT("Login Page"));
	SimpleBookMain->AddPage(RegPage, wxT("Reg Page"));
	SimpleBookMain->AddPage(ShopPage, wxT("Shop Page"));
	SimpleBookMain->AddPage(RootPage, wxT("Root page"));
	SimpleBookMain->AddPage(RootPageView, wxT("Root page view"));
	SimpleBookMain->AddPage(RootPageAddPro, wxT("Root page add product"));
	SimpleBookMain->AddPage(RootPageAddUsr, wxT("Root page add user"));
	SimpleBookMain->AddPage(HomeBasket, wxT("Home Page Basket"));

	ConnectEventButtonsShopPage();
}

MyFrame1::~MyFrame1()
{
	// Отключение событий
	HomePage->LoginButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::ShownLoginPage ), NULL, this);
	HomePage->RegButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::ShownRegedPage ), NULL, this);
	HomeBasket->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	LoginPage->LoginingButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnLogin), NULL, this);
	LoginPage->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	RegPage->LoginingButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnReged), NULL, this);
	RegPage->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Back_main_window), NULL, this);
	ShopPage->backButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::ViewBack), NULL, this);
	RootPage->reloginButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::Relogin), NULL, this);
	RootPage->showTable->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowTable), NULL, this);
	RootPage->addProduct->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowAddProduct), NULL, this);
	RootPage->addUser->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::ShowAddUser), NULL, this);
	RootPageView->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	RootPageView->removeButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::RemoveElement), NULL, this);
	RootPageAddPro->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	RootPageAddPro->addButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::AddProduct), NULL, this);
	RootPageAddUsr->backButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::BackRoot), NULL, this);
	RootPageAddUsr->addButton->Disconnect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame1::AddUser), NULL, this);
	// Удаление подключения
	delete con;
}

void MyFrame1::ShownLoginPage(wxCommandEvent& event)
{
	std::cout << "Pressed button login" << std::endl;
	SimpleBookMain->ChangeSelection(Login_page_id);
}

void MyFrame1::ShownRegedPage(wxCommandEvent& event)
{
	std::cout << "Presed button Reged" << std::endl;
	SimpleBookMain->ChangeSelection(Reg_page_id);
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
		login = res->getString(1);
		password = res->getString(2);
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
	if (RootPage->listTables->GetStringSelection() == wxT(""))
	{
		std::cout << "Выберете таблицу для просмотра" << std::endl;
		return ;
	}
	currentTable = RootPage->listTables->GetStringSelection();
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * from " + currentTable);
	data = res->getMetaData();
	RootPageView->UpdateGrid(res, data);
	SimpleBookMain->ChangeSelection(Root_page_view_id);
	delete stmt;
	delete res;
}

void MyFrame1::ShowTable(std::string nameTable)
{
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * from " + nameTable);
	data = res->getMetaData();
	RootPageView->UpdateGrid(res, data);
	delete stmt;
	delete res;
}

void MyFrame1::ShowAddProduct(wxCommandEvent& event)
{
	SimpleBookMain->ChangeSelection(Root_page_add_product_id);
}

void MyFrame1::PictureImage(wxFileDirPickerEvent& event)
{
	RootPageAddPro->UpdateSelectImage();
}

void MyFrame1::AddProduct(wxCommandEvent& event)
{
	ShowTable("product");
	RootPageAddPro->AddProduct(LastId(RootPageView->gridTable), prep_stmt, con);
}

void MyFrame1::RemoveElement(wxCommandEvent& event)
{
	wxNumberEntryDialog dialog(this,
					wxT("Введите ID удаляемого значения"),
					wxT("ID товара: "),
					wxT("Ввод ID"), 1, 1, 100);
	int id = 0;
	if (dialog.ShowModal() == wxID_OK)
	{
		id = dialog.GetValue();
		RootPageView->RemoveElement(id);
	}
	try
	{
		stmt = con->createStatement();
		stmt->executeQuery("DELETE FROM " + currentTable + " WHERE id=" + std::to_string(id));
	}
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
	delete stmt;
}

int MyFrame1::LastId(wxGrid* grid)
{
    std::vector <int> CurrentId;
	int row = grid->GetNumberRows() - 1;
	int size_id = std::stoi(grid->GetCellValue(row, 0).ToStdString()) + 10;
    CurrentId.reserve(size_id);
    for (int i=0; i < grid->GetNumberRows(); i++)
    {
        CurrentId.push_back(std::stoi(grid->GetCellValue(i, 0).ToStdString()));
    }
    for (int i=1; i < grid->GetNumberRows() + 10; i++)
    {
        if (std::find(CurrentId.begin(), CurrentId.end(), i) != CurrentId.end())
        {
			continue;
        }
		else
		{
			std::cout << "Следующий id равен = " << i << std::endl;
            return i;
		}
    }
	return -1;
}

void MyFrame1::ShowAddUser(wxCommandEvent& event)
{
	SimpleBookMain->ChangeSelection(Root_page_add_user_id);
}

void MyFrame1::AddUser(wxCommandEvent& event)
{
	ShowTable("users");
	RootPageAddUsr->AddUser(LastId(RootPageView->gridTable), prep_stmt, con);
}

void MyFrame1::ShowBasketPage(wxCommandEvent& event)
{
	SimpleBookMain->ChangeSelection(Home_basket_id);
}