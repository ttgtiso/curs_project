#pragma once

#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/simplebook.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame1 : public wxFrame
{
	private:
		
	protected:
		wxScrolledWindow* m_scrolledWindow1;
		wxSimplebook* m_simplebook2;
		wxPanel* m_panel2;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText3;
		wxButton* m_button17;
		wxStaticText* m_staticText4;
		wxButton* m_button18;
		wxPanel* m_panel3;

		// Virtual event handlers, override them in your derived class
		virtual void OnLogin( wxCommandEvent& event );


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};