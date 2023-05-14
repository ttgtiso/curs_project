#ifndef MAINWINDOW_H
	#define MAINWINDOW_H
#include <main.h>
#include <HomePage.h>
#include <LoginPage.h>
#include <RegPage.h>

class MyFrame1 : public wxFrame
{
	private:
		
	protected:
		/***************|      Корень окна       |*********************/
		wxSimplebook* SimpleBookMain;
		HomePagePanel* HomePage;
		LoginPagePanel* LoginPage;
		RegPagePanel* RegPage;

		/***************|    События приложения   |*********************/
		virtual void OnLogin( wxCommandEvent& event );
		virtual void OnReged( wxCommandEvent& event );
		virtual void Back_main_window( wxCommandEvent& event ); 


	public:
		MyFrame1(const wxString &title, const wxPoint &pos, const wxSize &size);
		~MyFrame1();

};
#endif