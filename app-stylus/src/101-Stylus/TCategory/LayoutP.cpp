#include "101-Stylus/TCategory/LayoutP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

LayoutP::LayoutP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
	: BasePanel(tailwind_config, extra_widgets_wrapper)
{
	classes_data_map_ = {
		{"display", "none"},
		{"aspect_ratio", "none"},
		{"container", "none"},
		{"columns", "none"},
		{"break_after", "none"},
		{"break_before", "none"},
		{"break_inside", "none"},
		{"box_decoration_break", "none"},
		{"box_sizing", "none"},
		{"floats", "none"},
		{"clear", "none"},
		{"isolation", "none"},
		{"object_fit", "none"},
		{"object_position", "none"},
		{"overflow", "none"},
		{"overflow_x", "none"},
		{"overflow_y", "none"},
		{"overscroll_behavior", "none"},
		{"overscroll_behavior_x", "none"},
		{"overscroll_behavior_y", "none"},
		{"position", "none"},
		{"inset", "none"},
		{"inset_x", "none"},
		{"inset_y", "none"},
		{"top", "none"},
		{"right", "none"},
		{"bottom", "none"},
		{"left", "none"},
		{"visibility", "none"},
		{"z_index", "none"}};

	std::map<std::string, Propriety> classes_vec_map = {
		{"display", tailwind_config->layout.display},
		{"aspect_ratio", tailwind_config->layout.aspectRatio},
		{"container", tailwind_config->layout.container},
		{"columns", tailwind_config->layout.columns},
		{"break_after", tailwind_config->layout.breakAfter},
		{"break_before", tailwind_config->layout.breakBefore},
		{"break_inside", tailwind_config->layout.breakInside},
		{"box_decoration_break", tailwind_config->layout.boxDecorationBreak},
		{"box_sizing", tailwind_config->layout.boxSizing},
		{"floats", tailwind_config->layout.floats},
		{"clear", tailwind_config->layout.clear},
		{"isolation", tailwind_config->layout.isolation},
		{"object_fit", tailwind_config->layout.objectFit},
		{"object_position", tailwind_config->layout.objectPosition},
		{"overflow", tailwind_config->layout.overflow},
		{"overflow_x", tailwind_config->layout.overflow_x},
		{"overflow_y", tailwind_config->layout.overflow_y},
		{"overscroll_behavior", tailwind_config->layout.overscrollBehavior},
		{"overscroll_behavior_x", tailwind_config->layout.overscrollBehavior_x},
		{"overscroll_behavior_y", tailwind_config->layout.overscrollBehavior_y},
		{"position", tailwind_config->layout.position},
		{"inset", tailwind_config->layout.inset},
		{"inset_x", tailwind_config->layout.inset_x},
		{"inset_y", tailwind_config->layout.inset_y},
		{"top", tailwind_config->layout.top},
		{"right", tailwind_config->layout.right},
		{"bottom", tailwind_config->layout.bottom},
		{"left", tailwind_config->layout.left},
		{"visibility", tailwind_config->layout.visibility},
		{"z_index", tailwind_config->layout.zIndex}};

	title->setText("Layout");

	m_main_toggler_ = addToggler(centralWidget, "|");
	centralWidget->hide();

	auto container_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto display_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto columns_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto aspect_ratio_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_after_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_before_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto break_inside_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto position_inset_sides_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_decoration_break_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto box_sizing_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto floats_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto clear_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto isolation_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_fit_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto object_position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_overscroll_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overflow_wrapper = overflow_overscroll_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto overscroll_behavior_wrapper = overflow_overscroll_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto visibility_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto z_index_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	// links to docs
	display_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["display"].docs_link, "Display")));
	aspect_ratio_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["aspect_ratio"].docs_link, "Aspect ratio")));
	container_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["container"].docs_link, "Container")));
	columns_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["columns"].docs_link, "Columns")));
	break_after_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["break_after"].docs_link, "Break after")));
	break_before_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["break_before"].docs_link, "Break before")));
	break_inside_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["break_inside"].docs_link, "Break inside")));
	position_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["position"].docs_link, "Position")));
	position_inset_sides_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["inset"].docs_link, "Inset | Top | Left | Bottom | Right")));
	box_decoration_break_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["box_decoration_break"].docs_link, "Box deco br")));
	box_sizing_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["box_sizing"].docs_link, "Box sizing")));
	floats_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["floats"].docs_link, "Floats")));
	clear_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["clear"].docs_link, "Clear")));
	isolation_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["isolation"].docs_link, "Isolation")));
	object_fit_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["object_fit"].docs_link, "Object fit")));
	object_position_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["object_position"].docs_link, "Object position")));
	auto overflow_anchor = overflow_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["overflow"].docs_link, "Overflow")));
	auto overscroll_anchor = overscroll_behavior_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["overscroll_behavior"].docs_link, "Overscroll behavior")));
	visibility_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["visibility"].docs_link, "Visibility")));
	z_index_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["z_index"].docs_link, "Z index")));

	overflow_anchor->addStyleClass("!text-center");
	overscroll_anchor->addStyleClass("!text-center");

	display_wrapper->setStyleClass(wrapper_classes);
	columns_wrapper->setStyleClass(wrapper_classes);
	aspect_ratio_wrapper->setStyleClass(wrapper_classes);
	break_after_wrapper->setStyleClass(wrapper_classes);
	break_before_wrapper->setStyleClass(wrapper_classes);
	break_inside_wrapper->setStyleClass(wrapper_classes);
	position_wrapper->setStyleClass(wrapper_classes);
	position_inset_sides_wrapper->setStyleClass(wrapper_classes + " flex-col items-stretch text-center");
	box_decoration_break_wrapper->setStyleClass(wrapper_classes);
	box_sizing_wrapper->setStyleClass(wrapper_classes);
	floats_wrapper->setStyleClass(wrapper_classes);
	clear_wrapper->setStyleClass(wrapper_classes);
	isolation_wrapper->setStyleClass(wrapper_classes);
	object_fit_wrapper->setStyleClass(wrapper_classes);
	object_position_wrapper->setStyleClass(wrapper_classes);
	overflow_wrapper->setStyleClass(wrapper_classes + " flex-col items-stretch text-center");
	overflow_overscroll_wrapper->setStyleClass(wrapper_classes + " space-x-2");
	overscroll_behavior_wrapper->setStyleClass(wrapper_classes + " flex-col items-stretch text-center");
	visibility_wrapper->setStyleClass(wrapper_classes);
	z_index_wrapper->setStyleClass(wrapper_classes);
	container_wrapper->setStyleClass(wrapper_classes);

	{
		combobox_map_["container"] = container_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["container"].getClasses()));

		combobox_map_["display"] = display_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["display"].getClasses()));
	}
	{
		combobox_map_["position"] = position_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["position"].getClasses()));

		auto positions_container = position_inset_sides_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		combobox_map_["inset"] = positions_container->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["inset"].getClasses()));
		auto inset_x_y_wrapper = positions_container->addWidget(std::make_unique<Wt::WContainerWidget>());

		combobox_map_["inset_x"] = inset_x_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["inset_x"].getClasses()));
		combobox_map_["inset_y"] = inset_x_y_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["inset_y"].getClasses()));

		auto directions_wrapper = position_inset_sides_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto direction_top_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto direction_left_right_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
		auto direction_bottom_wrapper = directions_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

		combobox_map_["top"] = direction_top_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["top"].getClasses()));
		combobox_map_["left"] = direction_left_right_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["left"].getClasses()));
		combobox_map_["right"] = direction_left_right_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["right"].getClasses()));
		combobox_map_["bottom"] = direction_bottom_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["bottom"].getClasses()));

		positions_container->setStyleClass("");
		inset_x_y_wrapper->setStyleClass("flex");
		directions_wrapper->setStyleClass("my-3 mx-auto px-4 min-h-[90px] w-4/5  border-[4px] border-dashed border-neutral-300 flex flex-col justify-between items-stretch");
		direction_top_wrapper->setStyleClass("flex mb-1 flex-col w-fit mx-auto -mt-3");
		direction_left_right_wrapper->setStyleClass("mb-1 flex justify-between -mx-12 space-x-6");
		direction_bottom_wrapper->setStyleClass("flex flex-col w-fit mx-auto -mb-3");
	}

	combobox_map_["aspect_ratio"] = aspect_ratio_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["aspect_ratio"].getClasses()));
	combobox_map_["columns"] = columns_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["columns"].getClasses()));
	combobox_map_["break_after"] = break_after_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["break_after"].getClasses()));
	combobox_map_["break_before"] = break_before_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["break_before"].getClasses()));
	combobox_map_["break_inside"] = break_inside_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["break_inside"].getClasses()));
	combobox_map_["box_decoration_break"] = box_decoration_break_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["box_decoration_break"].getClasses()));
	combobox_map_["box_sizing"] = box_sizing_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["box_sizing"].getClasses()));
	combobox_map_["floats"] = floats_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["floats"].getClasses()));
	combobox_map_["clear"] = clear_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["clear"].getClasses()));
	combobox_map_["isolation"] = isolation_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["isolation"].getClasses()));
	combobox_map_["object_fit"] = object_fit_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["object_fit"].getClasses()));
	combobox_map_["object_position"] = object_position_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["object_position"].getClasses()));
	combobox_map_["overflow"] = overflow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["overflow"].getClasses()));
	combobox_map_["overflow_x"] = overflow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["overflow_x"].getClasses()));
	combobox_map_["overflow_y"] = overflow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["overflow_y"].getClasses()));
	combobox_map_["overscroll_behavior"] = overscroll_behavior_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["overscroll_behavior"].getClasses()));
	combobox_map_["overscroll_behavior_x"] = overscroll_behavior_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["overscroll_behavior_x"].getClasses()));
	combobox_map_["overscroll_behavior_y"] = overscroll_behavior_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["overscroll_behavior_y"].getClasses()));
	combobox_map_["visibility"] = visibility_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["visibility"].getClasses()));
	combobox_map_["z_index"] = z_index_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["z_index"].getClasses()));

	for (auto &[key, combobox] : combobox_map_)
	{
		combobox->classChanged().connect(this, [=](std::string className)
										 {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
		if (classes_vec_map[key].custom_value)
			combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
	}

	setExtraWidgets(classes_vec_map);
};

void LayoutP::setCustomTestValues()
{
	classes_data_map_["display"] = "flex";
	classes_data_map_["aspect_ratio"] = "aspect-auto";
	classes_data_map_["container"] = "container";
	classes_data_map_["columns"] = "columns-5";
	classes_data_map_["break_after"] = "break-after-avoid";
	classes_data_map_["break_before"] = "break-before-auto";
	classes_data_map_["break_inside"] = "break-inside-avoid";
	classes_data_map_["box_decoration_break"] = "box-decoration-clone";
	classes_data_map_["box_sizing"] = "box-border";
	classes_data_map_["floats"] = "float-right";
	classes_data_map_["clear"] = "clear-both";
	classes_data_map_["isolation"] = "isolate";
	classes_data_map_["object_fit"] = "object-contain";
	classes_data_map_["object_position"] = "object-bottom";
	classes_data_map_["overflow"] = "overflow-auto";
	classes_data_map_["overflow_x"] = "overflow-x-auto";
	classes_data_map_["overflow_y"] = "overflow-y-auto";
	classes_data_map_["overscroll_behavior"] = "overscroll-auto";
	classes_data_map_["overscroll_behavior_x"] = "overscroll-x-auto";
	classes_data_map_["overscroll_behavior_y"] = "overscroll-y-auto";
	classes_data_map_["position"] = "absolute";
	classes_data_map_["inset"] = "inset-4";
	classes_data_map_["inset_x"] = "inset-x-4";
	classes_data_map_["inset_y"] = "inset-y-4";
	classes_data_map_["top"] = "top-48";
	classes_data_map_["right"] = "right-12";
	classes_data_map_["bottom"] = "bottom-12";
	classes_data_map_["left"] = "left-12";
	classes_data_map_["visibility"] = "visible";
	classes_data_map_["z_index"] = "z-10";
}
