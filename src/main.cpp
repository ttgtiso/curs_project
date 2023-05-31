#include <main.h>
#include <MainWindow.h>

//Определение точки входа в программу.
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxImage::AddHandler( new wxPNGHandler ); // Добавление поддержки PNG
    wxImage::AddHandler( new wxJPEGHandler ); // Добавление поддержки JPEG
    MyFrame1 *frame1 = new MyFrame1(wxT("Автоваз"), wxDefaultPosition, wxSize(500, 600));
    frame1->Show(true);
    frame1->Bind(wxEVT_SIZE, &MyFrame1::OnSize, frame1);
    frame1->Layout();
    return true;
}
