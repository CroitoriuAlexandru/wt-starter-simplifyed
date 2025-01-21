#include "101-Stylus/TCategory/FlexAndGridP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

FlexAndGridP::FlexAndGridP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
	: BasePanel(tailwind_config, extra_widgets_wrapper)
{
	classes_data_map_ = {
		{"order", "none"},
		{"direction", "none"},
		{"wrap", "none"},
		{"align_content", "none"},
		{"justify_content", "none"},
		{"align_items", "none"},
		{"basis", "none"},
		{"grow_shrink", "none"},
		{"grow", "none"},
		{"shrink", "none"},
		{"justify_items", "none"},
		{"justify_self", "none"},
		{"align_self", "none"},
		{"place_content", "none"},
		{"place_items", "none"},
		{"place_self", "none"},
		{"grid_template_columns", "none"},
		{"grid_cols_start", "none"},
		{"grid_cols_span", "none"},
		{"grid_cols_end", "none"},
		{"grid_template_rows", "none"},
		{"grid_rows_start", "none"},
		{"grid_rows_span", "none"},
		{"grid_rows_end", "none"},
		{"grid_auto_flow", "none"},
		{"grid_auto_columns", "none"},
		{"grid_auto_rows", "none"},
		{"gap", "none"},
		{"gap_x", "none"},
		{"gap_y", "none"}};

	std::map<std::string, Propriety> classes_vec_map{
		{"order", tailwind_config->flexboxAndGrid.order},
		{"direction", tailwind_config->flexboxAndGrid.flexDirection},
		{"wrap", tailwind_config->flexboxAndGrid.flexWrap},
		{"align_content", tailwind_config->flexboxAndGrid.alignContent},
		{"justify_content", tailwind_config->flexboxAndGrid.justifyContent},
		{"align_items", tailwind_config->flexboxAndGrid.alignItems},
		{"basis", tailwind_config->flexboxAndGrid.flexBasis},
		{"grow_shrink", tailwind_config->flexboxAndGrid.flex},
		{"grow", tailwind_config->flexboxAndGrid.flexGrow},
		{"shrink", tailwind_config->flexboxAndGrid.flexShrink},
		{"justify_items", tailwind_config->flexboxAndGrid.justifyItems},
		{"justify_self", tailwind_config->flexboxAndGrid.justifySelf},
		{"align_self", tailwind_config->flexboxAndGrid.alignSelf},
		{"place_content", tailwind_config->flexboxAndGrid.placeContent},
		{"place_items", tailwind_config->flexboxAndGrid.placeItems},
		{"place_self", tailwind_config->flexboxAndGrid.placeSelf},
		{"grid_template_columns", tailwind_config->flexboxAndGrid.gridTemplateColumns},
		{"grid_cols_start", tailwind_config->flexboxAndGrid.gridColumnStart},
		{"grid_cols_span", tailwind_config->flexboxAndGrid.gridColumn_span},
		{"grid_cols_end", tailwind_config->flexboxAndGrid.gridColumnEnd},
		{"grid_template_rows", tailwind_config->flexboxAndGrid.gridTemplateRows},
		{"grid_rows_start", tailwind_config->flexboxAndGrid.gridRowStart},
		{"grid_rows_span", tailwind_config->flexboxAndGrid.gridRow_span},
		{"grid_rows_end", tailwind_config->flexboxAndGrid.gridRowEnd},
		{"grid_auto_flow", tailwind_config->flexboxAndGrid.gridAutoFlow},
		{"grid_auto_columns", tailwind_config->flexboxAndGrid.gridAutoColumns},
		{"grid_auto_rows", tailwind_config->flexboxAndGrid.gridAutoRows},
		{"gap", tailwind_config->flexboxAndGrid.gap},
		{"gap_x", tailwind_config->flexboxAndGrid.gap_x},
		{"gap_y", tailwind_config->flexboxAndGrid.gap_y}};

	title->setText("Flex and Grid");

	auto flex_elem_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_elem_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto flex_and_grid_elem_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	auto flex_parent_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_parent_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto flex_and_grid_parent_container = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

	m_flex_elem_toggler_ = addToggler(flex_elem_container, "|");
	m_flex_parent_toggler_ = addToggler(flex_parent_container, "||");
	m_grid_elem_toggler_ = addToggler(grid_elem_container, "|||");
	m_grid_parent_toggler_ = addToggler(grid_parent_container, "||||");

	m_flex_elem_toggler_->changed().connect([=]()
											{
		if(m_flex_elem_toggler_->isChecked()){
			flex_and_grid_elem_container->show();
		}else{
			flex_and_grid_elem_container->hide();
		} });
	m_grid_elem_toggler_->changed().connect([=]()
											{
		if(m_grid_elem_toggler_->isChecked()){
			flex_and_grid_elem_container->show();
		}else{
			flex_and_grid_elem_container->hide();
		} });

	m_flex_parent_toggler_->changed().connect([=]()
											  {
		if(m_flex_parent_toggler_->isChecked()){
			flex_and_grid_parent_container->show();
		}else{
			flex_and_grid_parent_container->hide();
		} });
	m_grid_parent_toggler_->changed().connect([=]()
											  {
		if(m_grid_parent_toggler_->isChecked()){
			flex_and_grid_parent_container->show();
		}else{
			flex_and_grid_parent_container->hide();
		} });

	m_flex_elem_toggler_->changed().emit();
	m_flex_parent_toggler_->changed().emit();
	m_grid_elem_toggler_->changed().emit();
	m_grid_parent_toggler_->changed().emit();

	// flex element
	auto direction_wrapper = flex_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto wrap_wrapper = flex_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// flex parent
	auto grow_shrink_wrapper = flex_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grow_wrapper = flex_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto shrink_wrapper = flex_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto basis_wrapper = flex_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// grid element
	auto grid_template_columns_wrapper = grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_template_rows_wrapper = grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_rows_wrapper = grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_rows_span_wrapper = grid_rows_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_rows_start_end_wrapper = grid_rows_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_auto_flow_wrapper = grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_auto_columns_wrapper = grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_auto_rows_wrapper = grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// grid parent
	auto grid_cols_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_cols_span_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto grid_cols_start_end_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto justify_items_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto justify_self_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto place_content_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto place_items_wrapper = grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// flex and grid element
	auto justify_content_wrapper = flex_and_grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto align_content_wrapper = flex_and_grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto align_items_wrapper = flex_and_grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto gap_wrapper = flex_and_grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto gap_sides_wrapper = flex_and_grid_elem_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// flex and grid parent
	auto order_wrapper = flex_and_grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto align_self_wrapper = flex_and_grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto place_self_wrapper = flex_and_grid_parent_container->addWidget(std::make_unique<Wt::WContainerWidget>());

	// links to docs
	order_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["order"].docs_link, "Order")));
	basis_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["basis"].docs_link, "Basis")));
	direction_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["direction"].docs_link, "Flex Direction")))->addStyleClass("w-1/3");
	wrap_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["wrap"].docs_link, "Flex Wrap")))->addStyleClass("w-1/3");
	grow_shrink_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grow_shrink"].docs_link, "Grow Shrink")));
	grow_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grow"].docs_link, "Grow")));
	shrink_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["shrink"].docs_link, "Shrink")));
	justify_content_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["justify_content"].docs_link, "Justify Content")))->addStyleClass("w-1/3");
	justify_items_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["justify_items"].docs_link, "Justify Items")));
	justify_self_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["justify_self"].docs_link, "Justify Self")));
	align_content_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["align_content"].docs_link, "Align Content")))->addStyleClass("w-1/3");
	align_items_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["align_items"].docs_link, "Align Items")))->addStyleClass("w-1/3");
	align_self_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["align_self"].docs_link, "Align Self")));
	place_content_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["place_content"].docs_link, "Place Content")));
	place_items_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["place_items"].docs_link, "Place Items")));
	place_self_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["place_self"].docs_link, "Place Self")));
	grid_template_columns_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_template_columns"].docs_link, "Temp Cols")));
	grid_cols_span_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_cols_span"].docs_link, "Cols Span")));
	grid_template_rows_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_template_rows"].docs_link, "Temp Rows")));
	grid_rows_span_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_rows_span"].docs_link, "Rows Span")));
	grid_auto_flow_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_auto_flow"].docs_link, "Auto Flow")));
	grid_auto_columns_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_auto_columns"].docs_link, "Auto Columns")));
	grid_auto_rows_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grid_auto_rows"].docs_link, "Auto Rows")));
	gap_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["gap"].docs_link, "Gap")));

	auto direction_class_display_ = direction_wrapper->addWidget(std::make_unique<Wt::WText>("none"));
	auto wrap_class_display_ = wrap_wrapper->addWidget(std::make_unique<Wt::WText>("none"));
	auto justify_content_class_display_ = justify_content_wrapper->addWidget(std::make_unique<Wt::WText>("none"));
	auto align_content_class_display_ = align_content_wrapper->addWidget(std::make_unique<Wt::WText>("none"));
	auto align_items_class_display_ = align_items_wrapper->addWidget(std::make_unique<Wt::WText>("none"));

	direction_class_display_->setStyleClass("w-1/3 text-gray-500 ml-2 mr-8");
	wrap_class_display_->setStyleClass("w-1/3 text-gray-500 ml-2 mr-8");
	justify_content_class_display_->setStyleClass("w-1/3 text-gray-500 ml-2 mr-8");
	align_content_class_display_->setStyleClass("w-1/3 text-gray-500 ml-2 mr-8");
	align_items_class_display_->setStyleClass("w-1/3 text-gray-500 ml-2 mr-8");

	order_wrapper->setStyleClass(wrapper_classes);
	basis_wrapper->setStyleClass(wrapper_classes);

	direction_wrapper->setStyleClass(wrapper_classes + " flex-wrap !items-start !justify-start ");
	wrap_wrapper->setStyleClass(wrapper_classes + " flex-wrap !items-start !justify-start ");
	align_content_wrapper->setStyleClass(wrapper_classes + " flex-wrap !items-start !justify-start ");
	justify_content_wrapper->setStyleClass(wrapper_classes + " flex-wrap !items-start !justify-start ");
	align_items_wrapper->setStyleClass(wrapper_classes + " flex-wrap !items-start !justify-start ");

	grow_shrink_wrapper->setStyleClass(wrapper_classes);
	grow_wrapper->setStyleClass(wrapper_classes);
	shrink_wrapper->setStyleClass(wrapper_classes);
	justify_items_wrapper->setStyleClass(wrapper_classes);
	justify_self_wrapper->setStyleClass(wrapper_classes);
	align_self_wrapper->setStyleClass(wrapper_classes);
	place_content_wrapper->setStyleClass(wrapper_classes);
	place_items_wrapper->setStyleClass(wrapper_classes);
	place_self_wrapper->setStyleClass(wrapper_classes);

	grid_template_columns_wrapper->setStyleClass(wrapper_classes);
	grid_cols_span_wrapper->setStyleClass(wrapper_classes);
	grid_cols_start_end_wrapper->setStyleClass(wrapper_classes);
	grid_template_rows_wrapper->setStyleClass(wrapper_classes);
	grid_rows_span_wrapper->setStyleClass(wrapper_classes);
	grid_rows_start_end_wrapper->setStyleClass(wrapper_classes);
	grid_auto_flow_wrapper->setStyleClass(wrapper_classes);
	grid_auto_columns_wrapper->setStyleClass(wrapper_classes);
	grid_auto_rows_wrapper->setStyleClass(wrapper_classes);
	gap_wrapper->setStyleClass(wrapper_classes);
	gap_sides_wrapper->setStyleClass(wrapper_classes);

	combobox_map_["order"] = order_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["order"].getClasses()));

	selectionbox_map_["direction"] = direction_wrapper->addWidget(std::make_unique<SelectionBoxClassChanger>(classes_vec_map["direction"].getClasses()));
	selectionbox_map_["wrap"] = wrap_wrapper->addWidget(std::make_unique<SelectionBoxClassChanger>(classes_vec_map["wrap"].getClasses()));
	selectionbox_map_["align_content"] = align_content_wrapper->addWidget(std::make_unique<SelectionBoxClassChanger>(classes_vec_map["align_content"].getClasses()));
	selectionbox_map_["justify_content"] = justify_content_wrapper->addWidget(std::make_unique<SelectionBoxClassChanger>(classes_vec_map["justify_content"].getClasses()));
	selectionbox_map_["align_items"] = align_items_wrapper->addWidget(std::make_unique<SelectionBoxClassChanger>(classes_vec_map["align_items"].getClasses()));

	combobox_map_["basis"] = basis_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["basis"].getClasses()));
	combobox_map_["justify_items"] = justify_items_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["justify_items"].getClasses()));
	combobox_map_["grow_shrink"] = grow_shrink_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grow_shrink"].getClasses()));
	combobox_map_["grow"] = grow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grow"].getClasses()));
	combobox_map_["shrink"] = shrink_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["shrink"].getClasses()));
	combobox_map_["justify_self"] = justify_self_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["justify_self"].getClasses()));

	combobox_map_["align_self"] = align_self_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["align_self"].getClasses()));

	combobox_map_["place_content"] = place_content_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["place_content"].getClasses()));
	combobox_map_["place_items"] = place_items_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["place_items"].getClasses()));
	combobox_map_["place_self"] = place_self_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["place_self"].getClasses()));

	// grid
	combobox_map_["grid_template_columns"] = grid_template_columns_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_template_columns"].getClasses()));
	combobox_map_["grid_cols_span"] = grid_cols_span_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_cols_span"].getClasses()));
	combobox_map_["grid_cols_start"] = grid_cols_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_cols_start"].getClasses()));
	combobox_map_["grid_cols_end"] = grid_cols_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_cols_end"].getClasses()));
	combobox_map_["grid_template_rows"] = grid_template_rows_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_template_rows"].getClasses()));
	combobox_map_["grid_rows_start"] = grid_rows_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_rows_start"].getClasses()));
	combobox_map_["grid_rows_span"] = grid_rows_span_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_rows_span"].getClasses())); //

	combobox_map_["grid_rows_end"] = grid_rows_start_end_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_rows_end"].getClasses()));
	combobox_map_["grid_auto_flow"] = grid_auto_flow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_auto_flow"].getClasses()));
	combobox_map_["grid_auto_columns"] = grid_auto_columns_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_auto_columns"].getClasses()));
	combobox_map_["grid_auto_rows"] = grid_auto_rows_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grid_auto_rows"].getClasses()));

	combobox_map_["gap"] = gap_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["gap"].getClasses()));
	combobox_map_["gap_x"] = gap_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["gap_x"].getClasses()));
	combobox_map_["gap_y"] = gap_sides_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["gap_y"].getClasses()));

	// Signals
	for (auto &[key, combobox] : combobox_map_)
	{
		combobox->classChanged().connect(this, [=](std::string className)
										 {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
		if (classes_vec_map[key].custom_value)
			combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
	}
	for (auto &[key, selectionbox] : selectionbox_map_)
	{
		selectionbox->classChanged().connect(this, [=](std::string className)
											 { 
				classes_data_map_[key] = className; 
				std::cout << "sizing ------------ key : " << key << " className from normal: " << className << "\n";
				styleChanged_.emit(getStyles()); });
	}
	setExtraWidgets(classes_vec_map);
};

void FlexAndGridP::setCustomTestValues()
{
	setDisplayWidgets("order", "order-1");
	// flex
	setDisplayWidgets("basis", "basis-1/2");
	setDisplayWidgets("direction", "flex-col");
	setDisplayWidgets("wrap", "flex-wrap-reverse");
	setDisplayWidgets("grow_shrink", "flex-initial");
	setDisplayWidgets("grow", "grow");
	setDisplayWidgets("shrink", "shrink-0");
	setDisplayWidgets("justify_content", "justify-evenly");
	setDisplayWidgets("justify_items", "justify-items-center");
	setDisplayWidgets("justify_self", "justify-self-center");
	setDisplayWidgets("align_content", "content-evenly");
	setDisplayWidgets("align_items", "items-center");
	setDisplayWidgets("align_self", "self-center");
	setDisplayWidgets("place_content", "place-content-start");
	setDisplayWidgets("place_items", "place-items-end");
	setDisplayWidgets("place_self", "place-self-stretch");

	// grid
	setDisplayWidgets("grid_template_columns", "grid-cols-5");
	setDisplayWidgets("grid_cols_start", "col-start-5");
	setDisplayWidgets("grid_cols_span", "col-span-5");
	setDisplayWidgets("grid_cols_end", "col-end-5");
	setDisplayWidgets("grid_template_rows", "grid-rows-5");
	setDisplayWidgets("grid_rows_start", "row-start-5");
	setDisplayWidgets("grid_rows_span", "row-span-5");
	setDisplayWidgets("grid_rows_end", "row-end-5");
	setDisplayWidgets("grid_auto_flow", "grid-flow-col");
	setDisplayWidgets("grid_auto_columns", "auto-cols-auto");
	setDisplayWidgets("grid_auto_rows", "auto-rows-auto");
	setDisplayWidgets("gap", "gap-8");
	setDisplayWidgets("gap_x", "gap-x-8");
	setDisplayWidgets("gap_y", "gap-y-8");
}