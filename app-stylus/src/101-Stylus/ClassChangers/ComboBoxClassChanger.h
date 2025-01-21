#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WSpinBox.h>
#include <Wt/WSignal.h>
#include <Wt/WContainerWidget.h>
#include <vector>
#include <string>
#include <regex>

#include <Wt/WRadioButton.h>

#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include <Wt/WApplication.h>

class ComboBoxClassChanger : public Wt::WContainerWidget
{
public:
	ComboBoxClassChanger(std::vector<std::string> classes);

	void setComboBoxValues(std::vector<std::string> values);

	void setCustomValueString(std::string custom_start);
	std::string getValue();
	void setValue(std::string className = "none");

	void setCustom(bool custom);
	void disable(bool disable);

	Wt::WCheckBox *checkbox_important_;
	Wt::WComboBox *comboBox_class;
	Wt::WLineEdit *lineEdit_custom_value_;
	Wt::WCheckBox *checkBox_custom_value_;

	Wt::Signal<std::string> &classChanged() { return classChanged_; }
	void setDefaultValue(std::string defaultValue) { this->defaultValue = defaultValue; };

private:
	std::string defaultValue = "none";

	std::string custom_start_ = "none";
	Wt::Signal<std::string> classChanged_;
};