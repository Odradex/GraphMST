#pragma once
#include "Graph.h"
namespace Курсовая {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Result
	/// </summary>
	public ref class Result : public System::Windows::Forms::Form
	{
	public:
		Result(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		Result(Graph* g, bool darkThemeEnabled, bool primaMethod);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Result()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ resultPanel;



	protected:






	private: System::Windows::Forms::Label^ minWeightLabel;



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Result::typeid));
			this->resultPanel = (gcnew System::Windows::Forms::Panel());
			this->minWeightLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// resultPanel
			// 
			this->resultPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->resultPanel->AutoSize = true;
			this->resultPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(21)),
				static_cast<System::Int32>(static_cast<System::Byte>(21)));
			this->resultPanel->Location = System::Drawing::Point(12, 12);
			this->resultPanel->Name = L"resultPanel";
			this->resultPanel->Size = System::Drawing::Size(550, 350);
			this->resultPanel->TabIndex = 0;
			this->resultPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Result::resultPanel_Paint);
			// 
			// minWeightLabel
			// 
			this->minWeightLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->minWeightLabel->BackColor = System::Drawing::Color::Transparent;
			this->minWeightLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->minWeightLabel->ForeColor = System::Drawing::Color::Silver;
			this->minWeightLabel->Location = System::Drawing::Point(69, 365);
			this->minWeightLabel->Name = L"minWeightLabel";
			this->minWeightLabel->Size = System::Drawing::Size(428, 29);
			this->minWeightLabel->TabIndex = 6;
			this->minWeightLabel->Text = L"Минимальный вес: 45";
			this->minWeightLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Result
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Inherit;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(41)), static_cast<System::Int32>(static_cast<System::Byte>(41)),
				static_cast<System::Int32>(static_cast<System::Byte>(44)));
			this->ClientSize = System::Drawing::Size(575, 398);
			this->Controls->Add(this->minWeightLabel);
			this->Controls->Add(this->resultPanel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Result";
			this->Text = L"Result";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void resultPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
};
}
