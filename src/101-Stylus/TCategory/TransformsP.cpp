#include "101-Stylus/TCategory/TransformsP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

TransformsP::TransformsP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"scale", "none"},
        {"scale-x", "none"},
        {"scale-y", "none"},
        {"rotate", "none"},
        {"translate-x", "none"},
        {"translate-y", "none"},
        {"skew-x", "none"},
        {"skew-y", "none"},
        {"transform-origin", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"scale", tailwind_config->transforms.scale},
        {"scale-x", tailwind_config->transforms.scale_x},
        {"scale-y", tailwind_config->transforms.scale_y},
        {"rotate", tailwind_config->transforms.rotate},
        {"translate-x", tailwind_config->transforms.translate_x},
        {"translate-y", tailwind_config->transforms.translate_y},
        {"skew-x", tailwind_config->transforms.skew_x},
        {"skew-y", tailwind_config->transforms.skew_y},
        {"transform-origin", tailwind_config->transforms.transformOrigin}};

    title->setText("Transforms");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto scale_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scale_header_wrapper = scale_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scale_body_wrapper = scale_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto rotate_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto translate_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto translate_header_wrapper = translate_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto translate_body_wrapper = translate_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto skew_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto skew_header_wrapper = skew_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto skew_body_wrapper = skew_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto transform_origin_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    scale_header_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scale"].docs_link, "Scale")));
    rotate_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["rotate"].docs_link, "Rotate")));
    translate_header_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["translate-x"].docs_link, "Translate")));
    skew_header_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["skew-x"].docs_link, "Skew")));
    transform_origin_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["transform-origin"].docs_link, "Transform Origin")));

    scale_wrapper->setStyleClass(wrapper_classes + " !block");
    rotate_wrapper->setStyleClass(wrapper_classes);
    translate_wrapper->setStyleClass(wrapper_classes + " !block");
    skew_wrapper->setStyleClass(wrapper_classes + " !block");
    transform_origin_wrapper->setStyleClass(wrapper_classes);

    scale_header_wrapper->setStyleClass("flex");
    scale_body_wrapper->setStyleClass("flex");
    translate_body_wrapper->setStyleClass("flex");
    skew_body_wrapper->setStyleClass("flex");
    // add widgets
    combobox_map_["scale"] = scale_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scale"].getClasses()));
    combobox_map_["scale-x"] = scale_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scale-x"].getClasses()));
    combobox_map_["scale-y"] = scale_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scale-y"].getClasses()));
    combobox_map_["rotate"] = rotate_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["rotate"].getClasses()));
    combobox_map_["translate-x"] = translate_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["translate-x"].getClasses()));
    combobox_map_["translate-y"] = translate_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["translate-y"].getClasses()));
    combobox_map_["skew-x"] = skew_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["skew-x"].getClasses()));
    combobox_map_["skew-y"] = skew_body_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["skew-y"].getClasses()));
    combobox_map_["transform-origin"] = transform_origin_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["transform-origin"].getClasses()));

    // set signals
    for (auto &[key, combobox] : combobox_map_)
    {
        combobox->classChanged().connect(this, [=](std::string className)
                                         {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
        if (classes_vec_map[key].custom_value)
            combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
    }
    setExtraWidgets(classes_vec_map);
}

void TransformsP::setCustomTestValues()
{
    classes_data_map_["scale"] = "scale-150";
    classes_data_map_["scale-x"] = "scale-x-150";
    classes_data_map_["scale-y"] = "scale-y-150";
    classes_data_map_["rotate"] = "rotate-45";
    classes_data_map_["translate-x"] = "translate-x-12";
    classes_data_map_["translate-y"] = "translate-y-12";
    classes_data_map_["skew-x"] = "skew-x-12";
    classes_data_map_["skew-y"] = "skew-y-12";
    classes_data_map_["transform-origin"] = "origin-top-right";
}
