#include "Result.h"
#include <Windows.h>
#include "Graph.h"

using namespace Курсовая;

Graph* resultGraph;
bool darkTheme;
Result::Result(Graph* g, bool darkThemeEnabled, bool primaMethod)
{
	resultGraph = g;
	primaMethod ? resultGraph->PrimaMethod() : resultGraph->KraskalsMethod();
	darkTheme = darkThemeEnabled;
	InitializeComponent();
	Result::Text = primaMethod ? "Решение методом Прима" : "Решение методом Краскала";

}
void Result::resultPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	Graphics^ panelGraphics = this->resultPanel->CreateGraphics();
	panelGraphics->Clear(darkTheme? Color::FromArgb(21, 21, 21) : Color::Silver);
	Result::BackColor = darkTheme? Color::FromArgb(41, 41, 44) : SystemColors::Control;
	minWeightLabel->ForeColor = darkTheme ? Color::Silver : Color::Black;
	panelGraphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;
	resultGraph->DrawGraph(panelGraphics, true, darkTheme? Brushes::White : Brushes::Black, true);
	minWeightLabel->Text = "Минимальный вес: " + resultGraph->GetMinWeight();
}
