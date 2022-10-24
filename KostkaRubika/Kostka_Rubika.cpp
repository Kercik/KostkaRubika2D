#include "Logowanie.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);
	KostkaRubika::Logowanie form;
	Application::Run(% form);
}
