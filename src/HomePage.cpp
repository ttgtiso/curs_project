#include <HomePage.h>

ShopElement::ShopElement(wxWindow *parent, const wxPoint &pos, const wxSize &size)
 : wxPanel(parent, wxID_ANY, pos, size,  wxBORDER_THEME)
{
	// Создание "Центра управления картинкой"
	mainBoxSizer = new wxBoxSizer(wxVERTICAL);
	//PanelImage = new wxAnimationCtrl(this, wxID_ANY, wxNullAnimation, wxDefaultPosition, wxDefaultSize, wxAC_DEFAULT_STYLE);
	originalImage = new wxImage();
	//PanelImage->SetInactiveBitmap();

	ImagePanel = new wxPanel(this, wxID_ANY);
	ImageBoxSizer = new wxBoxSizer(wxVERTICAL);
	StaticBitmap = new wxStaticBitmap(ImagePanel, wxID_ANY, wxNullBitmap);
	StaticBitmap->SetMinSize(wxSize(150, 150));
	
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

ShopElement::~ShopElement()
{
	mainBoxSizer->Clear(true);
	delete originalImage;
}

void ShopElement::updateData(int id, std::string artiul, std::string model,
							std::string provider, int price, int warranty,
							int count, std::string PathToImage)
{
	this->id = std::to_string(id);
	this->articul = wxString::FromUTF8(artiul);
	this->model = wxString::FromUTF8(model);
	this->provider = wxString::FromUTF8(provider);
	this->price = std::to_string(price);
	this->warranty = std::to_string(warranty);
	this->count = std::to_string(count);
	this->PathToImage = wxString::FromUTF8(PathToImage);
	originalImage->LoadFile(this->PathToImage);
	LabelImageName->SetLabelText(this->model);
	LabelImagePrice->SetLabelText(this->price);
	image = new wxImage(originalImage->Scale(480, 346));
	bitmapImage = new wxBitmap(*image);
	wxClientDC dc(StaticBitmap);
	wxMemoryDC mdc;

	int w,h;
	dc.GetSize(&w, &h);
	mdc.SelectObject(*bitmapImage);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	dc.Blit(0, 0, bitmapImage->GetWidth(), bitmapImage->GetHeight(), &mdc, 0, 0, wxCOPY, 0);
	mdc.SelectObject(wxNullBitmap);
	
	delete bitmapImage;
	delete image;
}

HomePagePanel::HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) 
 : wxPanel(parent, wxID_ANY, pos, size)
{
	// Логин панель и её элементы
	LoginPanel = new wxStaticBox(this, wxID_ANY, wxT("Current User"), wxDefaultPosition, wxSize(200, 100));
	LoginPanelSizer = new wxStaticBoxSizer(LoginPanel, wxVERTICAL);
	wxImage* tmpImage = new wxImage(wxT("image/app/basket.png"));
	wxBitmap* tmpBitmap = new wxBitmap(*tmpImage);
	BasketButton = new wxBitmapButton(this, wxID_ANY, wxNullBitmap);
	BasketButton->SetBitmap(*tmpBitmap);
	delete tmpImage;
	delete tmpBitmap;
	BasketButton->SetHelpText(wxT("Зарегестрируйтесь что бы получить доступ к этому разделу."));

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
	borderScroll = new wxPanel(this , wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
	borderSizer = new wxBoxSizer(wxVERTICAL);
	borderScroll->SetSizer(borderSizer);
	DownPanelScroll = new wxScrolledWindow(borderScroll, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL);
	DownPanelScroll->SetScrollRate(10, 10);
	DownPanelScrollSizer = new wxBoxSizer(wxVERTICAL);
	borderSizer->Add(DownPanelScroll, 1, wxEXPAND);

	DownPanelScroll->SetSizer(DownPanelScrollSizer);
	DownPanelSizer->Add(borderScroll, 1, wxEXPAND | wxALL, 10);

	// Главный Sizer приложения
	MainPanelSizer = new wxBoxSizer(wxVERTICAL);
	MainPanelSizer->Add(UpPanelSizer, 0, wxEXPAND | wxALL, 5);
	MainPanelSizer->Add(DownPanelSizer, 1, wxEXPAND | wxALL, 5);

	this->SetSizerAndFit(MainPanelSizer);
}

void ShopElement::updateImage()
{
	image = new wxImage(originalImage->Scale(ImageBoxSizer->GetSize().x, ImageBoxSizer->GetSize().y));
	bitmapImage = new wxBitmap(*image);
	StaticBitmap->SetBitmap(*bitmapImage);
	delete bitmapImage;
	delete image;
}

// Принимает на вход таблицу "товары" а также количество колонок на одну строку.
void HomePagePanel::Init(sql::ResultSet* res, float col_columns)
{
	int row = 1;
	int columns = 1;
	// Функция ceil округляет в сторону большего значения.
	//int col_rows = ceil(res->getInt(1)/col_columns);
	ShopPanel.reserve(20);
	for (int i = 0; i < 20; i++)
	{
		ShopPanel.push_back(new wxPanel(DownPanelScroll, wxID_ANY, wxDefaultPosition, wxDefaultSize));
		DownPanelScrollSizer->Add(ShopPanel.at(i), 0, wxEXPAND | wxALL);
	}
	ShopPanels.reserve(20);
	res->first();
	for (int i = 0; i < 20; i++)
	{
		ShopPanels.push_back(new wxBoxSizer(wxHORIZONTAL));
		ShopPanel.at(i)->SetSizer((ShopPanels.at(i)));
	}
	ShopElements.push_back(new ShopElement(ShopPanel.at(0), wxDefaultPosition, wxDefaultSize));
	ShopElements.at(columns-1)->updateData(res->getInt(1), res->getString(2), res->getString(3),
											res->getString(4), res->getInt(5), res->getInt(6),
											res->getInt(7), res->getString(8));
	ShopPanels.at(row-1)->Add(ShopElements.at(columns-1), 1, wxEXPAND | wxALL, 5);
	ShopElements.at(columns-1)->updateImage();
	columns++;
	try
	{
		while (res->next())
		{
			if (columns > col_columns * row)
			{
				row += 1;
			}
			ShopElements.push_back(new ShopElement(ShopPanel.at(row - 1), wxDefaultPosition, wxDefaultSize));
			ShopElements.at(columns-1)->updateData(res->getInt(1), res->getString(2), res->getString(3),
											res->getString(4), res->getInt(5), res->getInt(6),
											res->getInt(7), res->getString(8));
			ShopPanels.at(row-1)->Add(ShopElements.at(columns-1), 1, wxEXPAND | wxALL, 5);
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
	col_column = col_columns;
}

void HomePagePanel::UpdateTable(sql::ResultSet* res)
{
	for (auto i : ShopPanels)
	{
		i->Clear();
	}
	for (auto i : ShopElements)
	{
		delete i;
	}
	ShopElements.clear();
	int columns = 1;
	int row = 1;
	res->first();
	ShopElements.push_back(new ShopElement(ShopPanel.at(0), wxDefaultPosition, wxDefaultSize));
	ShopElements.at(columns-1)->updateData(res->getInt(1), res->getString(2), res->getString(3),
											res->getString(4), res->getInt(5), res->getInt(6),
											res->getInt(7), res->getString(8));
	ShopPanels.at(row-1)->Add(ShopElements.at(columns-1), 1, wxEXPAND | wxALL, 5);
	ShopElements.at(columns-1)->updateImage();
	columns++;
	try
	{
		while (res->next())
		{
			if (columns > col_column * row)
			{
				row += 1;
			}
			ShopElements.push_back(new ShopElement(ShopPanel.at(row - 1), wxDefaultPosition, wxDefaultSize));
			ShopElements.at(columns-1)->updateData(res->getInt(1), res->getString(2), res->getString(3),
											res->getString(4), res->getInt(5), res->getInt(6),
											res->getInt(7), res->getString(8));
			ShopPanels.at(row-1)->Add(ShopElements.at(columns-1), 1, wxEXPAND | wxALL, 5);
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

HomePageBasket::HomePageBasket(wxWindow *parent, const wxPoint &pos, const wxSize &size)
 : wxPanel(parent, wxID_ANY, pos, size)
 {
	mainSizer = new wxBoxSizer(wxVERTICAL);
	upSizer = new wxBoxSizer(wxHORIZONTAL);
	backButton = new wxButton(this, wxID_ANY, wxT("Вернуться"));
	namePage = new wxStaticText(this, wxID_ANY, wxT("Корзина"));
	cancelButton = new wxButton(this, wxID_ANY, wxT("Очистить корзину"));
	panelElement = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL);
	panelSizer = new wxBoxSizer(wxVERTICAL);
	panelElement->SetSizer(panelSizer);
	panelElement->SetScrollRate(10, 10);
	upSizer->Add(backButton);
	upSizer->Add(namePage);
	
	downSizer = new wxBoxSizer(wxHORIZONTAL);
	downSizer->Add(0, 0, 1, wxEXPAND, 5);
	downSizer->Add(cancelButton);

	mainSizer->Add(upSizer, 0, wxEXPAND);
	mainSizer->Add(panelElement, 1, wxEXPAND);
	mainSizer->Add(downSizer, 0, wxEXPAND);
	
	this->SetSizer(mainSizer);
 }

 BasketElement::BasketElement(wxWindow *parent, const wxPoint &pos, const wxSize &size)
	: wxPanel(parent, wxID_ANY, pos, size, wxBORDER_THEME)
{
	mainSizer = new wxBoxSizer(wxVERTICAL);
	upSizer = new wxBoxSizer(wxHORIZONTAL);
	//downSizer = new wxBoxSizer(wxHORIZONTAL);

	imagePanel = new wxPanel(this, wxID_ANY);
	imageSizer = new wxBoxSizer(wxVERTICAL);
	imagePanel->SetSizer(imageSizer);
	imageProduct = new wxStaticBitmap(imagePanel, wxID_ANY, wxNullBitmap);
	imageSizer->Add(imageProduct);
	imageProduct->SetMinSize(wxSize(200, 200));
	imageProduct->SetMaxSize(wxSize(300, 300));
	priceLabel = new wxStaticText(this, wxID_ANY, wxT("Цена: "));
	countLabel = new wxStaticText(this, wxID_ANY, wxT("Количество: "));

	nameLabel = new wxStaticText(this, wxID_ANY, *wxEmptyString);
	//priceLabelText = new wxStaticText(this, wxID_ANY, *wxEmptyString);
	//countLabelText = new wxStaticText(this, wxID_ANY, *wxEmptyString);
	cancelButton = new wxButton(this, wxID_ANY, wxT("Удалить"));

	rightSizer = new wxBoxSizer(wxVERTICAL);
	rightSizer->Add(nameLabel);
	rightSizer->Add(priceLabel);
	rightSizer->Add(countLabel);
	rightSizer->Add(cancelButton);
	originalImage = new wxImage();
	upSizer->Add(imagePanel, 0, wxEXPAND | wxALL, 10);
	upSizer->Add(rightSizer, 0, wxEXPAND | wxALL, 10);

	//downSizer->Add(nameLabel, 1, wxEXPAND); 
	//downSizer->Add(priceLabelText, 1, wxEXPAND);
	//downSizer->Add(countLabelText, 1, wxEXPAND);
	//downSizer->Add(cancelButton, 0);

	mainSizer->Add(upSizer, 0, wxEXPAND);
	//mainSizer->Add(downSizer, 0, wxEXPAND);
	
	SetSizerAndFit(mainSizer);
}

void BasketElement::UpdateData(ShopElement* Element)
{
	delete originalImage;
	originalImage = new wxImage(Element->PathToImage);
	nameElement = Element->model;
	nameLabel->SetLabel((wxT("Имя: ") + Element->model));
	priceLabel->SetLabel((wxT("Цена: ") + Element->price));
	countLabel->SetLabel((wxT("Количество: ") + Element->count));
	UpdateImage();
}

void BasketElement::UpdateImage()
{
	image = new wxImage(originalImage->Scale(imagePanel->GetSize().x, imagePanel->GetSize().y));
	bitmapImage = new wxBitmap(*image);
	imageProduct->SetBitmap(*bitmapImage);
	delete bitmapImage;
	delete image;
}

BasketElement::~BasketElement()
{
	delete originalImage;
}

 void HomePageBasket::UpdateBasketElement(wxVector <wxString> *listShop, wxVector <ShopElement*> *ShopElements)
 {
	if (!(listBasket.empty()))
	{
		for (auto i : listBasket)
		{
			delete i;
		}
		listBasket.clear();
		panelSizer->Clear(true);
	}
	if (listShop->empty())
		return ;
	for (int i = 0; i < listShop->size(); i++)
	{
		for (int j = 0; j < ShopElements->size(); j++)
		{
			if (listShop->at(i) == ShopElements->at(j)->model)
			{
				listBasket.push_back(new BasketElement(panelElement, wxDefaultPosition, wxDefaultSize));
				listBasket.at(i)->UpdateData(ShopElements->at(j));
				panelSizer->Add(listBasket.at(i), 0, wxEXPAND);
				break;
			}
		}
	}

 }

void HomePageBasket::UpdateImage()
{
	for (auto Element : listBasket)
	{
		Element->UpdateImage();
	}
}
