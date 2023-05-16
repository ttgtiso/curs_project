#include <HomePage.h>

ShopElement::ShopElement(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
	// Создание "Центра управления картинкой"
	mainBoxSizer = new wxBoxSizer(wxVERTICAL);
	//PanelImage = new wxAnimationCtrl(this, wxID_ANY, wxNullAnimation, wxDefaultPosition, wxDefaultSize, wxAC_DEFAULT_STYLE);
	originalImage = new wxImage(wxT("image/src/test.jpg"));
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

HomePagePanel::HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
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
	ShopPanel1 = new ShopElement(this, wxDefaultPosition, wxDefaultSize);
	DownPanelSizer->Add(ShopPanel1, 1, wxEXPAND | wxALL);

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
		std::cout << "Sizer size x,y: " << ImageBoxSizer->GetSize().x << " " << ImageBoxSizer->GetSize().y << std::endl;
	}
	else
	{
		image = new wxImage(originalImage->Scale(480, 346));
		bitmapImage = new wxBitmap(*image);
		StaticBitmap->SetBitmap(*bitmapImage);
	}
}
