#include <ShopPage.h>

ShopPagePanel::ShopPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);
    upSizer = new wxBoxSizer(wxHORIZONTAL);
    upRightSizer = new wxBoxSizer(wxVERTICAL);

    imagePanel = new wxPanel(this, wxID_ANY);
    imageSizer = new wxBoxSizer(wxVERTICAL);
    image = new wxStaticBitmap(imagePanel, wxID_ANY, wxNullBitmap);
    labelPanel = new wxPanel(this, wxID_ANY);
    idLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));
    articulLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));
    modelLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));
    providerLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));
    priceLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));
    warrantyLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));
    countLabel = new wxStaticText(labelPanel, wxID_ANY, wxT(""));

    labelSizer = new wxBoxSizer(wxVERTICAL);
    buyButton = new wxButton(this, wxID_ANY, wxT("Добавить в корзину"));
    backButton = new wxButton(this, wxID_ANY, wxT("Back"));
    
    aboutLabel = new wxStaticText(this, wxID_ANY, wxT(""));
    originalImage = new wxImage();

    labelSizer->Add(idLabel, 1, wxEXPAND);
    labelSizer->Add(articulLabel, 1, wxEXPAND);
    labelSizer->Add(modelLabel, 1, wxEXPAND);
    labelSizer->Add(providerLabel, 1, wxEXPAND);
    labelSizer->Add(priceLabel, 1, wxEXPAND);
    labelSizer->Add(warrantyLabel, 1, wxEXPAND);
    labelSizer->Add(countLabel, 1, wxEXPAND);
    labelPanel->SetSizer(labelSizer);

    upRightSizer->Add(labelPanel, 1, wxEXPAND);
    upRightSizer->Add(buyButton, 0);

    imageSizer->Add(image, 1, wxEXPAND | wxALL);
    imagePanel->SetSizer(imageSizer);

    upSizer->Add(imagePanel, 1, wxEXPAND | wxALL);
    upSizer->Add(upRightSizer, 1, wxEXPAND | wxALL);

    mainSizer->Add(backButton, 0, wxALL);
    mainSizer->Add(upSizer, 1, wxEXPAND | wxALL);
    mainSizer->Add(aboutLabel, 1, wxEXPAND | wxALL);

    this->SetSizerAndFit(mainSizer);
}

void ShopPagePanel::UpdateData(ShopElement *Element)
{
    delete originalImage;
    originalImage = new wxImage(Element->PathToImage);
    idLabel->SetLabelText(wxT("ID товара: " + Element->id));
    articulLabel->SetLabelText(wxT("Артикул: " + Element->articul));
    modelLabel->SetLabelText(wxT("Модель: " + Element->model));
    providerLabel->SetLabelText(wxT("Производитель: " + Element->provider));
    priceLabel->SetLabelText(wxT("Цена: " + Element->price));
    warrantyLabel->SetLabelText(wxT("Гарантия: " + Element->warranty));
    countLabel->SetLabelText(wxT("Количество: " + Element->count));
}

void ShopPagePanel::UpdateImage()
{
	currentImage = new wxImage(originalImage->Scale(labelPanel->GetSize().x, labelPanel->GetSize().y));
	bitmapImage = new wxBitmap(*currentImage);
	image->SetBitmap(*bitmapImage);
    delete bitmapImage;
	delete currentImage;
}

void ShopPagePanel::UpdateImage(wxSize size)
{
    currentImage = new wxImage(originalImage->Scale(size.x, size.y));
    bitmapImage = new wxBitmap(*currentImage);
    image->SetBitmap(*bitmapImage);
    delete bitmapImage;
    delete currentImage;
}