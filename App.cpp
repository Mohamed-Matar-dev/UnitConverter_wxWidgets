#include "App.h"
#include "MainFrame.h"


wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainframe = new MainFrame("Unit Converter");
	mainframe->SetClientSize(300, 200);
	mainframe->Center();
	mainframe->Show();

	return true;
}