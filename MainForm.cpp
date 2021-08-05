#include "MainForm.h"
#include <Windows.h>
#include "Graph.h"
#include "Result.h"
/*
MainForm - ������� ���� ����������, � ������� ����������
���� �����, ��� �������������� � ����� ������ �������.

���� MainForm.cpp �������� ����������� ������� ��������� ����
��������� � ������ ��������������� �������
*/
using namespace ��������;
using namespace std;

[STAThreadAttribute]

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	��������::MainForm form; //������� ������ �����...
	Application::Run(%form); //... � �������� ��
	return 0;
}

int tbTag = 1;
Graph gr; //����, � ������� �������� ������������

void valueBox_LostFocus(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ������ ������ �����������.
	  ��� ������ ������ ����������� �������� � ����������.
	  ���� ��� ���������, ��������������� ��� � ����� �����������
	  ����� ���������. ���� ���, ��������� ���������� � ������������ ������.
	*/
	TextBox^ tb = (TextBox^)sender;
	try
	{
		gr.UpdateEdge(Convert::ToInt32(tb->Tag), Convert::ToInt32(tb->Text)); //���������� �������� � �����
	}
	catch (const System::FormatException^)
	{
		tb->Undo();
		MessageBox::Show("�������� ������ ������.\n������� ������������� ��������.", "������", MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
	}
}

void MainForm::GraphMatrix_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	/*
	  ������� ��������� �������� � ������.
	  ��� ��������� ����������� ������ ��� ����������� �� ������������.
	  ���� ��� ���������, ��������������� ��� � ����� �����������
	  ����� ���������.
	*/
	int valueTag = gr.UpdateValue(e->RowIndex, e->ColumnIndex - 1, Convert::ToInt32(GraphMatrix[e->ColumnIndex, e->RowIndex]->Value));
	Convert::ToInt32(GraphMatrix[e->ColumnIndex, e->RowIndex]->Value);

	if (valueTag == -1)
	{
		MessageBox::Show("�� ������� �������������� �����.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	((TextBox^)panel1->Controls->Find(valueTag.ToString(), true)[0])->Text = GraphMatrix[e->ColumnIndex, e->RowIndex]->Value->ToString();
}
void MainForm::GraphMatrix_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e)
{
	/*
	  ������� ������ � �������.
	  ���� � ������ ���� �������� ������������ ������, 
	  ��������� ���������� � ��������� ��������� �� ������.
	*/
	MessageBox::Show("�������� ������ ������.\n������� ������������� ��������.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
	e->ThrowException = false;
	GraphMatrix->CancelEdit();
	e->Cancel; 
}
TextBox^ AddTextbox(Point pos, String^ value = "")
{
	/*
	   ������� ���������� ������ ����������.
	   ��� ������ ������� ��������� � �������� ����� � � �������� �������.
	   ���������� ������������� ���������� �����, ������������ ��� ����� 
	   � ������ (� ��� �� �������).
	*/
	TextBox^ tb = gcnew TextBox;
	tb->Location = Point(pos.X - 7, pos.Y + 5);
	tb->Size = System::Drawing::Size(27, 20);
	tb->MaxLength = 4;
	tb->BackColor = System::Drawing::SystemColors::ScrollBar;
	tb->Text = value;
	tb->LostFocus += gcnew EventHandler(valueBox_LostFocus);
	tb->Tag = tbTag;
	tb->Name = tbTag.ToString();
	++tbTag;
	return tb;
}

#pragma region ������
int temp1 = -1, temp2 = -1;
void MainForm::panel1_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������.
	  � ����������� �� ���������� ����������� ��� �����
	  � ���� ����� �������� ������������ �������,
	  ������� ����� ����������� �� ������.
	*/
	panel1->Select();
	Point mousePos = this->panel1->PointToClient(Cursor->Position);
	//���� ������ ������ "�������"
	if (this->NodeSelect->Enabled == false)
	{
		if (gr.detectNode(mousePos) >= 0)
		{
			MessageBox::Show(this, "� ���� ����� ��� ���� �������.", "������", MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return;
		}
		gr.AddNode(mousePos);	
		panel1->Invalidate();
	}
	//���� ������ ������ "�����"
	if (this->EdgeSelect->Enabled == false)
	{
		if (temp1 >= 0)
		{
			temp2 = gr.detectNode(mousePos);
			if (temp2 == -1)
				return;
			gr.SetNodeSelect(temp2, true);
		}
		else
		{
			temp1 = gr.detectNode(mousePos);
			if (temp1 == -1)
				return;
			gr.SetNodeSelect(temp1, true);
		}
		if (temp1 >= 0 && temp2 >= 0 && temp1 != temp2)
		{
			if (gr.CheckEdgeExistence(temp1, temp2))
			{
				temp1 = -1;
				temp2 = -1;
				return;
			}
			TextBox^ valueBox = AddTextbox(Point((gr.GetNode(temp1).X + gr.GetNode(temp2).X) / 2, (gr.GetNode(temp1).Y + gr.GetNode(temp2).Y) / 2));
			this->panel1->Controls->Add(valueBox);
			valueBox->Select();

			gr.AddEdge(temp1, temp2, Convert::ToInt32(valueBox->Tag));
			temp1 = -1;
			temp2 = -1;
		}
	}
}
void MainForm::panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	/*
	  ������ ��������� ������.
	  ��� ������������ ������� ����������� ��������� � �������� ������� ��������� � �����.
	  � ������ ������� ��������� ��� ������ ����� ������������ ������� ����
	  ��������� ������ �����������, ��� ��������� � ����������� ����������
	  � �������� �� ���. ��� �������������� ������ ���������
	  � �������� ������ ������ ��������� ��������� ��� ������ ������.
	*/
	Graphics^ g = this->panel1->CreateGraphics();
	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;
	g->Clear(MainForm::BackColor == SystemColors::Control? Color::Silver : Color::FromArgb(21,21,21));
	gr.DrawGraph(g);
	delete g;
}
#pragma endregion
#pragma region ������
void MainForm::EdgeSelect_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "�����".
	  ����������� ���� � ���������� ������ "�������".
	  �����, ��� ������ ������ ���������� �������� �����
	  ������ ������ �� ����� ��������� �� ���������
	  ��� ����� ������������ �����������
	  �������������.
	*/
	this->NodeSelect->Enabled = true;
	this->NodeSelect->FlatAppearance->BorderColor = Color::White;

	this->EdgeSelect->Enabled = false;
	this->EdgeSelect->FlatAppearance->BorderColor = Color::DimGray;
}
void MainForm::NodeSelect_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "�������".
	  ����������� ���� � ���������� ������ "�����".
	  �����, ��� ������ ������ ���������� �������� �����
	  ������ ������ �� ����� ��������� �� ���������
	  ��� ����� ������������ �����������
	  �������������.
	*/
	this->EdgeSelect->Enabled = true;
	this->EdgeSelect->FlatAppearance->BorderColor = Color::White;

	this->NodeSelect->Enabled = false;
	this->NodeSelect->FlatAppearance->BorderColor = Color::DimGray;

}
void MainForm::Rebuild_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "����������� ����".
	  ��������� ������ �� ������� ���������, �������
	  ����������� ������� DataTable � ������ ��
	  � �������� ��������� ������ ��� DataGridView.
	*/
	System::String^ t = gcnew System::String(" ");

	bool rowsCreated = false;
	DataTable^ dt = gcnew DataTable;
	DataRow^ row = dt->NewRow();
	dt->Columns->Add("#", String::typeid);
	dt->Columns["#"]->ReadOnly = true;

	for (int k = 0; k < gr.GetNodeAmount(); k++)
	{
		t = " ";
		t = t->Replace(' ', gr.GetNodeLetter(k));
		dt->Columns->Add(t, int::typeid);
	}
	for (int i = 0; i < gr.GetNodeAmount(); i++)
	{
		DataRow^ row = dt->NewRow();
		t = " ";
		t = t->Replace(' ', gr.GetNodeLetter(i));
		row["#"] = t;
		for (int j = 0; j < gr.GetNodeAmount(); j++)
		{
			t = " ";
			t = t->Replace(' ', gr.GetNodeLetter(j));
			row[t] = gr.GetMatrixElem(i, j);
		}
		dt->Rows->Add(row);
	}
	this->GraphMatrix->DataSource = dt;
	this->GraphMatrix->Show();
}
void MainForm::doneButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "�������� �������".
	  ����� �������� ��������� ����� ������� ������ � �������, 
	  ������� � ���������� ���� � ���������� ��������� �������� ��������
	  � ����������� �����.
	*/
	if (gr.GetNodeAmount() == 0)
		return;
	if (gr.CheckNodesConnection() == false)
	{
		MessageBox::Show("���� �� �������� �������.\n�������� ����������� ����� � ��������� �������.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}	

	Result^ res;
	if (PrimsMethod->Checked == true)
	{
		res = gcnew Result(&gr, MainForm::BackColor == SystemColors::Control ? false : true, true);
		res->Size = this->Size;
		res->Show();
	}
	else if (KraskallsMethod->Checked == true)
	{
		res = gcnew Result(&gr, MainForm::BackColor == SystemColors::Control ? false : true, false);
		res->Size = this->Size;
		res->Show();
	}	
	else if (BothMethods->Checked == true)
	{
		res = gcnew Result(&gr, MainForm::BackColor == SystemColors::Control ? false : true, true);
		res->Size = this->Size;
		res->Show();
		res = gcnew Result(&gr, MainForm::BackColor == SystemColors::Control ? false : true, false);
		res->Size = this->Size;
		res->Show();
	}
}
void MainForm::EraseSelect_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "������� ����".
	  �� ��������� ������ ������ ��-�� ���������� �������,
	  ����������� � ������������ �������������. ��� ��� ��������� 
	  ������� ��� ������ � ����� � ������� ����� ������
	  ��� �����������
	*/
	if (sender != this->�����������ToolStripMenuItem)
		switch (MessageBox::Show("���� ����� ������.\n�� �������?", "��������", MessageBoxButtons::YesNo, MessageBoxIcon::Warning))
		{
		case(System::Windows::Forms::DialogResult::Yes):
			break;
		case(System::Windows::Forms::DialogResult::No):
			return;
		}

	gr.Clear();
	tbTag = 1;
	Panel^ temp = gcnew Panel();

	temp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(21)),
		static_cast<System::Int32>(static_cast<System::Byte>(21)));
	temp->Size = panel1->Size;
	temp->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	temp->Cursor = System::Windows::Forms::Cursors::Cross;
	temp->ForeColor = System::Drawing::Color::Black;
	temp->Name = L"panel1";
	temp->AutoSize = false;
	temp->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	temp->Anchor = AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Top;
	temp->Location = System::Drawing::Point(3, 6);
	temp->Click += gcnew System::EventHandler(this, &MainForm::panel1_Click);
	temp->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint);
	tabPage1->Controls->Remove(panel1);
	panel1 = temp;
	tabPage1->Controls->Add(panel1);
}
#pragma endregion
#pragma region ������
void MainForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "� ���������".
	  ���������� ���� � ����������� � ��������� � 
	  �� ���������.
	*/
	MessageBox::Show("��������� ��� ���������� ������������ ��������� ������ �����. \n \n������� � �������� ��������� ������� �������� ��������� � 2020-� ����. \n \n������� �.�. | ������ �-893\n\n2020", "� ���������", MessageBoxButtons::OK);
}
void MainForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  ������� ����� �� ������ "�������" ������� "����".
	  �������� ����� ���� ��������� �� �������.
	*/
	������ToolStripMenuItem->Checked = false;
	�������ToolStripMenuItem->Checked = true;

	this->BackColor = SystemColors::Control;
	this->ForeColor = Color::Black;
	groupBoxSolution->ForeColor = Color::Black;
	EdgeSelect->FlatStyle = FlatStyle::System;
	NodeSelect->FlatStyle = FlatStyle::System;
	EraseSelect->FlatStyle = FlatStyle::System;
	Rebuild->FlatStyle = FlatStyle::System;
	doneButton->FlatStyle = FlatStyle::System;
	tabPage1->BackColor = Color::White;
	tabPage2->BackColor = Color::White;
	GraphMatrix->BackgroundColor = Color::Silver;
	GraphMatrix->DefaultCellStyle->BackColor = Color::White;
	GraphMatrix->DefaultCellStyle->ForeColor = Color::Black;
	panelTop->Visible = false;
	panelLeft->Visible = false;
}
void MainForm::������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	�������ToolStripMenuItem->Checked = false;
	������ToolStripMenuItem->Checked = true;
	this->BackColor = Color::FromArgb(41, 41, 44);
	this->ForeColor = Color::White;
	groupBoxSolution->ForeColor = Color::White;
	EdgeSelect->FlatStyle = FlatStyle::Flat;
	NodeSelect->FlatStyle = FlatStyle::Flat;
	EraseSelect->FlatStyle = FlatStyle::Flat;
	Rebuild->FlatStyle = FlatStyle::Flat;
	doneButton->FlatStyle = FlatStyle::Flat;
	tabPage1->BackColor = Color::DimGray;
	tabPage2->BackColor = Color::DimGray;
	GraphMatrix->BackgroundColor = Color::FromArgb(41, 41, 44);
	GraphMatrix->DefaultCellStyle->BackColor = Color::FromArgb(32,32,33);
	GraphMatrix->DefaultCellStyle->ForeColor = Color::White;
	panelTop->Visible = true;
	panelLeft->Visible = true;
}
void MainForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}
void MainForm::�������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::IO::StreamWriter^ saveFile;
	if (saveFileDialog1->FileName == "")
	{
		saveFileDialog1->DefaultExt = "txt";
		saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� �����|*.*";
		saveFileDialog1->InitialDirectory = "%USERNAME%/Desktop";
		saveFileDialog1->AddExtension = true;

		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
			return;
		saveFile = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
	}
	else
		saveFile = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
	
	gr.Save(saveFile);
	saveFile->Close();
}
void MainForm::�����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::IO::StreamReader^ loadFile;
	openFileDialog1->FileName = "New Graph";
	openFileDialog1->FilterIndex = 1;
	openFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� �����|*.*";
	openFileDialog1->InitialDirectory = "%USERNAME%/Desktop";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return;
	else
	{
		EraseSelect_Click(this->�����������ToolStripMenuItem, nullptr);
		loadFile = gcnew System::IO::StreamReader(openFileDialog1->FileName);
	}
	gr.Load(loadFile);
	loadFile->Close();
	panel1->Invalidate();
	tbTag = 1;
	for (Edge e : gr.GetEdges())
		this->panel1->Controls->Add(AddTextbox(Point(abs(gr.GetNode(e.startNode).X + gr.GetNode(e.endNode).X) / 2, abs(gr.GetNode(e.startNode).Y + gr.GetNode(e.endNode).Y) / 2), e.value.ToString()));
}
void MainForm::������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::IO::StreamWriter^ saveFile;
	saveFileDialog1->DefaultExt = "txt";
	saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� �����|*.*";
	saveFileDialog1->InitialDirectory = "%USERNAME%/Desktop";
	saveFileDialog1->AddExtension = true;

	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return;
	saveFile = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);

	gr.Save(saveFile);
	saveFile->Close();
}
#pragma endregion