#ifndef ROOT_PAGE_H
	#define ROOT_PAGE_H
#include <main.h>

class RootPagePanel : public wxPanel
{
protected:
    wxBoxSizer* mainSizer;
    
    wxBoxSizer* upSizer;
    wxBoxSizer* downSizer;

    // Настройка логотипа
    wxImage* originalImage;
    wxImage* image;
    wxBitmap* bitmapImage;

    // Настройкка верхней части приложения
    wxPanel* logoPanel;
    wxBoxSizer* logoSizer;
    wxStaticBitmap* logoImage;

    wxPanel* loginPanel;
    wxBoxSizer* loginSizer;
    wxStaticText* userName;

    // Настройка нижний части приложения
    wxBoxSizer* leftDownSizer;
    wxStaticText* textList;

    wxBoxSizer* rightDownSizer;
public:
    wxButton* showTable;
    wxButton* addUser;
    wxButton* editUser;
    wxButton* addProduct;
    wxButton* reloginButton;
    wxListBox* listTables;
    RootPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void UpdateImage();
    void clearData();
    void UpdateList(sql::ResultSet* res);
};

class RootPageViewColumn : public wxPanel
{
protected:
    wxBoxSizer* mainSizer;
    wxStaticText* nameTable;
    wxGrid* gridTable;
public:
    wxButton* backButton;
    RootPageViewColumn(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void UpdateGrid(sql::ResultSet* res, sql::ResultSetMetaData* data);
    void RemoveGrid();
};

#endif