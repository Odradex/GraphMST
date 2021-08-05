#include "MainForm.h"
#include <Windows.h>
#include "Graph.h"
#include "Result.h"
/*
MainForm - главное окно приложения, в котором происходит
ввод графа, его редактирование и выбор метода решения.

Файл MainForm.cpp содержит обработчики событий основного окна
программы и другие вспомогательные функции
*/
using namespace Курсовая;
using namespace std;

[STAThreadAttribute]

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Курсовая::MainForm form; //Создаем обьект формы...
	Application::Run(%form); //... и запукаем ее
	return 0;
}

int tbTag = 1;
Graph gr; //Граф, с которым работает пользователь

void valueBox_LostFocus(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие потери фокуса текстбоксом.
	  При потере фокуса проверяется значение в текстбоксе.
	  Если оно допустимо, соответствующий вес в графе обновляется
	  новым значением. Если нет, изменения отменяются и отображается ошибка.
	*/
	TextBox^ tb = (TextBox^)sender;
	try
	{
		gr.UpdateEdge(Convert::ToInt32(tb->Tag), Convert::ToInt32(tb->Text)); //Обновление значения в графе
	}
	catch (const System::FormatException^)
	{
		tb->Undo();
		MessageBox::Show("Неверный формат данных.\nВведите целочисленное значение.", "Ошибка", MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
	}
}

void MainForm::GraphMatrix_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	/*
	  Событие изменения значения в ячейке.
	  При изменении содержимого ячейки оно проверяется на допустимость.
	  Если оно допустимо, соответствующий вес в графе обновляется
	  новым значением.
	*/
	int valueTag = gr.UpdateValue(e->RowIndex, e->ColumnIndex - 1, Convert::ToInt32(GraphMatrix[e->ColumnIndex, e->RowIndex]->Value));
	Convert::ToInt32(GraphMatrix[e->ColumnIndex, e->RowIndex]->Value);

	if (valueTag == -1)
	{
		MessageBox::Show("Вы выбрали несуществующее ребро.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	((TextBox^)panel1->Controls->Find(valueTag.ToString(), true)[0])->Text = GraphMatrix[e->ColumnIndex, e->RowIndex]->Value->ToString();
}
void MainForm::GraphMatrix_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e)
{
	/*
	  Событие ошибки в таблице.
	  Если в ячейку были введенны недопустимые данные, 
	  изменение отменяется и выводится сообщение об ошибке.
	*/
	MessageBox::Show("Неверный формат данных.\nВведите целочисленное значение.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	e->ThrowException = false;
	GraphMatrix->CancelEdit();
	e->Cancel; 
}
TextBox^ AddTextbox(Point pos, String^ value = "")
{
	/*
	   Функция добавления нового текстбокса.
	   При вызове создает текстбокс в заданной точке и с заданным текстом.
	   текстбоксу присваевается порядковый номер, определяющий его связь 
	   с ребром (с тем же номером).
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

#pragma region Панель
int temp1 = -1, temp2 = -1;
void MainForm::panel1_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие клика по панели.
	  В зависимости от выбранного инструмента при клике
	  в граф будет добавлен определенный элемент,
	  который сразу отобразится на панели.
	*/
	panel1->Select();
	Point mousePos = this->panel1->PointToClient(Cursor->Position);
	//Если нажата кнопка "Вершина"
	if (this->NodeSelect->Enabled == false)
	{
		if (gr.detectNode(mousePos) >= 0)
		{
			MessageBox::Show(this, "В этом месте уже есть вершина.", "Ошибка", MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return;
		}
		gr.AddNode(mousePos);	
		panel1->Invalidate();
	}
	//Если нажата кнопка "Грань"
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
	  Событе отрисовки панели.
	  При срабатывании создает поверхность рисования и вызывает функцию отрисовки у графа.
	  В ранних версиях программы при каждом новом срабатывании события граф
	  рисовался поверх предыдущего, что приводило к графическим артефактам
	  и нагрузке на ОЗУ. Для предотвращения такого поведения
	  в релизной версии панель рисования очищается при каждом вызове.
	*/
	Graphics^ g = this->panel1->CreateGraphics();
	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;
	g->Clear(MainForm::BackColor == SystemColors::Control? Color::Silver : Color::FromArgb(21,21,21));
	gr.DrawGraph(g);
	delete g;
}
#pragma endregion
#pragma region Кнопки
void MainForm::EdgeSelect_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие клика по кнопке "Грань".
	  Деактивирет себя и активирует кнопку "Вершина".
	  Также, при темной версии оформления изменяет цвета
	  границ кнопок на более походящие их состоянию
	  для более интуитивного визуального
	  представления.
	*/
	this->NodeSelect->Enabled = true;
	this->NodeSelect->FlatAppearance->BorderColor = Color::White;

	this->EdgeSelect->Enabled = false;
	this->EdgeSelect->FlatAppearance->BorderColor = Color::DimGray;
}
void MainForm::NodeSelect_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие клика по кнопке "Вершина".
	  Деактивирет себя и активирует кнопку "Грань".
	  Также, при темной версии оформления изменяет цвета
	  границ кнопок на более походящие их состоянию
	  для более интуитивного визуального
	  представления.
	*/
	this->EdgeSelect->Enabled = true;
	this->EdgeSelect->FlatAppearance->BorderColor = Color::White;

	this->NodeSelect->Enabled = false;
	this->NodeSelect->FlatAppearance->BorderColor = Color::DimGray;

}
void MainForm::Rebuild_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие клика по кнопке "Перестроить граф".
	  Используя данные из матрицы смежности, создает
	  идентичноую таблицу DataTable и задает ее
	  в качестве источника данных для DataGridView.
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
	  Событие клика по кнопке "Получить решение".
	  После проверки связности графа методом обхода в глубину, 
	  создает и отображает окно с полученным указанным способом каркасом
	  и минимальным весом.
	*/
	if (gr.GetNodeAmount() == 0)
		return;
	if (gr.CheckNodesConnection() == false)
	{
		MessageBox::Show("Граф не является связным.\nДобавьте недостающие грани и повторите попытку.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
	  Событие клика по кнопке "Стереть граф".
	  Во избежание потери данных из-за случайного нажатия,
	  запрашивает у пользователя подтверждение. При его получении 
	  удаляет все данные о графе и создает новую панель
	  без текстбоксов
	*/
	if (sender != this->открытьГрафToolStripMenuItem)
		switch (MessageBox::Show("Граф будет удален.\nВы уверены?", "Внимание", MessageBoxButtons::YesNo, MessageBoxIcon::Warning))
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
#pragma region Тулбар
void MainForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие клика по кнопке "О программе".
	  Отображает окно с информацией о программе и 
	  ее создателе.
	*/
	MessageBox::Show("Программа для нахождения минимального остовного дерева графа. \n \nСоздано в качестве курсового проекта Даниилом Сиваковым в 2020-м году. \n \nСиваков Д.Т. | Группа т-893\n\n2020", "О программе", MessageBoxButtons::OK);
}
void MainForm::светлаяToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*
	  Событие клика по кнопке "Светлая" подменю "Тема".
	  Изменяет цвета всех элементов на светлые.
	*/
	темнаяToolStripMenuItem->Checked = false;
	светлаяToolStripMenuItem->Checked = true;

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
void MainForm::темнаяToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	светлаяToolStripMenuItem->Checked = false;
	темнаяToolStripMenuItem->Checked = true;
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
void MainForm::закрытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}
void MainForm::сохранитьГрафToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::IO::StreamWriter^ saveFile;
	if (saveFileDialog1->FileName == "")
	{
		saveFileDialog1->DefaultExt = "txt";
		saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы|*.*";
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
void MainForm::открытьГрафToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::IO::StreamReader^ loadFile;
	openFileDialog1->FileName = "New Graph";
	openFileDialog1->FilterIndex = 1;
	openFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы|*.*";
	openFileDialog1->InitialDirectory = "%USERNAME%/Desktop";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return;
	else
	{
		EraseSelect_Click(this->открытьГрафToolStripMenuItem, nullptr);
		loadFile = gcnew System::IO::StreamReader(openFileDialog1->FileName);
	}
	gr.Load(loadFile);
	loadFile->Close();
	panel1->Invalidate();
	tbTag = 1;
	for (Edge e : gr.GetEdges())
		this->panel1->Controls->Add(AddTextbox(Point(abs(gr.GetNode(e.startNode).X + gr.GetNode(e.endNode).X) / 2, abs(gr.GetNode(e.startNode).Y + gr.GetNode(e.endNode).Y) / 2), e.value.ToString()));
}
void MainForm::сохранитьКакToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::IO::StreamWriter^ saveFile;
	saveFileDialog1->DefaultExt = "txt";
	saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы|*.*";
	saveFileDialog1->InitialDirectory = "%USERNAME%/Desktop";
	saveFileDialog1->AddExtension = true;

	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return;
	saveFile = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);

	gr.Save(saveFile);
	saveFile->Close();
}
#pragma endregion