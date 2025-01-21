#include "101-Stylus/TCategory/InteractivityP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

InteractivityP::InteractivityP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"accent_color", "none"},
        {"appearance", "none"},
        {"cursor", "none"},
        {"caret_color", "none"},
        {"pointer_events", "none"},
        {"resize", "none"},
        {"scroll_behavior", "none"},
        {"scroll_m", "none"},
        {"scroll_mx", "none"},
        {"scroll_my", "none"},
        {"scroll_mt", "none"},
        {"scroll_mr", "none"},
        {"scroll_mb", "none"},
        {"scroll_ml", "none"},
        {"scroll_p", "none"},
        {"scroll_px", "none"},
        {"scroll_py", "none"},
        {"scroll_pt", "none"},
        {"scroll_pr", "none"},
        {"scroll_pb", "none"},
        {"scroll_pl", "none"},
        {"scroll_snap_align", "none"},
        {"scroll_snap_stop", "none"},
        {"scroll_snap_type", "none"},
        {"scroll_snap_strictness", "none"},
        {"touch_action", "none"},
        {"user_select", "none"},
        {"will_change", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"accent_color", tailwind_config->interactivity.accentColor},
        {"appearance", tailwind_config->interactivity.appearance},
        {"cursor", tailwind_config->interactivity.cursor},
        {"caret_color", tailwind_config->interactivity.caretColor},
        {"pointer_events", tailwind_config->interactivity.pointerEvents},
        {"resize", tailwind_config->interactivity.resize},
        {"scroll_behavior", tailwind_config->interactivity.scrollBehavior},
        {"scroll_m", tailwind_config->interactivity.scrollMargin},
        {"scroll_mx", tailwind_config->interactivity.scrollMargin_x},
        {"scroll_my", tailwind_config->interactivity.scrollMargin_y},
        {"scroll_mt", tailwind_config->interactivity.scrollMargin_t},
        {"scroll_mr", tailwind_config->interactivity.scrollMargin_r},
        {"scroll_mb", tailwind_config->interactivity.scrollMargin_b},
        {"scroll_ml", tailwind_config->interactivity.scrollMargin_l},
        {"scroll_p", tailwind_config->interactivity.scrollPadding},
        {"scroll_px", tailwind_config->interactivity.scrollPadding_x},
        {"scroll_py", tailwind_config->interactivity.scrollPadding_y},
        {"scroll_pt", tailwind_config->interactivity.scrollPadding_t},
        {"scroll_pr", tailwind_config->interactivity.scrollPadding_r},
        {"scroll_pb", tailwind_config->interactivity.scrollPadding_b},
        {"scroll_pl", tailwind_config->interactivity.scrollPadding_l},
        {"scroll_snap_align", tailwind_config->interactivity.scrollSnapAlign},
        {"scroll_snap_stop", tailwind_config->interactivity.scrollSnapStop},
        {"scroll_snap_type", tailwind_config->interactivity.scrollSnapType},
        {"scroll_snap_strictness", tailwind_config->interactivity.scrollSnapStrictness},
        {"touch_action", tailwind_config->interactivity.touchAction},
        {"user_select", tailwind_config->interactivity.userSelect},
        {"will_change", tailwind_config->interactivity.willChange}};

    title->setText("Interactivity");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto accent_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto appearance_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto cursor_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto caret_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto pointer_events_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto resize_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scroll_behavior_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    auto margin_padding_general_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scroll_margin_general_wrapper = margin_padding_general_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scroll_padding_general_wrapper = margin_padding_general_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

    auto margin_padding_direction_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto m_p_direction_first_wrapper = margin_padding_direction_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto m_p_direction_second_wrapper = margin_padding_direction_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto m_p_direction_third_wrapper = margin_padding_direction_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto m_p_direction_fourth_wrapper = margin_padding_direction_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

    auto scroll_snap_align_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scroll_snap_stop_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scroll_snap_type_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto scroll_snap_strictness_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto touch_action_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto user_select_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto will_change_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    accent_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["accent_color"].docs_link, "Accent Col")));
    appearance_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["appearance"].docs_link, "Appearance")));
    cursor_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["cursor"].docs_link, "Cursor")));
    caret_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["caret_color"].docs_link, "Caret Col")));
    pointer_events_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["pointer_events"].docs_link, "Pointer Events")));
    resize_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["resize"].docs_link, "Resize")));
    scroll_behavior_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_behavior"].docs_link, "Scroll Behavior")));
    // scroll_margin_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_m"].docs_link, "Scroll Margin")));
    // scroll_padding_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_p"].docs_link, "Scroll Padding")));
    scroll_snap_align_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_snap_align"].docs_link, "Scroll Snap Align")));
    scroll_snap_stop_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_snap_stop"].docs_link, "Scroll Snap Stop")));
    scroll_snap_type_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_snap_type"].docs_link, "Scroll Snap Type")));
    scroll_snap_strictness_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["scroll_snap_strictness"].docs_link, "Scroll Snap Strictness")));
    touch_action_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["touch_action"].docs_link, "Touch Action")));
    user_select_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["user_select"].docs_link, "User Select")));
    will_change_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["will_change"].docs_link, "Will Change")));

    accent_color_wrapper->setStyleClass(wrapper_classes);
    appearance_wrapper->setStyleClass(wrapper_classes);
    cursor_wrapper->setStyleClass(wrapper_classes);
    caret_color_wrapper->setStyleClass(wrapper_classes);
    pointer_events_wrapper->setStyleClass(wrapper_classes);
    resize_wrapper->setStyleClass(wrapper_classes);
    scroll_behavior_wrapper->setStyleClass(wrapper_classes);
    // scroll_margin_wrapper->setStyleClass(wrapper_classes);
    // scroll_padding_wrapper->setStyleClass(wrapper_classes);
    scroll_snap_align_wrapper->setStyleClass(wrapper_classes);
    scroll_snap_stop_wrapper->setStyleClass(wrapper_classes);
    scroll_snap_type_wrapper->setStyleClass(wrapper_classes);
    scroll_snap_strictness_wrapper->setStyleClass(wrapper_classes);
    touch_action_wrapper->setStyleClass(wrapper_classes);
    user_select_wrapper->setStyleClass(wrapper_classes);
    will_change_wrapper->setStyleClass(wrapper_classes);

    margin_padding_general_wrapper->setStyleClass("flex text-center");
    scroll_margin_general_wrapper->setStyleClass("w-1/2");
    scroll_padding_general_wrapper->setStyleClass("w-1/2");

    margin_padding_direction_wrapper->setStyleClass("my-6 mx-auto px-4 min-h-[90px] w-4/5  border-[4px] border-dashed border-neutral-300 flex flex-col justify-between items-stretch");
    m_p_direction_first_wrapper->setStyleClass("flex mb-1 flex-col w-fit mx-auto -mt-7");
    m_p_direction_second_wrapper->setStyleClass("mb-1 flex justify-between -mx-12 space-x-6");
    m_p_direction_third_wrapper->setStyleClass("mb-1 flex justify-around -mx-8 space-x-1");
    m_p_direction_fourth_wrapper->setStyleClass("flex flex-col w-fit mx-auto -mb-7");

    combobox_map_["scroll_p"] = scroll_padding_general_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_p"].getClasses()));
    combobox_map_["scroll_px"] = scroll_padding_general_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_px"].getClasses()));
    combobox_map_["scroll_py"] = scroll_padding_general_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_py"].getClasses()));

    combobox_map_["scroll_m"] = scroll_margin_general_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_m"].getClasses()));
    combobox_map_["scroll_mx"] = scroll_margin_general_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_mx"].getClasses()));
    combobox_map_["scroll_my"] = scroll_margin_general_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_my"].getClasses()));

    combobox_map_["scroll_mt"] = m_p_direction_first_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_mt"].getClasses()));
    combobox_map_["scroll_pt"] = m_p_direction_first_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_pt"].getClasses()));
    combobox_map_["scroll_mr"] = m_p_direction_second_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_mr"].getClasses()));
    combobox_map_["scroll_ml"] = m_p_direction_second_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_ml"].getClasses()));
    combobox_map_["scroll_pr"] = m_p_direction_third_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_pr"].getClasses()));
    combobox_map_["scroll_pl"] = m_p_direction_third_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_pl"].getClasses()));
    combobox_map_["scroll_pb"] = m_p_direction_fourth_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_pb"].getClasses()));
    combobox_map_["scroll_mb"] = m_p_direction_fourth_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_mb"].getClasses()));

    colors_map_["accent_color"] = accent_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["accent_color"]));
    combobox_map_["appearance"] = appearance_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["appearance"].getClasses()));
    combobox_map_["cursor"] = cursor_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["cursor"].getClasses()));
    colors_map_["caret_color"] = caret_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["caret_color"]));
    combobox_map_["pointer_events"] = pointer_events_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["pointer_events"].getClasses()));
    combobox_map_["resize"] = resize_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["resize"].getClasses()));
    combobox_map_["scroll_behavior"] = scroll_behavior_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_behavior"].getClasses()));
    combobox_map_["scroll_snap_align"] = scroll_snap_align_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_snap_align"].getClasses()));
    combobox_map_["scroll_snap_stop"] = scroll_snap_stop_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_snap_stop"].getClasses()));
    combobox_map_["scroll_snap_type"] = scroll_snap_type_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_snap_type"].getClasses()));
    combobox_map_["scroll_snap_strictness"] = scroll_snap_strictness_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["scroll_snap_strictness"].getClasses()));
    combobox_map_["touch_action"] = touch_action_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["touch_action"].getClasses()));
    combobox_map_["user_select"] = user_select_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["user_select"].getClasses()));
    combobox_map_["will_change"] = will_change_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["will_change"].getClasses()));

    // signals for default classes for tailwind
    for (auto &[key, combobox] : combobox_map_)
    {
        combobox->classChanged().connect(this, [=](std::string className)
                                         {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
        if (classes_vec_map[key].custom_value)
            combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
    }
    for (const auto &[key, widget] : colors_map_)
    {
        widget->classChanged().connect(this, [=](std::string className)
                                       {
            classes_data_map_[key] = className;
            styleChanged_.emit(getStyles()); });
        widget->setCustom(false);
    }

    setExtraWidgets(classes_vec_map);
}

void InteractivityP::setCustomTestValues()
{
    classes_data_map_["accent_color"] = "accent-sky-900";
    classes_data_map_["appearance"] = "appearance-none";
    classes_data_map_["cursor"] = "cursor-not-allowed";
    classes_data_map_["caret_color"] = "caret-transparent";
    classes_data_map_["pointer_events"] = "pointer-events-auto";
    classes_data_map_["resize"] = "resize-none";
    classes_data_map_["scroll_behavior"] = "scroll-smooth";
    classes_data_map_["scroll_snap_align"] = "snap-start";
    classes_data_map_["scroll_snap_stop"] = "snap-always";
    classes_data_map_["scroll_snap_type"] = "snap-x";
    classes_data_map_["scroll_snap_strictness"] = "snap-mandatory";
    classes_data_map_["touch_action"] = "touch-auto";
    classes_data_map_["user_select"] = "select-auto";
    classes_data_map_["will_change"] = "will-change-auto";
    classes_data_map_["scroll_p"] = "scroll-p-6";
    classes_data_map_["scroll_px"] = "scroll-px-6";
    classes_data_map_["scroll_py"] = "scroll-py-6";
    classes_data_map_["scroll_pt"] = "scroll-pt-6";
    classes_data_map_["scroll_pr"] = "scroll-pr-6";
    classes_data_map_["scroll_pb"] = "scroll-pb-6";
    classes_data_map_["scroll_pl"] = "scroll-pl-6";
    classes_data_map_["scroll_m"] = "scroll-m-6";
    classes_data_map_["scroll_mx"] = "scroll-mx-6";
    classes_data_map_["scroll_my"] = "scroll-my-6";
    classes_data_map_["scroll_mt"] = "scroll-mt-6";
    classes_data_map_["scroll_mr"] = "scroll-mr-6";
    classes_data_map_["scroll_mb"] = "scroll-mb-6";
    classes_data_map_["scroll_ml"] = "scroll-ml-6";
}