#include "101-Stylus/TCategory/FiltersP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

FiltersP::FiltersP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"blur", "none"},
        {"brightness", "none"},
        {"contrast", "none"},
        {"drop_shadow", "none"},
        {"grayscale", "none"},
        {"hue_rotate", "none"},
        {"invert", "none"},
        {"saturate", "none"},
        {"sepia", "none"},
        {"backdrop_blur", "none"},
        {"backdrop_brightness", "none"},
        {"backdrop_contrast", "none"},
        {"backdrop_grayscale", "none"},
        {"backdrop_hue_rotate", "none"},
        {"backdrop_invert", "none"},
        {"backdrop_opacity", "none"},
        {"backdrop_saturate", "none"},
        {"backdrop_sepia", "none"}};

    std::map<std::string, Propriety> classes_vec_map{
        {"blur", tailwind_config->filters.blur},
        {"brightness", tailwind_config->filters.brightness},
        {"contrast", tailwind_config->filters.contrast},
        {"drop_shadow", tailwind_config->filters.dropShadow},
        {"grayscale", tailwind_config->filters.grayscale},
        {"hue_rotate", tailwind_config->filters.hueRotate},
        {"invert", tailwind_config->filters.invert},
        {"saturate", tailwind_config->filters.saturate},
        {"sepia", tailwind_config->filters.sepia},
        {"backdrop_blur", tailwind_config->filters.backdropBlur},
        {"backdrop_brightness", tailwind_config->filters.backdropBrightness},
        {"backdrop_contrast", tailwind_config->filters.backdropContrast},
        {"backdrop_grayscale", tailwind_config->filters.backdropGrayscale},
        {"backdrop_hue_rotate", tailwind_config->filters.backdropHueRotate},
        {"backdrop_invert", tailwind_config->filters.backdropInvert},
        {"backdrop_opacity", tailwind_config->filters.backdropOpacity},
        {"backdrop_saturate", tailwind_config->filters.backdropSaturate},
        {"backdrop_sepia", tailwind_config->filters.backdropSepia}};

    title->setText("Filters");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto blur_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto brightness_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto contrast_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto drop_shadow_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto grayscale_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto hue_rotate_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto invert_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto saturate_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto sepia_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_blur_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_brightness_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_contrast_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_grayscale_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_hue_rotate_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_invert_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_opacity_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_saturate_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto backdrop_sepia_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    blur_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["blur"].docs_link, "Blur")));
    brightness_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["brightness"].docs_link, "Brightness")));
    contrast_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["contrast"].docs_link, "Contrast")));
    drop_shadow_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["drop_shadow"].docs_link, "Drop Shadow")));
    grayscale_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["grayscale"].docs_link, "Grayscale")));
    hue_rotate_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["hue_rotate"].docs_link, "Hue Rotate")));
    invert_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["invert"].docs_link, "Invert")));
    saturate_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["saturate"].docs_link, "Saturate")));
    sepia_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["sepia"].docs_link, "Sepia")));
    backdrop_blur_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_blur"].docs_link, "BDrop Blur")));
    backdrop_brightness_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_brightness"].docs_link, "BDrop Brightness")));
    backdrop_contrast_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_contrast"].docs_link, "BDrop Contrast")));
    backdrop_grayscale_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_grayscale"].docs_link, "BDrop Grayscale")));
    backdrop_hue_rotate_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_hue_rotate"].docs_link, "BDrop Hue Rotate")));
    backdrop_invert_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_invert"].docs_link, "BDrop Invert")));
    backdrop_opacity_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_opacity"].docs_link, "BDrop Opacity")));
    backdrop_saturate_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_saturate"].docs_link, "BDrop Saturate")));
    backdrop_sepia_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["backdrop_sepia"].docs_link, "BDrop Sepia")));

    blur_wrapper->setStyleClass(wrapper_classes);
    brightness_wrapper->setStyleClass(wrapper_classes);
    contrast_wrapper->setStyleClass(wrapper_classes);
    drop_shadow_wrapper->setStyleClass(wrapper_classes);
    grayscale_wrapper->setStyleClass(wrapper_classes);
    hue_rotate_wrapper->setStyleClass(wrapper_classes);
    invert_wrapper->setStyleClass(wrapper_classes);
    saturate_wrapper->setStyleClass(wrapper_classes);
    sepia_wrapper->setStyleClass(wrapper_classes);
    backdrop_blur_wrapper->setStyleClass(wrapper_classes);
    backdrop_brightness_wrapper->setStyleClass(wrapper_classes);
    backdrop_contrast_wrapper->setStyleClass(wrapper_classes);
    backdrop_grayscale_wrapper->setStyleClass(wrapper_classes);
    backdrop_hue_rotate_wrapper->setStyleClass(wrapper_classes);
    backdrop_invert_wrapper->setStyleClass(wrapper_classes);
    backdrop_opacity_wrapper->setStyleClass(wrapper_classes);
    backdrop_saturate_wrapper->setStyleClass(wrapper_classes);
    backdrop_sepia_wrapper->setStyleClass(wrapper_classes);

    // add widgets
    combobox_map_["blur"] = blur_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["blur"].getClasses()));
    combobox_map_["brightness"] = brightness_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["brightness"].getClasses()));
    combobox_map_["contrast"] = contrast_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["contrast"].getClasses()));
    combobox_map_["drop_shadow"] = drop_shadow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["drop_shadow"].getClasses()));
    combobox_map_["grayscale"] = grayscale_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["grayscale"].getClasses()));
    combobox_map_["hue_rotate"] = hue_rotate_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["hue_rotate"].getClasses()));
    combobox_map_["invert"] = invert_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["invert"].getClasses()));
    combobox_map_["saturate"] = saturate_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["saturate"].getClasses()));
    combobox_map_["sepia"] = sepia_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["sepia"].getClasses()));
    combobox_map_["backdrop_blur"] = backdrop_blur_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_blur"].getClasses()));
    combobox_map_["backdrop_brightness"] = backdrop_brightness_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_brightness"].getClasses()));
    combobox_map_["backdrop_contrast"] = backdrop_contrast_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_contrast"].getClasses()));
    combobox_map_["backdrop_grayscale"] = backdrop_grayscale_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_grayscale"].getClasses()));
    combobox_map_["backdrop_hue_rotate"] = backdrop_hue_rotate_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_hue_rotate"].getClasses()));
    combobox_map_["backdrop_invert"] = backdrop_invert_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_invert"].getClasses()));
    combobox_map_["backdrop_opacity"] = backdrop_opacity_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_opacity"].getClasses()));
    combobox_map_["backdrop_saturate"] = backdrop_saturate_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_saturate"].getClasses()));
    combobox_map_["backdrop_sepia"] = backdrop_sepia_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["backdrop_sepia"].getClasses()));

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

void FiltersP::setCustomTestValues()
{
    classes_data_map_["blur"] = "blur-sm";
    classes_data_map_["brightness"] = "brightness-50";
    classes_data_map_["contrast"] = "contrast-50";
    classes_data_map_["drop_shadow"] = "drop-shadow-md";
    classes_data_map_["grayscale"] = "grayscale";
    classes_data_map_["hue_rotate"] = "hue-rotate-90";
    classes_data_map_["invert"] = "invert";
    classes_data_map_["saturate"] = "saturate-50";
    classes_data_map_["sepia"] = "sepia";
    classes_data_map_["backdrop_blur"] = "backdrop-blur-sm";
    classes_data_map_["backdrop_brightness"] = "backdrop-brightness-50";
    classes_data_map_["backdrop_contrast"] = "backdrop-contrast-50";
    classes_data_map_["backdrop_grayscale"] = "backdrop-grayscale";
    classes_data_map_["backdrop_hue_rotate"] = "backdrop-hue-rotate-90";
    classes_data_map_["backdrop_invert"] = "backdrop-invert";
    classes_data_map_["backdrop_opacity"] = "backdrop-opacity-50";
    classes_data_map_["backdrop_saturate"] = "backdrop-saturate-50";
    classes_data_map_["backdrop_sepia"] = "backdrop-sepia";
}
