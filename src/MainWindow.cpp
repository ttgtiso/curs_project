#include <MainWindow.h>

enum Panel_id
{
	Home_panel_id,
	Login_panel_id,
	Reg_panel_id
};

/*
// Перечисление id кнопок.
enum ButtonId
{
    first_button_id = wxID_LAST + 1,
    second_button_id,
    first_button2_id,
    second_button2_id
};
// clang-format off.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(first_button_id, MyFrame::OnClick_first)
    EVT_BUTTON(second_button_id, MyFrame::OnClick_second)
wxEND_EVENT_TABLE()
; // clang-forman on.
*/

MyFrame1::MyFrame1(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	SimpleBookMain = new wxSimplebook(this);
	HomePage = new HomePagePanel(SimpleBookMain, wxDefaultPosition, wxDefaultSize);
	HomePage->LoginButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnLogin), NULL, this);
	HomePage->RegButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::OnReged), NULL, this);

	SimpleBookMain->AddPage(HomePage, wxT("HomePage"));

}


MyFrame1::~MyFrame1()
{
	// Отключение событий
	HomePage->LoginButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnLogin ), NULL, this );
	HomePage->RegButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnReged ), NULL, this );
}

void MyFrame1::OnLogin(wxCommandEvent& event)
{
	std::cout << "Pressed button login" << std::endl;
	//SimpleBookMain->ChangeSelection(Login_panel_id);
	/*
	try{
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("localhost:3306", "app_user", "Password123!");

	stmt = con->createStatement();
	stmt->execute("USE test");
	stmt->execute("DROP TABLE IF EXISTS test");
	stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
	stmt->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
	
	delete stmt;
	delete con;
	} 
	catch(sql::SQLException &e)
	{
		std::cout << e.what();
	}
	*/
}

void MyFrame1::OnReged(wxCommandEvent& event)
{
	std::cout << "Presed button Reged" << std::endl;
	//SimpleBook_main->ChangeSelection(Reg_panel_id);
}

void MyFrame1::Back_main_window(wxCommandEvent& event)
{
	std::cout << "Back to main window" << std::endl;
	//SimpleBook_main->ChangeSelection(Home_panel_id);
}
