#pragma once
#include <Wt/WContainerWidget.h>

#include <Wt/WButtonGroup.h>
#include <Wt/WSpinBox.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WRadioButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WCheckBox.h>

#include <Wt/WString.h>
#include <regex>

#include "101-Stylus/Tailwind/Base.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

class ColorsWidget : public Wt::WContainerWidget
{
public:
	ColorsWidget(Propriety proprietyColor);
	void setCustomValueString(std::string custom_start) { custom_start_ = custom_start; };

	// std::string getValue() { return current_value; };
	std::string getValue();
	void setValue(std::string className = "none");
	void setCustom(bool custom);

	std::string custom_start_;

	Wt::WContainerWidget *color_picker_display;
	Wt::WContainerWidget *colors_wrapper;
	Wt::WText *color_picker_text;

	std::shared_ptr<Wt::WButtonGroup> colors_group;
	Wt::WSpinBox *opacity_widget;
	Wt::WLineEdit *lineEdit_custom_value_;
	Wt::WCheckBox *checkbox_important_;
	Wt::WCheckBox *checkBox_custom_value_;

	std::vector<std::string> colors_vector = {};
	int getIndexOfStringInVector(std::string str, std::vector<std::string> vec);

	Wt::Signal<std::string> &classChanged() { return classChanged_; }
	std::string color_class = "none";	// color class from picker
	std::string opacity_value = "none"; // ...-.../100
	std::string picker_value = "none";	// class to be applied
	std::string custom_value = "none";	// custom value
	std::string display_bg_class = "bg-white";

private:
	void setDisplayBackground(std::string new_class);
	Wt::Signal<std::string> classChanged_;
	Propriety proprietyColor_;
};