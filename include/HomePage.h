#ifndef HOMEPAGE_H
    #define HOMEPAGE_H
#include <main.h>

class ShopElement : public wxPanel
{
	private:

	protected:
		wxBoxSizer *mainBoxSizer;
		wxStaticText* LabelImageName;
		wxStaticText* LabelImagePrice;
		wxBoxSizer* ImageBoxSizer;
		wxPanel* ImagePanel;
		wxImage* originalImage;

	public:
		wxButton* ViewButton;
		wxBitmap* bitmapImage;
		wxImage* image;
		wxStaticBitmap* StaticBitmap;
		ShopElement(wxWindow *parent, const wxPoint &pos, const wxSize &size);
		void updateImage();
		void updateData(int id, std::string artiul, std::string model,
						std::string provider, int price, int warranty,
						int count, std::string PathToImage);
		wxString id;
		wxString articul;
		wxString model;
		wxString provider;
		wxString price;
		wxString warranty;
		wxString count;
		wxString PathToImage;
		~ShopElement();
};

class HomePagePanel : public wxPanel
{
private:

protected:
	/***************| Элемнты домашнего окна |*********************/
	wxPanel* DownPanel;
	wxBoxSizer* MainPanelSizer;
	wxBoxSizer* UpPanelSizer;
	wxBoxSizer* DownPanelSizer;
	
	// Элементы окна регистрации
	wxStaticBoxSizer* LoginPanelSizer;
	wxStaticText* LoginLabel;
	wxStaticText* RegLabel;
	wxBoxSizer* DownPanelScrollSizer;
	int col_column;

public:
	//Элементы для нижнией панели
	wxStaticBox* LoginPanel;
	wxVector <wxBoxSizer*> ShopPanels;
	wxVector <ShopElement*> ShopElements;
	wxVector <wxPanel*> ShopPanel;
	wxButton* LoginButton;
	wxButton* RegButton;
	wxBitmapButton* BasketButton;
	wxScrolledWindow* DownPanelScroll;
	wxPanel* borderScroll;
	wxBoxSizer* borderSizer;
    HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
	void Init(sql::ResultSet* res, float col_columns);
	void UpdateImage();
	void UpdateImage(wxSize size);
	void UpdateTable(sql::ResultSet* res);
};

class BasketElement : public wxPanel
{
protected:
	wxBoxSizer* mainSizer;
	wxBoxSizer* upSizer;
	wxBoxSizer* downSizer;
	wxBoxSizer* rightSizer;
	wxPanel* imagePanel;
	wxBoxSizer* imageSizer;
	wxStaticBitmap* imageProduct;
	wxStaticText* priceLabel;
	wxStaticText* countLabel;
	wxStaticText* nameLabel;
	wxStaticText* priceLabelText;
	wxStaticText* countLabelText;
	wxImage* originalImage;
	wxImage* image;
	wxBitmap* bitmapImage;
public:
	wxButton* cancelButton;
	BasketElement(wxWindow *parent, const wxPoint &pos, const wxSize &size);
	void UpdateData(ShopElement *Element);
	void UpdateImage();
	~BasketElement();
	wxString nameElement;
};


class HomePageBasket : public wxPanel
{
protected:
	wxBoxSizer* mainSizer;
	wxBoxSizer* upSizer;
	wxBoxSizer* downSizer;
	wxStaticText* namePage;
	wxScrolledWindow* panelElement;
	wxBoxSizer* panelSizer;
	
public:
	wxButton* backButton;
	wxButton* cancelButton;
	HomePageBasket(wxWindow *parent, const wxPoint &pos, const wxSize &size);
	void UpdateBasketElement(wxVector <wxString> *listShop, wxVector <ShopElement*> *ShopElements);
	void UpdateImage();
	wxVector <BasketElement*> listBasket;
};

#endif