#include <main.h>
#include <MainWindow.h>

//Определение точки входа в программу.
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxImage::AddHandler( new wxPNGHandler );
    wxImage::AddHandler( new wxJPEGHandler );
    MyFrame1 *frame1 = new MyFrame1(wxT("Автоваз"), wxDefaultPosition, wxSize(500, 600));
    frame1->Show(true);
    return true;
}
