#include "101-Stylus/TCategory/EffectsP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

EffectsP::EffectsP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"box_shadow", "none"},
        {"box_shadow_inner", "none"},
        {"box_shadow_color", "none"},
        {"opacity", "none"},
        {"mix_blend_mode", "none"},
        {"background_blend_mode", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"box_shadow", tailwind_config->effects.boxShadow},
        {"box_shadow_inner", tailwind_config->effects.boxShadow_inner},
        {"box_shadow_color", tailwind_config->effects.boxShadowColor},
        {"opacity", tailwind_config->effects.opacity},
        {"mix_blend_mode", tailwind_config->effects.mixBlendMode},
        {"background_blend_mode", tailwind_config->effects.backgroundBlendMode}};

    title->setText("Effects");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto box_shadow_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto box_shadow_header_wrapper = box_shadow_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto box_shadow_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto opacity_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto mix_blend_mode_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto background_blend_mode_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    box_shadow_header_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["box_shadow"].docs_link, "Shadow")))->setCanReceiveFocus(false);
    box_shadow_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["box_shadow_color"].docs_link, "Color")))->setCanReceiveFocus(false);
    opacity_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["opacity"].docs_link, "Opacity")))->setCanReceiveFocus(false);
    mix_blend_mode_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["mix_blend_mode"].docs_link, "Mix Blend Mode")))->setCanReceiveFocus(false);
    background_blend_mode_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["background_blend_mode"].docs_link, "Background Blend Mode")))->setCanReceiveFocus(false);

    box_shadow_wrapper->setStyleClass(wrapper_classes + " flex-col");
    box_shadow_header_wrapper->setStyleClass("flex items-center justify-between w-full");
    box_shadow_color_wrapper->setStyleClass(wrapper_classes);
    opacity_wrapper->setStyleClass(wrapper_classes);
    mix_blend_mode_wrapper->setStyleClass(wrapper_classes);
    background_blend_mode_wrapper->setStyleClass(wrapper_classes);

    // add widgets
    combobox_map_["box_shadow"] = box_shadow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["box_shadow"].getClasses()));
    combobox_map_["opacity"] = opacity_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["opacity"].getClasses()));
    combobox_map_["mix_blend_mode"] = mix_blend_mode_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["mix_blend_mode"].getClasses()));
    combobox_map_["background_blend_mode"] = background_blend_mode_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["background_blend_mode"].getClasses()));
    colors_map_["box_shadow_color"] = box_shadow_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["box_shadow_color"]));

    checkbox_map_["box_shadow_inner"] = box_shadow_header_wrapper->addWidget(std::make_unique<Wt::WCheckBox>("Shadow Inner"));

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
                                             {classes_data_map_[color.first] = className; styleChanged_.emit(getStyles()); });
    }
    checkbox_map_["box_shadow_inner"]->changed().connect(this, [=]()
                                                         { 
		if(checkbox_map_["box_shadow_inner"]->isChecked())
			classes_data_map_["box_shadow_inner"] = "shadow-inner"; 
		else 
			classes_data_map_["box_shadow_inner"] = "none";
		styleChanged_.emit(getStyles()); });

    setExtraWidgets(classes_vec_map);
}

void EffectsP::setCustomTestValues()
{
    classes_data_map_["box_shadow"] = "shadow-md";
    classes_data_map_["box_shadow_inner"] = "shadow-inner";
    classes_data_map_["box_shadow_color"] = "shadow-red-500";
    classes_data_map_["opacity"] = "opacity-50";
    classes_data_map_["mix_blend_mode"] = "mix-blend-normal";
    classes_data_map_["background_blend_mode"] = "bg-blend-multiply";
}
