#ifndef LOGIN_PAGE_H
	#define LOGIN_PAGE_H
#include <main.h>

class LoginPagePanel : public wxPanel
{
private:

protected:
	/***************| Элемнты страницы авторизации |*********************/
    wxBoxSizer* mainSizer;
	wxStaticBox* LoginPanel;
	wxStaticBoxSizer* LoginPanelSizer;

	wxBoxSizer* LoginBoxSizerHorizontal;
	wxBoxSizer* LoginBoxSizerVertical;
    wxStaticText* LoginLabel;
    wxStaticText* PasswordLabel;

public:
    wxTextCtrl* LoginEdit;
    wxButton* LoginingButton;
    wxTextCtrl* PasswordEdit;
    wxButton* backButton;
    LoginPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
};

#endif