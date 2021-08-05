#pragma once
#include "graph.h"

namespace Êóðñîâàÿ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}



	private: System::Windows::Forms::Button^ doneButton;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;



	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Panel^ panel1;



	
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ ôàéëToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ñîõðàíèòüÃðàôToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ îòêðûòüÃðàôToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ íàñòðîéêèToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ òåìàToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ñâåòëàÿToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ òåìíàÿToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ïîìîùüToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ îÏðîãðàììåToolStripMenuItem;
	private: System::Windows::Forms::DataGridView^ GraphMatrix;
	private: System::Windows::Forms::Button^ Rebuild;
	private: System::Windows::Forms::GroupBox^ groupBoxSolution;
	private: System::Windows::Forms::RadioButton^ KraskallsMethod;


	private: System::Windows::Forms::RadioButton^ PrimsMethod;
	private: System::Windows::Forms::RadioButton^ BothMethods;
	private: System::Windows::Forms::Panel^ panelRight;
	private: System::Windows::Forms::Panel^ panelLeft;


	private: System::Windows::Forms::Panel^ panelBottom;

	private: System::Windows::Forms::Panel^ panelTop;

	private: System::Windows::Forms::Button^ EdgeSelect;

	private: System::Windows::Forms::Button^ NodeSelect;
	private: System::Windows::Forms::Button^ EraseSelect;
	private: System::Windows::Forms::ToolStripMenuItem^ ñîõðàíèòüÊàêToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ çàêðûòüToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;


	protected:


	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->Rebuild = (gcnew System::Windows::Forms::Button());
			this->GraphMatrix = (gcnew System::Windows::Forms::DataGridView());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îòêðûòüÃðàôToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõðàíèòüÃðàôToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõðàíèòüÊàêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->íàñòðîéêèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->òåìàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñâåòëàÿToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->òåìíàÿToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çàêðûòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïîìîùüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îÏðîãðàììåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBoxSolution = (gcnew System::Windows::Forms::GroupBox());
			this->BothMethods = (gcnew System::Windows::Forms::RadioButton());
			this->KraskallsMethod = (gcnew System::Windows::Forms::RadioButton());
			this->PrimsMethod = (gcnew System::Windows::Forms::RadioButton());
			this->panelRight = (gcnew System::Windows::Forms::Panel());
			this->panelLeft = (gcnew System::Windows::Forms::Panel());
			this->panelBottom = (gcnew System::Windows::Forms::Panel());
			this->panelTop = (gcnew System::Windows::Forms::Panel());
			this->EdgeSelect = (gcnew System::Windows::Forms::Button());
			this->NodeSelect = (gcnew System::Windows::Forms::Button());
			this->EraseSelect = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GraphMatrix))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->groupBoxSolution->SuspendLayout();
			this->SuspendLayout();
			// 
			// doneButton
			// 
			resources->ApplyResources(this->doneButton, L"doneButton");
			this->doneButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->doneButton->FlatAppearance->BorderSize = 2;
			this->doneButton->ForeColor = System::Drawing::Color::White;
			this->doneButton->Name = L"doneButton";
			this->doneButton->UseVisualStyleBackColor = false;
			this->doneButton->Click += gcnew System::EventHandler(this, &MainForm::doneButton_Click);
			// 
			// tabControl1
			// 
			resources->ApplyResources(this->tabControl1, L"tabControl1");
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->HotTrack = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::DimGray;
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->ForeColor = System::Drawing::Color::White;
			resources->ApplyResources(this->tabPage1, L"tabPage1");
			this->tabPage1->Name = L"tabPage1";
			// 
			// panel1
			// 
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(21)),
				static_cast<System::Int32>(static_cast<System::Byte>(21)));
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Cursor = System::Windows::Forms::Cursors::Cross;
			this->panel1->ForeColor = System::Drawing::Color::Black;
			this->panel1->Name = L"panel1";
			this->panel1->Click += gcnew System::EventHandler(this, &MainForm::panel1_Click);
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint);
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::DimGray;
			this->tabPage2->Controls->Add(this->Rebuild);
			this->tabPage2->Controls->Add(this->GraphMatrix);
			resources->ApplyResources(this->tabPage2, L"tabPage2");
			this->tabPage2->Name = L"tabPage2";
			// 
			// Rebuild
			// 
			resources->ApplyResources(this->Rebuild, L"Rebuild");
			this->Rebuild->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			this->Rebuild->Name = L"Rebuild";
			this->Rebuild->UseVisualStyleBackColor = false;
			this->Rebuild->Click += gcnew System::EventHandler(this, &MainForm::Rebuild_Click);
			// 
			// GraphMatrix
			// 
			this->GraphMatrix->AllowUserToAddRows = false;
			this->GraphMatrix->AllowUserToDeleteRows = false;
			this->GraphMatrix->AllowUserToResizeColumns = false;
			this->GraphMatrix->AllowUserToResizeRows = false;
			resources->ApplyResources(this->GraphMatrix, L"GraphMatrix");
			this->GraphMatrix->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::DisplayedCellsExceptHeader;
			this->GraphMatrix->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)),
				static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(21)));
			this->GraphMatrix->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
				static_cast<System::Int32>(static_cast<System::Byte>(205)));
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::Color::White;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->GraphMatrix->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->NullValue = L"INF";
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(123)), static_cast<System::Int32>(static_cast<System::Byte>(205)));
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->GraphMatrix->DefaultCellStyle = dataGridViewCellStyle2;
			this->GraphMatrix->EnableHeadersVisualStyles = false;
			this->GraphMatrix->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
				static_cast<System::Int32>(static_cast<System::Byte>(205)));
			this->GraphMatrix->Name = L"GraphMatrix";
			this->GraphMatrix->RowHeadersVisible = false;
			this->GraphMatrix->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->GraphMatrix->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::GraphMatrix_CellValueChanged);
			this->GraphMatrix->DataError += gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(this, &MainForm::GraphMatrix_DataError);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
				static_cast<System::Int32>(static_cast<System::Byte>(205)));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->ôàéëToolStripMenuItem,
					this->íàñòðîéêèToolStripMenuItem, this->ïîìîùüToolStripMenuItem
			});
			resources->ApplyResources(this->menuStrip1, L"menuStrip1");
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			// 
			// ôàéëToolStripMenuItem
			// 
			this->ôàéëToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(123)), static_cast<System::Int32>(static_cast<System::Byte>(205)));
			resources->ApplyResources(this->ôàéëToolStripMenuItem, L"ôàéëToolStripMenuItem");
			this->ôàéëToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->îòêðûòüÃðàôToolStripMenuItem,
					this->ñîõðàíèòüÃðàôToolStripMenuItem, this->ñîõðàíèòüÊàêToolStripMenuItem
			});
			this->ôàéëToolStripMenuItem->ForeColor = System::Drawing::Color::Black;
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			// 
			// îòêðûòüÃðàôToolStripMenuItem
			// 
			this->îòêðûòüÃðàôToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			resources->ApplyResources(this->îòêðûòüÃðàôToolStripMenuItem, L"îòêðûòüÃðàôToolStripMenuItem");
			this->îòêðûòüÃðàôToolStripMenuItem->Name = L"îòêðûòüÃðàôToolStripMenuItem";
			this->îòêðûòüÃðàôToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::îòêðûòüÃðàôToolStripMenuItem_Click);
			// 
			// ñîõðàíèòüÃðàôToolStripMenuItem
			// 
			this->ñîõðàíèòüÃðàôToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			resources->ApplyResources(this->ñîõðàíèòüÃðàôToolStripMenuItem, L"ñîõðàíèòüÃðàôToolStripMenuItem");
			this->ñîõðàíèòüÃðàôToolStripMenuItem->Name = L"ñîõðàíèòüÃðàôToolStripMenuItem";
			this->ñîõðàíèòüÃðàôToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñîõðàíèòüÃðàôToolStripMenuItem_Click);
			// 
			// ñîõðàíèòüÊàêToolStripMenuItem
			// 
			this->ñîõðàíèòüÊàêToolStripMenuItem->BackColor = System::Drawing::SystemColors::Control;
			resources->ApplyResources(this->ñîõðàíèòüÊàêToolStripMenuItem, L"ñîõðàíèòüÊàêToolStripMenuItem");
			this->ñîõðàíèòüÊàêToolStripMenuItem->Name = L"ñîõðàíèòüÊàêToolStripMenuItem";
			this->ñîõðàíèòüÊàêToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñîõðàíèòüÊàêToolStripMenuItem_Click);
			// 
			// íàñòðîéêèToolStripMenuItem
			// 
			this->íàñòðîéêèToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->òåìàToolStripMenuItem,
					this->çàêðûòüToolStripMenuItem
			});
			this->íàñòðîéêèToolStripMenuItem->ForeColor = System::Drawing::Color::Black;
			this->íàñòðîéêèToolStripMenuItem->Name = L"íàñòðîéêèToolStripMenuItem";
			resources->ApplyResources(this->íàñòðîéêèToolStripMenuItem, L"íàñòðîéêèToolStripMenuItem");
			// 
			// òåìàToolStripMenuItem
			// 
			this->òåìàToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ñâåòëàÿToolStripMenuItem,
					this->òåìíàÿToolStripMenuItem
			});
			resources->ApplyResources(this->òåìàToolStripMenuItem, L"òåìàToolStripMenuItem");
			this->òåìàToolStripMenuItem->Name = L"òåìàToolStripMenuItem";
			// 
			// ñâåòëàÿToolStripMenuItem
			// 
			this->ñâåòëàÿToolStripMenuItem->Name = L"ñâåòëàÿToolStripMenuItem";
			resources->ApplyResources(this->ñâåòëàÿToolStripMenuItem, L"ñâåòëàÿToolStripMenuItem");
			this->ñâåòëàÿToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ñâåòëàÿToolStripMenuItem_Click);
			// 
			// òåìíàÿToolStripMenuItem
			// 
			this->òåìíàÿToolStripMenuItem->Checked = true;
			this->òåìíàÿToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->òåìíàÿToolStripMenuItem->Name = L"òåìíàÿToolStripMenuItem";
			resources->ApplyResources(this->òåìíàÿToolStripMenuItem, L"òåìíàÿToolStripMenuItem");
			this->òåìíàÿToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::òåìíàÿToolStripMenuItem_Click);
			// 
			// çàêðûòüToolStripMenuItem
			// 
			resources->ApplyResources(this->çàêðûòüToolStripMenuItem, L"çàêðûòüToolStripMenuItem");
			this->çàêðûòüToolStripMenuItem->Name = L"çàêðûòüToolStripMenuItem";
			this->çàêðûòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::çàêðûòüToolStripMenuItem_Click);
			// 
			// ïîìîùüToolStripMenuItem
			// 
			this->ïîìîùüToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->îÏðîãðàììåToolStripMenuItem });
			this->ïîìîùüToolStripMenuItem->ForeColor = System::Drawing::Color::Black;
			this->ïîìîùüToolStripMenuItem->Name = L"ïîìîùüToolStripMenuItem";
			resources->ApplyResources(this->ïîìîùüToolStripMenuItem, L"ïîìîùüToolStripMenuItem");
			// 
			// îÏðîãðàììåToolStripMenuItem
			// 
			resources->ApplyResources(this->îÏðîãðàììåToolStripMenuItem, L"îÏðîãðàììåToolStripMenuItem");
			this->îÏðîãðàììåToolStripMenuItem->Name = L"îÏðîãðàììåToolStripMenuItem";
			this->îÏðîãðàììåToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::îÏðîãðàììåToolStripMenuItem_Click);
			// 
			// groupBoxSolution
			// 
			resources->ApplyResources(this->groupBoxSolution, L"groupBoxSolution");
			this->groupBoxSolution->Controls->Add(this->BothMethods);
			this->groupBoxSolution->Controls->Add(this->KraskallsMethod);
			this->groupBoxSolution->Controls->Add(this->PrimsMethod);
			this->groupBoxSolution->ForeColor = System::Drawing::Color::White;
			this->groupBoxSolution->Name = L"groupBoxSolution";
			this->groupBoxSolution->TabStop = false;
			// 
			// BothMethods
			// 
			resources->ApplyResources(this->BothMethods, L"BothMethods");
			this->BothMethods->Name = L"BothMethods";
			this->BothMethods->UseVisualStyleBackColor = true;
			// 
			// KraskallsMethod
			// 
			resources->ApplyResources(this->KraskallsMethod, L"KraskallsMethod");
			this->KraskallsMethod->Name = L"KraskallsMethod";
			this->KraskallsMethod->UseVisualStyleBackColor = true;
			// 
			// PrimsMethod
			// 
			resources->ApplyResources(this->PrimsMethod, L"PrimsMethod");
			this->PrimsMethod->Checked = true;
			this->PrimsMethod->Name = L"PrimsMethod";
			this->PrimsMethod->TabStop = true;
			this->PrimsMethod->UseVisualStyleBackColor = true;
			// 
			// panelRight
			// 
			resources->ApplyResources(this->panelRight, L"panelRight");
			this->panelRight->Name = L"panelRight";
			// 
			// panelLeft
			// 
			resources->ApplyResources(this->panelLeft, L"panelLeft");
			this->panelLeft->Name = L"panelLeft";
			// 
			// panelBottom
			// 
			resources->ApplyResources(this->panelBottom, L"panelBottom");
			this->panelBottom->Name = L"panelBottom";
			// 
			// panelTop
			// 
			resources->ApplyResources(this->panelTop, L"panelTop");
			this->panelTop->Name = L"panelTop";
			// 
			// EdgeSelect
			// 
			resources->ApplyResources(this->EdgeSelect, L"EdgeSelect");
			this->EdgeSelect->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->EdgeSelect->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->EdgeSelect->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->EdgeSelect->FlatAppearance->BorderSize = 2;
			this->EdgeSelect->ForeColor = System::Drawing::Color::White;
			this->EdgeSelect->Name = L"EdgeSelect";
			this->EdgeSelect->TabStop = false;
			this->EdgeSelect->UseVisualStyleBackColor = false;
			this->EdgeSelect->Click += gcnew System::EventHandler(this, &MainForm::EdgeSelect_Click);
			// 
			// NodeSelect
			// 
			resources->ApplyResources(this->NodeSelect, L"NodeSelect");
			this->NodeSelect->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->NodeSelect->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->NodeSelect->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->NodeSelect->FlatAppearance->BorderSize = 2;
			this->NodeSelect->ForeColor = System::Drawing::Color::White;
			this->NodeSelect->Name = L"NodeSelect";
			this->NodeSelect->TabStop = false;
			this->NodeSelect->UseVisualStyleBackColor = false;
			this->NodeSelect->Click += gcnew System::EventHandler(this, &MainForm::NodeSelect_Click);
			// 
			// EraseSelect
			// 
			resources->ApplyResources(this->EraseSelect, L"EraseSelect");
			this->EraseSelect->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->EraseSelect->FlatAppearance->BorderSize = 2;
			this->EraseSelect->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(124)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->EraseSelect->ForeColor = System::Drawing::Color::Orange;
			this->EraseSelect->Name = L"EraseSelect";
			this->EraseSelect->TabStop = false;
			this->EraseSelect->UseVisualStyleBackColor = false;
			this->EraseSelect->Click += gcnew System::EventHandler(this, &MainForm::EraseSelect_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// MainForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(41)), static_cast<System::Int32>(static_cast<System::Byte>(41)),
				static_cast<System::Int32>(static_cast<System::Byte>(44)));
			this->Controls->Add(this->NodeSelect);
			this->Controls->Add(this->EraseSelect);
			this->Controls->Add(this->panelTop);
			this->Controls->Add(this->EdgeSelect);
			this->Controls->Add(this->panelBottom);
			this->Controls->Add(this->panelLeft);
			this->Controls->Add(this->panelRight);
			this->Controls->Add(this->groupBoxSolution);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->menuStrip1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->ForeColor = System::Drawing::Color::White;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GraphMatrix))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBoxSolution->ResumeLayout(false);
			this->groupBoxSolution->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:

	System::Void panel1_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void EdgeSelect_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void doneButton_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void NodeSelect_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
    System::Void Rebuild_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void îÏðîãðàììåToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void EraseSelect_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void ñâåòëàÿToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void òåìíàÿToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void çàêðûòüToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void ñîõðàíèòüÃðàôToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void îòêðûòüÃðàôToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void GraphMatrix_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
	System::Void ñîõðàíèòüÊàêToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void GraphMatrix_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e);
};
};

