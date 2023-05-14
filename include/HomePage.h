#ifndef HOMEPAGE_H
    #define HOMEPAGE_H
#include <main.h>

class HomePagePanel : public wxPanel
{
private:

protected:
	/***************| Элемнты домашнего окна |*********************/
	wxPanel* DownPanel;
	wxBoxSizer* MainPanelSizer;
	wxBoxSizer* UpPanelSizer;
	wxBoxSizer* DownPanelSizer;

	//Элементы окна регистрации
	wxStaticBox* LoginPanel;
	wxStaticBoxSizer* LoginPanelSizer;
	wxStaticText* LoginLabel;
	wxStaticText* RegLabel;

public:
	wxButton* LoginButton;
	wxButton* RegButton;
    HomePagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
};

#endif