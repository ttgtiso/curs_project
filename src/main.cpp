#include <wx/wx.h>
#include <wx/notebook.h>

// Главный класс приложения.
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

//Определение точки входа в программу.
wxIMPLEMENT_APP(MyApp);

// Опеределение фреймов приложения.
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString & title, const wxPoint &pos, const wxSize &size);
private:
    void OnClick_first(wxCommandEvent&);
    void OnClick_second(wxCommandEvent&);
    wxDECLARE_EVENT_TABLE();
}; 

class MyFrame2 : public wxFrame 
{
public:
    MyFrame2(const wxString & title, const wxPoint &pos, const wxSize &size);
private:
    void OnClick_first(wxCommandEvent& );
    void OnClick_second(wxCommandEvent& );
    wxDECLARE_EVENT_TABLE();
};


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

wxBEGIN_EVENT_TABLE(MyFrame2, wxFrame)
    EVT_BUTTON(first_button2_id, MyFrame2::OnClick_first)
    EVT_BUTTON(second_button2_id, MyFrame2::OnClick_second)
wxEND_EVENT_TABLE()
;

MyFrame *frame1 = nullptr;
MyFrame2 *frame2 = nullptr;

bool MyApp::OnInit()
{
    frame1 = new MyFrame("The 1 frame", wxDefaultPosition, wxDefaultSize);
    frame1->Show(true);
    frame2 = new MyFrame2("The 2 frame", wxDefaultPosition, wxDefaultSize);
    return true;
}

MyFrame::MyFrame(const wxString & title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxButton *button = new wxButton(this, first_button_id, "button1");
    wxButton *button2 = new wxButton(this, second_button_id, "button2");
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(button, 100);
    sizer->Add(button2, 100);

    this->SetSizerAndFit(sizer);
}

void MyFrame::OnClick_first(wxCommandEvent &event)
{
    std::cout << "The 1 frame." << std::endl;
}

void MyFrame::OnClick_second(wxCommandEvent &event)
{
    frame1->Show(false);
    frame2->Show(true);
}

MyFrame2::MyFrame2(const wxString & title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxButton *button = new wxButton(this, first_button2_id, "button1");
    wxButton *button2 = new wxButton(this, second_button2_id, "button2");
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(button, 100);
    sizer->Add(button2, 100);

    this->SetSizerAndFit(sizer);
}

void MyFrame2::OnClick_first(wxCommandEvent& event)
{
    std::cout << "This 2 framw" << std::endl;
}

void MyFrame2::OnClick_second(wxCommandEvent& event)
{
    frame2->Show(false);
    frame1->Show(true);
}