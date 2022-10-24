#pragma once
#include "Kostka_Rubika.h"
#include "Rejestracja.h"

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
	/// Podsumowanie informacji o Logowanie
	/// </summary>
	public ref class Logowanie : public System::Windows::Forms::Form
	{
	private:
		bool database_on = true;
	public:
		Logowanie(void)
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
		~Logowanie()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;


		   Kostka_Rubika^ drugie_okno2;
		   Rejestracja^ okienko;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		   /// jej zawartoœci w edytorze kodu.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->SuspendLayout();
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(76, 37);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(100, 20);
			   this->textBox1->TabIndex = 0;
			   // 
			   // textBox2
			   // 
			   this->textBox2->Location = System::Drawing::Point(76, 63);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->PasswordChar = '*';
			   this->textBox2->Size = System::Drawing::Size(100, 20);
			   this->textBox2->TabIndex = 1;
			   this->textBox2->TextChanged += gcnew System::EventHandler(this, &Logowanie::textBox2_TextChanged);
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(76, 104);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(100, 23);
			   this->button1->TabIndex = 2;
			   this->button1->Text = L"Zaloguj";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Logowanie::button1_Click);
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(76, 215);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(100, 23);
			   this->button2->TabIndex = 3;
			   this->button2->Text = L"Zajerestruj sie";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Logowanie::button2_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(24, 43);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(29, 13);
			   this->label1->TabIndex = 4;
			   this->label1->Text = L"login";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(27, 69);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(32, 13);
			   this->label2->TabIndex = 5;
			   this->label2->Text = L"haslo";
			   // 
			   // Logowanie
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(284, 261);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->textBox1);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			   this->MaximizeBox = false;
			   this->MinimizeBox = false;
			   this->Name = L"Logowanie";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Logowanie";
			   this->Load += gcnew System::EventHandler(this, &Logowanie::Logowanie_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (database_on == true)
		{
			try
			{
				SqlConnection^ Database = gcnew SqlConnection("Server=tcp:kostkarubika.database.windows.net,1433;Initial Catalog=KostkaRubika;Persist Security Info=False;User ID=Rubik;Password=Haslo1234;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;");
				SqlCommand^ cmd = gcnew SqlCommand("SELECT haslo FROM Logowanie WHERE login = @login", Database);
				cmd->Parameters->AddWithValue("@login", textBox1->Text);
				Database->Open();
				SqlDataReader^ nazwa = cmd->ExecuteReader();
				if (nazwa->Read() && nazwa->GetSqlString(0) == textBox2->Text)
				{
					Database->Close();
					String^ loginek = textBox1->Text;
					drugie_okno2 = gcnew Kostka_Rubika(loginek, database_on);
					this->Hide();
					drugie_okno2->ShowDialog();
					this->Close();

				}
				else {
					Database->Close();
					textBox1->Text = "";
					textBox2->Text = "";
					MessageBox::Show("Niepoprawne dane logowania!");
				}

			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}
		else
		{
			String^ loginek = textBox1->Text;
			drugie_okno2 = gcnew Kostka_Rubika(loginek, database_on);
			this->Hide();
			drugie_okno2->ShowDialog();
			this->Close();
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		okienko = gcnew Rejestracja;
		this->Hide();
		okienko->ShowDialog();
		this->Close();
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Logowanie_Load(System::Object^ sender, System::EventArgs^ e) {
		textBox2->Hide();
		label2->Hide();
		button2->Hide();
		database_on = false;
	}
	};
}
