#ifndef  SHOP_PAGE_H
	#define SHOP_PAGE_H
#include <main.h>
#include <HomePage.h>

class ShopPagePanel : public wxPanel
{
private:

protected:
	/***************| Элемнты страницы покупки |*********************/
    wxBoxSizer* mainSizer;
    wxBoxSizer* upSizer;
    wxBoxSizer* upRightSizer;
    wxPanel* imagePanel;
    wxBoxSizer* imageSizer;
    wxImage* currentImage;
    wxImage* originalImage;
    wxBitmap* bitmapImage;
    wxStaticText* idLabel;
    wxStaticText* articulLabel;
    wxStaticText* modelLabel;
    wxStaticText* providerLabel;
    wxStaticText* priceLabel;
    wxStaticText* warrantyLabel;
    wxStaticText* countLabel;
    wxStaticText* aboutLabel;
    wxBoxSizer* labelSizer;
    wxPanel* labelPanel;

public:
    wxButton* buyButton;
    wxButton* backButton;
    wxStaticBitmap* image;
    ShopPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void UpdateData(ShopElement *Element);
    void UpdateImage();
    void UpdateImage(wxSize size);
    ShopElement* CurrentElement;
};

#endif