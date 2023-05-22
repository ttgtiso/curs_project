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
    wxStaticBitmap* image;
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
    ShopPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void UpdateData(ShopElement *Element);
    void UpdateImage();
};

#endif