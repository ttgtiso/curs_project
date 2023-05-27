#include <RootPage.h>

RootPagePanel::RootPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) : wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);

    upSizer = new wxBoxSizer(wxHORIZONTAL);
    downSizer = new wxBoxSizer(wxHORIZONTAL);

    logoPanel = new wxPanel(this, wxID_ANY);
    logoSizer = new wxBoxSizer(wxVERTICAL);
    originalImage = new wxImage(wxT("image/app/full_logo.png"));
    image = new wxImage();
    bitmapImage = new wxBitmap();
    logoImage = new wxStaticBitmap(logoPanel, wxID_ANY, wxNullBitmap);
    logoSizer->Add(logoImage);
    logoPanel->SetSizer(logoSizer);

    loginPanel = new wxPanel(this, wxID_ANY);
    loginSizer = new wxBoxSizer(wxVERTICAL);
    userName = new wxStaticText(loginPanel, wxID_ANY, wxT("Добро пожаловать\nВаш уровень доступа:\nАдминистратор"));
    reloginButton = new wxButton(loginPanel, wxID_ANY, wxT("Выйти"));
    loginSizer->Add(userName);
    loginSizer->Add(reloginButton);
    loginPanel->SetSizer(loginSizer);
    loginPanel->SetMinSize(wxSize(200, 150));
    upSizer->Add(logoPanel, 2, wxEXPAND);
    upSizer->Add(loginPanel, 1, wxEXPAND);

    leftDownSizer = new wxBoxSizer(wxVERTICAL);
    textList = new wxStaticText(this, wxID_ANY, wxT("В базе данных присутствую следующие таблицы:"));
    listTables = new wxListBox(this, wxID_ANY);

    leftDownSizer->Add(textList);
    leftDownSizer->Add(listTables, 1, wxEXPAND);

    rightDownSizer = new wxBoxSizer(wxVERTICAL);
    showTable = new wxButton(this, wxID_ANY, wxT("Посмотреть записи в таблице."));
    addUser = new wxButton(this, wxID_ANY, wxT("Добавление нового пользователя"));
    editUser = new wxButton(this, wxID_ANY, wxT("Редактирование существующих пользователей"));
    addProduct = new wxButton(this, wxID_ANY, wxT("Добавить товар"));
    rightDownSizer->Add(showTable);
    rightDownSizer->Add(addUser);
    rightDownSizer->Add(editUser);
    rightDownSizer->Add(addProduct);
    
    downSizer->Add(leftDownSizer, 1, wxEXPAND);
    downSizer->Add(rightDownSizer, 1, wxEXPAND);
    mainSizer->Add(upSizer, 0, wxEXPAND);
    mainSizer->Add(downSizer, 1, wxEXPAND);

    this->SetSizer(mainSizer);
}

void RootPagePanel::UpdateList(sql::ResultSet* res)
{
    wxString tmp;
    while (res->next())
    {
        tmp = std::string(res->getString(1));
        listTables->Append(tmp);
    }
}

void RootPagePanel::UpdateImage()
{
	delete bitmapImage;
	delete image;
	image = new wxImage(originalImage->Scale(loginPanel->GetSize().x * 2, loginPanel->GetSize().y));
	bitmapImage = new wxBitmap(*image);
	logoImage->SetBitmap(*bitmapImage);
}

void RootPagePanel::clearData()
{
    listTables->Clear();
}

RootPageViewColumn::RootPageViewColumn(wxWindow *parent, const wxPoint &pos, const wxSize &size) 
: wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);
    nameTable = new wxStaticText(this, wxID_ANY, wxT("Просмотр таблицы: "));
    
    gridTable = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	// Grid
	gridTable->CreateGrid(30, 10);
	gridTable->EnableEditing(false);
	gridTable->EnableGridLines(true);
	gridTable->EnableDragGridSize(false);
	gridTable->SetMargins(0, 0);

	// Columns
	gridTable->AutoSizeColumns();
	gridTable->EnableDragColMove(false);
	gridTable->EnableDragColSize(true);
	gridTable->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	gridTable->AutoSizeRows();
	gridTable->EnableDragRowSize(true);
	gridTable->SetRowLabelSize(1);
	gridTable->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Cell Defaults
	gridTable->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);

    backButton = new wxButton(this, wxID_ANY, wxT("Вернуться"));

    mainSizer->Add(nameTable);
    mainSizer->Add(gridTable, 1, wxALL|wxEXPAND, 5);
    mainSizer->Add(backButton);

    this->SetSizer(mainSizer);
}

void RootPageViewColumn::UpdateGrid(sql::ResultSet* res, sql::ResultSetMetaData* data)
{
    gridTable->ClearGrid();
    RemoveGrid();
    int col_column = data->getColumnCount();
    int count = data->getColumnCount();
    std::string tmp;
    
    try
	{
		res->next();
        res->getString(1);
	}
	catch(sql::SQLException &e)
	{
        std::cout << e.what() << std::endl;
		std::cout << "Таблица " << data->getTableName(1) << " пустая." << std::endl;
        gridTable->InsertCols(0, col_column);
        for (int i=1; i<=count; i++)
        {
            tmp = data->getColumnName(i);
            gridTable->SetColLabelValue(i-1, tmp);
        }
        return ;
	}
    res->last();
    int last = res->getInt(1);
    res->first();
    
    gridTable->InsertCols(0, col_column);
    gridTable->InsertRows(0, last);

    for (int i=1; i<=count; i++)
    {
        tmp = data->getColumnName(i);
        gridTable->SetColLabelValue(i-1, tmp);
    }

    for (int i=0; i < last; i++)
    {
        for (int j=1; j <= col_column; j++)
        {
            tmp = res->getString(j);
            gridTable->SetCellValue(i, j-1, tmp);
        }
        if (i == last)
            break;
        else res->next();
    }
    
    gridTable->AutoSize();
    Layout();
    
}

void RootPageViewColumn::RemoveGrid()
{
    if (gridTable->GetNumberRows() == 0)
    {
        gridTable->DeleteCols(0, gridTable->GetNumberCols());
    }
    else
    {
        gridTable->DeleteRows(0, gridTable->GetNumberRows());
        gridTable->DeleteCols(0, gridTable->GetNumberCols());
    }
}