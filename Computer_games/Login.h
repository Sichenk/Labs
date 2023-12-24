#pragma once
#include "Games.h"

namespace Computergames {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Login : public System::Windows::Forms::Form
	{
	public:
		Login(void)
		{
			InitializeComponent();
		}

	protected:
		~Login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonLogin;
	private: System::Windows::Forms::Label^ authorization;
	private: System::Windows::Forms::Button^ buttonClose;
	private: System::Windows::Forms::Label^ name;
	private: System::Windows::Forms::Label^ password;
	private: System::Windows::Forms::TextBox^ textBoxLogin;
	private: System::Windows::Forms::TextBox^ textBoxPassword;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Login::typeid));
			this->buttonLogin = (gcnew System::Windows::Forms::Button());
			this->authorization = (gcnew System::Windows::Forms::Label());
			this->buttonClose = (gcnew System::Windows::Forms::Button());
			this->name = (gcnew System::Windows::Forms::Label());
			this->password = (gcnew System::Windows::Forms::Label());
			this->textBoxLogin = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// buttonLogin
			// 
			this->buttonLogin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonLogin->Location = System::Drawing::Point(556, 342);
			this->buttonLogin->Name = L"buttonLogin";
			this->buttonLogin->Size = System::Drawing::Size(205, 60);
			this->buttonLogin->TabIndex = 10;
			this->buttonLogin->Text = L"Войти\r\n";
			this->buttonLogin->UseVisualStyleBackColor = true;
			this->buttonLogin->Click += gcnew System::EventHandler(this, &Login::buttonLogin_Click);
			// 
			// authorization
			// 
			this->authorization->AutoSize = true;
			this->authorization->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->authorization->Location = System::Drawing::Point(285, 9);
			this->authorization->Name = L"authorization";
			this->authorization->Size = System::Drawing::Size(166, 29);
			this->authorization->TabIndex = 11;
			this->authorization->Text = L"Авторизация";
			// 
			// buttonClose
			// 
			this->buttonClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonClose->Location = System::Drawing::Point(12, 342);
			this->buttonClose->Name = L"buttonClose";
			this->buttonClose->Size = System::Drawing::Size(205, 60);
			this->buttonClose->TabIndex = 12;
			this->buttonClose->Text = L"Закрыть\r\n";
			this->buttonClose->UseVisualStyleBackColor = true;
			this->buttonClose->Click += gcnew System::EventHandler(this, &Login::buttonClose_Click);
			// 
			// name
			// 
			this->name->AutoSize = true;
			this->name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name->Location = System::Drawing::Point(12, 141);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(240, 29);
			this->name->TabIndex = 13;
			this->name->Text = L"Имя пользователя:";
			// 
			// password
			// 
			this->password->AutoSize = true;
			this->password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->password->Location = System::Drawing::Point(147, 204);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(105, 29);
			this->password->TabIndex = 14;
			this->password->Text = L"Пароль:";
			// 
			// textBoxLogin
			// 
			this->textBoxLogin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxLogin->Location = System::Drawing::Point(268, 138);
			this->textBoxLogin->Name = L"textBoxLogin";
			this->textBoxLogin->Size = System::Drawing::Size(294, 35);
			this->textBoxLogin->TabIndex = 15;
			// 
			// textBoxPassword
			// 
			this->textBoxPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxPassword->Location = System::Drawing::Point(268, 204);
			this->textBoxPassword->Name = L"textBoxPassword";
			this->textBoxPassword->Size = System::Drawing::Size(294, 35);
			this->textBoxPassword->TabIndex = 16;
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->ClientSize = System::Drawing::Size(773, 414);
			this->Controls->Add(this->textBoxPassword);
			this->Controls->Add(this->textBoxLogin);
			this->Controls->Add(this->password);
			this->Controls->Add(this->name);
			this->Controls->Add(this->buttonClose);
			this->Controls->Add(this->authorization);
			this->Controls->Add(this->buttonLogin);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Login";
			this->Text = L"Log in";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		const int SIZE = 901;

		int hashFunction(String^ str) {
			int hash = 0;
			for (int i = 0; i < str->Length; ++i) {
				hash += (i + 1) * static_cast<size_t>(str[i]);
			}
			return hash % SIZE;
		}

		bool checkUser(int userHash, int passwordHash) {
			return (userHash == hashFunction("user") &&
				passwordHash == hashFunction("password"));
		}

	private: System::Void buttonLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ login = textBoxLogin->Text;
		String^ password = textBoxPassword->Text;

		int userHash = hashFunction(login);
		int passwordHash = hashFunction(password);

		if (checkUser(userHash, passwordHash)) {
			// Вход выполнен успешно
			Games^ games = gcnew Games();
			games->Show();
			Login::Hide();
		}
		else {
			// Неверные логин или пароль
			MessageBox::Show("Неверный логин или пароль");
		}
	}
	private: System::Void buttonClose_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	};
}

