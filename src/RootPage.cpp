#include <RootPage.h>

RootPagePanel::RootPagePanel(wxWindow *parent, const wxPoint &pos, const wxSize &size) 
: wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);

    upSizer = new wxBoxSizer(wxHORIZONTAL);
    downSizer = new wxBoxSizer(wxHORIZONTAL);

    logoPanel = new wxPanel(this, wxID_ANY);
    logoSizer = new wxBoxSizer(wxVERTICAL);
    originalImage = new wxImage(wxT("image/app/full_logo.png"));
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
    //editUser = new wxButton(this, wxID_ANY, wxT("Редактирование существующих пользователей"));
    addProduct = new wxButton(this, wxID_ANY, wxT("Добавить товар"));
    rightDownSizer->Add(showTable);
    rightDownSizer->Add(addUser);
    //rightDownSizer->Add(editUser);
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
	image = new wxImage(originalImage->Scale(loginPanel->GetSize().x * 2, loginPanel->GetSize().y));
	bitmapImage = new wxBitmap(*image);
	logoImage->SetBitmap(*bitmapImage);
    delete bitmapImage;
	delete image;
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

    downSizer = new wxBoxSizer(wxHORIZONTAL);
    removeButton = new wxButton(this, wxID_ANY, wxT("Удалить запись"));
    backButton = new wxButton(this, wxID_ANY, wxT("Вернуться"));

    downSizer->Add(0, 0, 1, wxEXPAND, 5);
    downSizer->Add(removeButton, 0, wxALL, 5);
    downSizer->Add(backButton, 0, wxALL, 5);

    mainSizer->Add(nameTable);
    mainSizer->Add(gridTable, 1, wxALL|wxEXPAND, 5);
    mainSizer->Add(downSizer, 0, wxEXPAND);

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
    int last = res->getRow();
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

void RootPageViewColumn::RemoveElement(int id)
{
    wxString tmp = std::to_string(id);
    for (int i=0; i < gridTable->GetNumberRows(); i++)
    {
        if (gridTable->GetCellValue(i, 0) == tmp)
        {
            gridTable->DeleteRows(i, 1);
            return ;
        }
    }
}

RootPageAddProduct::RootPageAddProduct(wxWindow *parent, const wxPoint &pos, const wxSize &size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);
    
    backButton = new wxButton(this, wxID_ANY, wxT("Назад"));
    horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    
    leftSizer = new wxBoxSizer(wxVERTICAL);
    imageProduct = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    imageProduct->SetMaxSize(wxSize(400, 400));
    wxString tmp = "BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|JPEG Files (*.jpg)|*.jpg;*jpeg| All files|*.*";
    imagePicker = new wxFilePickerCtrl(this, wxID_ANY, wxT("Выберете изображение"), wxT("Выберете изображение"), tmp);

    leftSizer->Add(imageProduct, 0);
    leftSizer->Add(imagePicker, 0, wxEXPAND);

    rightSizer = new wxBoxSizer(wxVERTICAL);

    productText1 = new wxStaticText(this, wxID_ANY, wxT("Артикул товара"));
    productEdit1 = new wxTextCtrl(this, wxID_ANY);
    productText2 = new wxStaticText(this, wxID_ANY, wxT("Название"));
    productEdit2 = new wxTextCtrl(this, wxID_ANY);
    productText3 = new wxStaticText(this, wxID_ANY, wxT("Производитель"));
    productEdit3 = new wxTextCtrl(this, wxID_ANY);
    productText4 = new wxStaticText(this, wxID_ANY, wxT("Цена"));
    productEdit4 = new wxTextCtrl(this, wxID_ANY);
    productText5 = new wxStaticText(this, wxID_ANY, wxT("Гарантия"));
    productEdit5 = new wxTextCtrl(this, wxID_ANY);
    productText6 = new wxStaticText(this, wxID_ANY, wxT("Количество"));
    productEdit6 = new wxTextCtrl(this, wxID_ANY);
    productText7 = new wxStaticText(this , wxID_ANY, wxT("Описание"));
    productEdit7 = new wxTextCtrl(this , wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    downSizer = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(this, wxID_ANY, wxT("Добавить"));
    
    downSizer->Add(0, 0, 1, wxEXPAND, 5);
    downSizer->Add(addButton, 0, wxALIGN_BOTTOM);

    rightSizer->Add(productText1, 0, wxTop, 5);
    rightSizer->Add(productEdit1, 1, wxEXPAND | wxALL, 5);
    rightSizer->Add(productText2, 0, wxTop, 5);
    rightSizer->Add(productEdit2, 1, wxEXPAND | wxALL, 5);
    rightSizer->Add(productText3, 0, wxTop, 5);
    rightSizer->Add(productEdit3, 1, wxEXPAND | wxALL, 5);
    rightSizer->Add(productText4, 0, wxTop, 5);
    rightSizer->Add(productEdit4, 1, wxEXPAND | wxALL, 5);
    rightSizer->Add(productText5, 0, wxTop, 5);
    rightSizer->Add(productEdit5, 1, wxEXPAND | wxALL, 5);
    rightSizer->Add(productText6, 0, wxTop, 5);
    rightSizer->Add(productEdit6, 1, wxEXPAND | wxALL, 5);
    rightSizer->Add(productText7, 0, wxTop, 5);
    rightSizer->Add(productEdit7, 2, wxEXPAND);
    rightSizer->Add(downSizer, 1, wxEXPAND);

    horizontalSizer->Add(leftSizer, 1, wxEXPAND);
    horizontalSizer->Add(rightSizer, 1, wxEXPAND);

    mainSizer->Add(backButton, 0);
    mainSizer->Add(horizontalSizer, 1, wxEXPAND);
    UpdateSelectImage();
    this->SetSizer(mainSizer);
}

void RootPageAddProduct::UpdateSelectImage()
{
    if (imagePicker->GetPath() == wxT("Выберете изображение"))
    {
        imageBitmap = new wxBitmap(wxT("image/app/image_not_found.png"));
        imageProduct->SetBitmap(*imageBitmap);
    }
    else
    {
        delete imageBitmap;
        imageBitmap = new wxBitmap(imagePicker->GetPath());
        imageProduct->SetBitmap(*imageBitmap);
    }
}

void RootPageAddProduct::AddProduct(int id, sql::PreparedStatement *prep_stmt, sql::Connection *con)
{
    std::string string1 = productEdit1->GetValue().ToStdString();
    std::string string2 = productEdit2->GetValue().ToStdString();
    std::string string3 = productEdit3->GetValue().ToStdString();
    std::string string4 = productEdit4->GetValue().ToStdString();
    std::string string5 = productEdit5->GetValue().ToStdString();
    std::string string6 = productEdit6->GetValue().ToStdString();
    std::wstring string9 = productEdit7->GetValue().ToStdWstring();
    std::string string10(string9.begin(), string9.end());
    wxString PathToImage = imagePicker->GetPath();
    std::wstring string7 = PathToImage.ToStdWstring();
    std::string tmp1(string7.rbegin(), string7.rbegin()+4);
    std::string tmp2(tmp1.rbegin(), tmp1.rend());
    std::cout << string7 << std::endl;
    wxString new_file = "image/src/test" + std::to_string(id) + tmp2;
    string7 = new_file.ToStdWstring();
    std::string string8(string7.begin(), string7.end());
    wxCopyFile(PathToImage, new_file);
    try
    {
		std::cout << "Выполнение подключения к базе данных..." << std::endl;
		prep_stmt = con->prepareStatement("INSERT INTO product VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
		prep_stmt->setInt(1, id);
		prep_stmt->setString(2, string1);
		prep_stmt->setString(3, string2);
		prep_stmt->setString(4, string3);
		prep_stmt->setInt(5, std::stoi(string4));
		prep_stmt->setInt(6, std::stoi(string5));
		prep_stmt->setInt(7, std::stoi(string6));
        prep_stmt->setString(8, string8);
        prep_stmt->setString(9, string10);
		prep_stmt->execute();
		std::cout << "Выполнение запроса завершено" << std::endl;
		delete prep_stmt;
	} 
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void RootPageAddProduct::ClearPage()
{
    delete imageBitmap;
    productEdit1->SetValue(*wxEmptyString);
    productEdit2->SetValue(*wxEmptyString);
    productEdit3->SetValue(*wxEmptyString);
    productEdit4->SetValue(*wxEmptyString);
    productEdit5->SetValue(*wxEmptyString);
    productEdit6->SetValue(*wxEmptyString);
    productEdit7->SetValue(*wxEmptyString);
    imagePicker->SetPath(*wxEmptyString);
    imageBitmap = new wxBitmap(wxT("image/app/image_not_found.png"));
    imageProduct->SetBitmap(*imageBitmap);
}

RootPageAddUser::RootPageAddUser(wxWindow *parent, const wxPoint &pos, const wxSize &size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    mainSizer = new wxBoxSizer(wxVERTICAL);
    verticalSizer = new wxBoxSizer(wxVERTICAL);

    userText1 = new wxStaticText(this, wxID_ANY, wxT("Логин"));
    userEdit1 = new wxTextCtrl(this, wxID_ANY);
    userText2 = new wxStaticText(this, wxID_ANY, wxT("Пароль"));
    userEdit2 = new wxTextCtrl(this, wxID_ANY);
    userText3 = new wxStaticText(this, wxID_ANY, wxT("Уровень привилегий"));
    userEdit3 = new wxTextCtrl(this, wxID_ANY);
    userText4 = new wxStaticText(this, wxID_ANY, wxT("ФИО"));
    userEdit4 = new wxTextCtrl(this, wxID_ANY);
    userText5 = new wxStaticText(this, wxID_ANY, wxT("Телефон"));
    userEdit5 = new wxTextCtrl(this, wxID_ANY);
    userText6 = new wxStaticText(this, wxID_ANY, wxT("Количество покупок"));
    userEdit6 = new wxTextCtrl(this, wxID_ANY);
    
    verticalSizer->Add(userText1);
    verticalSizer->Add(userEdit1);
    verticalSizer->Add(userText2);
    verticalSizer->Add(userEdit2);
    verticalSizer->Add(userText3);
    verticalSizer->Add(userEdit3);
    verticalSizer->Add(userText4);
    verticalSizer->Add(userEdit4);
    verticalSizer->Add(userText5);
    verticalSizer->Add(userEdit5);
    verticalSizer->Add(userText6);
    verticalSizer->Add(userEdit6);

    downSizer = new wxBoxSizer(wxHORIZONTAL);
    addButton = new wxButton(this, wxID_ANY, wxT("Добавить"));
    backButton = new wxButton(this, wxID_ANY, wxT("Вернуться"));
    downSizer->Add(0, 0, 1, wxEXPAND, 5);
    downSizer->Add(addButton);

    mainSizer->Add(backButton);
    mainSizer->Add(verticalSizer);
    mainSizer->Add(downSizer);

    this->SetSizerAndFit(mainSizer);
}

void RootPageAddUser::AddUser(int id, sql::PreparedStatement *prep_stmt, sql::Connection *con)
{
    std::string string1 = userEdit1->GetValue().ToStdString();
    std::string string2 = userEdit2->GetValue().ToStdString();
    std::string string3 = userEdit3->GetValue().ToStdString();
    std::string string4 = userEdit4->GetValue().ToStdString();
    std::string string5 = userEdit5->GetValue().ToStdString();
    std::string string6 = userEdit6->GetValue().ToStdString();
    try
    {
		std::cout << "Выполнение подключения к базе данных..." << std::endl;
		prep_stmt = con->prepareStatement("INSERT INTO users VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
		prep_stmt->setInt(1, id);
		prep_stmt->setString(2, string1);
		prep_stmt->setString(3, string2);
		prep_stmt->setInt(4, std::stoi(string3));
		prep_stmt->setString(5, string4);
		prep_stmt->setString(6, string5);
		prep_stmt->setInt(7, std::stoi(string6));
        prep_stmt->setString(8, "");
		prep_stmt->execute();
		std::cout << "Выполнение запроса завершено" << std::endl;
		delete prep_stmt;
	} 
	catch(sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void RootPageAddUser::ClearPage()
{
    userEdit1->SetValue(*wxEmptyString);
    userEdit2->SetValue(*wxEmptyString);
    userEdit3->SetValue(*wxEmptyString);
    userEdit4->SetValue(*wxEmptyString);
    userEdit5->SetValue(*wxEmptyString);
    userEdit6->SetValue(*wxEmptyString);
}