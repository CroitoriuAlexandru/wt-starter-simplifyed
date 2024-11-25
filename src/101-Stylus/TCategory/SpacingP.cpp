#include "101-Stylus/TCategory/SpacingP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

SpacingP::SpacingP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
	: BasePanel(tailwind_config, extra_widgets_wrapper)
{
	classes_data_map_ = {
		{"padding", "none"},
		{"padding_x", "none"},
		{"padding_y", "none"},
		{"padding_t", "none"},
		{"padding_l", "none"},
		{"padding_r", "none"},
		{"padding_b", "none"},
		{"margin", "none"},
		{"margin_x", "none"},
		{"margin_y", "none"},
		{"margin_t", "none"},
		{"margin_l", "none"},
		{"margin_r", "none"},
		{"margin_b", "none"},
		{"space_x", "none"},
		{"space_y", "none"},
		{"space_x_reverse", "none"},
		{"space_y_reverse", "none"}};

	std::map<std::string, Propriety> classes_vec_map{
		{"margin", tailwind_config_->spacing.margin},
		{"margin_x", tailwind_config_->spacing.margin_x},
		{"margin_y", tailwind_config_->spacing.margin_y},
		{"margin_t", tailwind_config_->spacing.margin_t},
		{"margin_l", tailwind_config_->spacing.margin_l},
		{"margin_r", tailwind_config_->spacing.margin_r},
		{"margin_b", tailwind_config_->spacing.margin_b},
		{"padding", tailwind_config_->spacing.padding},
		{"padding_x", tailwind_config_->spacing.padding_x},
		{"padding_y", tailwind_config_->spacing.padding_y},
		{"padding_t", tailwind_config_->spacing.padding_t},
		{"padding_l", tailwind_config_->spacing.padding_l},
		{"padding_r", tailwind_config_->spacing.padding_r},
		{"padding_b", tailwind_config_->spacing.padding_b},
		{"space_x", tailwind_config_->spacing.spaceBetween_x},
		{"space_y", tailwind_config_->spacing.spaceBetween_y},
		{"space_x_reverse", tailwind_config_->spacing.spaceXReverse},
		{"space_y_reverse", tailwind_config_->spacing.spaceYReverse}};

	// for (auto &[key, prop] : classes_vec_map)
	// {
	// 	if (prop.getClasses().size() > 1)
	// 	{
	// 		std::reverse(prop.getClasses().begin() + 1, prop.getClasses().end());
	// 	}
	// }

	title->setText("Spacing");

	auto main_directions_wrapper_ = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto sides_wrapper_ = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto spacing_wrapper_ = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	m_show_main_directions_toggler_ = addToggler(main_directions_wrapper_, "|");
	m_show_sides_toggler_ = addToggler(sides_wrapper_, "||");
	m_show_spacing_toggler_ = addToggler(spacing_wrapper_, "|||");

	main_directions_wrapper_->hide();
	sides_wrapper_->hide();
	spacing_wrapper_->hide();

	auto space_header_wrapper = spacing_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto space_body_wrapper = spacing_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto margin_wrapper = main_directions_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto padding_wrapper = main_directions_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto direction_first_wrapper = sides_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_seccond_wrapper = sides_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_third_wrapper = sides_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto direction_fourth_wrapper = sides_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());

	// links to docs
	margin_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["margin"].docs_link, "Margin")));
	padding_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["padding"].docs_link, "Padding")));
	space_header_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["space_x"].docs_link, "Space Between")));

	auto space_x_wrapper = space_body_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto space_y_wrapper = space_body_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	centralWidget->addStyleClass("flex flex-col w-full");

	main_directions_wrapper_->setStyleClass("flex text-center w-full");
	margin_wrapper->setStyleClass("w-1/2");
	padding_wrapper->setStyleClass("w-1/2");

	sides_wrapper_->setStyleClass("my-6 mx-auto px-4 min-h-[90px] w-4/5  border-[4px] border-dashed border-neutral-500 flex flex-col justify-between items-stretch");
	direction_first_wrapper->setStyleClass("flex mb-1 flex-col w-fit mx-auto -mt-7");
	direction_seccond_wrapper->setStyleClass("mb-1 flex justify-between -mx-12 space-x-6");
	direction_third_wrapper->setStyleClass("mb-1 flex justify-around -mx-8 space-x-1");
	direction_fourth_wrapper->setStyleClass("flex flex-col w-fit mx-auto -mb-7");

	// spacing_wrapper_->setStyleClass("flex flex-wrap");
	space_header_wrapper->setStyleClass("flex");
	space_body_wrapper->setStyleClass("flex");
	space_x_wrapper->setStyleClass("w-1/2");
	space_y_wrapper->setStyleClass("w-1/2");

	combobox_map_["margin"] = margin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin"].getClasses()));
	combobox_map_["margin_x"] = margin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin_x"].getClasses()));
	combobox_map_["margin_y"] = margin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin_y"].getClasses()));

	combobox_map_["padding"] = padding_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding"].getClasses()));
	combobox_map_["padding_x"] = padding_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding_x"].getClasses()));
	combobox_map_["padding_y"] = padding_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding_y"].getClasses()));

	combobox_map_["margin_t"] = direction_first_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin_t"].getClasses()));
	combobox_map_["padding_t"] = direction_first_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding_t"].getClasses()));

	combobox_map_["margin_l"] = direction_seccond_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin_l"].getClasses()));
	combobox_map_["margin_r"] = direction_seccond_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin_r"].getClasses()));

	combobox_map_["padding_l"] = direction_third_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding_l"].getClasses()));
	combobox_map_["padding_r"] = direction_third_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding_r"].getClasses()));

	combobox_map_["margin_b"] = direction_fourth_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["margin_b"].getClasses()));
	combobox_map_["padding_b"] = direction_fourth_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["padding_b"].getClasses()));

	checkbox_map_["space_x_reverse"] = space_x_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Space X Reverse"));
	checkbox_map_["space_y_reverse"] = space_y_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Space Y Reverse"));

	combobox_map_["space_y"] = space_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["space_y"].getClasses()));
	combobox_map_["space_x"] = space_x_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["space_x"].getClasses()));

	// signals
	for (auto &[key, combobox] : combobox_map_)
	{
		combobox->classChanged().connect(this, [=](std::string className)
										 {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
		if (classes_vec_map[key].custom_value)
			combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
	}

	checkbox_map_["space_x_reverse"]->changed().connect(this, [=]()
														{ 
			if(checkbox_map_["space_x_reverse"]->isChecked())
				classes_data_map_["space_x_reverse"] = "space-x-reverse"; 
			else 
				classes_data_map_["space_x_reverse"] = "none";
			styleChanged_.emit(getStyles()); });
	checkbox_map_["space_x_reverse"]->changed().connect(this, [=]()
														{ 
			if(checkbox_map_["space_x_reverse"]->isChecked())
				classes_data_map_["space_y_reverse"] = "space-y-reverse"; 
			else 
				classes_data_map_["space_y_reverse"] = "none";
			styleChanged_.emit(getStyles()); });
	setExtraWidgets(classes_vec_map);
	// std::cout << "combobox_map_ : \n";
	// for(auto& [key, value] : combobox_map_) std::cout << key << " : " << value << std::endl;
	// std::cout << "colors_map_ : \n";
	// for(auto& [key, value] : colors_map_) std::cout << key << " : " << value << std::endl;
	// std::cout << "checkbox_map_ : \n";
	// for(auto& [key, value] : checkbox_map_) std::cout << key << " : " << value << std::endl;
	// std::cout << "selectionbox_map_ : \n";
	// for(auto& [key, value] : selectionbox_map_) std::cout << key << " : " << value << std::endl;
};

void SpacingP::setCustomTestValues()
{

	classes_data_map_["margin"] = "m-2";
	classes_data_map_["margin_x"] = "mx-2";
	classes_data_map_["margin_y"] = "my-2";
	classes_data_map_["margin_t"] = "mt-2";
	classes_data_map_["margin_r"] = "mr-2";
	classes_data_map_["margin_b"] = "mb-2";
	classes_data_map_["margin_l"] = "ml-2";
	classes_data_map_["padding"] = "p-2";
	classes_data_map_["padding_x"] = "px-2";
	classes_data_map_["padding_y"] = "py-2";
	classes_data_map_["padding_t"] = "pt-2";
	classes_data_map_["padding_r"] = "pr-2";
	classes_data_map_["padding_b"] = "pb-2";
	classes_data_map_["padding_l"] = "pl-2";
	classes_data_map_["space_x"] = "space-x-2";
	classes_data_map_["space_y"] = "space-y-2";
	classes_data_map_["space_x_reverse"] = "space-x-reverse";
	classes_data_map_["space_y_reverse"] = "space-y-reverse";
}
