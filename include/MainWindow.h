#ifndef MAINWINDOW_H
	#define MAINWINDOW_H
#include <main.h>
#include <HomePage.h>
#include <LoginPage.h>
#include <RegPage.h>
#include <ShopPage.h>
#include <RootPage.h>

class MyFrame1 : public wxFrame
{
	private:
		
	protected:
		/***************|      Корень окна       |*********************/
		wxSimplebook* SimpleBookMain;
		RootPagePanel* RootPage;
		RootPageViewColumn* RootPageView;
		LoginPagePanel* LoginPage;
		RegPagePanel* RegPage;
		ShopPagePanel* ShopPage;

		/***************|    События приложения   |*********************/
		virtual void ShownLoginPage( wxCommandEvent& event );
		virtual void ShownRegedPage( wxCommandEvent& event );
		virtual void Back_main_window( wxCommandEvent& event ); 
		virtual void ViewContent( wxCommandEvent& event );
		virtual void ViewBack( wxCommandEvent& event );
		void ConnectEventButtonsShopPage();
		void OnLogin( wxCommandEvent& event );
		void OnReged( wxCommandEvent& event );
		void SetUser();
		void Relogin( wxCommandEvent& event );
		void ShowTable( wxCommandEvent& event );
		void BackRoot( wxCommandEvent& event );
		
		/***************|    События приложения   |*********************/
		sql::mysql::MySQL_Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt; // Данный тип поддерживает только простые SQL запросы
		sql::PreparedStatement *prep_stmt;
		sql::ResultSet *res;
		sql::ResultSetMetaData* data;

		/***************|    настройки текующего пользователя   |*********************/
		wxString userName;
		int userPrivilege;
		bool userLogining;
		

	public:
		HomePagePanel* HomePage;
		virtual void OnSize(wxSizeEvent& event);
		MyFrame1(const wxString &title, const wxPoint &pos, const wxSize &size);
		~MyFrame1();

};

#endif