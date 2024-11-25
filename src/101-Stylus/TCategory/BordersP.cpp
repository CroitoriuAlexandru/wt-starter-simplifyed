#include "101-Stylus/TCategory/BordersP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

BordersP::BordersP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
	: BasePanel(tailwind_config, extra_widgets_wrapper)
{
	classes_data_map_ = {
		{"border_radius", "none"},
		{"border_radius_s", "none"},
		{"border_radius_e", "none"},
		{"border_radius_t", "none"},
		{"border_radius_l", "none"},
		{"border_radius_r", "none"},
		{"border_radius_b", "none"},
		{"border_radius_ss", "none"},
		{"border_radius_se", "none"},
		{"border_radius_ee", "none"},
		{"border_radius_es", "none"},
		{"border_radius_tl", "none"},
		{"border_radius_tr", "none"},
		{"border_radius_bl", "none"},
		{"border_radius_br", "none"},
		{"border_width", "none"},
		{"border_width_x", "none"},
		{"border_width_y", "none"},
		{"border_width_s", "none"},
		{"border_width_e", "none"},
		{"border_width_t", "none"},
		{"border_width_r", "none"},
		{"border_width_b", "none"},
		{"border_width_l", "none"},
		{"border_color", "none"},
		{"border_style", "none"},
		{"divide_width_x", "none"},
		{"divide_width_y", "none"},
		{"divide_x_reverse", "none"},
		{"divide_y_reverse", "none"},
		{"divide_color", "none"},
		{"divide_style", "none"},
		{"outline_width", "none"},
		{"outline_color", "none"},
		{"outline_style", "none"},
		{"outline_offset", "none"},
		{"ring_width", "none"},
		{"ring_inset", "none"},
		{"ring_color", "none"},
		{"ring_offset_width", "none"},
		{"ring_offset_color", "none"}};

	std::map<std::string, Propriety> classes_vec_map = {
		{"border_radius", tailwind_config->borders.borderRadius},
		{"border_radius_s", tailwind_config->borders.borderRadius_s},
		{"border_radius_e", tailwind_config->borders.borderRadius_e},
		{"border_radius_t", tailwind_config->borders.borderRadius_t},
		{"border_radius_l", tailwind_config->borders.borderRadius_l},
		{"border_radius_r", tailwind_config->borders.borderRadius_r},
		{"border_radius_b", tailwind_config->borders.borderRadius_b},
		{"border_radius_ss", tailwind_config->borders.borderRadius_ss},
		{"border_radius_se", tailwind_config->borders.borderRadius_se},
		{"border_radius_ee", tailwind_config->borders.borderRadius_ee},
		{"border_radius_es", tailwind_config->borders.borderRadius_es},
		{"border_radius_tl", tailwind_config->borders.borderRadius_tl},
		{"border_radius_tr", tailwind_config->borders.borderRadius_tr},
		{"border_radius_bl", tailwind_config->borders.borderRadius_bl},
		{"border_radius_br", tailwind_config->borders.borderRadius_br},
		{"border_width", tailwind_config->borders.borderWidth},
		{"border_width_x", tailwind_config->borders.borderWidth_x},
		{"border_width_y", tailwind_config->borders.borderWidth_y},
		{"border_width_s", tailwind_config->borders.borderWidth_s},
		{"border_width_e", tailwind_config->borders.borderWidth_e},
		{"border_width_t", tailwind_config->borders.borderWidth_t},
		{"border_width_r", tailwind_config->borders.borderWidth_r},
		{"border_width_b", tailwind_config->borders.borderWidth_b},
		{"border_width_l", tailwind_config->borders.borderWidth_l},
		{"border_color", tailwind_config->borders.borderColor},
		{"border_style", tailwind_config->borders.borderStyle},
		{"divide_width_x", tailwind_config->borders.divideWidth_x},
		{"divide_width_y", tailwind_config->borders.divideWidth_y},
		{"divide_x_reverse", tailwind_config->borders.divideXReverse},
		{"divide_y_reverse", tailwind_config->borders.divideYReverse},
		{"divide_color", tailwind_config->borders.divideColor},
		{"divide_style", tailwind_config->borders.divideStyle},
		{"outline_width", tailwind_config->borders.outlineWidth},
		{"outline_color", tailwind_config->borders.outlineColor},
		{"outline_style", tailwind_config->borders.outlineStyle},
		{"outline_offset", tailwind_config->borders.outlineOffset},
		{"ring_width", tailwind_config->borders.ringWidth},
		{"ring_inset", tailwind_config->borders.ringInset},
		{"ring_color", tailwind_config->borders.ringColor},
		{"ring_offset_width", tailwind_config->borders.ringOffsetWidth},
		{"ring_offset_color", tailwind_config->borders.ringOffsetColor}};

	title->setText("Borders");

	m_main_toggler_ = addToggler(centralWidget, "|");
	centralWidget->hide();

	auto border_style_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto border_width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto border_radius_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto border_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto divide_style_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto divide_width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto divide_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto outline_style_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto outline_width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto outline_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto outline_offset_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto ring_width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto ring_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto ring_offset_width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto ring_offset_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	// links
	border_style_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["border_style"].docs_link, "Border Style")));
	border_width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["border_width"].docs_link, "Border Width")));
	border_radius_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["border_radius"].docs_link, "Border Radius")));
	border_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["border_color"].docs_link, "Border Color")));
	divide_style_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["divide_style"].docs_link, "Divide Style")));
	divide_width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["divide_width_x"].docs_link, "Divide Width")));
	divide_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["divide_color"].docs_link, "Divide Color")));
	outline_style_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["outline_style"].docs_link, "Outline Style")));
	outline_width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["outline_width"].docs_link, "Outline Width")));
	outline_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["outline_color"].docs_link, "Outline Color")));
	outline_offset_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["outline_offset"].docs_link, "Outline Offset")));
	ring_width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["ring_width"].docs_link, "Ring Width")));
	ring_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["ring_color"].docs_link, "Ring Color")));
	ring_offset_width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["ring_offset_width"].docs_link, "Ring Offset Width")));
	ring_offset_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["ring_offset_color"].docs_link, "Ring Offset Color")));

	border_radius_wrapper->setStyleClass(wrapper_classes + " flex-col items-stretch");
	border_width_wrapper->setStyleClass(wrapper_classes + " flex-col items-stretch");
	border_style_wrapper->setStyleClass(wrapper_classes);
	border_color_wrapper->setStyleClass(wrapper_classes);
	divide_width_wrapper->setStyleClass(wrapper_classes + " flex-col items-stretch");
	divide_style_wrapper->setStyleClass(wrapper_classes);
	divide_color_wrapper->setStyleClass(wrapper_classes);
	outline_width_wrapper->setStyleClass(wrapper_classes);
	outline_style_wrapper->setStyleClass(wrapper_classes);
	outline_color_wrapper->setStyleClass(wrapper_classes);
	outline_offset_wrapper->setStyleClass(wrapper_classes);
	ring_width_wrapper->setStyleClass(wrapper_classes);
	ring_color_wrapper->setStyleClass(wrapper_classes);
	ring_offset_width_wrapper->setStyleClass(wrapper_classes);
	ring_offset_color_wrapper->setStyleClass(wrapper_classes);

	// border radius
	{
		auto border_radius_top_wrapper = border_radius_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto border_radius_middle_wrapper = border_radius_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto border_radius_bottom_wrapper = border_radius_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		std::string radius_wrapper_styles = "flex flex-col";
		border_radius_top_wrapper->setStyleClass(radius_wrapper_styles);
		border_radius_middle_wrapper->setStyleClass(radius_wrapper_styles);
		border_radius_bottom_wrapper->setStyleClass(radius_wrapper_styles);

		auto top_main_wrapper = border_radius_top_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto top_sides_wrapper = border_radius_top_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto middle_main_wrapper = border_radius_middle_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto middle_sides_wrapper = border_radius_middle_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto bottom_main_wrapper = border_radius_bottom_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto bottom_sides_wrapper = border_radius_bottom_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto radius_start_wrapper = border_radius_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto radius_end_wrapper = border_radius_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto radius_start_end_wrapper = border_radius_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		top_main_wrapper->setStyleClass("flex");
		top_sides_wrapper->setStyleClass("flex");
		middle_main_wrapper->setStyleClass("flex");
		middle_sides_wrapper->setStyleClass("flex");
		bottom_main_wrapper->setStyleClass("flex");
		bottom_sides_wrapper->setStyleClass("flex");
		radius_start_wrapper->setStyleClass("flex");
		radius_end_wrapper->setStyleClass("flex");
		radius_start_end_wrapper->setStyleClass("flex");

		top_main_wrapper->addWidget(std::make_unique<Wt::WText>(""));
		middle_main_wrapper->addWidget(std::make_unique<Wt::WText>(""));
		bottom_main_wrapper->addWidget(std::make_unique<Wt::WText>(""));

		combobox_map_["border_radius_t"] = top_main_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_t"].getClasses()));
		combobox_map_["border_radius_tl"] = top_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_tl"].getClasses()));
		combobox_map_["border_radius_tr"] = top_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_tr"].getClasses()));

		combobox_map_["border_radius"] = middle_main_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius"].getClasses()));
		combobox_map_["border_radius_l"] = middle_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_l"].getClasses()));
		combobox_map_["border_radius_r"] = middle_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_r"].getClasses()));

		combobox_map_["border_radius_bl"] = bottom_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_bl"].getClasses()));
		combobox_map_["border_radius_b"] = bottom_main_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_b"].getClasses()));
		combobox_map_["border_radius_br"] = bottom_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_br"].getClasses()));

		combobox_map_["border_radius_s"] = radius_start_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_s"].getClasses()));
		combobox_map_["border_radius_ss"] = radius_start_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_ss"].getClasses()));

		combobox_map_["border_radius_e"] = radius_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_e"].getClasses()));
		combobox_map_["border_radius_ee"] = radius_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_ee"].getClasses()));

		combobox_map_["border_radius_es"] = radius_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_es"].getClasses()));
		combobox_map_["border_radius_se"] = radius_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_radius_se"].getClasses()));
	}

	// border width
	{
		combobox_map_["border_width"] = border_width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width"].getClasses()));
		auto border_width_x_y_wrapper = border_width_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		combobox_map_["border_width_x"] = border_width_x_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_x"].getClasses()));
		combobox_map_["border_width_y"] = border_width_x_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_y"].getClasses()));

		auto border_start_end_wrapper = border_width_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		combobox_map_["border_width_s"] = border_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_s"].getClasses()));
		combobox_map_["border_width_e"] = border_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_e"].getClasses()));

		auto border_directions_wrapper = border_width_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto border_direction_top_wrapper = border_directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto border_direction_left_right_wrapper = border_directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto border_direction_bottom_wrapper = border_directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		combobox_map_["border_width_t"] = border_direction_top_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_t"].getClasses()));
		combobox_map_["border_width_l"] = border_direction_left_right_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_l"].getClasses()));
		combobox_map_["border_width_r"] = border_direction_left_right_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_r"].getClasses()));
		combobox_map_["border_width_b"] = border_direction_bottom_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_width_b"].getClasses()));

		border_width_x_y_wrapper->setStyleClass("flex");
		border_start_end_wrapper->setStyleClass("flex");
		border_directions_wrapper->setStyleClass("my-3 mx-auto px-4 min-h-[90px] w-4/5  border-[4px] border-dashed border-neutral-300 flex flex-col justify-between items-stretch");
		border_direction_top_wrapper->setStyleClass("flex mb-1 flex-col w-fit mx-auto -mt-3");
		border_direction_left_right_wrapper->setStyleClass("mb-1 flex justify-between -mx-12 space-x-6");
		border_direction_bottom_wrapper->setStyleClass("flex flex-col w-fit mx-auto -mb-3");
	}

	combobox_map_["border_style"] = border_style_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_style"].getClasses()));
	colors_map_["border_color"] = border_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["border_color"]));

	auto divide_wrapper_controls = divide_width_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto divide_x_wrapper = divide_wrapper_controls->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto divide_y_wrapper = divide_wrapper_controls->addWidget(std::make_unique<Wt::WContainerWidget>());

	checkbox_map_["divide_x_reverse"] = divide_x_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Divide X Rev"));
	checkbox_map_["divide_y_reverse"] = divide_y_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Divide Y Rev"));

	checkbox_map_["divide_x_reverse"]->setStyleClass("font-bold text-neutral-400");
	checkbox_map_["divide_y_reverse"]->setStyleClass("font-bold text-neutral-400");

	combobox_map_["divide_width_x"] = divide_x_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["divide_width_x"].getClasses()));
	combobox_map_["divide_width_y"] = divide_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["divide_width_y"].getClasses()));
	divide_wrapper_controls->setStyleClass("flex w-full items-center justify-between");
	divide_x_wrapper->setStyleClass("flex flex-col items-center w-1/2");
	divide_y_wrapper->setStyleClass("flex flex-col w-1/2");

	colors_map_["divide_color"] = divide_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["divide_color"]));
	combobox_map_["divide_style"] = divide_style_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["divide_style"].getClasses()));

	// outline
	combobox_map_["outline_width"] = outline_width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["outline_width"].getClasses()));
	combobox_map_["outline_style"] = outline_style_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["outline_style"].getClasses()));
	colors_map_["outline_color"] = outline_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["outline_color"]));
	combobox_map_["outline_offset"] = outline_offset_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["outline_offset"].getClasses()));

	// ring
	combobox_map_["ring_width"] = ring_width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["ring_width"].getClasses()));
	checkbox_map_["ring_inset"] = ring_width_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Inset"));
	checkbox_map_["ring_inset"]->setStyleClass("font-bold text-neutral-400 ");

	combobox_map_["ring_offset_width"] = ring_offset_width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["ring_offset_width"].getClasses()));
	colors_map_["ring_color"] = ring_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["ring_color"]));
	colors_map_["ring_offset_color"] = ring_offset_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["ring_offset_color"]));

	// signals
	for (auto &[key, combobox] : combobox_map_)
	{
		combobox->classChanged().connect(this, [=](std::string className)
										 {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
		if (classes_vec_map[key].custom_value)
			combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
	}
	for (auto &color : colors_map_)
	{
		color.second->classChanged().connect(this, [=](std::string className)
											 {
			classes_data_map_[color.first] = className; styleChanged_.emit(getStyles()); 
			std::cout << "color changed " << className << "\n"; });
	}

	checkbox_map_["divide_x_reverse"]->changed().connect(this, [=]()
														 { 
		if(checkbox_map_["divide_x_reverse"] ->isChecked())
			classes_data_map_["divide_x_reverse"] = "divide-x-reverse"; 
		else 
			classes_data_map_["divide_x_reverse"] = "none";
		styleChanged_.emit(getStyles()); });

	checkbox_map_["divide_y_reverse"]->changed().connect(this, [=]()
														 { 
		if(checkbox_map_["divide_y_reverse"] ->isChecked())
			classes_data_map_["divide_y_reverse"] = "divide-y-reverse"; 
		else 
			classes_data_map_["divide_y_reverse"] = "none";
		styleChanged_.emit(getStyles()); });

	checkbox_map_["ring_inset"]->changed().connect(this, [=]()
												   { 
		if(checkbox_map_["ring_inset"]->isChecked())
			classes_data_map_["ring_inset"] = "ring-inset"; 
		else 
			classes_data_map_["ring_inset"] = "none";
		styleChanged_.emit(getStyles()); });

	setExtraWidgets(classes_vec_map);
};

void BordersP::setCustomTestValues()
{
	classes_data_map_["border_radius"] = "rounded-xl";
	classes_data_map_["border_radius_t"] = "rounded-t-xl";
	classes_data_map_["border_radius_l"] = "rounded-l-xl";
	classes_data_map_["border_radius_r"] = "rounded-r-xl";
	classes_data_map_["border_radius_b"] = "rounded-b-xl";
	classes_data_map_["border_radius_tl"] = "rounded-tl-xl";
	classes_data_map_["border_radius_tr"] = "rounded-tr-xl";
	classes_data_map_["border_radius_bl"] = "rounded-bl-xl";
	classes_data_map_["border_radius_br"] = "rounded-br-xl";
	classes_data_map_["border_radius_s"] = "rounded-s-xl";
	classes_data_map_["border_radius_e"] = "rounded-e-xl";
	classes_data_map_["border_radius_ss"] = "rounded-ss-xl";
	classes_data_map_["border_radius_ee"] = "rounded-ee-xl";
	classes_data_map_["border_radius_es"] = "rounded-es-xl";
	classes_data_map_["border_radius_se"] = "rounded-se-xl";

	classes_data_map_["border_width"] = "border-2";
	classes_data_map_["border_width_x"] = "border-x-2";
	classes_data_map_["border_width_y"] = "border-y-2";
	classes_data_map_["border_width_t"] = "border-t-2";
	classes_data_map_["border_width_l"] = "border-l-2";
	classes_data_map_["border_width_r"] = "border-r-2";
	classes_data_map_["border_width_b"] = "border-b-2";
	classes_data_map_["border_width_s"] = "border-s-2";
	classes_data_map_["border_width_e"] = "border-e-2";

	classes_data_map_["border_style"] = "border-dashed";

	classes_data_map_["divide_x"] = "divide-x-4";
	classes_data_map_["divide_y"] = "divide-y-4";
	classes_data_map_["divide_x_reverse"] = "divide-x-reverse";
	classes_data_map_["divide_y_reverse"] = "divide-y-reverse";
	classes_data_map_["divide_style"] = "divide-dashed";

	classes_data_map_["outline_width"] = "outline-2";
	classes_data_map_["outline_style"] = "outline-dashed";
	classes_data_map_["outline_offset"] = "outline-offset-4";

	classes_data_map_["ring_width"] = "ring-8";
	classes_data_map_["ring_offset_width"] = "ring-offset-4";
	classes_data_map_["ring_inset"] = "ring-inset";
}