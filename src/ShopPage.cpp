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
    bitmapImage = new wxBitmap();

    labelSizer->Add(idLabel);
    labelSizer->Add(articulLabel);
    labelSizer->Add(modelLabel);
    labelSizer->Add(providerLabel);
    labelSizer->Add(priceLabel);
    labelSizer->Add(warrantyLabel);
    labelSizer->Add(countLabel);
    labelPanel->SetSizer(labelSizer);

    upRightSizer->Add(labelPanel, 1, wxEXPAND);
    upRightSizer->Add(buyButton, 0);

    imageSizer->Add(image, 1, wxEXPAND | wxALL);
    imagePanel->SetSizer(imageSizer);

    upSizer->Add(imagePanel, 1, wxEXPAND);
    upSizer->Add(upRightSizer, 1, wxEXPAND);

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
    modelLabel->SetLabelText(wxT("Модель" + Element->model));
    providerLabel->SetLabelText(wxT("Производитель: " + Element->provider));
    priceLabel->SetLabelText(wxT("Цена: " + Element->price));
    warrantyLabel->SetLabelText(wxT("Гарантия: " + Element->warranty));
    countLabel->SetLabelText(wxT("Количество: " + Element->count));
    
}

void ShopPagePanel::UpdateImage()
{
    delete bitmapImage;
	delete currentImage;
	currentImage = new wxImage(originalImage->Scale(imagePanel->GetSize().x, imagePanel->GetSize().y));
	bitmapImage = new wxBitmap(*currentImage);
	image->SetBitmap(*bitmapImage);
    
}