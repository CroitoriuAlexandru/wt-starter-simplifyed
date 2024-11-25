#include "101-Stylus/TCategory/SizingP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

SizingP::SizingP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
	: BasePanel(tailwind_config, extra_widgets_wrapper)
{
	classes_data_map_ = {
		{"width", "none"},
		{"min_width", "none"},
		{"max_width", "none"},
		{"height", "none"},
		{"min_height", "none"},
		{"max_height", "none"}};

	std::map<std::string, Propriety> classes_vec_map = {
		{"width", tailwind_config_->sizing.width},
		{"min_width", tailwind_config_->sizing.minWidth},
		{"max_width", tailwind_config_->sizing.maxWidth},
		{"height", tailwind_config_->sizing.height},
		{"min_height", tailwind_config_->sizing.minHeight},
		{"max_height", tailwind_config_->sizing.maxHeight}};

	title->setText("Sizing");

	m_main_toggler_ = addToggler(centralWidget, "|");

	centralWidget->hide();

	auto width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto height_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	centralWidget->addStyleClass("flex w-full text-center");
	width_wrapper->setStyleClass("w-1/2");
	height_wrapper->setStyleClass("w-1/2");

	// links to docs
	auto width_anchor = width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["width"].docs_link, "Width")));
	auto height_anchor = height_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["height"].docs_link, "Height")));
	// width_anchor->addStyleClass("text-center self-center");
	// height_anchor->addStyleClass("text-center self-center");
	combobox_map_["width"] = width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["width"].getClasses()));
	combobox_map_["min_width"] = width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["min_width"].getClasses()));
	combobox_map_["max_width"] = width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["max_width"].getClasses()));

	combobox_map_["height"] = height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["height"].getClasses()));
	combobox_map_["min_height"] = height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["min_height"].getClasses()));
	combobox_map_["max_height"] = height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["max_height"].getClasses()));

	// signals for default classes for tailwind
	for (auto &[key, combobox] : combobox_map_)
	{
		combobox->classChanged().connect(this, [=](std::string className)
										 {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
		if (classes_vec_map[key].custom_value)
			combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
	}
	setExtraWidgets(classes_vec_map);
};

void SizingP::setCustomTestValues()
{
	classes_data_map_["width"] = "w-14";
	classes_data_map_["height"] = "h-14";
	classes_data_map_["min_width"] = "min-w-6";
	classes_data_map_["min_height"] = "min-h-6";
	classes_data_map_["max_width"] = "max-w-sm";
	classes_data_map_["max_height"] = "max-h-16";
}
