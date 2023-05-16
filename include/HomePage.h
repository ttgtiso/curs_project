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
		wxStaticBitmap* StaticBitmap;
		wxImage* originalImage;
		
	public:
		wxButton* ViewButton;
		wxBitmap* bitmapImage;
		wxImage* image;
		//wxAnimationCtrl* PanelImage;
		ShopElement(wxWindow *parent, const wxPoint &pos, const wxSize &size);
		void updateImage();
		//~ShopElement();
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
	wxStaticBox* LoginPanel;
	wxStaticBoxSizer* LoginPanelSizer;
	wxStaticText* LoginLabel;
	wxStaticText* RegLabel;

public:
	ShopElement* ShopPanel1;
	wxButton* LoginButton;
	wxButton* RegButton;
    HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
};

#endif