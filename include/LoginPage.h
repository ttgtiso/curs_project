#ifndef LOGIN_PAGE_H
	#define LOGIN_PAGE_H
#include <main.h>

class LoginPagePanel : public wxPanel
{
private:

protected:
	/***************| Элемнты страницы авторизации |*********************/
	wxStaticBox* LoginPanel;
	wxStaticBoxSizer* LoginPanelSizer;

	wxBoxSizer* LoginBoxSizerHorizontal;
	wxBoxSizer* LoginBoxSizerVertical;
    wxStaticText* LoginLabel;
    wxTextCtrl* LoginEdit;
    wxStaticText* PasswordLabel;
    wxTextCtrl* PasswordEdit;

public:
    wxButton* LoginingButton;
    LoginPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
};

#endif