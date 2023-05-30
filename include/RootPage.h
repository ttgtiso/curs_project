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
    wxBoxSizer* downSizer;
    wxStaticText* nameTable;
public:
    wxGrid* gridTable;
    wxButton* backButton;
    wxButton* removeButton;
    RootPageViewColumn(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void UpdateGrid(sql::ResultSet* res, sql::ResultSetMetaData* data);
    void RemoveGrid();
    void RemoveElement(int id);
};

class RootPageAddProduct : public wxPanel
{
protected:
    /******************| Графические элементы |*******************/
    wxBoxSizer* mainSizer;

    wxBoxSizer* horizontalSizer;
    wxBoxSizer* leftSizer;
    wxBoxSizer* rightSizer;
    
    wxStaticBitmap* imageProduct;
    
    wxStaticText* productText1;
    wxTextCtrl* productEdit1;
    wxStaticText* productText2;
    wxTextCtrl* productEdit2;
    wxStaticText* productText3;
    wxTextCtrl* productEdit3;
    wxStaticText* productText4;
    wxTextCtrl* productEdit4;
    wxStaticText* productText5;
    wxTextCtrl* productEdit5;
    wxStaticText* productText6;
    wxTextCtrl* productEdit6;
    wxStaticText* productText7;
    wxTextCtrl* productEdit7;

    wxBoxSizer* downSizer;

    /******************| Обычные переменные |*******************/
    wxBitmap* imageBitmap;
    
public:
    wxButton* addButton;
    wxButton* backButton;
    wxFilePickerCtrl* imagePicker;
    RootPageAddProduct(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void UpdateSelectImage();
    void AddProduct(int id, sql::PreparedStatement *prep_stmt, sql::Connection *con);
    void ClearPage();
};

class RootPageAddUser : public wxPanel
{
protected:
    wxBoxSizer* mainSizer;
    wxBoxSizer* verticalSizer;
    wxBoxSizer* downSizer;

    wxStaticText* userText1;
    wxTextCtrl* userEdit1;
    wxStaticText* userText2;
    wxTextCtrl* userEdit2;
    wxStaticText* userText3;
    wxTextCtrl* userEdit3;
    wxStaticText* userText4;
    wxTextCtrl* userEdit4;
    wxStaticText* userText5;
    wxTextCtrl* userEdit5;
    wxStaticText* userText6;
    wxTextCtrl* userEdit6;

public:
    wxButton* backButton;
    wxButton* addButton;
    RootPageAddUser(wxWindow *parent, const wxPoint &pos, const wxSize &size);
    void AddUser(int id, sql::PreparedStatement *prep_stmt, sql::Connection *con);
    void ClearPage();
    
};

#endif