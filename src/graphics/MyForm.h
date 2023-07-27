#pragma once
#include <atlstr.h>
namespace RayForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;	
	using namespace System::Diagnostics;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ but1;
	protected:

	protected:




	private: System::Windows::Forms::TextBox^ tb_screen_w;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ tb_screen_h;
	private: System::Windows::Forms::TextBox^ tb_death_cam;
	private: Control^ _editControl; //переменная под элемент управления редактирования ячейки
	private: array<array<float>^>^_materials;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ tb_cam_pos;

	private: System::Windows::Forms::TextBox^ tb_light_intensity;
	private: System::Windows::Forms::TextBox^ tb_light_pos;
	private: System::Windows::Forms::ListBox^ lb_lights;
	private: System::Windows::Forms::Label^ lab_back;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ tb_rgb;
	private: System::Windows::Forms::Label^ lab_material;
	private: System::Windows::Forms::TextBox^ tb_albedo;
	private: System::Windows::Forms::TextBox^ tb_shininess;
	private: System::Windows::Forms::TextBox^ tb_refraction;


	private: System::Windows::Forms::TextBox^ tb_radius;
	private: System::Windows::Forms::Label^ lb_sphere;
	private: System::Windows::Forms::TextBox^ tb_center;
	private: System::Windows::Forms::ComboBox^ comBoxPlane;

	private: System::Windows::Forms::TextBox^ tb_plane2;
	private: System::Windows::Forms::Label^ lb_plane;
	private: System::Windows::Forms::TextBox^ tb_plane1;
	private: System::Windows::Forms::TextBox^ tb_rotate;

	private: System::Windows::Forms::Label^ lb_comp_obj;
	private: System::Windows::Forms::TextBox^ tb_name_obj;

	private: System::Windows::Forms::TextBox^ tb_pos;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ add_mat;
	private: System::Windows::Forms::Button^ add_sphere;
	private: System::Windows::Forms::Button^ add_plane;
	private: System::Windows::Forms::Button^ add_obj;
	private: System::Windows::Forms::Button^ add_light;
	private: System::Windows::Forms::TextBox^ tb_name_mat;
	private: System::Windows::Forms::ComboBox^ comBoxSphere;
	private: System::Windows::Forms::ComboBox^ comBoxObj;

	private: System::Windows::Forms::TextBox^ tb_core;

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
			this->but1 = (gcnew System::Windows::Forms::Button());
			this->tb_screen_w = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tb_screen_h = (gcnew System::Windows::Forms::TextBox());
			this->tb_death_cam = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tb_cam_pos = (gcnew System::Windows::Forms::TextBox());
			this->tb_light_intensity = (gcnew System::Windows::Forms::TextBox());
			this->tb_light_pos = (gcnew System::Windows::Forms::TextBox());
			this->lb_lights = (gcnew System::Windows::Forms::ListBox());
			this->lab_back = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->tb_rgb = (gcnew System::Windows::Forms::TextBox());
			this->lab_material = (gcnew System::Windows::Forms::Label());
			this->tb_albedo = (gcnew System::Windows::Forms::TextBox());
			this->tb_shininess = (gcnew System::Windows::Forms::TextBox());
			this->tb_refraction = (gcnew System::Windows::Forms::TextBox());
			this->tb_radius = (gcnew System::Windows::Forms::TextBox());
			this->lb_sphere = (gcnew System::Windows::Forms::Label());
			this->tb_center = (gcnew System::Windows::Forms::TextBox());
			this->comBoxPlane = (gcnew System::Windows::Forms::ComboBox());
			this->tb_plane2 = (gcnew System::Windows::Forms::TextBox());
			this->lb_plane = (gcnew System::Windows::Forms::Label());
			this->tb_plane1 = (gcnew System::Windows::Forms::TextBox());
			this->tb_rotate = (gcnew System::Windows::Forms::TextBox());
			this->lb_comp_obj = (gcnew System::Windows::Forms::Label());
			this->tb_name_obj = (gcnew System::Windows::Forms::TextBox());
			this->tb_pos = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->add_mat = (gcnew System::Windows::Forms::Button());
			this->add_sphere = (gcnew System::Windows::Forms::Button());
			this->add_plane = (gcnew System::Windows::Forms::Button());
			this->add_obj = (gcnew System::Windows::Forms::Button());
			this->add_light = (gcnew System::Windows::Forms::Button());
			this->tb_name_mat = (gcnew System::Windows::Forms::TextBox());
			this->comBoxSphere = (gcnew System::Windows::Forms::ComboBox());
			this->comBoxObj = (gcnew System::Windows::Forms::ComboBox());
			this->tb_core = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// but1
			// 
			this->but1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->but1->Location = System::Drawing::Point(315, 553);
			this->but1->Name = L"but1";
			this->but1->Size = System::Drawing::Size(195, 64);
			this->but1->TabIndex = 0;
			this->but1->Text = L"start";
			this->but1->UseVisualStyleBackColor = true;
			this->but1->Click += gcnew System::EventHandler(this, &MyForm::but1_Click);
			// 
			// tb_screen_w
			// 
			this->tb_screen_w->BackColor = System::Drawing::SystemColors::Window;
			this->tb_screen_w->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_screen_w->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_screen_w->Location = System::Drawing::Point(165, 52);
			this->tb_screen_w->Name = L"tb_screen_w";
			this->tb_screen_w->Size = System::Drawing::Size(54, 26);
			this->tb_screen_w->TabIndex = 4;
			this->tb_screen_w->Text = L"800";
			this->tb_screen_w->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_screen_w_TextChanged);
			this->tb_screen_w->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_screen_w_KeyPress);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(25, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(134, 20);
			this->label2->TabIndex = 5;
			this->label2->Text = L"screen resolution:";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(225, 52);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(16, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"x";
			// 
			// tb_screen_h
			// 
			this->tb_screen_h->BackColor = System::Drawing::SystemColors::Window;
			this->tb_screen_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_screen_h->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_screen_h->Location = System::Drawing::Point(245, 52);
			this->tb_screen_h->Name = L"tb_screen_h";
			this->tb_screen_h->Size = System::Drawing::Size(55, 26);
			this->tb_screen_h->TabIndex = 7;
			this->tb_screen_h->Text = L"600";
			this->tb_screen_h->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_screen_h_TextChanged);
			this->tb_screen_h->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_screen_h_KeyPress);
			// 
			// tb_death_cam
			// 
			this->tb_death_cam->BackColor = System::Drawing::SystemColors::Window;
			this->tb_death_cam->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_death_cam->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_death_cam->Location = System::Drawing::Point(226, 87);
			this->tb_death_cam->Name = L"tb_death_cam";
			this->tb_death_cam->Size = System::Drawing::Size(55, 26);
			this->tb_death_cam->TabIndex = 11;
			this->tb_death_cam->Text = L"400";
			this->tb_death_cam->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			this->tb_death_cam->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_death_cam_KeyPress);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(25, 87);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(66, 20);
			this->label5->TabIndex = 9;
			this->label5->Text = L"camera:";
			// 
			// tb_cam_pos
			// 
			this->tb_cam_pos->BackColor = System::Drawing::SystemColors::Window;
			this->tb_cam_pos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_cam_pos->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_cam_pos->Location = System::Drawing::Point(95, 87);
			this->tb_cam_pos->Name = L"tb_cam_pos";
			this->tb_cam_pos->Size = System::Drawing::Size(125, 26);
			this->tb_cam_pos->TabIndex = 8;
			this->tb_cam_pos->Text = L"0,0,-18";
			this->tb_cam_pos->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			this->tb_cam_pos->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_cam_pos_KeyPress);
			// 
			// tb_light_intensity
			// 
			this->tb_light_intensity->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_light_intensity->BackColor = System::Drawing::SystemColors::Window;
			this->tb_light_intensity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_light_intensity->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_light_intensity->Location = System::Drawing::Point(204, 352);
			this->tb_light_intensity->Name = L"tb_light_intensity";
			this->tb_light_intensity->Size = System::Drawing::Size(55, 26);
			this->tb_light_intensity->TabIndex = 14;
			this->tb_light_intensity->Text = L"1.5";
			this->tb_light_intensity->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::tb_light_intensity_KeyDown);
			this->tb_light_intensity->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_light_intensity_KeyPress);
			// 
			// tb_light_pos
			// 
			this->tb_light_pos->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_light_pos->BackColor = System::Drawing::SystemColors::Window;
			this->tb_light_pos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_light_pos->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_light_pos->Location = System::Drawing::Point(73, 352);
			this->tb_light_pos->Name = L"tb_light_pos";
			this->tb_light_pos->Size = System::Drawing::Size(125, 26);
			this->tb_light_pos->TabIndex = 13;
			this->tb_light_pos->Text = L"-20,20,20";
			this->tb_light_pos->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::tb_light_pos_KeyDown);
			this->tb_light_pos->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_light_pos_KeyPress);
			// 
			// lb_lights
			// 
			this->lb_lights->FormattingEnabled = true;
			this->lb_lights->ItemHeight = 20;
			this->lb_lights->Location = System::Drawing::Point(29, 398);
			this->lb_lights->Name = L"lb_lights";
			this->lb_lights->Size = System::Drawing::Size(764, 144);
			this->lb_lights->TabIndex = 15;
			this->lb_lights->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::lb_lights_KeyDown);
			// 
			// lab_back
			// 
			this->lab_back->AutoSize = true;
			this->lab_back->Location = System::Drawing::Point(25, 129);
			this->lab_back->Name = L"lab_back";
			this->lab_back->Size = System::Drawing::Size(97, 20);
			this->lab_back->TabIndex = 16;
			this->lab_back->Text = L"background:";
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->BackColor = System::Drawing::SystemColors::Window;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->textBox2->Location = System::Drawing::Point(125, 129);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(385, 26);
			this->textBox2->TabIndex = 17;
			this->textBox2->Text = L"D:/Game/RayTracing/MakeRayTracing/data/background.jpg";
			// 
			// tb_rgb
			// 
			this->tb_rgb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_rgb->BackColor = System::Drawing::SystemColors::Window;
			this->tb_rgb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_rgb->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_rgb->Location = System::Drawing::Point(262, 170);
			this->tb_rgb->Name = L"tb_rgb";
			this->tb_rgb->Size = System::Drawing::Size(120, 26);
			this->tb_rgb->TabIndex = 20;
			this->tb_rgb->Text = L"0.3,0.1,0.1";
			// 
			// lab_material
			// 
			this->lab_material->AutoSize = true;
			this->lab_material->Location = System::Drawing::Point(25, 170);
			this->lab_material->Name = L"lab_material";
			this->lab_material->Size = System::Drawing::Size(69, 20);
			this->lab_material->TabIndex = 19;
			this->lab_material->Text = L"material:";
			// 
			// tb_albedo
			// 
			this->tb_albedo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_albedo->BackColor = System::Drawing::SystemColors::Window;
			this->tb_albedo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_albedo->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_albedo->Location = System::Drawing::Point(95, 170);
			this->tb_albedo->Name = L"tb_albedo";
			this->tb_albedo->Size = System::Drawing::Size(160, 26);
			this->tb_albedo->TabIndex = 18;
			this->tb_albedo->Text = L"0.9,0.1,0.0,0.0";
			// 
			// tb_shininess
			// 
			this->tb_shininess->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_shininess->BackColor = System::Drawing::SystemColors::Window;
			this->tb_shininess->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_shininess->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_shininess->Location = System::Drawing::Point(387, 170);
			this->tb_shininess->Name = L"tb_shininess";
			this->tb_shininess->Size = System::Drawing::Size(50, 26);
			this->tb_shininess->TabIndex = 21;
			this->tb_shininess->Text = L"30";
			// 
			// tb_refraction
			// 
			this->tb_refraction->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_refraction->BackColor = System::Drawing::SystemColors::Window;
			this->tb_refraction->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_refraction->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_refraction->Location = System::Drawing::Point(443, 170);
			this->tb_refraction->Name = L"tb_refraction";
			this->tb_refraction->Size = System::Drawing::Size(50, 26);
			this->tb_refraction->TabIndex = 22;
			this->tb_refraction->Text = L"1";
			// 
			// tb_radius
			// 
			this->tb_radius->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_radius->BackColor = System::Drawing::SystemColors::Window;
			this->tb_radius->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_radius->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_radius->Location = System::Drawing::Point(193, 223);
			this->tb_radius->Name = L"tb_radius";
			this->tb_radius->Size = System::Drawing::Size(48, 26);
			this->tb_radius->TabIndex = 26;
			this->tb_radius->Text = L"2";
			// 
			// lb_sphere
			// 
			this->lb_sphere->AutoSize = true;
			this->lb_sphere->Location = System::Drawing::Point(25, 223);
			this->lb_sphere->Name = L"lb_sphere";
			this->lb_sphere->Size = System::Drawing::Size(62, 20);
			this->lb_sphere->TabIndex = 25;
			this->lb_sphere->Text = L"sphere:";
			// 
			// tb_center
			// 
			this->tb_center->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_center->BackColor = System::Drawing::SystemColors::Window;
			this->tb_center->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_center->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_center->Location = System::Drawing::Point(95, 223);
			this->tb_center->Name = L"tb_center";
			this->tb_center->Size = System::Drawing::Size(92, 26);
			this->tb_center->TabIndex = 24;
			this->tb_center->Text = L"-3,0,0";
			// 
			// comBoxPlane
			// 
			this->comBoxPlane->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comBoxPlane->FormattingEnabled = true;
			this->comBoxPlane->Location = System::Drawing::Point(296, 263);
			this->comBoxPlane->Name = L"comBoxPlane";
			this->comBoxPlane->Size = System::Drawing::Size(121, 28);
			this->comBoxPlane->TabIndex = 31;
			// 
			// tb_plane2
			// 
			this->tb_plane2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_plane2->BackColor = System::Drawing::SystemColors::Window;
			this->tb_plane2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_plane2->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_plane2->Location = System::Drawing::Point(193, 263);
			this->tb_plane2->Name = L"tb_plane2";
			this->tb_plane2->Size = System::Drawing::Size(88, 26);
			this->tb_plane2->TabIndex = 30;
			this->tb_plane2->Text = L"10,4,-10";
			// 
			// lb_plane
			// 
			this->lb_plane->AutoSize = true;
			this->lb_plane->Location = System::Drawing::Point(25, 263);
			this->lb_plane->Name = L"lb_plane";
			this->lb_plane->Size = System::Drawing::Size(52, 20);
			this->lb_plane->TabIndex = 29;
			this->lb_plane->Text = L"plane:";
			// 
			// tb_plane1
			// 
			this->tb_plane1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_plane1->BackColor = System::Drawing::SystemColors::Window;
			this->tb_plane1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_plane1->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_plane1->Location = System::Drawing::Point(95, 263);
			this->tb_plane1->Name = L"tb_plane1";
			this->tb_plane1->Size = System::Drawing::Size(92, 26);
			this->tb_plane1->TabIndex = 28;
			this->tb_plane1->Text = L"-10,4,-30";
			// 
			// tb_rotate
			// 
			this->tb_rotate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_rotate->BackColor = System::Drawing::SystemColors::Window;
			this->tb_rotate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_rotate->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_rotate->Location = System::Drawing::Point(382, 305);
			this->tb_rotate->Name = L"tb_rotate";
			this->tb_rotate->Size = System::Drawing::Size(100, 26);
			this->tb_rotate->TabIndex = 34;
			this->tb_rotate->Text = L"0,0.6,0";
			// 
			// lb_comp_obj
			// 
			this->lb_comp_obj->AutoSize = true;
			this->lb_comp_obj->Location = System::Drawing::Point(25, 308);
			this->lb_comp_obj->Name = L"lb_comp_obj";
			this->lb_comp_obj->Size = System::Drawing::Size(91, 20);
			this->lb_comp_obj->TabIndex = 33;
			this->lb_comp_obj->Text = L"grid_object:";
			// 
			// tb_name_obj
			// 
			this->tb_name_obj->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_name_obj->BackColor = System::Drawing::SystemColors::Window;
			this->tb_name_obj->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_name_obj->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_name_obj->Location = System::Drawing::Point(122, 305);
			this->tb_name_obj->Name = L"tb_name_obj";
			this->tb_name_obj->Size = System::Drawing::Size(255, 26);
			this->tb_name_obj->TabIndex = 32;
			this->tb_name_obj->Text = L"D:/Game/RayTracing/MakeRayTracing/data/duck.obj";
			// 
			// tb_pos
			// 
			this->tb_pos->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_pos->BackColor = System::Drawing::SystemColors::Window;
			this->tb_pos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_pos->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_pos->Location = System::Drawing::Point(488, 305);
			this->tb_pos->Name = L"tb_pos";
			this->tb_pos->Size = System::Drawing::Size(100, 26);
			this->tb_pos->TabIndex = 35;
			this->tb_pos->Text = L"0,0.4,-23";
			this->tb_pos->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 352);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 20);
			this->label1->TabIndex = 36;
			this->label1->Text = L"light:";
			// 
			// add_mat
			// 
			this->add_mat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->add_mat->Location = System::Drawing::Point(608, 165);
			this->add_mat->Name = L"add_mat";
			this->add_mat->Size = System::Drawing::Size(75, 31);
			this->add_mat->TabIndex = 37;
			this->add_mat->Text = L"add";
			this->add_mat->UseVisualStyleBackColor = true;
			this->add_mat->Click += gcnew System::EventHandler(this, &MyForm::add_mat_Click);
			// 
			// add_sphere
			// 
			this->add_sphere->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->add_sphere->Location = System::Drawing::Point(423, 218);
			this->add_sphere->Name = L"add_sphere";
			this->add_sphere->Size = System::Drawing::Size(75, 31);
			this->add_sphere->TabIndex = 38;
			this->add_sphere->Text = L"add";
			this->add_sphere->UseVisualStyleBackColor = true;
			this->add_sphere->Click += gcnew System::EventHandler(this, &MyForm::add_sphere_Click);
			// 
			// add_plane
			// 
			this->add_plane->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->add_plane->Location = System::Drawing::Point(423, 263);
			this->add_plane->Name = L"add_plane";
			this->add_plane->Size = System::Drawing::Size(75, 31);
			this->add_plane->TabIndex = 39;
			this->add_plane->Text = L"add";
			this->add_plane->UseVisualStyleBackColor = true;
			this->add_plane->Click += gcnew System::EventHandler(this, &MyForm::add_plane_Click);
			// 
			// add_obj
			// 
			this->add_obj->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->add_obj->Location = System::Drawing::Point(718, 305);
			this->add_obj->Name = L"add_obj";
			this->add_obj->Size = System::Drawing::Size(75, 31);
			this->add_obj->TabIndex = 40;
			this->add_obj->Text = L"add";
			this->add_obj->UseVisualStyleBackColor = true;
			this->add_obj->Click += gcnew System::EventHandler(this, &MyForm::add_obj_Click);
			// 
			// add_light
			// 
			this->add_light->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->add_light->Location = System::Drawing::Point(265, 350);
			this->add_light->Name = L"add_light";
			this->add_light->Size = System::Drawing::Size(75, 31);
			this->add_light->TabIndex = 41;
			this->add_light->Text = L"add";
			this->add_light->UseVisualStyleBackColor = true;
			this->add_light->Click += gcnew System::EventHandler(this, &MyForm::add_light_Click);
			// 
			// tb_name_mat
			// 
			this->tb_name_mat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tb_name_mat->BackColor = System::Drawing::SystemColors::Window;
			this->tb_name_mat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_name_mat->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_name_mat->Location = System::Drawing::Point(499, 170);
			this->tb_name_mat->Name = L"tb_name_mat";
			this->tb_name_mat->Size = System::Drawing::Size(103, 26);
			this->tb_name_mat->TabIndex = 42;
			this->tb_name_mat->Text = L"name";
			// 
			// comBoxSphere
			// 
			this->comBoxSphere->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comBoxSphere->FormattingEnabled = true;
			this->comBoxSphere->Location = System::Drawing::Point(247, 223);
			this->comBoxSphere->Name = L"comBoxSphere";
			this->comBoxSphere->Size = System::Drawing::Size(121, 28);
			this->comBoxSphere->TabIndex = 43;
			// 
			// comBoxObj
			// 
			this->comBoxObj->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comBoxObj->FormattingEnabled = true;
			this->comBoxObj->Location = System::Drawing::Point(591, 305);
			this->comBoxObj->Name = L"comBoxObj";
			this->comBoxObj->Size = System::Drawing::Size(121, 28);
			this->comBoxObj->TabIndex = 44;
			// 
			// tb_core
			// 
			this->tb_core->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tb_core->BackColor = System::Drawing::SystemColors::Window;
			this->tb_core->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_core->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->tb_core->Location = System::Drawing::Point(29, 12);
			this->tb_core->Name = L"tb_core";
			this->tb_core->Size = System::Drawing::Size(190, 26);
			this->tb_core->TabIndex = 46;
			this->tb_core->Text = L"ray_tracing.exe";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(805, 629);
			this->Controls->Add(this->tb_core);
			this->Controls->Add(this->comBoxObj);
			this->Controls->Add(this->comBoxSphere);
			this->Controls->Add(this->tb_name_mat);
			this->Controls->Add(this->add_light);
			this->Controls->Add(this->add_obj);
			this->Controls->Add(this->add_plane);
			this->Controls->Add(this->add_sphere);
			this->Controls->Add(this->add_mat);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tb_pos);
			this->Controls->Add(this->tb_rotate);
			this->Controls->Add(this->lb_comp_obj);
			this->Controls->Add(this->tb_name_obj);
			this->Controls->Add(this->comBoxPlane);
			this->Controls->Add(this->tb_plane2);
			this->Controls->Add(this->lb_plane);
			this->Controls->Add(this->tb_plane1);
			this->Controls->Add(this->tb_radius);
			this->Controls->Add(this->lb_sphere);
			this->Controls->Add(this->tb_center);
			this->Controls->Add(this->tb_refraction);
			this->Controls->Add(this->tb_shininess);
			this->Controls->Add(this->tb_rgb);
			this->Controls->Add(this->lab_material);
			this->Controls->Add(this->tb_albedo);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->lab_back);
			this->Controls->Add(this->lb_lights);
			this->Controls->Add(this->tb_light_intensity);
			this->Controls->Add(this->tb_light_pos);
			this->Controls->Add(this->tb_death_cam);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tb_cam_pos);
			this->Controls->Add(this->tb_screen_h);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tb_screen_w);
			this->Controls->Add(this->but1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Enter += gcnew System::EventHandler(this, &MyForm::MyForm_Enter);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void WriteDigit(System::Windows::Forms::TextBox^ box, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) &&
			(e->KeyChar != '.'))
		{
			e->Handled = true;
		}

		// only allow one decimal point
		if ((e->KeyChar == '.') && (box->Text->IndexOf('.') > -1))
		{
			e->Handled = true;
		}
	}
	private: System::Void WriteDigitInt(System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if (!Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void WriteDigitList(System::Windows::Forms::TextBox^ box, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) &&
			(e->KeyChar != '.') && (e->KeyChar != ','))
		{
			e->Handled = true;
		}

		String^ p = ".";
		String^ com = ",";
		//точки и запятые подряд запрещены
		if ((box->Text->EndsWith(p) || box->Text->EndsWith(com)) && 
			((e->KeyChar == '.') || (e->KeyChar == ',')))
		{
			e->Handled = true;
		}
	}

	private: System::Void but1_Click(System::Object^ sender, System::EventArgs^ e) {				
					
		int traccer(const char* scr);
		void add_screen(int w, int h);
		void add_camera(const char* cam);
		void add_material(const float* material);
		void add_sphere(const char* sphere);
		void add_light(const char* light);
		void add_plane(const char* plane);
		void add_object(const char* object);
		void add_background(const char* file);

		String^ str = tb_cam_pos->Text + "," + this->tb_death_cam->Text;
		char* c_cam = (char*)(void*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
		add_camera(c_cam);
		Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)c_cam);

		add_screen(Convert::ToInt32(this->tb_screen_w->Text), Convert::ToInt32(this->tb_screen_h->Text));
		
		c_cam = (char*)(void*)Runtime::InteropServices::
			Marshal::StringToHGlobalAnsi(this->textBox2->Text);
		add_background(c_cam);
		Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)c_cam);

		if (this->lb_lights->Items->Count)
		{
			for each (array<float> ^ m in _materials)
			{
				float mat[9];
				for (size_t i = 0; i < 9; i++) mat[i] = m[i];
				add_material(mat);
			}
			for each (String ^ obj in this->lb_lights->Items)
			{
				char* c_obj = (char*)(void*)Runtime::InteropServices::Marshal::
					StringToHGlobalAnsi((obj->Split(':')[1])->ToString());

				if (obj->Split(':')[0] == "sphere")
				{
					add_sphere(c_obj);
				}
				else if (obj->Split(':')[0] == "plane")
				{
					add_plane(c_obj);
				}
				else if (obj->Split(':')[0] == "light")
				{
					add_light(c_obj);
				}
				else if (obj->Split(':')[0] == "obj")
				{
					char* tmp = (char*)(void*)Runtime::InteropServices::Marshal::
						StringToHGlobalAnsi((obj->Split(':')[1] + ":" + obj->Split(':')[2])->ToString());

					add_object(tmp);

					Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)tmp);
				}

				Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)c_obj);
			}
		}

		char* src = (char*)(void*)Runtime::InteropServices::
			Marshal::StringToHGlobalAnsi(this->tb_core->Text);
		traccer(src);
		Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)src);		
		//Process::Start("D:/Game/RayTracing/x64/Debug/RayTracing.exe");
	}
	private: void add_material(String^ name, array<float>^ mat)
	{
		array<array<float>^>^ buf = _materials;
		_materials->Resize(_materials, _materials->Length + 1);
		for (size_t i = 0; i < buf->Length; i++)
		{
			_materials[i] = buf[i];
		}
		_materials[buf->Length] = mat;
		this->comBoxPlane->Items->Add(name);		
		this->comBoxSphere->Items->Add(name);
		this->comBoxObj->Items->Add(name);
	}
		   
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {		
								
		_materials->Resize(_materials, 0);
		array<float>^ ivory = { 0.6, 0.3, 0.1, 0.0, 0.4f, 0.4f, 0.3f, 50., 1.0 };
		array<float>^ red_rubber = { 0.9, 0.1, 0.0, 0.0,0.3, 0.1, 0.1, 30., 1.0 };
		array<float>^ green_rubber = { 0.9, 0.15, 0.0, 0.0,0.1, 0.5, 0.0, 10., 1.0 };
		array<float>^ glass = { 0.0, 0.5, 0.1, 0.8, 0.6, 0.7, 0.8, 125., 1.5 };
		array<float>^ mirror = { 0.0, 10.0, 0.8, 0.0,1.0, 1.0, 1.0, 1425., 1.0 };
		
		add_material("ivory", ivory);
		add_material("red_rubber", red_rubber);
		add_material("green_rubber", green_rubber);
		add_material("glass", glass);
		add_material("mirror", mirror);
		
		this->comBoxPlane->SelectedIndex = 0;		
		this->comBoxObj->SelectedIndex = 0;
		this->comBoxSphere->SelectedIndex = 0;
	}
	
private: System::Void MyForm_Enter(System::Object^ sender, System::EventArgs^ e) {
	
}


private: System::Void listBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {	
	if (e->KeyCode == Keys::Delete)
	{
		//listBox1->Items->Remove(listBox1->SelectedItem);
	}
}

private: System::Void tb_screen_h_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tb_screen_w_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tb_screen_w_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	WriteDigitInt(e);
}
private: System::Void tb_screen_h_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	WriteDigitInt(e);
}
private: System::Void tb_death_cam_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	WriteDigit(this->tb_death_cam,e);
}
private: System::Void tb_cam_pos_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	WriteDigitList(this->tb_cam_pos, e);
}
private: System::Void tb_light_intensity_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	WriteDigit(this->tb_light_intensity, e);
}
private: System::Void tb_light_pos_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	WriteDigitList(this->tb_light_pos, e);	
}
private: System::Void tb_light_pos_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter)
	{
		String^ pos = this->tb_light_pos->Text;
		String^ intens = this->tb_light_intensity->Text;
		lb_lights->Items->Add(pos + "," + intens);
	}
}
private: System::Void tb_light_intensity_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter)
	{
		String^ pos = this->tb_light_pos->Text;
		String^ intens = this->tb_light_intensity->Text;
		lb_lights->Items->Add(pos + "," + intens);
	}
}
private: System::Void lb_lights_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Delete)
	{
		lb_lights->Items->Remove(lb_lights->SelectedItem);
	}
}


private: System::Void grid_lights_EditingControlShowing(System::Object ^ sender, System::Windows::Forms::DataGridViewEditingControlShowingEventArgs ^ e)
{
	_editControl = e->Control;
	_editControl->KeyPress += gcnew KeyPressEventHandler(this, &MyForm::EditingControl_KeyPress); //подпись на событие ввода значений с клавиатуры
}

private: System::Void grid_lights_CellEndEdit(System::Object ^ sender, System::Windows::Forms::DataGridViewCellEventArgs ^ e)
{

	//Может пригодится. Проверка на неверное значение на этапе закрытия элемента управления редактирования. Есть 1 минус - вставка при помощи комбинации CTRL+V может обойти этот этап
	//String ^s = _editControl->Text;

	//if (_editControl->Text == L"-")
	// ((DataGridView^)sender)[e->RowIndex, e->ColumnIndex]->Value = String::Empty; //удаление значения, если введено только "-"


	_editControl->KeyPress -= gcnew KeyPressEventHandler(this, &MyForm::EditingControl_KeyPress);
}

private: System::Void EditingControl_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	if (!Char::IsControl(e->KeyChar) && 
		!Char::IsDigit(e->KeyChar) && (e->KeyChar != '.'))
	{
		e->Handled = true;
	}

	DataGridViewTextBoxEditingControl^ cell = ((DataGridViewTextBoxEditingControl^)sender);	
	if ((e->KeyChar == '.') && (cell->Text->IndexOf('.') > -1))
	{
		e->Handled = true;
	}
}
private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void add_mat_Click(System::Object^ sender, System::EventArgs^ e) {

	array<float>^ mat = { 0,0,0,0, 0,0,0 ,0,0 };
	array<String^>^ albedo = tb_albedo->Text->Split(',');
				
	mat[0] = Convert::ToDouble(albedo[0]->Replace('.', ','));
	mat[1] = Convert::ToDouble(albedo[1]->Replace('.', ','));
	mat[2] = Convert::ToDouble(albedo[2]->Replace('.', ','));
	mat[3] = Convert::ToDouble(albedo[3]->Replace('.', ','));

	array<String^>^ rgb = tb_rgb->Text->Split(',');
	mat[4] = Convert::ToDouble(rgb[0]->Replace('.', ','));
	mat[5] = Convert::ToDouble(rgb[1]->Replace('.', ','));
	mat[6] = Convert::ToDouble(rgb[2]->Replace('.', ','));

	mat[7] = Convert::ToDouble(tb_shininess->Text->Replace('.', ','));
	mat[8] = Convert::ToDouble(tb_refraction->Text->Replace('.', ','));

	add_material(tb_name_mat->Text, mat);	
}
private: System::Void add_sphere_Click(System::Object^ sender, System::EventArgs^ e) {
	
	lb_lights->Items->Add("sphere:" + tb_center->Text + "," + tb_radius->Text +
		"," + comBoxSphere->SelectedIndex);	
}
private: System::Void add_plane_Click(System::Object^ sender, System::EventArgs^ e) {
	lb_lights->Items->Add("plane:" + tb_plane1->Text + "," + tb_plane2->Text +
		"," + comBoxPlane->SelectedIndex);
}
private: System::Void add_obj_Click(System::Object^ sender, System::EventArgs^ e) {
	lb_lights->Items->Add("obj:" +  tb_rotate->Text +
		"," + tb_pos->Text + "," + comBoxObj->SelectedIndex + ","
	+ tb_name_obj->Text);
}
private: System::Void add_light_Click(System::Object^ sender, System::EventArgs^ e) {
	lb_lights->Items->Add("light:" + tb_light_pos->Text + "," + tb_light_intensity->Text);
}
};
}
