#ifndef INIT_H
  #define INIT_H
#pragma once
// Подключение графической библиотеки wxWidgets
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
//Подключение конектора MySQL C++
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

#endif

