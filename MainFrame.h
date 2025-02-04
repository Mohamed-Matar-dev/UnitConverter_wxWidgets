#pragma once
#include <wx/wx.h>
#include "UnitType.h"


class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControl();
	void BindControl();
	void SetUpSizer();
	constexpr double CelsiusToFahrenheitF(double value);
	constexpr double FahrenheitToCelsiusF(double value);
	constexpr double KilometersToMilesF(double value);
	constexpr double MilesToKilometersF(double value);
	void OnComboBoxChange(wxCommandEvent& evt);
	void OnText1Change(wxCommandEvent& evt);
	void OnText2Change(wxCommandEvent& evt);

	wxPanel* panel;
	bool updating;
	wxComboBox* UnitSelected;
	wxTextCtrl* text1;
	wxTextCtrl* text2;
	wxString input;
	double convertedValue;
	wxStaticText* label1;
	wxStaticText* label2;
	
};

