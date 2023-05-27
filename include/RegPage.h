#ifndef REG_PAGE_H
	#define REG_PAGE_H
#include <main.h>

class RegPagePanel : public wxPanel
{
private:

protected:
	/***************| Элемнты страницы авторизации |*********************/
	wxBoxSizer* mainSizer;
	wxStaticBox* LoginPanel;
	wxStaticBoxSizer* LoginPanelSizer;

	wxBoxSizer* LoginBoxSizerHorizontal;
	wxBoxSizer* LoginBoxSizerVertical;

	wxStaticText* UserNameLabel;
	wxTextCtrl* UserNameEdit;
	wxStaticText* UserPhoneLabel;
	wxTextCtrl* UserPhoneEdit;
    wxStaticText* LoginLabel;
    wxTextCtrl* LoginEdit;
    wxStaticText* PasswordLabel;
    wxTextCtrl* PasswordEdit;
	wxStaticText* ConfirmPasswordLabel;
	wxTextCtrl* ConfirmPasswordEdit;

public:
    wxButton* LoginingButton;
	wxButton* backButton;
    RegPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
};

#endif