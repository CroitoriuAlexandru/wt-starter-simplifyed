#include "101-Stylus/ClassChangers/ColorsWidget.h"

ColorsWidget::ColorsWidget(Propriety proprietyColor)
	: Wt::WContainerWidget(),
	  colors_group(std::make_shared<Wt::WButtonGroup>()),
	  proprietyColor_(proprietyColor)
{
	setStyleClass("flex items-center w-fit relative");

	checkbox_important_ = addWidget(std::make_unique<Wt::WCheckBox>("!"));
	auto radioButton_none = addWidget(std::make_unique<Wt::WRadioButton>("X"));
	color_picker_display = addWidget(std::make_unique<Wt::WContainerWidget>());
	lineEdit_custom_value_ = addWidget(std::make_unique<Wt::WLineEdit>());
	auto opacity_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
	checkBox_custom_value_ = addWidget(std::make_unique<Wt::WCheckBox>("]"));

	opacity_wrapper->setStyleClass("");
	// colors_picker_wrapper->setStyleClass("flex flex-row-reverse whitespace-nowrap justify-between items-center w-full");
	lineEdit_custom_value_->setStyleClass("px-1 w-full grow rounded-md h-full text-center appearance-none min-w-[70px] border border-solid border-black border-gray-700 bg-gray-800");

	// opacity_wrapper->addWidget(std::make_unique<Wt::WText>("Opacity"))->setStyleClass("font-bold text-neutral-400 text-sm ml-auto mr-1");
	checkBox_custom_value_->setStyleClass("text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:text [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0 [&>span]:hover:bg-neutral-950 rounded-md ");
	checkbox_important_->setStyleClass("text-center p-0.5 [&>input]:hidden [&>span]:px-1 [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0  rounded-md font-bold hover:bg-neutral-950");

	radioButton_none->setStyleClass("[&>input]:hidden "
									"m-0.5 mb-1 "
									"[&>span]:font-bold "
									"[&>span]:text-red-700 "
									"[&>span]:bg-gray-900 "
									"[&>span]:text-bold "
									"[&>span]:text-gray-200 "
									"[&>span]:p-0.5 "
									"[&>span]:px-1 "
									"[&>span]:border-2 "
									"[&>span]:border-solid "
									"[&>span]:border-gray-600 "
									"[&>span]:rounded-md "
									"[&>input:checked~span]:bg-gray-300 "
									"[&>input:checked~span]:text-gray-900");

	opacity_widget = opacity_wrapper->addWidget(std::make_unique<Wt::WSpinBox>());

	opacity_widget->setRange(0, 100);
	opacity_widget->setValue(100);
	opacity_widget->setStyleClass("px-1 w-[60px] grow rounded-md h-full text-center appearance-none min-w-[40px] border border-solid border-gray-700 bg-gray-800");

	color_picker_display->setStyleClass("cursor-pointer px-2 min-h-[16px] text-gray-500 text-center focus:outline rounded mr-2 border border-solid border-neutral-300 bg-contain " + display_bg_class);
	color_picker_text = color_picker_display->addWidget(std::make_unique<Wt::WText>("none"));
	color_picker_display->setCanReceiveFocus(true);

	colors_wrapper = color_picker_display->addWidget(std::make_unique<Wt::WContainerWidget>());
	colors_wrapper->clicked().preventPropagation();
	colors_wrapper->setStyleClass("z-50 w-[270px] absolute top-8 right-2 p-1 bg-gradient-to-br from-gray-700 to-gray-600 rounded-md outline outline-gray-800");
	colors_wrapper->hide();

	int index = 0;
	colors_vector.push_back("none");
	colors_group->addButton(radioButton_none, index);
	index++;

	auto class_name = proprietyColor.class_name;
	for (auto color : proprietyColor.tailwind_config_->color_variants)
	{
		std::string color_class_ = class_name + "-" + color.first;

		// a new row is created for each color
		auto row_wrapper = colors_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		row_wrapper->setStyleClass("flex justify-between");

		for (auto variant : color.second)
		{
			auto btn = row_wrapper->addWidget(std::make_unique<Wt::WRadioButton>(" "));
			auto separator = "";
			if (color.first.compare("") != 0)
			{
				separator = "-";
			}
			std::string bg_color_class = color.first + separator + variant.first;
			std::string full_class_name = color_class_ + separator + variant.first;
			Wt::WString tooltip_text = "not set yet";

			std::string btn_styles = R"(
					flex flex-col font-bold text-[11px] cursor-pointer
					[&>input]:hidden [&>span]:hover:ring-[1px] 
					[&>input:checked_+_span]:ring-[1px] 
					[&>input:checked_+_span]:ring-gray-500  
					[&>input:checked_+_span]:ring-[1px] 
					[&>input:checked_+_span]:z-50)";
			btn->setStyleClass(btn_styles);

			if (variant.first.compare("inherit") == 0)
			{
				btn->setText("inherit");
				btn->addStyleClass("");
			}
			else if (variant.first.compare("current") == 0)
			{
				btn->setText("current");
				btn->addStyleClass("");
			}
			else if (variant.first.compare("transparent") == 0)
			{
				btn->setText("transparent");
				btn->addStyleClass("");
			}
			else if (variant.first.compare("black") == 0)
			{
				btn->setText("black");
				btn->addStyleClass("");
			}
			else if (variant.first.compare("white") == 0)
			{
				btn->setText("white");
				btn->addStyleClass("");
			}
			else
			{
				// [&>span]:px-2
				btn->addStyleClass("[&>span]:py-1.5 [&>span]:m-px grow [&>span]:min-w-full]");
				btn->addStyleClass("[&>span]:bg-" + bg_color_class + " ");
			}
			btn->setToolTip(Wt::WString().tr("tooltip-styleClasses").arg(tooltip_text).arg(full_class_name), Wt::TextFormat::UnsafeXHTML);

			colors_group->addButton(btn, index);
			colors_vector.push_back(full_class_name);
			index++;
		}
	}

	color_picker_display->clicked().connect(this, [=]()
											{ 
		if(!lineEdit_custom_value_->isHidden()) return;
		colors_wrapper->isHidden() ? colors_wrapper->show() : colors_wrapper->hide(); });
	color_picker_display->doubleClicked().connect([=]()
												  {
		setValue("none");
		classChanged_.emit("none"); });

	classChanged_.connect(this, [=](std::string new_class)
						  { setDisplayBackground(new_class); });

	colors_group->checkedChanged().connect(this, [=]()
										   { 
			picker_value = colors_vector[colors_group->checkedId()]; 
			if(picker_value.compare("none") == 0) {
				colors_wrapper->hide();
			}
			classChanged_.emit(getValue()); });

	opacity_widget->valueChanged().connect(this, [=](int value)
										   { 
		if(value > 100) {
			opacity_widget->setValue(100); 
		}
		opacity_value = std::to_string(value);
		classChanged_.emit(getValue()); });

	lineEdit_custom_value_->enterPressed().connect(this, [=]()
												   {
		custom_value = lineEdit_custom_value_->text().toUTF8();
		classChanged_.emit(getValue()); });
	lineEdit_custom_value_->doubleClicked().connect([=]()
													{
		setValue("none");
		classChanged_.emit("none"); });

	checkBox_custom_value_->clicked().connect(this, [=]()
											  { setCustom(checkBox_custom_value_->isChecked()); });

	checkbox_important_->clicked().connect(this, [=]()
										   {

		if(getValue().compare("none") != 0) classChanged_.emit(getValue()); });
}

void ColorsWidget::setDisplayBackground(std::string new_class)
{

	color_picker_text->setText(new_class);
	std::string bg_class = new_class.substr(new_class.find("-") + 1, new_class.length() - new_class.find("-") + 1);

	if (bg_class.compare("inherit") == 0 ||
		bg_class.compare("current") == 0 ||
		bg_class.compare("transparent") == 0 ||
		bg_class.compare("black") == 0)
		bg_class = "none";
	else
		bg_class = "bg-" + bg_class;

	color_picker_display->removeStyleClass(display_bg_class);
	display_bg_class = bg_class;
	color_picker_display->addStyleClass(display_bg_class);
}

void ColorsWidget::setCustom(bool custom)
{
	if (custom_start_.compare("none") == 0)
		return;
	if (custom)
	{
		checkBox_custom_value_->setChecked(true);
		lineEdit_custom_value_->show();
		color_picker_display->toggleStyleClass("!px-2", true, true);
		color_picker_display->setCanReceiveFocus(false);
		color_picker_text->hide();
		// colors_picker_wrapper->hide();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-500", true, true);
	}
	else
	{
		checkBox_custom_value_->setChecked(false);
		lineEdit_custom_value_->hide();
		color_picker_display->toggleStyleClass("!px-2", false, true);
		color_picker_display->setCanReceiveFocus(true);
		color_picker_text->show();
		// colors_picker_wrapper->show();
		checkBox_custom_value_->toggleStyleClass("[&>span]:text-green-500", false, true);
	}
}

int ColorsWidget::getIndexOfStringInVector(std::string str, std::vector<std::string> vec)
{
	for (int index = 0; index < vec.size(); ++index)
	{
		if (vec[index].compare(str) == 0)
			return index;
	}
	return -1;
}

void ColorsWidget::setValue(std::string className)
{

	color_class = className;
	if (className.compare("none") == 0)
	{
		colors_group->setCheckedButton(0);
		opacity_widget->setValue(100);
		setCustom(false);
		color_class = "none";
		opacity_value = "none";
		picker_value = "none";
		custom_value = "none";
		setDisplayBackground("none");
		colors_wrapper->hide();
		return;
	}
	if (className[0] == '!')
	{
		checkbox_important_->setChecked(true);
		className = className.substr(1, className.length() - 1);
	}
	else
	{
		checkbox_important_->setChecked(false);
	}
	std::string class_name = className.substr(0, className.find("/"));
	int index = getIndexOfStringInVector(class_name, colors_vector);
	if (index == -1) // custom value
	{
		setCustom(true);
		// remove text until first [
		std::string custom_input_text = className.substr(className.find("[") + 1, className.length() - className.find("[") - 1);
		// remove text after first ]
		custom_input_text = custom_input_text.substr(0, custom_input_text.find("]"));

		lineEdit_custom_value_->setText(custom_input_text);
		custom_value = custom_input_text;
	}
	else
	{ // value found in colors_vector
		setCustom(false);
		custom_value = "none";
		std::string color_class_name = colors_vector[index];
		colors_group->button(index)->setChecked(true);
		picker_value = color_class_name;
	}

	if (className.find("/") != std::string::npos)
	{
		std::string opacity = className.substr(className.find("/") + 1, className.length() - className.find("/") - 1);
		if (opacity.find("[") != std::string::npos)
		{
			opacity = opacity.substr(opacity.find("[") + 2, opacity.length() - opacity.find("[") - 2);
			opacity = opacity.substr(0, opacity.find("]"));
		}
		opacity_widget->setValue(std::stoi(opacity));
	}
	setDisplayBackground(className);
}

std::string ColorsWidget::getValue()
{

	std::string selectedClass = "none";
	if (checkBox_custom_value_->isChecked() && custom_value.compare("none") != 0)
	{
		selectedClass = custom_start_ + "[" + custom_value + "]";
	}
	else if (picker_value.compare("none") != 0)
	{
		selectedClass = picker_value;
	}
	if (checkbox_important_->isChecked())
	{
		selectedClass = "!" + selectedClass;
	}
	if (opacity_value.compare("none") != 0 && opacity_value.compare("100") != 0)
	{
		bool found;
		for (auto opacity : proprietyColor_.tailwind_config_->variants_and_css["opacity"])
		{
			if (opacity.first.compare(opacity_value) == 0)
				found = true;
		}
		if (!found)
			selectedClass += "/[." + opacity_value + "]";
		else
			selectedClass += "/" + opacity_value;
	}
	return selectedClass;
}
