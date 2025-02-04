#include "MainFrame.h"
#include <wx/wx.h>
#include "UnitType.h"



MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{	
	CreateControl();
	SetUpSizer();
	BindControl();
	
	
}

UnitType selectedUnit = CelsiusToFahrenheit;


void MainFrame::CreateControl()
{
	panel = new wxPanel(this);

	// ComboBox for Unit Selection
	UnitSelected = new wxComboBox(panel, wxID_ANY, "Select Conversion", wxDefaultPosition, wxSize(200, -1), 0,
		nullptr, wxCB_READONLY);
	

	// Text Controls for Input and Output
	text1 = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1),
		wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));
	text2 = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1),
		wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));

	// Labels for Input and Output Fields
	label1 = new wxStaticText(panel, wxID_ANY, "Celsius:");
	label2 = new wxStaticText(panel, wxID_ANY, "Fahrenheit:");
}

void MainFrame::SetUpSizer()
{
	// Create Vertical Box Sizer for Main Layout
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

	// Horizontal Sizer for First Row (Label and Text Control)
	wxBoxSizer* row1 = new wxBoxSizer(wxHORIZONTAL);
	row1->Add(label1, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
	row1->Add(text1, 1, wxEXPAND);

	// Horizontal Sizer for Second Row (Label and Text Control)
	wxBoxSizer* row2 = new wxBoxSizer(wxHORIZONTAL);
	row2->Add(label2, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
	row2->Add(text2, 1, wxEXPAND);

	// Add Components to the Main Vertical Sizer
	vbox->Add(UnitSelected, 0, wxALL | wxEXPAND, 15);
	vbox->Add(row1, 0, wxALL | wxEXPAND, 15);
	vbox->Add(row2, 0, wxALL | wxEXPAND, 15);

	panel->SetSizer(vbox);
}

void MainFrame::BindControl()
{
	
	UnitSelected->Append("Celsius to Fahrenheit");
	UnitSelected->Append("Kilometers to Miles");
	UnitSelected->SetValue("Celsius to Fahrenheit");
	

	UnitSelected->Bind(wxEVT_COMBOBOX, &MainFrame::OnComboBoxChange, this);
	text1->Bind(wxEVT_TEXT, &MainFrame::OnText1Change, this);
	text2->Bind(wxEVT_TEXT, &MainFrame::OnText2Change, this);
}

void MainFrame::OnText1Change(wxCommandEvent& evt)
{
	if (updating) return;  // Avoid recursive updates
	updating = true;
	input = text1->GetValue();
	double value;
	if (text1->GetValue().ToDouble(&value))
	{
		switch (selectedUnit) {
		case CelsiusToFahrenheit:
			convertedValue = CelsiusToFahrenheitF(value);
			text2->SetValue(wxString::Format(wxT("%.2f"), convertedValue));
			break;

		case KilometersToMiles:
			convertedValue = KilometersToMilesF(value);
			text2->SetValue(wxString::Format(wxT("%.2f"), convertedValue));
			break;
		
		}
	}
	updating = false;
}

void MainFrame::OnText2Change(wxCommandEvent& evt)
{
	if (updating) return;  // Avoid recursive updates
	updating = true;
	input = text2->GetValue();
	double value;
	if (text2->GetValue().ToDouble(&value))
	{
		switch (selectedUnit) {
		case CelsiusToFahrenheit:
			convertedValue = FahrenheitToCelsiusF(value);
			text1->SetValue(wxString::Format(wxT("%.2f"), convertedValue));
			break;
		case KilometersToMiles:
			convertedValue = MilesToKilometersF(value);
			text1->SetValue(wxString::Format(wxT("%.2f"), convertedValue));
			break;
		
		}
	}
	updating = false;
}

constexpr double MainFrame::CelsiusToFahrenheitF(double value)
{
	return (value * 1.8) + 32;
}

constexpr double MainFrame::FahrenheitToCelsiusF(double value)
{
	return (value - 32) / 1.8;
}

constexpr double MainFrame::KilometersToMilesF(double value)
{
	return value * 0.621;
}

constexpr double MainFrame::MilesToKilometersF(double value)
{
	return value * 1.609;
}

void MainFrame::OnComboBoxChange(wxCommandEvent& evt)
{
	if (UnitSelected->GetSelection() == 0) {
		selectedUnit = CelsiusToFahrenheit;
		label1->SetLabel("Celsius:");
		label2->SetLabel("Fahrenheit:");
	}
	else if (UnitSelected->GetSelection() == 1) {
		selectedUnit = KilometersToMiles;
		label1->SetLabel("Kilometer");
		label2->SetLabel("Miles");
	}

	panel->Layout();

}
