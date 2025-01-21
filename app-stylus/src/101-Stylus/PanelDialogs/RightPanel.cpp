#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/Stylus.h"
// #include "002-Dbo/Session.h"

RightPanel::RightPanel(std::shared_ptr<Stylus> stylus)
    : BaseDialogPanel(stylus)
{
    // addStyleClass("w-[450px] relative");
    addStyleClass("w-[450px]");

    setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
    auto content_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    contents()->addStyleClass("!bg-gray-800");

    dark_mode_regex_ = boost::regex(R"(dark:[a-zA-Z0-9\-!_\[\.\]\(\+\)\\/\\%]+)");

    std::unordered_map<std::string, std::string> category_classes_map = {
        {"layout", ""},
        {"flex_and_grid", ""},
        {"sizing", ""},
        {"spacing", ""},
        {"typography", ""},
        {"background", ""},
        {"borders", ""},
        {"transforms", ""},
        {"filters", ""},
        {"effects", ""},
        {"tables", ""},
        {"transitions_and_animation", ""},
        {"interactivity", ""},
        {"svg", ""},
        {"accesibility", ""}};

    category_classes_data_map_ = {
        {"DEFAULT", category_classes_map},
        {"dark", category_classes_map},
    };

    auto extra_widgets_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());

    category_wrappers_["not_found_classes"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    not_found_classes_widget_ = category_wrappers_["not_found_classes"]->addWidget(std::make_unique<Wt::WTextArea>());
    category_wrappers_["layout"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["flex_and_grid"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["sizing"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["spacing"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["typography"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["background"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["borders"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["transforms"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["filters"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["effects"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["tables"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["transitions_and_animation"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["interactivity"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["svg"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    category_wrappers_["accesibility"] = extra_widgets_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

    not_found_classes_widget_->setStyleClass("border text-sm rounded-lg block w-full p-2 mx-1 focus:ring-green-500 focus:border-green-500 bg-gray-600");
    not_found_classes_widget_->keyWentDown().connect([=](Wt::WKeyEvent event)
                                                     { Wt::WApplication::instance()->globalKeyWentDown().emit(event); });

    for (auto &[key, widget] : category_wrappers_)
    {
        widget->setStyleClass("flex flex-wrap space-x-2 ");
        if (key.compare("not_found_classes") != 0)
        {
            widget->addWidget(std::make_unique<Wt::WText>(key))->setStyleClass("ml-2 text-md font-bold text-gray-500 w-full grow");
        }
    }

    panelsWrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    panelsWrapper->setStyleClass("flex flex-col !max-h-[100vh]");

    flexAndGridWidget_ = panelsWrapper->addWidget(std::make_unique<FlexAndGridP>(stylus_->tailwind_config_, category_wrappers_["flex_and_grid"]));
    flexAndGridWidget_->styleChanged().connect(this, [=]()
                                               {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["flex_and_grid"] = flexAndGridWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["flex_and_grid"] = flexAndGridWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });

    layoutWidget_ = panelsWrapper->addWidget(std::make_unique<LayoutP>(stylus_->tailwind_config_, category_wrappers_["layout"]));
    layoutWidget_->styleChanged().connect(this, [=]()
                                          {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["layout"] = layoutWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["layout"] = layoutWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    spacingWidget_ = panelsWrapper->addWidget(std::make_unique<SpacingP>(stylus_->tailwind_config_, category_wrappers_["spacing"]));
    spacingWidget_->styleChanged().connect(this, [=](std::string style_classes)
                                           {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["spacing"] = style_classes;
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["spacing"] = style_classes;
        }
        styleChanged_.emit(getStyles()); });
    sizingWidget_ = panelsWrapper->addWidget(std::make_unique<SizingP>(stylus_->tailwind_config_, category_wrappers_["sizing"]));
    sizingWidget_->styleChanged().connect(this, [=]()
                                          {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["sizing"] = sizingWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["sizing"] = sizingWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    typographyWidget_ = panelsWrapper->addWidget(std::make_unique<TypographyP>(stylus_->tailwind_config_, category_wrappers_["typography"]));
    typographyWidget_->styleChanged().connect(this, [=]()
                                              {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["typography"] = typographyWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["typography"] = typographyWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    backgroundWidget_ = panelsWrapper->addWidget(std::make_unique<BackgroundP>(stylus_->tailwind_config_, category_wrappers_["background"]));
    backgroundWidget_->styleChanged().connect(this, [=]()
                                              {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["background"] = backgroundWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["background"] = backgroundWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    bordersWidget_ = panelsWrapper->addWidget(std::make_unique<BordersP>(stylus_->tailwind_config_, category_wrappers_["borders"]));
    bordersWidget_->styleChanged().connect(this, [=]()
                                           {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["borders"] = bordersWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["borders"] = bordersWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    effectsWidget_ = panelsWrapper->addWidget(std::make_unique<EffectsP>(stylus_->tailwind_config_, category_wrappers_["effects"]));
    effectsWidget_->styleChanged().connect(this, [=]()
                                           {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["effects"] = effectsWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["effects"] = effectsWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    filtersWidget_ = panelsWrapper->addWidget(std::make_unique<FiltersP>(stylus_->tailwind_config_, category_wrappers_["filters"]));
    filtersWidget_->styleChanged().connect(this, [=]()
                                           {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["filters"] = filtersWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["filters"] = filtersWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    tablesWidget_ = panelsWrapper->addWidget(std::make_unique<TablesP>(stylus_->tailwind_config_, category_wrappers_["tables"]));
    tablesWidget_->styleChanged().connect(this, [=]()
                                          {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["tables"] = tablesWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["tables"] = tablesWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    transitionsAndAnimationWidget_ = panelsWrapper->addWidget(std::make_unique<TransitionsAndAnimationP>(stylus_->tailwind_config_, category_wrappers_["transitions_and_animation"]));
    transitionsAndAnimationWidget_->styleChanged().connect(this, [=]()
                                                           {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["transitions_and_animation"] = transitionsAndAnimationWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["transitions_and_animation"] = transitionsAndAnimationWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    transformsWidget_ = panelsWrapper->addWidget(std::make_unique<TransformsP>(stylus_->tailwind_config_, category_wrappers_["transforms"]));
    transformsWidget_->styleChanged().connect(this, [=]()
                                              {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["transforms"] = transformsWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["transforms"] = transformsWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    interactivityWidget_ = panelsWrapper->addWidget(std::make_unique<InteractivityP>(stylus_->tailwind_config_, category_wrappers_["interactivity"]));
    interactivityWidget_->styleChanged().connect(this, [=]()
                                                 {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["interactivity"] = interactivityWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["interactivity"] = interactivityWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    svgWidget_ = panelsWrapper->addWidget(std::make_unique<SvgP>(stylus_->tailwind_config_, category_wrappers_["svg"]));
    svgWidget_->styleChanged().connect(this, [=]()
                                       {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["svg"] = svgWidget_->getStyles();
        }else if(current_prefix_.compare("dark") == 0){
            category_classes_data_map_["dark"]["svg"] = svgWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });
    accesibilityWidget_ = panelsWrapper->addWidget(std::make_unique<AccesibilityP>(stylus_->tailwind_config_, category_wrappers_["accesibility"]));
    accesibilityWidget_->styleChanged().connect(this, [=]()
                                                {
        if(current_prefix_.compare("DEFAULT") == 0){
            category_classes_data_map_["DEFAULT"]["accesibility"] = accesibilityWidget_->getStyles();
        }else if(current_prefix_ == "dark"){
            category_classes_data_map_["dark"]["accesibility"] = accesibilityWidget_->getStyles();
        }
        styleChanged_.emit(getStyles()); });

    setStyleClasses("");

    styleChanged_.connect([=](std::string style_classes)
                          {
                              std::cout << "\n style classese changed <" << style_classes << ">\n";
                              if (!xml_brain_)
                                  return;
                              if (xml_brain_->selected_node_->ToElement())
                              {
                                  xml_brain_->selected_node_->ToElement()->SetAttribute("class", style_classes.c_str());
                                //   xml_brain_->selected_node_->style_class_changed().emit(style_classes);
                                  xml_brain_->saveXmlToDbo();
                              }else if(xml_brain_->selected_node_->ToText()){
                                auto temp_text = tempText(xml_brain_->selected_node_);
                                if(temp_text.name_ != ""){
                                    Wt::WString new_temp_text = "${" + temp_text.name_ + " class=\"" + style_classes + "\" \"widget=\"" + temp_text.widget_ + "(" + temp_text.widget_text_ + ") }";  
                                    xml_brain_->selected_node_->ToText()->SetValue(new_temp_text.toUTF8().c_str());
                                    xml_brain_->saveXmlToDbo();
                                }
                              }
                                stylus_->setXmlBrain(xml_brain_); });

    setPanelsMode(RIGHT_PANEL_MODE::NORMAL);

    // stylus_->node_selected().connect([=]()
    //                                  {
    //     if (stylus_->xml_brain_)
    //     {
    //         setXmlBrain(stylus_->xml_brain_);
    //     } });
}

void RightPanel::setStyleClasses(std::string classes)
{
    // std::cout << "\n RightPanelDialog::setStyleClasses(std::string classes) \n";
    classes = " " + classes + " ";

    std::vector<std::string> dark_classes = findAndRemoveMatches(dark_mode_regex_, classes);
    std::string dark_classes_str = "";
    for (auto &dark_class : dark_classes)
    {
        dark_classes_str += dark_class.substr(5) + " ";
    }
    // std::cout << "\n\n\n dark_classes_str = " << dark_classes_str << "\n\n\n";

    dark_classes_str = setTablesClasses(dark_classes_str, "dark");
    dark_classes_str = setFiltersClasses(dark_classes_str, "dark");
    dark_classes_str = setLayoutClasses(dark_classes_str, "dark");
    dark_classes_str = setFlexAndGridClasses(dark_classes_str, "dark");
    dark_classes_str = setSpacingClasses(dark_classes_str, "dark");
    dark_classes_str = setSizingClasses(dark_classes_str, "dark");
    dark_classes_str = setTypographyClasses(dark_classes_str, "dark");
    dark_classes_str = setBackgroundClasses(dark_classes_str, "dark");
    dark_classes_str = setBordersClasses(dark_classes_str, "dark");
    dark_classes_str = setEffectsClasses(dark_classes_str, "dark");
    dark_classes_str = setTransitionsAndAnimationClasses(dark_classes_str, "dark");
    dark_classes_str = setTransformsClasses(dark_classes_str, "dark");
    dark_classes_str = setAccesibilityClasses(dark_classes_str, "dark");
    dark_classes_str = setInteractivityClasses(dark_classes_str, "dark");
    dark_classes_str = setSvgClasses(dark_classes_str, "dark");

    classes = setTablesClasses(classes, "DEFAULT") + " ";
    classes = setFiltersClasses(classes, "DEFAULT") + " ";
    classes = setLayoutClasses(classes, "DEFAULT") + " ";
    classes = setFlexAndGridClasses(classes, "DEFAULT") + " ";
    classes = setSpacingClasses(classes, "DEFAULT") + " ";
    classes = setSizingClasses(classes, "DEFAULT") + " ";
    classes = setTypographyClasses(classes, "DEFAULT") + " ";
    classes = setBackgroundClasses(classes, "DEFAULT") + " ";
    classes = setBordersClasses(classes, "DEFAULT") + " ";
    classes = setEffectsClasses(classes, "DEFAULT") + " ";
    classes = setTransitionsAndAnimationClasses(classes, "DEFAULT") + " ";
    classes = setTransformsClasses(classes, "DEFAULT") + " ";
    classes = setAccesibilityClasses(classes, "DEFAULT") + " ";
    classes = setInteractivityClasses(classes, "DEFAULT") + " ";
    classes = setSvgClasses(classes, "DEFAULT") + " ";

    auto iss = std::istringstream(dark_classes_str);
    std::string word;
    while (iss >> word)
    {
        notFoundClasses = "dark:" + word + " ";
    }
    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");
    notFoundClasses = std::regex_replace(notFoundClasses, std::regex("\\s+$"), "");
    not_found_classes_widget_->setText(notFoundClasses);
}

std::string RightPanel::getStyles()
{
    std::string styles = "";

    for (auto &[prefix, category_classes_map] : category_classes_data_map_)
    {
        for (auto &[category, classes] : category_classes_map)
        {
            if (classes.compare("") != 0)
            {
                if (prefix.compare("DEFAULT") == 0)
                    styles += classes + " ";
                else if (prefix.compare("dark") == 0)
                {
                    std::istringstream iss(classes);
                    std::string word;
                    while (iss >> word)
                    {
                        styles += "dark:" + word + " ";
                    }
                }
            }
        }
    }

    return styles + " " + notFoundClasses;
}

void RightPanel::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    if (xml_brain == nullptr)
    {
        setStyleClasses("");
        return;
    }
    std::cout << "\n RightPanelDialog::setXmLBrain(std::shared_ptr<XMLBrain> xml_brain) \n";
    if (xml_brain->selected_node_ == xml_brain->message_node_)
    {
        std::cout << "\n selected is template node\n";
        setStyleClasses("");
        return;
    }
    xml_brain_ = xml_brain;
    if (xml_brain_->selected_node_->ToElement())
    {
        if (xml_brain_->selected_node_->ToElement()->Attribute("class"))
        {
            std::cout << "\n selected node has class attribute \n";
            setStyleClasses(xml_brain_->selected_node_->ToElement()->Attribute("class"));
        }
    }
    else if (tempText(xml_brain_->selected_node_).name_ != "")
    {
        setStyleClasses(tempText(xml_brain_->selected_node_).style_classes_);
    }
    else
    {
        setStyleClasses("");
    }
}

void RightPanel::setPanelsMode(RIGHT_PANEL_MODE mode)
{
    std::cout << "\n RightPanel::setPanelsMode(RightPanelMode mode) \n";
    flexAndGridWidget_->setPanelMode(mode);
    layoutWidget_->setPanelMode(mode);
    spacingWidget_->setPanelMode(mode);
    sizingWidget_->setPanelMode(mode);
    typographyWidget_->setPanelMode(mode);
    backgroundWidget_->setPanelMode(mode);
    bordersWidget_->setPanelMode(mode);
    effectsWidget_->setPanelMode(mode);
    filtersWidget_->setPanelMode(mode);
    tablesWidget_->setPanelMode(mode);
    transitionsAndAnimationWidget_->setPanelMode(mode);
    transformsWidget_->setPanelMode(mode);
    interactivityWidget_->setPanelMode(mode);
    svgWidget_->setPanelMode(mode);
    accesibilityWidget_->setPanelMode(mode);
}

std::string RightPanel::setFlexAndGridClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setFlexAndGridClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["order"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.order.regex, classes);
    classes_data_map["direction"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.flexDirection.regex, classes);
    classes_data_map["wrap"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.flexWrap.regex, classes);
    classes_data_map["align_content"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.alignContent.regex, classes);
    classes_data_map["justify_content"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.justifyContent.regex, classes);
    classes_data_map["align_items"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.alignItems.regex, classes);
    classes_data_map["basis"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.flexBasis.regex, classes);
    classes_data_map["grow_shrink"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.flex.regex, classes);
    classes_data_map["grow"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.flexGrow.regex, classes);
    classes_data_map["shrink"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.flexShrink.regex, classes);
    classes_data_map["justify_items"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.justifyItems.regex, classes);
    classes_data_map["justify_self"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.justifySelf.regex, classes);
    classes_data_map["align_self"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.alignSelf.regex, classes);
    classes_data_map["place_content"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.placeContent.regex, classes);
    classes_data_map["place_items"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.placeItems.regex, classes);
    classes_data_map["place_self"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.placeSelf.regex, classes);
    classes_data_map["grid_template_columns"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridTemplateColumns.regex, classes);
    classes_data_map["grid_cols_start"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridColumnStart.regex, classes);
    classes_data_map["grid_cols_span"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridColumn_span.regex, classes);
    classes_data_map["grid_cols_end"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridColumnEnd.regex, classes);
    classes_data_map["grid_template_rows"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridTemplateRows.regex, classes);
    classes_data_map["grid_rows_start"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridRowStart.regex, classes);
    classes_data_map["grid_rows_span"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridRow_span.regex, classes);
    classes_data_map["grid_rows_end"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridRowEnd.regex, classes);
    classes_data_map["grid_auto_flow"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridAutoFlow.regex, classes);
    classes_data_map["grid_auto_columns"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridAutoColumns.regex, classes);
    classes_data_map["grid_auto_rows"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gridAutoRows.regex, classes);
    classes_data_map["gap"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gap.regex, classes);
    classes_data_map["gap_x"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gap_x.regex, classes);
    classes_data_map["gap_y"] = findAndRemoveMatche(stylus_->tailwind_config_->flexboxAndGrid.gap_y.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["flex_and_grid"] = this_classes;

    flexAndGridWidget_->m_flex_parent_toggler_->setChecked(false);
    flexAndGridWidget_->m_grid_parent_toggler_->setChecked(false);
    flexAndGridWidget_->m_flex_elem_toggler_->setChecked(false);
    flexAndGridWidget_->m_grid_elem_toggler_->setChecked(false);
    flexAndGridWidget_->m_flex_elem_toggler_->changed().emit();
    flexAndGridWidget_->m_grid_elem_toggler_->changed().emit();
    flexAndGridWidget_->m_flex_parent_toggler_->changed().emit();

    // check if class 'flex' is in in getStyles()
    auto styles = getStyles();
    if (current_prefix_.compare(prefix) == 0)
    {
        flexAndGridWidget_->setClasses(classes_data_map);
        if (styles.find("flex") != std::string::npos)
        {
            flexAndGridWidget_->m_flex_elem_toggler_->setChecked(true);
            flexAndGridWidget_->m_flex_elem_toggler_->changed().emit();
        }
        else if (styles.find("grid") != std::string::npos)
        {
            flexAndGridWidget_->m_grid_elem_toggler_->setChecked(true);
            flexAndGridWidget_->m_grid_elem_toggler_->changed().emit();
        }

        if (!stylus_->xml_brain_ || !stylus_->xml_brain_->selected_node_)
            return classes;
        if (stylus_->xml_brain_->selected_node_ != stylus_->xml_brain_->message_node_)
        {
            if (stylus_->xml_brain_->selected_node_->Parent() != stylus_->xml_brain_->message_node_)
            {
                if (stylus_->xml_brain_->selected_node_->Parent()->ToElement()->Attribute("class"))
                {
                    std::string parent_classes = stylus_->xml_brain_->selected_node_->Parent()->ToElement()->Attribute("class");
                    if (parent_classes.find("flex") != std::string::npos)
                    {
                        flexAndGridWidget_->m_flex_parent_toggler_->setChecked(true);
                        flexAndGridWidget_->m_flex_parent_toggler_->changed().emit();
                    }
                    else if (parent_classes.find("grid") != std::string::npos)
                    {
                        flexAndGridWidget_->m_grid_parent_toggler_->setChecked(true);
                        flexAndGridWidget_->m_grid_parent_toggler_->changed().emit();
                    }
                }
            }
        }
    }

    return classes;
}
std::string RightPanel::setBackgroundClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setBackgroundClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    // std::cout << "\n\n regex bg color : " << stylus_->tailwind_config_->spacing.padding.regex << "\n\n";
    classes_data_map["attachment"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundAttachment.regex, classes);
    classes_data_map["clip"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundClip.regex, classes);
    classes_data_map["origin"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundOrigin.regex, classes);
    classes_data_map["position"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundPosition.regex, classes);
    classes_data_map["repeat"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundRepeat.regex, classes);
    classes_data_map["size"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundSize.regex, classes);
    classes_data_map["gradient"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundImage.regex, classes);
    classes_data_map["bg_color"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColor.regex, classes);
    classes_data_map["color_from_step"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColorFromStep.regex, classes);
    classes_data_map["color_from"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColorFrom.regex, classes);
    classes_data_map["color_via_step"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColorViaStep.regex, classes);
    classes_data_map["color_via"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColorVia.regex, classes);
    classes_data_map["color_to_step"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColorToStep.regex, classes);
    classes_data_map["color_to"] = findAndRemoveMatche(stylus_->tailwind_config_->backgrounds.backgroundColorTo.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["background"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        backgroundWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            backgroundWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            backgroundWidget_->m_main_toggler_->setChecked(false);
        }
    }
    backgroundWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setSpacingClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setSpacingClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["padding"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding.regex, classes);
    classes_data_map["padding_x"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding_x.regex, classes);
    classes_data_map["padding_y"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding_y.regex, classes);
    classes_data_map["padding_t"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding_t.regex, classes);
    classes_data_map["padding_l"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding_l.regex, classes);
    classes_data_map["padding_r"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding_r.regex, classes);
    classes_data_map["padding_b"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.padding_b.regex, classes);
    classes_data_map["margin"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin.regex, classes);
    classes_data_map["margin_x"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin_x.regex, classes);
    classes_data_map["margin_y"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin_y.regex, classes);
    classes_data_map["margin_t"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin_t.regex, classes);
    classes_data_map["margin_l"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin_l.regex, classes);
    classes_data_map["margin_r"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin_r.regex, classes);
    classes_data_map["margin_b"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.margin_b.regex, classes);
    classes_data_map["space_x"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.spaceBetween_x.regex, classes);
    classes_data_map["space_y"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.spaceBetween_y.regex, classes);
    classes_data_map["space_x_reverse"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.spaceXReverse.regex, classes);
    classes_data_map["space_y_reverse"] = findAndRemoveMatche(stylus_->tailwind_config_->spacing.spaceYReverse.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["spacing"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        spacingWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            spacingWidget_->m_show_main_directions_toggler_->setChecked(true);
            spacingWidget_->m_show_sides_toggler_->setChecked(true);
            spacingWidget_->m_show_spacing_toggler_->setChecked(true);
        }
        else
        {
            spacingWidget_->m_show_main_directions_toggler_->setChecked(false);
            spacingWidget_->m_show_sides_toggler_->setChecked(false);
            spacingWidget_->m_show_spacing_toggler_->setChecked(false);
        }
    }

    spacingWidget_->m_show_main_directions_toggler_->changed().emit();
    spacingWidget_->m_show_sides_toggler_->changed().emit();
    spacingWidget_->m_show_spacing_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setSizingClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setSizingClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["max_width"] = findAndRemoveMatche(stylus_->tailwind_config_->sizing.maxWidth.regex, classes);
    classes_data_map["min_width"] = findAndRemoveMatche(stylus_->tailwind_config_->sizing.minWidth.regex, classes);
    classes_data_map["min_height"] = findAndRemoveMatche(stylus_->tailwind_config_->sizing.minHeight.regex, classes);
    classes_data_map["max_height"] = findAndRemoveMatche(stylus_->tailwind_config_->sizing.maxHeight.regex, classes);
    classes_data_map["width"] = findAndRemoveMatche(stylus_->tailwind_config_->sizing.width.regex, classes);
    classes_data_map["height"] = findAndRemoveMatche(stylus_->tailwind_config_->sizing.height.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["sizing"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        sizingWidget_->setClasses(classes_data_map);
        if (this_classes == "")
        {
            sizingWidget_->m_main_toggler_->setChecked(false);
        }
        else
        {
            sizingWidget_->m_main_toggler_->setChecked(true);
        }
    }

    sizingWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setLayoutClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setLayoutClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["display"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.display.regex, classes);
    classes_data_map["aspect_ratio"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.aspectRatio.regex, classes);
    classes_data_map["container"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.container.regex, classes);
    classes_data_map["columns"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.columns.regex, classes);
    classes_data_map["break_after"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.breakAfter.regex, classes);
    classes_data_map["break_before"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.breakBefore.regex, classes);
    classes_data_map["break_inside"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.breakInside.regex, classes);
    classes_data_map["box_decoration_break"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.boxDecorationBreak.regex, classes);
    classes_data_map["box_sizing"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.boxSizing.regex, classes);
    classes_data_map["floats"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.floats.regex, classes);
    classes_data_map["clear"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.clear.regex, classes);
    classes_data_map["isolation"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.isolation.regex, classes);
    classes_data_map["object_fit"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.objectFit.regex, classes);
    classes_data_map["object_position"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.objectPosition.regex, classes);
    classes_data_map["overflow"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.overflow.regex, classes);
    classes_data_map["overflow_x"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.overflow_x.regex, classes);
    classes_data_map["overflow_y"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.overflow_y.regex, classes);
    classes_data_map["overscroll_behavior"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.overscrollBehavior.regex, classes);
    classes_data_map["overscroll_behavior_x"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.overscrollBehavior_x.regex, classes);
    classes_data_map["overscroll_behavior_y"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.overscrollBehavior_y.regex, classes);
    classes_data_map["position"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.position.regex, classes);
    classes_data_map["inset"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.inset.regex, classes);
    classes_data_map["inset_x"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.inset_x.regex, classes);
    classes_data_map["inset_y"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.inset_y.regex, classes);
    classes_data_map["top"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.top.regex, classes);
    classes_data_map["right"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.right.regex, classes);
    classes_data_map["bottom"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.bottom.regex, classes);
    classes_data_map["left"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.left.regex, classes);
    classes_data_map["visibility"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.visibility.regex, classes);
    classes_data_map["z_index"] = findAndRemoveMatche(stylus_->tailwind_config_->layout.zIndex.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["layout"] = this_classes;
    if (current_prefix_.compare(prefix) == 0)
    {
        layoutWidget_->setClasses(classes_data_map);
        if (this_classes == "")
        {
            layoutWidget_->m_main_toggler_->setChecked(false);
        }
        else
        {
            layoutWidget_->m_main_toggler_->setChecked(true);
        }
    }

    layoutWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setTypographyClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setTypographyClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["font_family"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.fontFamily.regex, classes);
    classes_data_map["font_size"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.fontSize.regex, classes);
    classes_data_map["font_smoothing"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.fontSmoothing.regex, classes);
    classes_data_map["font_style"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.fontStyle.regex, classes);
    classes_data_map["font_weight"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.fontWeight.regex, classes);
    classes_data_map["font_variant_numeric"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.fontVariantNumeric.regex, classes);
    classes_data_map["letter_spacing"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.letterSpacing.regex, classes);
    classes_data_map["line_clamp"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.lineClamp.regex, classes);
    classes_data_map["line_height"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.lineHeight.regex, classes);
    classes_data_map["list_style_image"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.listStyleImage.regex, classes);
    classes_data_map["list_style_position"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.listStylePosition.regex, classes);
    classes_data_map["list_style_type"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.listStyleType.regex, classes);
    classes_data_map["text_align"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textAlign.regex, classes);
    classes_data_map["text_color"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textColor.regex, classes);
    classes_data_map["text_decoration"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textDecoration.regex, classes);
    classes_data_map["text_decoration_color"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textDecorationColor.regex, classes);
    classes_data_map["text_decoration_style"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textDecorationStyle.regex, classes);
    classes_data_map["text_decoration_thickness"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textDecorationThickness.regex, classes);
    classes_data_map["text_underline_offset"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textUnderlineOffset.regex, classes);
    classes_data_map["text_transform"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textTransform.regex, classes);
    classes_data_map["text_overflow"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textOverflow.regex, classes);
    classes_data_map["text_wrap"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textWrap.regex, classes);
    classes_data_map["text_indent"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.textIndent.regex, classes);
    classes_data_map["vertical_align"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.verticalAlign.regex, classes);
    classes_data_map["whitespace"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.whitespace.regex, classes);
    classes_data_map["word_break"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.wordBreak.regex, classes);
    classes_data_map["hyphens"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.hyphens.regex, classes);
    classes_data_map["content"] = findAndRemoveMatche(stylus_->tailwind_config_->typography.content.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["typography"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        typographyWidget_->setClasses(classes_data_map);
        if (this_classes == "")
        {
            typographyWidget_->m_main_toggler_->setChecked(false);
        }
        else
        {
            typographyWidget_->m_main_toggler_->setChecked(true);
        }
    }
    typographyWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setBordersClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setBordersClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["border_radius"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius.regex, classes);
    classes_data_map["border_radius_s"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_s.regex, classes);
    classes_data_map["border_radius_e"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_e.regex, classes);
    classes_data_map["border_radius_t"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_t.regex, classes);
    classes_data_map["border_radius_l"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_l.regex, classes);
    classes_data_map["border_radius_r"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_r.regex, classes);
    classes_data_map["border_radius_b"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_b.regex, classes);
    classes_data_map["border_radius_ss"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_ss.regex, classes);
    classes_data_map["border_radius_se"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_se.regex, classes);
    classes_data_map["border_radius_ee"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_ee.regex, classes);
    classes_data_map["border_radius_es"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_es.regex, classes);
    classes_data_map["border_radius_tl"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_tl.regex, classes);
    classes_data_map["border_radius_tr"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_tr.regex, classes);
    classes_data_map["border_radius_bl"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_bl.regex, classes);
    classes_data_map["border_radius_br"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderRadius_br.regex, classes);
    classes_data_map["border_width"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth.regex, classes);
    classes_data_map["border_width_x"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_x.regex, classes);
    classes_data_map["border_width_y"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_y.regex, classes);
    classes_data_map["border_width_s"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_s.regex, classes);
    classes_data_map["border_width_e"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_e.regex, classes);
    classes_data_map["border_width_t"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_t.regex, classes);
    classes_data_map["border_width_r"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_r.regex, classes);
    classes_data_map["border_width_b"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_b.regex, classes);
    classes_data_map["border_width_l"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderWidth_l.regex, classes);
    classes_data_map["border_color"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderColor.regex, classes);
    classes_data_map["border_style"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.borderStyle.regex, classes);
    classes_data_map["divide_width_x"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.divideWidth_x.regex, classes);
    classes_data_map["divide_width_y"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.divideWidth_y.regex, classes);
    classes_data_map["divide_x_reverse"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.divideXReverse.regex, classes);
    classes_data_map["divide_y_reverse"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.divideYReverse.regex, classes);
    classes_data_map["divide_color"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.divideColor.regex, classes);
    classes_data_map["divide_style"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.divideStyle.regex, classes);
    classes_data_map["outline_width"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.outlineWidth.regex, classes);
    classes_data_map["outline_color"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.outlineColor.regex, classes);
    classes_data_map["outline_style"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.outlineStyle.regex, classes);
    classes_data_map["outline_offset"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.outlineOffset.regex, classes);
    classes_data_map["ring_width"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.ringWidth.regex, classes);
    classes_data_map["ring_inset"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.ringInset.regex, classes);
    classes_data_map["ring_color"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.ringColor.regex, classes);
    classes_data_map["ring_offset_width"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.ringOffsetWidth.regex, classes);
    classes_data_map["ring_offset_color"] = findAndRemoveMatche(stylus_->tailwind_config_->borders.ringOffsetColor.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["borders"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        bordersWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            bordersWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            bordersWidget_->m_main_toggler_->setChecked(false);
        }
    }

    bordersWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setFiltersClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setFiltersClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["blur"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.blur.regex, classes);
    classes_data_map["brightness"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.brightness.regex, classes);
    classes_data_map["contrast"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.contrast.regex, classes);
    classes_data_map["drop_shadow"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.dropShadow.regex, classes);
    classes_data_map["grayscale"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.grayscale.regex, classes);
    classes_data_map["hue_rotate"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.hueRotate.regex, classes);
    classes_data_map["invert"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.invert.regex, classes);
    classes_data_map["saturate"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.saturate.regex, classes);
    classes_data_map["sepia"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.sepia.regex, classes);
    classes_data_map["backdrop_blur"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropBlur.regex, classes);
    classes_data_map["backdrop_brightness"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropBrightness.regex, classes);
    classes_data_map["backdrop_contrast"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropContrast.regex, classes);
    classes_data_map["backdrop_grayscale"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropGrayscale.regex, classes);
    classes_data_map["backdrop_hue_rotate"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropHueRotate.regex, classes);
    classes_data_map["backdrop_invert"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropInvert.regex, classes);
    classes_data_map["backdrop_opacity"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropOpacity.regex, classes);
    classes_data_map["backdrop_saturate"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropSaturate.regex, classes);
    classes_data_map["backdrop_sepia"] = findAndRemoveMatche(stylus_->tailwind_config_->filters.backdropSepia.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["filters"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        filtersWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            filtersWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            filtersWidget_->m_main_toggler_->setChecked(false);
        }
    }
    filtersWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setEffectsClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setEffectsClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["box_shadow"] = findAndRemoveMatche(stylus_->tailwind_config_->effects.boxShadow.regex, classes);
    classes_data_map["box_shadow_inner"] = findAndRemoveMatche(stylus_->tailwind_config_->effects.boxShadow_inner.regex, classes);
    classes_data_map["box_shadow_color"] = findAndRemoveMatche(stylus_->tailwind_config_->effects.boxShadowColor.regex, classes);
    classes_data_map["opacity"] = findAndRemoveMatche(stylus_->tailwind_config_->effects.opacity.regex, classes);
    classes_data_map["mix_blend_mode"] = findAndRemoveMatche(stylus_->tailwind_config_->effects.mixBlendMode.regex, classes);
    classes_data_map["background_blend_mode"] = findAndRemoveMatche(stylus_->tailwind_config_->effects.backgroundBlendMode.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["effects"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        effectsWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            effectsWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            effectsWidget_->m_main_toggler_->setChecked(false);
        }
    }

    effectsWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setTablesClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setTablesClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["border_collapse"] = findAndRemoveMatche(stylus_->tailwind_config_->tables.borderCollapse.regex, classes);
    classes_data_map["border_spacing"] = findAndRemoveMatche(stylus_->tailwind_config_->tables.borderSpacing.regex, classes);
    classes_data_map["border_spacing_x"] = findAndRemoveMatche(stylus_->tailwind_config_->tables.borderSpacing_x.regex, classes);
    classes_data_map["border_spacing_y"] = findAndRemoveMatche(stylus_->tailwind_config_->tables.borderSpacing_y.regex, classes);
    classes_data_map["table_layout"] = findAndRemoveMatche(stylus_->tailwind_config_->tables.tableLayout.regex, classes);
    classes_data_map["caption_side"] = findAndRemoveMatche(stylus_->tailwind_config_->tables.captionSide.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["tables"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        tablesWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            tablesWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            tablesWidget_->m_main_toggler_->setChecked(false);
        }
    }
    tablesWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setTransitionsAndAnimationClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setTransitionsAndAnimationClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["transition_propriety"] = findAndRemoveMatche(stylus_->tailwind_config_->transitionsAndAnimation.transitionProperty.regex, classes);
    classes_data_map["transition_duration"] = findAndRemoveMatche(stylus_->tailwind_config_->transitionsAndAnimation.transitionDuration.regex, classes);
    classes_data_map["transition_timing_function"] = findAndRemoveMatche(stylus_->tailwind_config_->transitionsAndAnimation.transitionTimingFunction.regex, classes);
    classes_data_map["transition_delay"] = findAndRemoveMatche(stylus_->tailwind_config_->transitionsAndAnimation.transitionDelay.regex, classes);
    classes_data_map["animation"] = findAndRemoveMatche(stylus_->tailwind_config_->transitionsAndAnimation.animation.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["transitions_and_animation"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        transitionsAndAnimationWidget_->setClasses(classes_data_map);
        if (category_classes_data_map_[prefix]["transitions_and_animation"] != "")
        {
            transitionsAndAnimationWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            transitionsAndAnimationWidget_->m_main_toggler_->setChecked(false);
        }
    }

    transitionsAndAnimationWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setTransformsClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setTransformsClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["scale"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.scale.regex, classes);
    classes_data_map["scale-x"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.scale_x.regex, classes);
    classes_data_map["scale-y"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.scale_y.regex, classes);
    classes_data_map["rotate"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.rotate.regex, classes);
    classes_data_map["translate-x"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.translate_x.regex, classes);
    classes_data_map["translate-y"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.translate_y.regex, classes);
    classes_data_map["skew-x"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.skew_x.regex, classes);
    classes_data_map["skew-y"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.skew_y.regex, classes);
    classes_data_map["transform-origin"] = findAndRemoveMatche(stylus_->tailwind_config_->transforms.transformOrigin.regex, classes);

    std::string this_classes;
    // std::cout << prefix << std::endl;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["transforms"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        transformsWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            transformsWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            transformsWidget_->m_main_toggler_->setChecked(false);
        }
    }
    transformsWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setSvgClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setSvgClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["fill"] = findAndRemoveMatche(stylus_->tailwind_config_->svg.fill.regex, classes);
    classes_data_map["stroke"] = findAndRemoveMatche(stylus_->tailwind_config_->svg.stroke.regex, classes);
    classes_data_map["stroke-width"] = findAndRemoveMatche(stylus_->tailwind_config_->svg.strokeWidth.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["svg"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        svgWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            svgWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            svgWidget_->m_main_toggler_->setChecked(false);
        }
    }
    svgWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setAccesibilityClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setAccesibilityClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;
    classes_data_map["screen_readers"] = findAndRemoveMatche(stylus_->tailwind_config_->accesibility.screenReaders.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["accesibility"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        accesibilityWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            accesibilityWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            accesibilityWidget_->m_main_toggler_->setChecked(false);
        }
    }

    accesibilityWidget_->m_main_toggler_->changed().emit();

    return classes;
}
std::string RightPanel::setInteractivityClasses(std::string classes, std::string prefix)
{
    // std::cout << "\n RightPanel::setInteractivityClasses(std::string classes, std::string prefix) \n";
    std::map<std::string, std::string> classes_data_map;

    classes_data_map["accent_color"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.accentColor.regex, classes);
    classes_data_map["appearance"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.appearance.regex, classes);
    classes_data_map["cursor"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.cursor.regex, classes);
    classes_data_map["caret_color"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.caretColor.regex, classes);
    classes_data_map["pointer_events"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.pointerEvents.regex, classes);
    classes_data_map["resize"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.resize.regex, classes);
    classes_data_map["scroll_behavior"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollBehavior.regex, classes);
    classes_data_map["scroll_snap_align"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollSnapAlign.regex, classes);
    classes_data_map["scroll_snap_stop"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollSnapStop.regex, classes);
    classes_data_map["scroll_snap_type"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollSnapType.regex, classes);
    classes_data_map["scroll_snap_strictness"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollSnapStrictness.regex, classes);
    classes_data_map["touch_action"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.touchAction.regex, classes);
    classes_data_map["user_select"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.userSelect.regex, classes);
    classes_data_map["will_change"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.willChange.regex, classes);
    classes_data_map["scroll_p"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding.regex, classes);
    classes_data_map["scroll_px"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding_x.regex, classes);
    classes_data_map["scroll_py"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding_y.regex, classes);
    classes_data_map["scroll_pt"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding_t.regex, classes);
    classes_data_map["scroll_pr"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding_r.regex, classes);
    classes_data_map["scroll_pb"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding_b.regex, classes);
    classes_data_map["scroll_pl"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollPadding_l.regex, classes);
    classes_data_map["scroll_m"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin.regex, classes);
    classes_data_map["scroll_mx"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin_x.regex, classes);
    classes_data_map["scroll_my"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin_y.regex, classes);
    classes_data_map["scroll_mt"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin_t.regex, classes);
    classes_data_map["scroll_mr"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin_r.regex, classes);
    classes_data_map["scroll_mb"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin_b.regex, classes);
    classes_data_map["scroll_ml"] = findAndRemoveMatche(stylus_->tailwind_config_->interactivity.scrollMargin_l.regex, classes);

    std::string this_classes;
    for (auto [key, value] : classes_data_map)
    {
        if (value.compare("none") != 0)
            this_classes += value + " ";
    }
    category_classes_data_map_[prefix]["interactivity"] = this_classes;

    if (current_prefix_.compare(prefix) == 0)
    {
        interactivityWidget_->setClasses(classes_data_map);
        if (this_classes != "")
        {
            interactivityWidget_->m_main_toggler_->setChecked(true);
        }
        else
        {
            interactivityWidget_->m_main_toggler_->setChecked(false);
        }
    }
    interactivityWidget_->m_main_toggler_->changed().emit();

    return classes;
}

std::vector<std::string> RightPanel::findAndRemoveMatches(boost::regex regex, std::string &str)
{
    boost::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    boost::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end)
    {
        result += str.substr(lastPos, it->position() - lastPos);
        matches.push_back(it->str()); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    return matches;
}

std::string RightPanel::findAndRemoveMatche(boost::regex regex, std::string &str)
{
    boost::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    boost::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::string match = "";

    size_t lastPos = 0;
    while (it != end)
    {
        result += str.substr(lastPos, it->position() - lastPos);
        match = it->str(); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    // clean start whitespace from match
    match = boost::regex_replace(match, boost::regex("^\\s+"), "");

    if (match == "")
        match = "none";
    return match;
}