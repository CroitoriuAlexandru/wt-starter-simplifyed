#include "101-Stylus/TCategory/TablesP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

TablesP::TablesP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"border_collapse", "none"},
        {"border_spacing", "none"},
        {"border_spacing_x", "none"},
        {"border_spacing_y", "none"},
        {"table_layout", "none"},
        {"caption_side", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"border_collapse", tailwind_config->tables.borderCollapse},
        {"border_spacing", tailwind_config->tables.borderSpacing},
        {"border_spacing_x", tailwind_config->tables.borderSpacing_x},
        {"border_spacing_y", tailwind_config->tables.borderSpacing_y},
        {"table_layout", tailwind_config->tables.tableLayout},
        {"caption_side", tailwind_config->tables.captionSide}};

    title->setText("Tables");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto border_collapse_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto border_spacing_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto border_spacing_header = border_spacing_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto border_spacing_body = border_spacing_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto table_layout_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto caption_side_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    border_collapse_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["border_collapse"].docs_link, "Border Collapse")));
    border_spacing_header->addWidget(std::move(createAnchorToDocs(classes_vec_map["border_spacing"].docs_link, "Border Spacing")));
    table_layout_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["table_layout"].docs_link, "Table Layout")));
    caption_side_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["caption_side"].docs_link, "Caption Side")));

    border_collapse_wrapper->setStyleClass(wrapper_classes);
    border_spacing_wrapper->setStyleClass(wrapper_classes + " !block");
    border_spacing_header->setStyleClass("flex");
    border_spacing_body->setStyleClass("flex");
    table_layout_wrapper->setStyleClass(wrapper_classes);
    caption_side_wrapper->setStyleClass(wrapper_classes);

    // add widgets
    combobox_map_["border_collapse"] = border_collapse_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_collapse"].getClasses()));
    combobox_map_["border_spacing"] = border_spacing_header->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_spacing"].getClasses()));
    combobox_map_["border_spacing_x"] = border_spacing_body->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_spacing_x"].getClasses()));
    combobox_map_["border_spacing_y"] = border_spacing_body->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["border_spacing_y"].getClasses()));
    combobox_map_["table_layout"] = table_layout_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["table_layout"].getClasses()));
    combobox_map_["caption_side"] = caption_side_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["caption_side"].getClasses()));

    // signals
    for (auto &[key, combobox] : combobox_map_)
    {
        combobox->classChanged().connect(this, [=](std::string className)
                                         {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
        if (classes_vec_map[key].custom_value)
            combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
    }
    setExtraWidgets(classes_vec_map);
}

void TablesP::setCustomTestValues()
{
    classes_data_map_["border_collapse"] = "border-collapse";
    classes_data_map_["border_spacing"] = "border-spacing-12";
    classes_data_map_["border_spacing_x"] = "border-spacing-x-12";
    classes_data_map_["border_spacing_y"] = "border-spacing-y-12";
    classes_data_map_["table_layout"] = "table-auto";
    classes_data_map_["caption_side"] = "caption-top";
}
