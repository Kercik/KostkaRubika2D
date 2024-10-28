#pragma once
#include "Kostka_Rubika.h"

namespace KostkaRubika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;
	using namespace System::Data::Odbc;
	/// <summary>
	/// Podsumowanie informacji o Rejestracja
	/// </summary>


	public ref class Rejestracja : public System::Windows::Forms::Form
	{
	private:
		bool database_on3 = true;
	public:
		Rejestracja(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~Rejestracja()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Button^ button1;

		Kostka_Rubika^ nazwa_okna;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Rejestracja::typeid));
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(92, 56);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 5;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(92, 30);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 4;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(92, 82);
			this->textBox3->Name = L"textBox3";
			this->textBox3->PasswordChar = '*';
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(27, 56);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(32, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"haslo";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"login";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 82);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(72, 13);
			this->label3->TabIndex = 11;
			this->label3->Text = L"powtorz haslo";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(92, 140);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Zarejestruj siê";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Rejestracja::button1_Click);
			// 
			// Rejestracja
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Rejestracja";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Rejestracja";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox2->Text != textBox3->Text)
		{
			MessageBox::Show("Hasla musza byc identyczne");
		}
		else if (textBox2->Text == "" || textBox1->Text == "")
		{
			MessageBox::Show("Uzupe³nij dane!!!");
		}
		else if (textBox2->Text->Length <5)
		{
			MessageBox::Show("Zbyt krótki login");
		}
		else if (textBox1->Text->Length < 5)
		{
			MessageBox::Show("Zbyt krótkie has³o");
		}
		else
		{
			try {
				SqlConnection^ Database = gcnew SqlConnection("Server=tcp:kostkarubika.database.windows.net,1433;Initial Catalog=KostkaRubika;Persist Security Info=False;User ID=Rubik;Password=Haslo1234;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;");
				SqlCommand^ cmd = gcnew SqlCommand("INSERT into Logowanie(login,haslo) VALUES('" + textBox1->Text + "','" + textBox2->Text + "')", Database);
				Database->Open();
				try
				{
					Int32 ret = cmd->ExecuteNonQuery();
					if (ret == 1)
					{

						MessageBox::Show("Utworzono konto");
						String^ loginek = textBox1->Text;
						nazwa_okna = gcnew Kostka_Rubika(loginek, database_on3);
						this->Hide();
						nazwa_okna->ShowDialog();
						this->Close();
					}
					else
						MessageBox::Show("B³¹d");
				}
				catch (Exception^)
				{
					MessageBox::Show("B³¹d wprowadzania nowego loginu.\nPrawdopodobnie login istnieje");
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	};
}
