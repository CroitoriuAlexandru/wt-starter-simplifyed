#include "101-Stylus/TCategory/BackgroundP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

BackgroundP::BackgroundP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
	: BasePanel(tailwind_config, extra_widgets_wrapper)
{
	classes_data_map_ = {
		{"attachment", "none"},
		{"clip", "none"},
		{"origin", "none"},
		{"position", "none"},
		{"repeat", "none"},
		{"size", "none"},
		{"gradient", "none"},
		{"bg_color", "none"},
		{"color_from_step", "none"},
		{"color_from", "none"},
		{"color_via_step", "none"},
		{"color_via", "none"},
		{"color_to_step", "none"},
		{"color_to", "none"},
	};

	std::map<std::string, Propriety> classes_vec_map = {
		{"attachment", tailwind_config->backgrounds.backgroundAttachment},
		{"clip", tailwind_config->backgrounds.backgroundClip},
		{"origin", tailwind_config->backgrounds.backgroundOrigin},
		{"position", tailwind_config->backgrounds.backgroundPosition},
		{"repeat", tailwind_config->backgrounds.backgroundRepeat},
		{"size", tailwind_config->backgrounds.backgroundSize},
		{"gradient", tailwind_config->backgrounds.backgroundImage},
		{"bg_color", tailwind_config->backgrounds.backgroundColor},
		{"color_from_step", tailwind_config->backgrounds.backgroundColorFromStep},
		{"color_from", tailwind_config->backgrounds.backgroundColorFrom},
		{"color_via_step", tailwind_config->backgrounds.backgroundColorViaStep},
		{"color_via", tailwind_config->backgrounds.backgroundColorVia},
		{"color_to_step", tailwind_config->backgrounds.backgroundColorToStep},
		{"color_to", tailwind_config->backgrounds.backgroundColorTo},
	};

	title->setText("Backgrounds");

	m_main_toggler_ = addToggler(centralWidget, "|");
	centralWidget->hide();

	// widget wrappers
	auto gradient_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto color_steps_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto color_from_wrapper = color_steps_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto color_via_wrapper = color_steps_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto color_to_wrapper = color_steps_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto bg_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto attachment_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clip_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto origin_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto repeat_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto size_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	// links to docs
	gradient_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["gradient"].docs_link, "Gradient")));
	bg_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["bg_color"].docs_link, "Color")));
	attachment_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["attachment"].docs_link, "Attachment")));
	clip_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["clip"].docs_link, "Clip")));
	origin_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["origin"].docs_link, "Origin")));
	position_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["position"].docs_link, "Position")));
	repeat_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["repeat"].docs_link, "Repeat")));
	size_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["size"].docs_link, "Size")));
	color_from_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["color_from"].docs_link, "from")))->addStyleClass("mr-auto");
	color_via_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["color_via"].docs_link, "via")))->addStyleClass("mr-auto");
	color_to_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["color_to"].docs_link, "to")))->addStyleClass("mr-auto");

	color_steps_wrapper->setStyleClass("flex flex-col");
	color_from_wrapper->setStyleClass("flex items-center");
	color_via_wrapper->setStyleClass("flex items-center");
	color_to_wrapper->setStyleClass("flex items-center");
	gradient_wrapper->setStyleClass(wrapper_classes);
	bg_color_wrapper->setStyleClass(wrapper_classes);
	attachment_wrapper->setStyleClass(wrapper_classes);
	clip_wrapper->setStyleClass(wrapper_classes);
	origin_wrapper->setStyleClass(wrapper_classes);
	position_wrapper->setStyleClass(wrapper_classes);
	repeat_wrapper->setStyleClass(wrapper_classes);
	size_wrapper->setStyleClass(wrapper_classes);

	// widgets
	colors_map_["bg_color"] = bg_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["bg_color"]));
	combobox_map_["color_from_step"] = color_from_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["color_from_step"].getClasses()));
	combobox_map_["color_via_step"] = color_via_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["color_via_step"].getClasses()));
	combobox_map_["color_to_step"] = color_to_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["color_to_step"].getClasses()));
	colors_map_["color_from"] = color_from_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["color_from"]));
	colors_map_["color_via"] = color_via_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["color_via"]));
	colors_map_["color_to"] = color_to_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["color_to"]));

	combobox_map_["gradient"] = gradient_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["gradient"].getClasses()));
	combobox_map_["attachment"] = attachment_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["attachment"].getClasses()));
	combobox_map_["clip"] = clip_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["clip"].getClasses()));
	combobox_map_["origin"] = origin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["origin"].getClasses()));
	combobox_map_["position"] = position_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["position"].getClasses()));
	combobox_map_["repeat"] = repeat_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["repeat"].getClasses()));
	combobox_map_["size"] = size_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["size"].getClasses()));

	combobox_map_["color_from_step"]->addStyleClass("!w-fit");
	combobox_map_["color_via_step"]->addStyleClass("!w-fit");
	combobox_map_["color_to_step"]->addStyleClass("!w-fit");

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
											 {classes_data_map_[color.first] = className; styleChanged_.emit(getStyles()); });
	}
	setExtraWidgets(classes_vec_map);
};

void BackgroundP::setCustomTestValues()
{
	classes_data_map_["color_from"] = "from-red-500";
	classes_data_map_["color_via"] = "via-green-500";
	classes_data_map_["color_to"] = "to-blue-500";
	classes_data_map_["color_from_step"] = "from-15%";
	classes_data_map_["color_via_step"] = "via-40%";
	classes_data_map_["color_to_step"] = "to-85%";
	classes_data_map_["gradient"] = "bg-gradient-to-r";
	classes_data_map_["bg_color"] = "bg-sky-500/65";
	classes_data_map_["attachment"] = "bg-fixed";
	classes_data_map_["clip"] = "bg-clip-padding";
	classes_data_map_["origin"] = "bg-origin-border";
	classes_data_map_["position"] = "bg-top";
	classes_data_map_["repeat"] = "bg-repeat";
	classes_data_map_["size"] = "bg-auto";
}
