#include <main.h>

//Определение точки входа в программу.
wxIMPLEMENT_APP(MyApp);

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

bool MyApp::OnInit()
{
    MyFrame1 *frame1 = new MyFrame1(nullptr, wxID_ANY, wxT("Автоваз, почти."), wxDefaultPosition, wxSize(700, 600), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    frame1->Show(true);
    return true;
}
MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_simplebook2 = new wxSimplebook( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel2 = new wxPanel( m_simplebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( m_panel2, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALL, 5 );


	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Покупатель") ), wxVERTICAL );

	m_staticText3 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Аунтифицируйтесь в системе"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	sbSizer2->Add( m_staticText3, 0, wxALL, 5 );

	m_button17 = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Войти"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_button17, 0, wxALL|wxEXPAND, 5 );

	m_staticText4 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Нет аккаунта?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	sbSizer2->Add( m_staticText4, 0, wxALL, 5 );

	m_button18 = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Зарегестрироваться"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_button18, 0, wxALL|wxEXPAND, 5 );


	bSizer5->Add( sbSizer2, 0, 0, 5 );


	m_panel2->SetSizer( bSizer5 );
	m_panel2->Layout();
	bSizer5->Fit( m_panel2 );
	m_simplebook2->AddPage( m_panel2, wxT("a page"), false );
	m_panel3 = new wxPanel( m_simplebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_simplebook2->AddPage( m_panel3, wxT("a page"), false );

	bSizer4->Add( m_simplebook2, 1, wxEXPAND | wxALL, 5 );


	m_scrolledWindow1->SetSizer( bSizer4 );
	m_scrolledWindow1->Layout();
	bSizer4->Fit( m_scrolledWindow1 );
	bSizer1->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnLogin ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OnLogin ), NULL, this );

}

void MyFrame1::OnLogin(wxCommandEvent& event)
{
	std::cout << "Pressed button login" << std::endl;
	/*
	// Instantiate Driver
	sql::Driver* driver = sql::mariadb::get_driver_instance();

	// Configure Connection
	sql::SQLString url("jdbc:mariadb://localhost:3306/todo");
	sql::Properties properties({{"user", "app_user"}, {"password", "Password123!"}});

	// Establish Connection
	std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

	// Create a new PreparedStatement
	std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into tasks (description) values (?)"));

	// Bind values to SQL statement
	stmnt->setString(1, description);

	// Execute query
	stmnt->executeQuery();

	// Create a new Statement
	std::unique_ptr stmnt(conn->createStatement());

	// Execute query
	sql::ResultSet *res = stmnt->executeQuery("select * from tasks");

	// Loop through and print results
	while (res->next()) {
		std::cout << "id = " << res->getInt(1);
		std::cout << ", description = " << res->getString(2);
		std::cout << ", completed = " << res->getBoolean(3) << "\n";
	}

	// Create a new PreparedStatement
	std::unique_ptr stmnt(conn->prepareStatement("update tasks set completed = ? where id = ?"));

	// Bind values to SQL statement
	stmnt->setBoolean(1, completed);
	stmnt->setInt(2, id);

	// Execute query
	stmnt->executeQuery();

	// Create a new PreparedStatement
	std::unique_ptr stmnt(conn->prepareStatement("delete from tasks where id = ?"));

	// Bind values to SQL statement
	stmnt->setInt(1, id);

	// Execute query
	stmnt->executeQuery();
	*/

}