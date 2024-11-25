#include "101-Stylus/TCategory/SvgP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

SvgP::SvgP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"fill", "none"},
        {"stroke", "none"},
        {"stroke-width", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"fill", tailwind_config->svg.fill},
        {"stroke", tailwind_config->svg.stroke},
        {"stroke-width", tailwind_config->svg.strokeWidth}};
    title->setText("SVG");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto fill_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto stroke_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto stroke_width_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    fill_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["fill"].docs_link, "Fill")));
    stroke_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["stroke"].docs_link, "Stroke")));
    stroke_width_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["stroke-width"].docs_link, "Stroke Width")));

    fill_wrapper->setStyleClass("flex justify-between relative w-full");
    stroke_wrapper->setStyleClass("flex justify-between relative");
    stroke_width_wrapper->setStyleClass(wrapper_classes);

    // add widgets
    colors_map_["fill"] = fill_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["fill"]));
    colors_map_["stroke"] = stroke_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["stroke"]));
    combobox_map_["stroke-width"] = stroke_width_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["stroke-width"].getClasses()));

    // set signals
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
}

void SvgP::setCustomTestValues()
{
    classes_data_map_["fill"] = "fill-red-500";
    classes_data_map_["stroke"] = "stroke-green-500";
    classes_data_map_["stroke-width"] = "stroke-2";
}
