#include <HomePage.h>

ShopElement::ShopElement(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
	// Создание "Центра управления картинкой"
	mainBoxSizer = new wxBoxSizer(wxVERTICAL);
	//PanelImage = new wxAnimationCtrl(this, wxID_ANY, wxNullAnimation, wxDefaultPosition, wxDefaultSize, wxAC_DEFAULT_STYLE);
	originalImage = new wxImage();
	//PanelImage->SetInactiveBitmap();

	ImagePanel = new wxPanel(this, wxID_ANY);
	ImageBoxSizer = new wxBoxSizer(wxVERTICAL);
	StaticBitmap = new wxStaticBitmap(ImagePanel, wxID_ANY, wxNullBitmap);
	
	ImageBoxSizer->Add(StaticBitmap, 1, wxEXPAND | wxALL);
	ImagePanel->SetSizerAndFit(ImageBoxSizer);

	//Добавление остальных элементов
	LabelImageName = new wxStaticText(this, wxID_ANY, wxT("Автомагазин"));
	LabelImagePrice = new wxStaticText(this, wxID_ANY, wxT("2 000 000 руб"));
	ViewButton = new wxButton(this, wxID_ANY, wxT("Посмотреть"));

	mainBoxSizer->Add(ImagePanel, 1, wxEXPAND | wxALL);
	mainBoxSizer->Add(LabelImageName, 0, wxEXPAND | wxALL);
	mainBoxSizer->Add(LabelImagePrice, 0 , wxALIGN_RIGHT);
	mainBoxSizer->Add(ViewButton, 0, wxEXPAND | wxALL);

	image = new wxImage();

	this->SetSizerAndFit(mainBoxSizer);

}

void ShopElement::updateData(int id, std::string artiul, std::string model,
							std::string provider, int price, int warranty,
							int count, std::string PathToImage)
{
	this->id = std::to_string(id);
	this->articul = artiul;
	this->model = model;
	this->provider = provider;
	this->price = std::to_string(price);
	this->warranty = std::to_string(warranty);
	this->count = std::to_string(count);
	this->PathToImage = PathToImage;
	originalImage->LoadFile(this->PathToImage);
	LabelImageName->SetLabelText(this->model);
	LabelImagePrice->SetLabelText(this->price);
	image = new wxImage(originalImage->Scale(480, 346));
	bitmapImage = new wxBitmap(*image);
	StaticBitmap->SetBitmap(*bitmapImage);
}

HomePagePanel::HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
	// Логин панель и её элементы
	LoginPanel = new wxStaticBox(this, wxID_ANY, wxT("Current User"), wxDefaultPosition, wxSize(200, 100));
	LoginPanelSizer = new wxStaticBoxSizer(LoginPanel, wxVERTICAL);
	BasketButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("image/app/basket.png"));

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
	UpPanelSizer->Add(BasketButton, 0, wxALL, 5);
	UpPanelSizer->Add(LoginPanelSizer);

	// Нижняя часть приложения
	DownPanelSizer = new wxBoxSizer(wxVERTICAL);
	
	//ShopPanel1 = new ShopElement(this, wxDefaultPosition, wxDefaultSize);
	//DownPanelSizer->Add(ShopPanel1, 1, wxEXPAND | wxALL);

	// Главный Sizer приложения
	MainPanelSizer = new wxBoxSizer(wxVERTICAL);
	MainPanelSizer->Add(UpPanelSizer, 0, wxEXPAND | wxALL, 5);
	MainPanelSizer->Add(DownPanelSizer, 1, wxEXPAND | wxALL, 5);

	this->SetSizerAndFit(MainPanelSizer);
}

void ShopElement::updateImage()
{
	if (image->IsOk())
	{
		delete bitmapImage;
		delete image;
		image = new wxImage(originalImage->Scale(ImageBoxSizer->GetSize().x, ImageBoxSizer->GetSize().y));
		bitmapImage = new wxBitmap(*image);
		StaticBitmap->SetBitmap(*bitmapImage);
	}
}

// Принимает на вход таблицу "товары" а также количество колонок на одну строку.
void HomePagePanel::Init(sql::ResultSet* res, float col_columns)
{
	int row = 1;
	int columns = 1;
	res->last();
	// Функция ceil округляет в сторону большего значения.
	int col_rows = ceil(res->getInt(1)/col_columns);
	ShopPanels.reserve(col_rows);
	res->first();
	ShopPanels.push_back(new wxBoxSizer(wxHORIZONTAL));
	DownPanelSizer->Add(ShopPanels.at(0), 1, wxEXPAND | wxALL);
	ShopElements.push_back(new ShopElement(this, wxDefaultPosition, wxDefaultSize));
	ShopElements.at(columns-1)->updateData(res->getInt(1), res->getString(2), res->getString(3),
											res->getString(4), res->getInt(5), res->getInt(6),
											res->getInt(7), res->getString(8));
	ShopPanels.at(row-1)->Add(ShopElements.at(columns-1), 1, wxEXPAND | wxALL);
	ShopElements.at(columns-1)->updateImage();
	columns++;
	try
	{
		while (res->next())
		{
			if (columns > col_columns * row)
			{
				row += 1;
				ShopPanels.push_back(new wxBoxSizer(wxHORIZONTAL));
				DownPanelSizer->Add(ShopPanels.at(row-1), 1, wxEXPAND | wxALL);
			}
			ShopElements.push_back(new ShopElement(this, wxDefaultPosition, wxDefaultSize));
			ShopElements.at(columns-1)->updateData(res->getInt(1), res->getString(2), res->getString(3),
											res->getString(4), res->getInt(5), res->getInt(6),
											res->getInt(7), res->getString(8));
			ShopPanels.at(row-1)->Add(ShopElements.at(columns-1), 1, wxEXPAND | wxALL);
			ShopElements.at(columns-1)->updateImage();
			columns++;
			std::cout << "| --------------------------------------- |" << std::endl;
			std::cout << "Id: " << res->getInt(1) << std::endl;
			std::cout << "Articul: " << res->getString(2) << std::endl; 
			std::cout << "Model: " << res->getString(3) << std::endl;
			std::cout << "Provider: " << res->getString(4) << std::endl;
			std::cout << "Price: " << res->getInt(5) << std::endl;
			std::cout << "Warranty: " << res->getInt(6) << std::endl; 
			std::cout << "Count: " << res->getInt(7) << std::endl;
			std::cout << "PathToImage: " << res->getString(8) << std::endl;
		}
	}
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void HomePagePanel::UpdateImage()
{
	std::cout << "Update Image Size" << std::endl;
	for (int i=0; i < ShopElements.size(); i++)
	{
		ShopElements.at(i)->updateImage();
	}
}