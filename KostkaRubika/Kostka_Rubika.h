#pragma once
#include "Kostka1.h"
#include <string>

namespace KostkaRubika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Data::SqlClient;
	using namespace System::Data::Odbc;


	
	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class Kostka_Rubika : public System::Windows::Forms::Form
	{
	private:
		int sec = 0, min = 0;
		int szift = 0;
		double skala;
		Kostka1* kostek;
		String^ loginek;
		bool database_on_2;
	public:
		Kostka_Rubika(String^ xd, bool database_on_temp)
		{
			loginek = xd;
			database_on_2 = database_on_temp;
			kostek = new Kostka1(0);
			InitializeComponent();
		}


	protected:
		~Kostka_Rubika()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		void top()
		{
			toolStripMenuItem3->Text = "brak";
			toolStripMenuItem4->Text = "brak";
			toolStripMenuItem5->Text = "brak";
			if (database_on_2 == true)
			{
				try
				{
					SqlConnection^ Database = gcnew SqlConnection("Server=tcp:kostkarubika.database.windows.net,1433;Initial Catalog=KostkaRubika;Persist Security Info=False;User ID=Rubik;Password=Haslo1234;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;");
					SqlCommand^ cmd = gcnew SqlCommand("select top 3 login , \"" + kostek->size + "\" from Logowanie WHERE \"" + kostek->size + "\" >= 0 order by \"" + kostek->size + "\"", Database);
					Database->Open();
					SqlDataReader^ rider = cmd->ExecuteReader();
					rider->Read();
					int x = rider->GetInt32(1);
					int y = x / 60;
					toolStripMenuItem3->Text = rider->GetString(0) + " || " + y + "m " + x % 60 + "s";
					rider->Read();
					x = rider->GetInt32(1);
					toolStripMenuItem4->Text = rider->GetString(0) + " || " + y + "m " + x % 60 + "s";
					rider->Read();
					x = rider->GetInt32(1);
					toolStripMenuItem5->Text = rider->GetString(0) + " || " + y + "m " + x % 60 + "s";
					Database->Close();
				}
				catch (Exception^) {}
			}
		}
		void sprawdz()
		{
			if (kostek->check() == 9999)
			{
				timer1->Stop();
				MessageBox::Show("Twój czas to: \n" + min.ToString() + " minut i " + sec.ToString() + " sekund", "Gratulacje");
				//
				int x;
				x = min * 60 + sec;
				if (database_on_2 == true)
				{
					SqlConnection^ Database = gcnew SqlConnection("Server=tcp:kostkarubika.database.windows.net,1433;Initial Catalog=KostkaRubika;Persist Security Info=False;User ID=Rubik;Password=Haslo1234;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;");
					SqlCommand^ cmd = gcnew SqlCommand("Select \"" + kostek->size + "\" FROM Logowanie", Database);
					Database->Open();
					// czy jest kolumna
					try
					{
						Int32 ret = cmd->ExecuteNonQuery();
						if (ret != 1)
						{
							//MessageBox::Show("Kolomna ju¿ jest");

							SqlCommand^ rider = gcnew SqlCommand("select \"" + kostek->size + "\" from Logowanie Where login = '" + loginek + "'", Database);
							Database->Close();
							Database->Open();
							SqlDataReader^ rdr = rider->ExecuteReader();
							// czy rekord pobity
							rdr->Read();
							int nazwa;
							try {
								nazwa = rdr->GetInt32(0);
							}
							catch (Exception^) {
								nazwa = INT32_MAX;
							}
							if (nazwa > x)
							{
								Database->Close();
								Database->Open();
								MessageBox::Show("Brawo pobi³eœ swój czas");
								SqlCommand^ cmd2 = gcnew SqlCommand("UPDATE Logowanie set \"" + kostek->size + "\" = " + x + " WHERE login = '" + loginek + "'", Database);
								cmd2->ExecuteNonQuery();
							}
							else
							{
								MessageBox::Show("s³abo");
							}
						}
					}
					catch (Exception^)
					{
						//MessageBox::Show("Tworzenie kolumny");

						SqlCommand^ cmd = gcnew SqlCommand("ALTER TABLE Logowanie ADD \"" + kostek->size + "\" int", Database);
						cmd->ExecuteNonQuery();
						Database->Close();
						Database->Open();
						SqlCommand^ rider = gcnew SqlCommand("select \"" + kostek->size + "\" from Logowanie Where login = '" + loginek + "'", Database);
						Database->Close();
						Database->Open();
						SqlDataReader^ rdr = rider->ExecuteReader();
						rdr->Read();
						int nazwa;
						try {
							nazwa = rdr->GetInt32(0);
						}
						catch (Exception^) {
							nazwa = INT32_MAX;
						}
						if (nazwa > x)
						{
							Database->Close();
							Database->Open();
							MessageBox::Show("Brawo pobi³eœ swój czas");
							SqlCommand^ cmd2 = gcnew SqlCommand("UPDATE Logowanie set \"" + kostek->size + "\" = " + x + " WHERE login = '" + loginek + "'", Database);
							cmd2->ExecuteNonQuery();
						}
						else
						{
							MessageBox::Show("s³abo");
						}
					}
				}

				czy_otwarte = 0;
				sec = 0;
				min = 0;
				delete kostek;
				pictureBox1->Hide();
				this->ClientSize = System::Drawing::Size(285, 307);
				label1->Show();
				button1->Show();
				numericUpDown1->Show();
			}
		}
		int czy_otwarte = 0;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;

	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^ zmianaRozmiaruToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem5;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;



	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zmianaRozmiaruToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(85, 77);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Wprowadz wymiary";
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button1->Location = System::Drawing::Point(97, 149);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Gotowe";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Kostka_Rubika::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 24);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(284, 262);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 32;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Kostka_Rubika::pictureBox1_Paint);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(97, 109);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(75, 20);
			this->numericUpDown1->TabIndex = 1;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Kostka_Rubika::numericUpDown1_ValueChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem1,
					this->toolStripMenuItem2, this->zmianaRozmiaruToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(284, 24);
			this->menuStrip1->TabIndex = 34;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem3,
					this->toolStripMenuItem4, this->toolStripMenuItem5
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(62, 20);
			this->toolStripMenuItem1->Text = L"Ranking";
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(97, 22);
			this->toolStripMenuItem3->Text = L"brak";
			this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &Kostka_Rubika::toolStripMenuItem3_Click);
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(97, 22);
			this->toolStripMenuItem4->Text = L"brak";
			// 
			// toolStripMenuItem5
			// 
			this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
			this->toolStripMenuItem5->Size = System::Drawing::Size(97, 22);
			this->toolStripMenuItem5->Text = L"brak";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(57, 20);
			this->toolStripMenuItem2->Text = L"Pomoc";
			this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &Kostka_Rubika::toolStripMenuItem2_Click);
			// 
			// zmianaRozmiaruToolStripMenuItem
			// 
			this->zmianaRozmiaruToolStripMenuItem->Name = L"zmianaRozmiaruToolStripMenuItem";
			this->zmianaRozmiaruToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->zmianaRozmiaruToolStripMenuItem->Text = L"Rozmiar";
			this->zmianaRozmiaruToolStripMenuItem->Click += gcnew System::EventHandler(this, &Kostka_Rubika::zmianaRozmiaruToolStripMenuItem_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Kostka_Rubika::timer1_Tick);
			// 
			// Kostka_Rubika
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::CornflowerBlue;
			this->ClientSize = System::Drawing::Size(284, 286);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Kostka_Rubika";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Kostka_Rubika";
			this->Load += gcnew System::EventHandler(this, &Kostka_Rubika::Kostka_Rubika_Load);
			this->SizeChanged += gcnew System::EventHandler(this, &Kostka_Rubika::Kostka_Rubika_SizeChanged);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Kostka_Rubika::Kostka_Rubika_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Kostka_Rubika::Kostka_Rubika_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Kostka_Rubika::Kostka_Rubika_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		kostek = new Kostka1(int(numericUpDown1->Value));
		top();
		kostek->losuj();
		czy_otwarte = 1;
		label1->Hide();
		button1->Hide();
		numericUpDown1->Hide();
		MessageBox::Show("Gotowy ?");
		timer1->Start();
		pictureBox1->Show();
		if (kostek->size < 8)
		{
			this->ClientSize = System::Drawing::Size(285 + (90 * (kostek->size - 3)), 307 + (90 * (kostek->size - 3)));
		}
		if (kostek->size >= 8)
		{
			this->ClientSize = System::Drawing::Size(285 + (90 * 4), 307 + (90 * 4));

		}
		this->Refresh();

	}
	private: System::Void Kostka_Rubika_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

	}
	private: System::Void Kostka_Rubika_Load(System::Object^ sender, System::EventArgs^ e) {
		KeyPreview = true;
	}
	private: System::Void Kostka_Rubika_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ShiftKey)
		{
			szift = 1;
		}
		if (e->KeyCode == Keys::Space && szift == 0)
		{
			kostek->RuchF();
			this->Refresh();
		}
		if (e->KeyCode == Keys::Space && szift == 1)
		{
			kostek->RuchF();
			kostek->RuchF();
			kostek->RuchF();
			this->Refresh();
			sprawdz();
		}
		if (e->KeyCode == Keys::A && szift == 0)
		{
			if (kostek->pozycjaY > 0)
			{
				kostek->pozycjaY--;
				this->Refresh();
			}
		}
		else if (e->KeyCode == Keys::A && szift == 1)
		{
			kostek->obrotkostkiR();
			kostek->obrotkostkiR();
			kostek->obrotkostkiR();
			this->Refresh();
		}
		if (e->KeyCode == Keys::W && szift == 0)
		{
			if (kostek->pozycjaX > 0)
			{
				kostek->pozycjaX--;
				this->Refresh();
			}
		}
		else if (e->KeyCode == Keys::W && szift == 1)
		{
			kostek->obrotkostkiU();
			this->Refresh();
		}
		if (e->KeyCode == Keys::S && szift == 0)
		{
			if (kostek->pozycjaX < kostek->size - 1)
			{
				kostek->pozycjaX++;
				this->Refresh();
			}
		}
		else if (e->KeyCode == Keys::S && szift == 1)
		{
			kostek->obrotkostkiU();
			kostek->obrotkostkiU();
			kostek->obrotkostkiU();
			this->Refresh();
		}
		if (e->KeyCode == Keys::D && szift == 0)
		{
			if (kostek->pozycjaY < kostek->size - 1)
			{
				kostek->pozycjaY++;
				this->Refresh();
			}
		}
		else if (e->KeyCode == Keys::D && szift == 1)
		{
			kostek->obrotkostkiR();
			this->Refresh();
		}
		if (e->KeyCode == Keys::J)
		{
			kostek->RuchX();
			this->Refresh();
			sprawdz();
		}
		if (e->KeyCode == Keys::I)
		{
			kostek->RuchY();
			this->Refresh();
			sprawdz();
		}
		if (e->KeyCode == Keys::K)
		{
			kostek->RuchY();
			kostek->RuchY();
			kostek->RuchY();
			this->Refresh();
			sprawdz();
		}
		if (e->KeyCode == Keys::L)
		{
			kostek->RuchX();
			kostek->RuchX();
			kostek->RuchX();
			this->Refresh();
			sprawdz();
		}
	}
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		if (kostek->size)
		{
			SolidBrush^ orangeBrush = gcnew SolidBrush(Color::DarkOrange);
			SolidBrush^ blueBrush = gcnew SolidBrush(Color::Blue);
			SolidBrush^ redBrush = gcnew SolidBrush(Color::Red);
			SolidBrush^ yellowBrush = gcnew SolidBrush(Color::Gold);
			SolidBrush^ whiteBrush = gcnew SolidBrush(Color::White);
			SolidBrush^ greenBrush = gcnew SolidBrush(Color::Green);
			SolidBrush^ magentaBrush = gcnew SolidBrush(Color::Magenta);
			// tworzenie obiektu
			float x = -40;
			float y = (90 * (kostek->size - 3)) - 25;
			float rozmiar = kostek->size;
			if (kostek->size > 7)
			{
				skala = 7 / (rozmiar);
			}
			else
			{
				skala = 1;
			}

			Point pointLG = Point((45 + x + (kostek->pozycjaY * 60)) * skala, (245 - 60 * (kostek->size - 1) + y + (kostek->pozycjaX * 60)) * skala);
			Point pointLD = Point((45 + x + (kostek->pozycjaY * 60)) * skala, (305 - 60 * (kostek->size - 1) + y + (kostek->pozycjaX * 60)) * skala);
			Point pointPD = Point((105 + x + (kostek->pozycjaY * 60)) * skala, (305 - 60 * (kostek->size - 1) + y + (kostek->pozycjaX * 60)) * skala);
			Point pointPG = Point((105 + x + (kostek->pozycjaY * 60)) * skala, (245 - 60 * (kostek->size - 1) + y + (kostek->pozycjaX * 60)) * skala);

			array<Point>^ tablicaPKT = { pointLG,pointLD,pointPD,pointPG };

			e->Graphics->FillPolygon(magentaBrush, tablicaPKT);

			for (int j = 0; j < kostek->size; j++)
			{
				for (int i = 0; i < kostek->size; i++)
				{
					Point pointLG = Point((50 + i * 60 + x) * skala, (250 - j * 60 + y) * skala);
					Point pointLD = Point((50 + i * 60 + x) * skala, (300 - j * 60 + y) * skala);
					Point pointPD = Point((100 + i * 60 + x) * skala, (300 - j * 60 + y) * skala);
					Point pointPG = Point((100 + i * 60 + x) * skala, (250 - j * 60 + y) * skala);

					array<Point>^ tablicaPKT = { pointLG,pointLD,pointPD,pointPG };

					switch (kostek->orange[kostek->size - 1 - j][i]) {
					case('o'):
						e->Graphics->FillPolygon(orangeBrush, tablicaPKT);
						break;
					case('g'):
						e->Graphics->FillPolygon(greenBrush, tablicaPKT);
						break;
					case('b'):
						e->Graphics->FillPolygon(blueBrush, tablicaPKT);
						break;
					case('w'):
						e->Graphics->FillPolygon(whiteBrush, tablicaPKT);
						break;
					case('y'):
						e->Graphics->FillPolygon(yellowBrush, tablicaPKT);
						break;
					case('r'):
						e->Graphics->FillPolygon(redBrush, tablicaPKT);
						break;
					}
				}
				for (int i = 0; i < kostek->size; i++)
				{
					Point pointLG = Point((50 + kostek->size * 60 + i * 30 + x) * skala, (250 - j * 60 - i * 30 + y) * skala);
					Point pointLD = Point((50 + kostek->size * 60 + i * 30 + x) * skala, (300 - j * 60 - i * 30 + y) * skala);
					Point pointPD = Point((50 + kostek->size * 60 + 25 + i * 30 + x) * skala, (275 - j * 60 - i * 30 + y) * skala);
					Point pointPG = Point((50 + kostek->size * 60 + 25 + i * 30 + x) * skala, (225 - j * 60 - i * 30 + y) * skala);

					array<Point>^ tablicaPKT = { pointLG,pointLD,pointPD,pointPG };
					switch (kostek->blue[kostek->size - 1 - j][i]) {
					case('o'):
						e->Graphics->FillPolygon(orangeBrush, tablicaPKT);
						break;
					case('g'):
						e->Graphics->FillPolygon(greenBrush, tablicaPKT);
						break;
					case('b'):
						e->Graphics->FillPolygon(blueBrush, tablicaPKT);
						break;
					case('w'):
						e->Graphics->FillPolygon(whiteBrush, tablicaPKT);
						break;
					case('y'):
						e->Graphics->FillPolygon(yellowBrush, tablicaPKT);
						break;
					case('r'):
						e->Graphics->FillPolygon(redBrush, tablicaPKT);
						break;
					}

					pointLG = Point((75 + 2 + i * 60 + j * 30 + x) * skala, (250 - kostek->size * 60 + 25 - j * 30 + y) * skala);
					pointLD = Point((50 + 2 + i * 60 + j * 30 + x) * skala, (300 - kostek->size * 60 - j * 30 + y) * skala);
					pointPD = Point((100 + 2 + i * 60 + j * 30 + x) * skala, (300 - kostek->size * 60 - j * 30 + y) * skala);
					pointPG = Point((125 + 2 + i * 60 + j * 30 + x) * skala, (250 - kostek->size * 60 + 25 - j * 30 + y) * skala);

					array<Point>^ tablicaPKT2 = { pointLG,pointLD,pointPD,pointPG };
					switch (kostek->yellow[kostek->size - 1 - j][i]) {
					case('o'):
						e->Graphics->FillPolygon(orangeBrush, tablicaPKT2);
						break;
					case('g'):
						e->Graphics->FillPolygon(greenBrush, tablicaPKT2);
						break;
					case('b'):
						e->Graphics->FillPolygon(blueBrush, tablicaPKT2);
						break;
					case('w'):
						e->Graphics->FillPolygon(whiteBrush, tablicaPKT2);
						break;
					case('y'):
						e->Graphics->FillPolygon(yellowBrush, tablicaPKT2);
						break;
					case('r'):
						e->Graphics->FillPolygon(redBrush, tablicaPKT2);
						break;
					}
				}
			}
		}

	}
	private: System::Void Kostka_Rubika_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ShiftKey)
		{
			szift = 0;
		}
	}
	private: System::Void Kostka_Rubika_SizeChanged(System::Object^ sender, System::EventArgs^ e) {
		this->Refresh();
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void toolStripComboBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void toolStripMenuItem3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		sec++;
		if (sec == 60)
		{
			min++;
			sec = sec - 60;
		}
	}
	private: System::Void zmianaRozmiaruToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (czy_otwarte == 1)
		{
			timer1->Stop();
			sec = 0;
			min = 0;
			delete kostek;
			pictureBox1->Hide();
			this->ClientSize = System::Drawing::Size(285, 307);
			label1->Show();
			button1->Show();
			numericUpDown1->Show();
			czy_otwarte = 0;
		}
	}
	private: System::Void toolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("W,A,S,D <=> zmiana po³o¿enia\n\nI,J,K,L <=> obrót œcianki\n\nShift+W,A,S,D <=> Obrot kostki\n\nSpace <=> Obrót pierwszej œciany\n\nShift+Space <=> Powrót pierwszej œciany", "Pomoc");
	}
	};
}
