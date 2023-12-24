#pragma once
#include <msclr/marshal_cppstd.h>
#include <Windows.h>
#include <iomanip>

namespace Computergames {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public value class Game {
	public:
		System::String^ title;
		int diskSpaceMB;
		System::String^ graphicsQuality;

	};

	public ref class Games : public System::Windows::Forms::Form
	{
	public:
		Games(void)
		{
			InitializeComponent();
		}

	protected:
		~Games()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Available_operations;
	protected:

	private: System::Windows::Forms::Button^ buttonCreateFirstFile;
	private: System::Windows::Forms::Label^ File_Name;
	private: System::Windows::Forms::TextBox^ textBoxFilename;

	private: System::Windows::Forms::Button^ buttonOpenFile;
	private: System::Windows::Forms::Button^ buttonAddToFile;

	private: System::Windows::Forms::TextBox^ gameNameTextBox;
	private: System::Windows::Forms::Label^ Game_name;

	private: System::Windows::Forms::TextBox^ gameSizeTextBox;
	private: System::Windows::Forms::Label^ Game_size;
	private: System::Windows::Forms::Label^ Game_quality;

	private: System::Windows::Forms::TextBox^ gameQualityTextBox;
	private: System::Windows::Forms::Button^ buttonReadFromFile;

	private: System::Windows::Forms::Button^ buttonDeleteFromFile;
	private: System::Windows::Forms::TextBox^ fieldToEditTextBox;
	private: System::Windows::Forms::Label^ Field_to_modify;
	private: System::Windows::Forms::Label^ Value_to_modify;

	private: System::Windows::Forms::TextBox^ OldValueTextBox;
	private: System::Windows::Forms::TextBox^ NewValueTextBox;
	private: System::Windows::Forms::Label^ New_value;

	private: System::Windows::Forms::Button^ buttonModifyFile;
	private: System::Windows::Forms::Button^ buttonSearchInFile;

	private: System::Windows::Forms::TextBox^ valueToSearchTextBox;
	private: System::Windows::Forms::Label^ Value_to_search;

	private: System::Windows::Forms::TextBox^ fieldToSearchTextBox;
	private: System::Windows::Forms::Label^ Field_to_search;

	private: System::Windows::Forms::Button^ buttonCreateSecondFile;

	private: System::Windows::Forms::Button^ buttonExit;
	private: System::Windows::Forms::TextBox^ textBoxOutput;
	private: System::Windows::Forms::VScrollBar^ ScrollBar;
	private: System::Windows::Forms::Label^ Output_Field;
	private: System::Windows::Forms::Label^ help;
	private: System::Windows::Forms::Label^ info;
	private: System::Windows::Forms::TextBox^ nameToDeleteTextBox;
	private: System::Windows::Forms::Label^ name_to_delete;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Games::typeid));
			this->Available_operations = (gcnew System::Windows::Forms::Label());
			this->buttonCreateFirstFile = (gcnew System::Windows::Forms::Button());
			this->File_Name = (gcnew System::Windows::Forms::Label());
			this->textBoxFilename = (gcnew System::Windows::Forms::TextBox());
			this->buttonOpenFile = (gcnew System::Windows::Forms::Button());
			this->buttonAddToFile = (gcnew System::Windows::Forms::Button());
			this->gameNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->Game_name = (gcnew System::Windows::Forms::Label());
			this->gameSizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->Game_size = (gcnew System::Windows::Forms::Label());
			this->Game_quality = (gcnew System::Windows::Forms::Label());
			this->gameQualityTextBox = (gcnew System::Windows::Forms::TextBox());
			this->buttonReadFromFile = (gcnew System::Windows::Forms::Button());
			this->buttonDeleteFromFile = (gcnew System::Windows::Forms::Button());
			this->fieldToEditTextBox = (gcnew System::Windows::Forms::TextBox());
			this->Field_to_modify = (gcnew System::Windows::Forms::Label());
			this->Value_to_modify = (gcnew System::Windows::Forms::Label());
			this->OldValueTextBox = (gcnew System::Windows::Forms::TextBox());
			this->NewValueTextBox = (gcnew System::Windows::Forms::TextBox());
			this->New_value = (gcnew System::Windows::Forms::Label());
			this->buttonModifyFile = (gcnew System::Windows::Forms::Button());
			this->buttonSearchInFile = (gcnew System::Windows::Forms::Button());
			this->valueToSearchTextBox = (gcnew System::Windows::Forms::TextBox());
			this->Value_to_search = (gcnew System::Windows::Forms::Label());
			this->fieldToSearchTextBox = (gcnew System::Windows::Forms::TextBox());
			this->Field_to_search = (gcnew System::Windows::Forms::Label());
			this->buttonCreateSecondFile = (gcnew System::Windows::Forms::Button());
			this->buttonExit = (gcnew System::Windows::Forms::Button());
			this->textBoxOutput = (gcnew System::Windows::Forms::TextBox());
			this->Output_Field = (gcnew System::Windows::Forms::Label());
			this->help = (gcnew System::Windows::Forms::Label());
			this->info = (gcnew System::Windows::Forms::Label());
			this->nameToDeleteTextBox = (gcnew System::Windows::Forms::TextBox());
			this->name_to_delete = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Available_operations
			// 
			this->Available_operations->AutoSize = true;
			this->Available_operations->BackColor = System::Drawing::Color::DarkGray;
			this->Available_operations->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->Available_operations->Location = System::Drawing::Point(813, 182);
			this->Available_operations->Name = L"Available_operations";
			this->Available_operations->Size = System::Drawing::Size(260, 29);
			this->Available_operations->TabIndex = 0;
			this->Available_operations->Text = L"Доступные операции";
			// 
			// buttonCreateFirstFile
			// 
			this->buttonCreateFirstFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->buttonCreateFirstFile->Location = System::Drawing::Point(105, 454);
			this->buttonCreateFirstFile->Name = L"buttonCreateFirstFile";
			this->buttonCreateFirstFile->Size = System::Drawing::Size(347, 45);
			this->buttonCreateFirstFile->TabIndex = 11;
			this->buttonCreateFirstFile->Text = L"Создать файл";
			this->buttonCreateFirstFile->UseVisualStyleBackColor = true;
			this->buttonCreateFirstFile->Click += gcnew System::EventHandler(this, &Games::buttonCreateFile_Click);
			// 
			// File_Name
			// 
			this->File_Name->AutoSize = true;
			this->File_Name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->File_Name->Location = System::Drawing::Point(100, 397);
			this->File_Name->Name = L"File_Name";
			this->File_Name->Size = System::Drawing::Size(149, 29);
			this->File_Name->TabIndex = 12;
			this->File_Name->Text = L"Имя файла:";
			// 
			// textBoxFilename
			// 
			this->textBoxFilename->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxFilename->Location = System::Drawing::Point(255, 397);
			this->textBoxFilename->Name = L"textBoxFilename";
			this->textBoxFilename->Size = System::Drawing::Size(196, 35);
			this->textBoxFilename->TabIndex = 13;
			// 
			// buttonOpenFile
			// 
			this->buttonOpenFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonOpenFile->Location = System::Drawing::Point(105, 505);
			this->buttonOpenFile->Name = L"buttonOpenFile";
			this->buttonOpenFile->Size = System::Drawing::Size(347, 45);
			this->buttonOpenFile->TabIndex = 16;
			this->buttonOpenFile->Text = L"Открыть файл";
			this->buttonOpenFile->UseVisualStyleBackColor = true;
			this->buttonOpenFile->Click += gcnew System::EventHandler(this, &Games::buttonOpenFile_Click);
			// 
			// buttonAddToFile
			// 
			this->buttonAddToFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonAddToFile->Location = System::Drawing::Point(506, 460);
			this->buttonAddToFile->Name = L"buttonAddToFile";
			this->buttonAddToFile->Size = System::Drawing::Size(512, 45);
			this->buttonAddToFile->TabIndex = 19;
			this->buttonAddToFile->Text = L"Добавить запись";
			this->buttonAddToFile->UseVisualStyleBackColor = true;
			this->buttonAddToFile->Click += gcnew System::EventHandler(this, &Games::buttonAddToFile_Click);
			// 
			// gameNameTextBox
			// 
			this->gameNameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->gameNameTextBox->Location = System::Drawing::Point(737, 286);
			this->gameNameTextBox->Name = L"gameNameTextBox";
			this->gameNameTextBox->Size = System::Drawing::Size(281, 35);
			this->gameNameTextBox->TabIndex = 18;
			// 
			// Game_name
			// 
			this->Game_name->AutoSize = true;
			this->Game_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Game_name->Location = System::Drawing::Point(536, 286);
			this->Game_name->Name = L"Game_name";
			this->Game_name->Size = System::Drawing::Size(195, 29);
			this->Game_name->TabIndex = 17;
			this->Game_name->Text = L"Название игры:";
			// 
			// gameSizeTextBox
			// 
			this->gameSizeTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->gameSizeTextBox->Location = System::Drawing::Point(737, 399);
			this->gameSizeTextBox->Name = L"gameSizeTextBox";
			this->gameSizeTextBox->Size = System::Drawing::Size(281, 35);
			this->gameSizeTextBox->TabIndex = 21;
			// 
			// Game_size
			// 
			this->Game_size->AutoSize = true;
			this->Game_size->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Game_size->Location = System::Drawing::Point(565, 399);
			this->Game_size->Name = L"Game_size";
			this->Game_size->Size = System::Drawing::Size(166, 29);
			this->Game_size->TabIndex = 20;
			this->Game_size->Text = L"Размер в Мб:";
			// 
			// Game_quality
			// 
			this->Game_quality->AutoSize = true;
			this->Game_quality->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Game_quality->Location = System::Drawing::Point(501, 342);
			this->Game_quality->Name = L"Game_quality";
			this->Game_quality->Size = System::Drawing::Size(231, 29);
			this->Game_quality->TabIndex = 22;
			this->Game_quality->Text = L"Качество графики:";
			// 
			// gameQualityTextBox
			// 
			this->gameQualityTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->gameQualityTextBox->Location = System::Drawing::Point(737, 342);
			this->gameQualityTextBox->Name = L"gameQualityTextBox";
			this->gameQualityTextBox->Size = System::Drawing::Size(281, 35);
			this->gameQualityTextBox->TabIndex = 23;
			// 
			// buttonReadFromFile
			// 
			this->buttonReadFromFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonReadFromFile->Location = System::Drawing::Point(104, 556);
			this->buttonReadFromFile->Name = L"buttonReadFromFile";
			this->buttonReadFromFile->Size = System::Drawing::Size(347, 45);
			this->buttonReadFromFile->TabIndex = 24;
			this->buttonReadFromFile->Text = L"Вывести файл";
			this->buttonReadFromFile->UseVisualStyleBackColor = true;
			this->buttonReadFromFile->Click += gcnew System::EventHandler(this, &Games::buttonReadFromFile_Click);
			// 
			// buttonDeleteFromFile
			// 
			this->buttonDeleteFromFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->buttonDeleteFromFile->Location = System::Drawing::Point(505, 601);
			this->buttonDeleteFromFile->Name = L"buttonDeleteFromFile";
			this->buttonDeleteFromFile->Size = System::Drawing::Size(511, 45);
			this->buttonDeleteFromFile->TabIndex = 25;
			this->buttonDeleteFromFile->Text = L"Удалить запись";
			this->buttonDeleteFromFile->UseVisualStyleBackColor = true;
			this->buttonDeleteFromFile->Click += gcnew System::EventHandler(this, &Games::buttonDeleteFromFile_Click);
			// 
			// fieldToEditTextBox
			// 
			this->fieldToEditTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fieldToEditTextBox->Location = System::Drawing::Point(1417, 280);
			this->fieldToEditTextBox->Name = L"fieldToEditTextBox";
			this->fieldToEditTextBox->Size = System::Drawing::Size(242, 35);
			this->fieldToEditTextBox->TabIndex = 27;
			// 
			// Field_to_modify
			// 
			this->Field_to_modify->AutoSize = true;
			this->Field_to_modify->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Field_to_modify->Location = System::Drawing::Point(1085, 283);
			this->Field_to_modify->Name = L"Field_to_modify";
			this->Field_to_modify->Size = System::Drawing::Size(326, 29);
			this->Field_to_modify->TabIndex = 26;
			this->Field_to_modify->Text = L"Поле для редактирования:";
			// 
			// Value_to_modify
			// 
			this->Value_to_modify->AutoSize = true;
			this->Value_to_modify->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Value_to_modify->Location = System::Drawing::Point(1039, 345);
			this->Value_to_modify->Name = L"Value_to_modify";
			this->Value_to_modify->Size = System::Drawing::Size(381, 29);
			this->Value_to_modify->TabIndex = 28;
			this->Value_to_modify->Text = L"Значение для редактирования:";
			// 
			// OldValueTextBox
			// 
			this->OldValueTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OldValueTextBox->Location = System::Drawing::Point(1417, 342);
			this->OldValueTextBox->Name = L"OldValueTextBox";
			this->OldValueTextBox->Size = System::Drawing::Size(242, 35);
			this->OldValueTextBox->TabIndex = 29;
			// 
			// NewValueTextBox
			// 
			this->NewValueTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NewValueTextBox->Location = System::Drawing::Point(1417, 397);
			this->NewValueTextBox->Name = L"NewValueTextBox";
			this->NewValueTextBox->Size = System::Drawing::Size(242, 35);
			this->NewValueTextBox->TabIndex = 31;
			// 
			// New_value
			// 
			this->New_value->AutoSize = true;
			this->New_value->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->New_value->Location = System::Drawing::Point(1201, 399);
			this->New_value->Name = L"New_value";
			this->New_value->Size = System::Drawing::Size(210, 29);
			this->New_value->TabIndex = 30;
			this->New_value->Text = L"Новое значение:";
			// 
			// buttonModifyFile
			// 
			this->buttonModifyFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonModifyFile->Location = System::Drawing::Point(1044, 457);
			this->buttonModifyFile->Name = L"buttonModifyFile";
			this->buttonModifyFile->Size = System::Drawing::Size(615, 45);
			this->buttonModifyFile->TabIndex = 32;
			this->buttonModifyFile->Text = L"Изменить";
			this->buttonModifyFile->UseVisualStyleBackColor = true;
			this->buttonModifyFile->Click += gcnew System::EventHandler(this, &Games::buttonModifyFile_Click);
			// 
			// buttonSearchInFile
			// 
			this->buttonSearchInFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonSearchInFile->Location = System::Drawing::Point(1055, 663);
			this->buttonSearchInFile->Name = L"buttonSearchInFile";
			this->buttonSearchInFile->Size = System::Drawing::Size(605, 45);
			this->buttonSearchInFile->TabIndex = 39;
			this->buttonSearchInFile->Text = L"Поиск в файле";
			this->buttonSearchInFile->UseVisualStyleBackColor = true;
			this->buttonSearchInFile->Click += gcnew System::EventHandler(this, &Games::buttonSearchInFile_Click);
			// 
			// valueToSearchTextBox
			// 
			this->valueToSearchTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->valueToSearchTextBox->Location = System::Drawing::Point(1417, 601);
			this->valueToSearchTextBox->Name = L"valueToSearchTextBox";
			this->valueToSearchTextBox->Size = System::Drawing::Size(243, 35);
			this->valueToSearchTextBox->TabIndex = 36;
			// 
			// Value_to_search
			// 
			this->Value_to_search->AutoSize = true;
			this->Value_to_search->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Value_to_search->Location = System::Drawing::Point(1141, 604);
			this->Value_to_search->Name = L"Value_to_search";
			this->Value_to_search->Size = System::Drawing::Size(270, 29);
			this->Value_to_search->TabIndex = 35;
			this->Value_to_search->Text = L"Значение для поиска:";
			// 
			// fieldToSearchTextBox
			// 
			this->fieldToSearchTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->fieldToSearchTextBox->Location = System::Drawing::Point(1417, 539);
			this->fieldToSearchTextBox->Name = L"fieldToSearchTextBox";
			this->fieldToSearchTextBox->Size = System::Drawing::Size(243, 35);
			this->fieldToSearchTextBox->TabIndex = 34;
			// 
			// Field_to_search
			// 
			this->Field_to_search->AutoSize = true;
			this->Field_to_search->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Field_to_search->Location = System::Drawing::Point(1196, 542);
			this->Field_to_search->Name = L"Field_to_search";
			this->Field_to_search->Size = System::Drawing::Size(215, 29);
			this->Field_to_search->TabIndex = 33;
			this->Field_to_search->Text = L"Поле для поиска:";
			// 
			// buttonCreateSecondFile
			// 
			this->buttonCreateSecondFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->buttonCreateSecondFile->Location = System::Drawing::Point(105, 607);
			this->buttonCreateSecondFile->Name = L"buttonCreateSecondFile";
			this->buttonCreateSecondFile->Size = System::Drawing::Size(347, 45);
			this->buttonCreateSecondFile->TabIndex = 40;
			this->buttonCreateSecondFile->Text = L"Создать копию файла";
			this->buttonCreateSecondFile->UseVisualStyleBackColor = true;
			this->buttonCreateSecondFile->Click += gcnew System::EventHandler(this, &Games::buttonCreateSecondFile_Click);
			// 
			// buttonExit
			// 
			this->buttonExit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonExit->Location = System::Drawing::Point(388, 728);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(932, 45);
			this->buttonExit->TabIndex = 46;
			this->buttonExit->Text = L"Выход";
			this->buttonExit->UseVisualStyleBackColor = false;
			this->buttonExit->Click += gcnew System::EventHandler(this, &Games::buttonExit_Click);
			// 
			// textBoxOutput
			// 
			this->textBoxOutput->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBoxOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxOutput->Location = System::Drawing::Point(123, 41);
			this->textBoxOutput->Multiline = true;
			this->textBoxOutput->Name = L"textBoxOutput";
			this->textBoxOutput->Size = System::Drawing::Size(1443, 133);
			this->textBoxOutput->TabIndex = 47;
			// 
			// Output_Field
			// 
			this->Output_Field->AutoSize = true;
			this->Output_Field->BackColor = System::Drawing::Color::DarkGray;
			this->Output_Field->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Output_Field->Location = System::Drawing::Point(737, 9);
			this->Output_Field->Name = L"Output_Field";
			this->Output_Field->Size = System::Drawing::Size(163, 29);
			this->Output_Field->TabIndex = 48;
			this->Output_Field->Text = L"Поле вывода";
			// 
			// help
			// 
			this->help->AutoSize = true;
			this->help->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->help->Location = System::Drawing::Point(221, 182);
			this->help->Name = L"help";
			this->help->Size = System::Drawing::Size(110, 29);
			this->help->TabIndex = 49;
			this->help->Text = L"Справка";
			// 
			// info
			// 
			this->info->AutoSize = true;
			this->info->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->info->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->info->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->info->Location = System::Drawing::Point(80, 227);
			this->info->Name = L"info";
			this->info->Size = System::Drawing::Size(371, 142);
			this->info->TabIndex = 50;
			this->info->Text = L"\r\nИмя файла: в формате .txt\r\nНазвание игры: любое\r\nКачество графики: в формате пл"
				L"охая/хорошая\r\nРазмер: в целочисленном формате\r\nПоле: в формате название/графика/"
				L"память\r\n\r\n";
			this->info->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// nameToDeleteTextBox
			// 
			this->nameToDeleteTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->nameToDeleteTextBox->Location = System::Drawing::Point(737, 553);
			this->nameToDeleteTextBox->Name = L"nameToDeleteTextBox";
			this->nameToDeleteTextBox->Size = System::Drawing::Size(280, 35);
			this->nameToDeleteTextBox->TabIndex = 52;
			// 
			// name_to_delete
			// 
			this->name_to_delete->AutoSize = true;
			this->name_to_delete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name_to_delete->Location = System::Drawing::Point(536, 556);
			this->name_to_delete->Name = L"name_to_delete";
			this->name_to_delete->Size = System::Drawing::Size(195, 29);
			this->name_to_delete->TabIndex = 51;
			this->name_to_delete->Text = L"Название игры:";
			// 
			// Games
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->ClientSize = System::Drawing::Size(1684, 785);
			this->Controls->Add(this->nameToDeleteTextBox);
			this->Controls->Add(this->name_to_delete);
			this->Controls->Add(this->info);
			this->Controls->Add(this->help);
			this->Controls->Add(this->Output_Field);
			this->Controls->Add(this->textBoxOutput);
			this->Controls->Add(this->buttonExit);
			this->Controls->Add(this->buttonCreateSecondFile);
			this->Controls->Add(this->buttonSearchInFile);
			this->Controls->Add(this->valueToSearchTextBox);
			this->Controls->Add(this->Value_to_search);
			this->Controls->Add(this->fieldToSearchTextBox);
			this->Controls->Add(this->Field_to_search);
			this->Controls->Add(this->buttonModifyFile);
			this->Controls->Add(this->NewValueTextBox);
			this->Controls->Add(this->New_value);
			this->Controls->Add(this->OldValueTextBox);
			this->Controls->Add(this->Value_to_modify);
			this->Controls->Add(this->fieldToEditTextBox);
			this->Controls->Add(this->Field_to_modify);
			this->Controls->Add(this->buttonDeleteFromFile);
			this->Controls->Add(this->buttonReadFromFile);
			this->Controls->Add(this->gameQualityTextBox);
			this->Controls->Add(this->Game_quality);
			this->Controls->Add(this->gameSizeTextBox);
			this->Controls->Add(this->Game_size);
			this->Controls->Add(this->buttonAddToFile);
			this->Controls->Add(this->gameNameTextBox);
			this->Controls->Add(this->Game_name);
			this->Controls->Add(this->buttonOpenFile);
			this->Controls->Add(this->textBoxFilename);
			this->Controls->Add(this->File_Name);
			this->Controls->Add(this->buttonCreateFirstFile);
			this->Controls->Add(this->Available_operations);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Games";
			this->Text = L"Games";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Games::ProgramExit);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ProgramExit(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		Application::Exit();
	}
	private:
		System::String^ openedFileName;
	private: System::Void buttonCreateFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ filenameTextBoxToCreate = textBoxFilename->Text;

		if (filenameTextBoxToCreate->Trim() == "") {
			MessageBox::Show("Имя файла не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		if (filenameTextBoxToCreate->Trim() == "temp.txt") {
			MessageBox::Show("Нельзя использовать данное название для создания файла.\nПожалуйста, введите корректное название файла.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::string filename = msclr::interop::marshal_as<std::string>(filenameTextBoxToCreate);
		std::string fullPath = "C:\\" + filename;

		if (System::IO::File::Exists(gcnew System::String(fullPath.c_str()))) {
			MessageBox::Show("Файл с именем '" + filenameTextBoxToCreate + "' уже существует.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		try {
			System::IO::StreamWriter^ outFile = gcnew System::IO::StreamWriter(gcnew System::String(fullPath.c_str()));

			if (outFile->BaseStream->CanWrite) {
				MessageBox::Show("Файл '" + filenameTextBoxToCreate + "' успешно создан в C:\\", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
					TruncateOrPad("Название игры", 50),
					TruncateOrPad("Графика игры", 50),
					TruncateOrPad("Размер на диске в МБ", 50)));

				outFile->Close();
			}
			else {
				MessageBox::Show("Не удалось создать файл.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при записи в файл: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}
	private: System::Void buttonOpenFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ filenameTextBoxToOpen = textBoxFilename->Text;

		if (filenameTextBoxToOpen->Trim() == "") {
			MessageBox::Show("Имя файла не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::string filename = msclr::interop::marshal_as<std::string>(filenameTextBoxToOpen);
		std::string fullPath = "C:\\" + filename;

		try {
			System::IO::StreamReader^ inFile = gcnew System::IO::StreamReader(gcnew System::String(fullPath.c_str()));

			if (inFile->BaseStream->CanRead) {
				MessageBox::Show("Файл '" + filenameTextBoxToOpen + "' успешно открыт.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

				// Сохранение имени открытого файла
				openedFileName = filenameTextBoxToOpen;

				inFile->Close();
			}
			else {
				MessageBox::Show("Не удалось открыть файл.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при чтении из файла: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}
		   //---------------------------------------------------------------------------------------------------------------------------
	private: System::Void buttonReadFromFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ filenameTextBoxToRead = textBoxFilename->Text;

		if (filenameTextBoxToRead->Trim() == "") {
			MessageBox::Show("Имя файла не может быть пустым.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::string filename = msclr::interop::marshal_as<std::string>(filenameTextBoxToRead);
		std::string fullPath = "C:\\" + filename;

		try {
			System::IO::StreamReader^ inFile = gcnew System::IO::StreamReader(gcnew System::String(fullPath.c_str()), System::Text::Encoding::UTF8);

			if (inFile->BaseStream->CanRead) {
				MessageBox::Show("Файл '" + filenameTextBoxToRead + "' успешно открыт для чтения.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

				textBoxOutput->Text = "";
				// Чтение из файла
				while (!inFile->EndOfStream) {
					System::String^ line = inFile->ReadLine();
					textBoxOutput->Text += line + "\r\n";
				}

				inFile->Close();
			}
			else {
				MessageBox::Show("Не удалось открыть файл для чтения.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при чтении из файла: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}
	private: System::Void buttonCreateSecondFile_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(openedFileName)) {
			MessageBox::Show("Сначала откройте файл.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		System::String^ fullPath = "C:\\" + openedFileName;
		System::IO::StreamReader^ originalFile = gcnew System::IO::StreamReader(fullPath);
		try {

			if (originalFile->BaseStream->CanRead) {

				System::String^ secondFileName = textBoxFilename->Text;

				if (secondFileName->Trim() == "temp.txt") {
					MessageBox::Show("Нельзя использовать данное имя для создания файла.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}

				// Открываем второй файл для записи
				System::IO::StreamWriter^ secondFile = gcnew System::IO::StreamWriter("C:\\" + secondFileName);

				if (secondFile->BaseStream->CanWrite) {
					// Читаем данные из исходного файла и записываем во второй файл
					while (!originalFile->EndOfStream) {
						System::String^ line = originalFile->ReadLine();
						secondFile->WriteLine(line);
					}

					// Закрываем файлы
					originalFile->Close();
					secondFile->Close();

					MessageBox::Show("Второй файл успешно создан на основе исходного.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Не удалось открыть второй файл для записи.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					originalFile->Close();
					return;
				}
			}
			else {
				MessageBox::Show("Не удалось открыть исходный файл.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при чтении из файла: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		finally {
			originalFile->Close();
		}
	}
		   System::String^ TruncateOrPad(System::String^ input, int length) {
			   if (input->Length > length) {
				   return input->Substring(0, length);
			   }
			   else {
				   return input->PadRight(length);
			   }
		   }
	private: System::Void buttonAddToFile_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(openedFileName)) {
			MessageBox::Show("Сначала откройте файл.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		System::String^ fullPath = "C:\\" + openedFileName;
		System::IO::StreamWriter^ outFile = gcnew System::IO::StreamWriter(fullPath, true);
		try {
			Game newGame;

			// Используем MessageBox для ввода данных
			newGame.title = gameNameTextBox->Text;

			// Ввод данных о месте на диске
			System::String^ diskSpaceInput = gameSizeTextBox->Text;

			try {
				newGame.diskSpaceMB = System::Convert::ToInt32(diskSpaceInput);

				if (newGame.diskSpaceMB <= 0) {
					throw gcnew System::FormatException("Ошибка: введите положительное число.");
				}
			}
			catch (System::FormatException^) {
				MessageBox::Show("Ошибка: введено не число или отрицательное значение.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Ввод данных о графике
			newGame.graphicsQuality = gameQualityTextBox->Text;

			if (newGame.graphicsQuality != "хорошая" && newGame.graphicsQuality != "плохая") {
				MessageBox::Show("Пожалуйста введите данные о графике в формате: хорошая/плохая", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
				TruncateOrPad(newGame.title, 50),
				TruncateOrPad(newGame.graphicsQuality, 50),
				TruncateOrPad(System::Convert::ToString(newGame.diskSpaceMB), 50)));

			MessageBox::Show("Запись успешно добавлена в файл.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при добавлении записи в файл: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			outFile->Close();
		}
	}
	private: System::Void buttonDeleteFromFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ fullPath = "C:\\" + openedFileName;
		System::String^ tempPath = "C:\\temp.txt";

		System::IO::StreamReader^ inFile = gcnew System::IO::StreamReader(fullPath);
		System::IO::StreamWriter^ outFile = gcnew System::IO::StreamWriter(tempPath, true);
		try {

			if (!inFile->BaseStream->CanRead || !outFile->BaseStream->CanWrite) {
				MessageBox::Show("Не удалось открыть файл для удаления записи.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				inFile->Close();
				outFile->Close();
				System::IO::File::Delete(fullPath);
				return;
			}

			// Пропустить заголовочную строку
			String^ header = inFile->ReadLine();

			String^ titleToDelete;
			bool found = false;

			titleToDelete = nameToDeleteTextBox->Text;

			Game game;

			outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
				TruncateOrPad("Название игры", 50),
				TruncateOrPad("Графика игры", 50),
				TruncateOrPad("Размер на диске в МБ", 50)));

			while (!inFile->EndOfStream) {
				String^ line = inFile->ReadLine();
				List<String^>^ columns = gcnew List<String^>(line->Split('\t', '|'));

				if (columns->Count == 5) {
					game.title = columns[0]->Trim();
					game.graphicsQuality = columns[2]->Trim();
					game.diskSpaceMB = System::Convert::ToInt32(columns[4]->Trim());

					if (game.title == titleToDelete) {
						found = true;
					}
					else {
						outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
							TruncateOrPad(game.title, 50),
							TruncateOrPad(game.graphicsQuality, 50),
							TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
					}
				}
			}

			inFile->Close();
			outFile->Close();

			if (found) {
				if (System::IO::File::Exists(fullPath) && System::IO::File::Exists(tempPath)) {
					System::IO::File::Delete(fullPath);
					System::IO::File::Move(tempPath, fullPath);
					MessageBox::Show("Запись с названием '" + titleToDelete + "' удалена успешно.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Ошибка при замене файла.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					inFile->Close();
					outFile->Close();
					System::IO::File::Delete(fullPath);
					return;
				}
			}
			else {
				MessageBox::Show("Запись не найдена.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
				inFile->Close();
				outFile->Close();
				System::IO::File::Delete(fullPath);
				return;
			}
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при удалении записи из файла: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			inFile->Close();
			outFile->Close();
			System::IO::File::Delete(fullPath);
			return;
		}
		finally {
			inFile->Close();
			outFile->Close();
		}
	}
	private: System::Void buttonModifyFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ fullPath = "C:\\" + openedFileName;

		System::IO::StreamReader^ inFile = nullptr;
		System::IO::StreamWriter^ outFile = nullptr;

		try {
			inFile = gcnew System::IO::StreamReader(fullPath);
			outFile = gcnew System::IO::StreamWriter("C:\\temp.txt", true);

			if (!inFile->BaseStream->CanRead || !outFile->BaseStream->CanWrite) {
				MessageBox::Show("Не удалось открыть файл для редактирования записей.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				inFile->Close();
				outFile->Close();
				System::IO::File::Delete("C:\\temp.txt");
				return;
			}

			// Пропустить заголовочную строку
			String^ header = inFile->ReadLine();

			String^ fieldToEdit;
			String^ searchKey;
			String^ newValue;
			bool found = false;

			fieldToEdit = fieldToEditTextBox->Text;

			Game game;
			outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
				TruncateOrPad("Название игры", 50),
				TruncateOrPad("Графика игры", 50),
				TruncateOrPad("Размер на диске в МБ", 50)));

			if (fieldToEdit == "название") {
				searchKey = OldValueTextBox->Text;
				newValue = NewValueTextBox->Text;

				while (!inFile->EndOfStream) {
					String^ line = inFile->ReadLine();
					List<String^>^ columns = gcnew List<String^>(line->Split('\t', '|'));

					if (columns->Count == 5) {
						game.title = columns[0]->Trim();
						game.diskSpaceMB = System::Convert::ToInt32(columns[4]->Trim());
						game.graphicsQuality = columns[2]->Trim();

						if (game.title == searchKey) {
							found = true;
							game.title = newValue;

							outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
								TruncateOrPad(game.title, 50),
								TruncateOrPad(game.graphicsQuality, 50),
								TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
						}
						else {
							outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
								TruncateOrPad(game.title, 50),
								TruncateOrPad(game.graphicsQuality, 50),
								TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
						}
					}
				}
			}
			else if (fieldToEdit == "память") {
				int searchValue;
				while (true) {
					searchValue = System::Convert::ToInt32(OldValueTextBox->Text);

					if (searchValue > 0) {
						break;
					}
					else {
						MessageBox::Show("Ошибка: введите положительное число.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
						inFile->Close();
						outFile->Close();
						System::IO::File::Delete("C:\\temp.txt");
						return;
					}
				}

				int newValue;
				while (true) {
					newValue = System::Convert::ToInt32(NewValueTextBox->Text);

					if (newValue > 0) {
						break;
					}
					else {
						MessageBox::Show("Ошибка: введите положительное число.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
						inFile->Close();
						outFile->Close();
						System::IO::File::Delete("C:\\temp.txt");
						return;
					}
				}

				while (!inFile->EndOfStream) {
					String^ line = inFile->ReadLine();
					List<String^>^ columns = gcnew List<String^>(line->Split('\t', '|'));

					if (columns->Count == 5) {
						game.title = columns[0]->Trim();
						game.diskSpaceMB = System::Convert::ToInt32(columns[4]->Trim());
						game.graphicsQuality = columns[2]->Trim();

						if (game.diskSpaceMB == searchValue) {
							found = true;
							game.diskSpaceMB = newValue;

							outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
								TruncateOrPad(game.title, 50),
								TruncateOrPad(game.graphicsQuality, 50),
								TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
						}
						else {
							outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
								TruncateOrPad(game.title, 50),
								TruncateOrPad(game.graphicsQuality, 50),
								TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
						}
					}
				}
			}
			else if (fieldToEdit == "графика") {
				searchKey = OldValueTextBox->Text;

				while (searchKey != "плохая" && searchKey != "хорошая") {
					MessageBox::Show("Ошибка: качество графики должно быть в формате плохая/хорошая.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					inFile->Close();
					outFile->Close();
					System::IO::File::Delete("C:\\temp.txt");
					return;
				}

				newValue = NewValueTextBox->Text;

				while (newValue != "плохая" && newValue != "хорошая") {
					MessageBox::Show("Ошибка: качество графики должно быть в формате плохая/хорошая.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
					inFile->Close();
					outFile->Close();
					System::IO::File::Delete("C:\\temp.txt");
					return;
				}

				while (!inFile->EndOfStream) {
					String^ line = inFile->ReadLine();
					List<String^>^ columns = gcnew List<String^>(line->Split('\t', '|'));

					if (columns->Count == 5) {
						game.title = columns[0]->Trim();
						game.diskSpaceMB = System::Convert::ToInt32(columns[4]->Trim());
						game.graphicsQuality = columns[2]->Trim();

						if (game.graphicsQuality == searchKey) {
							found = true;
							game.graphicsQuality = newValue;

							outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
								TruncateOrPad(game.title, 50),
								TruncateOrPad(game.graphicsQuality, 50),
								TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
						}
						else {
							outFile->WriteLine(String::Format("{0}\t|{1}\t|{2}",
								TruncateOrPad(game.title, 50),
								TruncateOrPad(game.graphicsQuality, 50),
								TruncateOrPad(System::Convert::ToString(game.diskSpaceMB), 50)));
						}
					}
				}
			}
			else {
				MessageBox::Show("Некорректное поле для редактирования.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				inFile->Close();
				outFile->Close();
				System::IO::File::Delete("C:\\temp.txt");
				return;
			}

			inFile->Close();
			outFile->Close();

			if (found) {
				System::IO::File::Delete(fullPath);
				System::IO::File::Move("C:\\temp.txt", fullPath);
				MessageBox::Show("Запись успешно отредактирована.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				System::IO::File::Delete("C:\\temp.txt");
				MessageBox::Show("Запись не найдена.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
				inFile->Close();
				outFile->Close();
				System::IO::File::Delete("C:\\temp.txt");
				return;
			}
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при редактировании записи: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			inFile->Close();
			outFile->Close();
			System::IO::File::Delete("C:\\temp.txt");
			return;
		}
		finally {
			inFile->Close();
			outFile->Close();
		}
	}
	private: System::Void buttonSearchInFile_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ fullPath = "C:\\" + openedFileName;

		try {
			System::IO::StreamReader^ inFile = gcnew System::IO::StreamReader(fullPath);

			if (!inFile->BaseStream->CanRead) {
				MessageBox::Show("Не удается открыть файл для поиска данных.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Пропустить заголовочную строку
			String^ header = inFile->ReadLine();

			String^ fieldToSearch;
			String^ searchKey;

			fieldToSearch = fieldToSearchTextBox->Text;

			Game game;
			bool found = false;

			textBoxOutput->Text = "";
			textBoxOutput->Text += header + "\r\n";
			while (!inFile->EndOfStream) {
				String^ line = inFile->ReadLine();
				List<String^>^ columns = gcnew List<String^>(line->Split('\t', '|'));

				if (columns->Count == 5) {
					game.title = columns[0]->Trim();
					game.diskSpaceMB = System::Convert::ToInt32(columns[4]->Trim());
					game.graphicsQuality = columns[2]->Trim();

					if (fieldToSearch == "название") {
						searchKey = valueToSearchTextBox->Text;
						if (game.title == searchKey) {
							found = true;
							textBoxOutput->Text += line + "\r\n";
						}
					}
					else if (fieldToSearch == "память") {
						int searchValue;
						if (Int32::TryParse(valueToSearchTextBox->Text, searchValue) && searchValue > 0) {
							if (game.diskSpaceMB == searchValue) {
								found = true;
								textBoxOutput->Text += line + "\r\n";
							}
						}
						else {
							MessageBox::Show("Ошибка: введите положительное число.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
							return;
						}
					}
					else if (fieldToSearch == "графика") {
						searchKey = valueToSearchTextBox->Text;
						if (game.graphicsQuality == searchKey) {
							found = true;
							textBoxOutput->Text += line + "\r\n";
						}
					}
					else {
						MessageBox::Show("Некорректное поле для поиска.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}
				}
			}

			if (!found) {
				MessageBox::Show("Запись не найдена.", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			inFile->Close();
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Ошибка при поиске записи в файле: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}
	private: System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	};
}
