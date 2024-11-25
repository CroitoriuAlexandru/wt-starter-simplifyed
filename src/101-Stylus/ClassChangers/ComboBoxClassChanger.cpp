#include "101-Stylus/ClassChangers/ComboBoxClassChanger.h"
#include <iostream>
#include <regex>
#include <Wt/WApplication.h>

void ComboBoxClassChanger::setCustom(bool custom)
{
	if (custom_start_.compare("none") == 0)
		return;
	if (custom)
	{
		checkBox_custom_value_->setChecked(true);
		comboBox_class->hide();
		lineEdit_custom_value_->show();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-400", true, true);
	}
	else
	{
		checkBox_custom_value_->setChecked(false);
		lineEdit_custom_value_->hide();
		comboBox_class->show();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-400", false, true);
	}
}

void ComboBoxClassChanger::setCustomValueString(std::string custom_start)
{
	custom_start_ = custom_start;

	checkBox_custom_value_->show();

	lineEdit_custom_value_->enable();
	checkBox_custom_value_->enable();

	checkBox_custom_value_->clicked().connect(this, [=]()
											  {
		if(checkBox_custom_value_->isChecked()){
			setCustom(true);
		}else{
			setCustom(false);
		} });

	lineEdit_custom_value_->keyWentDown().connect(this, [=](Wt::WKeyEvent e)
												  { Wt::WApplication::instance()->globalKeyWentDown().emit(e); });

	lineEdit_custom_value_->enterPressed().connect(this, [=]()
												   {
		if(lineEdit_custom_value_->text().toUTF8() != ""){
			classChanged_.emit(getValue());
		}
		lineEdit_custom_value_->setFocus(); });
	lineEdit_custom_value_->doubleClicked().connect([=]()
													{
		setValue("none");
		classChanged_.emit("none"); });
}

ComboBoxClassChanger::ComboBoxClassChanger(std::vector<std::string> classes)
	: Wt::WContainerWidget()
{
	setStyleClass("flex justify-betwen items-center w-full text-[14px] py-0.5 rounded-sm ");
	// setToolTip(Wt::WString().tr("stylus-tooltip-style-class-widget").arg("first argument").arg("seccond argument"), Wt::TextFormat::UnsafeXHTML);

	checkbox_important_ = addWidget(std::make_unique<Wt::WCheckBox>("!"));
	comboBox_class = addWidget(std::make_unique<Wt::WComboBox>());
	lineEdit_custom_value_ = addWidget(std::make_unique<Wt::WLineEdit>());
	checkBox_custom_value_ = addWidget(std::make_unique<Wt::WCheckBox>("]"));

	lineEdit_custom_value_->hide();
	lineEdit_custom_value_->disable();
	checkBox_custom_value_->hide();
	checkBox_custom_value_->disable();

	// set styles
	comboBox_class->setStyleClass("px-1 w-full grow rounded-md h-full text-center appearance-none min-w-[70px] border border-solid border-gray-500 bg-gray-600");
	checkBox_custom_value_->setStyleClass("text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md ");

	checkbox_important_->setStyleClass("text-center p-0.5 [&>input]:hidden [&>input:checked_~span]:text-red-500 [&>span]:px-1 [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0  rounded-md font-bold");
	lineEdit_custom_value_->setStyleClass("bg-gray-600 text-green-400 px-1 w-full grow rounded-md h-full  text-center border-gray-500 appearance-none min-w-[70px]");

	setComboBoxValues(classes);

	checkbox_important_->clicked().connect(this, [=]()
										   { classChanged_.emit(getValue()); });

	classChanged_.connect(this, [=](std::string className)
						  {
		if(getValue().compare("none") == 0) 
			comboBox_class->toggleStyleClass("text-green-400", false);
			else 
			comboBox_class->toggleStyleClass("text-green-400", true); });

	comboBox_class->doubleClicked().connect([=]()
											{
		setValue("none");
		classChanged_.emit("none"); });
	comboBox_class->keyWentDown().connect(this, [=](Wt::WKeyEvent e)
										  { Wt::WApplication::instance()->globalKeyWentDown().emit(e); });
	comboBox_class->sactivated().connect(this, [=](Wt::WString className)
										 {
		classChanged_.emit(className.toUTF8());
		comboBox_class->setFocus(true); });

	// comboBox_class->keyWentUp().connect(this, [=](Wt::WKeyEvent e){
	// 	if(e.modifiers() == Wt::KeyboardModifier::Control)
	// 	{
	// 		if(e.key() == Wt::Key::Delete){
	// 			// reset to default
	// 			comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
	// 			checkbox_important_->setChecked(false);
	// 			checkbox_important_->toggleStyleClass("text-red-500", false, true);
	// 			classChanged_.emit(getValue());
	// 			comboBox_class->setFocus();
	// 		}else if (e.key() == Wt::Key::End){
	// 			// toggle important
	// 			if(checkbox_important_->isChecked()) {
	// 				checkbox_important_->setChecked(false);
	// 			} else {
	// 				checkbox_important_->setChecked(true);
	// 			}
	// 		}else if (e.key() == Wt::Key::Home){
	// 			// toggle custom value
	// 			if(checkBox_custom_value_->isChecked()) {
	// 				setCustom(false);
	// 				comboBox_class->setFocus(true);
	// 			} else {
	// 				setCustom(true);
	// 				lineEdit_custom_value_->setFocus(true);
	// 			}
	// 		}

	// 	}
	// 	 if (e.key() == Wt::Key::Escape){
	// 		auto app = Wt::WApplication::instance();
	// 		auto appDevWidget = app->findWidget("app-dev-widget");
	// 		if(appDevWidget != nullptr) appDevWidget->setFocus(true);
	// 	}
	// });

	setValue("none");
}

void ComboBoxClassChanger::setComboBoxValues(std::vector<std::string> values)
{
	comboBox_class->clear();
	for (auto value : values)
	{
		comboBox_class->addItem(value);
	}
}

std::string ComboBoxClassChanger::getValue()
{
	std::string selectedClass = "";

	if (custom_start_.compare("none") != 0 &&
		checkBox_custom_value_->isChecked() &&
		lineEdit_custom_value_->text().toUTF8() != "")
	{
		selectedClass = custom_start_ + "[" + lineEdit_custom_value_->valueText().toUTF8() + "]";
	}
	else
	{
		selectedClass = comboBox_class->currentText().toUTF8();
	}
	if (checkbox_important_->isChecked() && selectedClass.compare(defaultValue) != 0)
	{
		selectedClass = "!" + selectedClass;
	}

	return selectedClass;
}

void ComboBoxClassChanger::setValue(std::string className)
{

	if (className.compare("none") == 0)
	{
		comboBox_class->setCurrentIndex(comboBox_class->findText(defaultValue, Wt::MatchFlag::StringExactly));
		if (custom_start_.compare("none") != 0)
		{
			setCustom(false);
		}
		comboBox_class->toggleStyleClass("text-green-400", false);
		checkbox_important_->setChecked(false);
		return;
	}

	comboBox_class->toggleStyleClass("text-green-400", true);
	// check for ! at the start of the class
	if (className.find("!") != std::string::npos)
	{
		checkbox_important_->setChecked(true);
		className = className.substr(1, className.length() - 1);
	}
	else
	{
		checkbox_important_->setChecked(false);
	}

	if (className.find("]") != std::string::npos)
	{
		checkBox_custom_value_->setChecked(true);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		// find the next '[' position in className
		int pos = className.find("[");
		if (pos != std::string::npos)
		{
			// find the next ']' position in className
			int pos2 = className.find("]");
			if (pos2 != std::string::npos)
			{
				// get the value between '[' and ']'
				std::string value = className.substr(pos + 1, pos2 - pos - 1);
				lineEdit_custom_value_->setText(value);
			}
		}
	}
	else
	{
		checkBox_custom_value_->setChecked(false);
		checkBox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
	}
}
void ComboBoxClassChanger::disable(bool disable)
{
	if (disable)
	{
		comboBox_class->disable();
		checkBox_custom_value_->disable();
		checkbox_important_->disable();
		lineEdit_custom_value_->disable();
	}
	else
	{
		comboBox_class->enable();
		checkBox_custom_value_->enable();
		checkbox_important_->enable();
		lineEdit_custom_value_->enable();
	}
}
