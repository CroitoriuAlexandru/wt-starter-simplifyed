#include "101-Stylus/TCategory/TransitionsAndAnimationP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

TransitionsAndAnimationP::TransitionsAndAnimationP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"transition_propriety", "none"},
        {"transition_duration", "none"},
        {"transition_timing_function", "none"},
        {"transition_delay", "none"},
        {"animation", "none"}};
    std::map<std::string, Propriety> classes_vec_map = {
        {"transition_propriety", tailwind_config_->transitionsAndAnimation.transitionProperty},
        {"transition_duration", tailwind_config_->transitionsAndAnimation.transitionDuration},
        {"transition_timing_function", tailwind_config_->transitionsAndAnimation.transitionTimingFunction},
        {"transition_delay", tailwind_config_->transitionsAndAnimation.transitionDelay},
        {"animation", tailwind_config_->transitionsAndAnimation.animation}};

    title->setText("Transitions And Animation");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto transition_propriety_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto transition_duration_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto transition_timing_function_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto transition_delay_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto animation_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    transition_propriety_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["transition_propriety"].docs_link, "Trans")));
    transition_duration_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["transition_duration"].docs_link, "Dur")));
    transition_timing_function_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["transition_timing_function"].docs_link, "Time")));
    transition_delay_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["transition_delay"].docs_link, "Delay")));
    animation_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["animation"].docs_link, "Anim")));

    transition_propriety_wrapper->setStyleClass(wrapper_classes);
    transition_duration_wrapper->setStyleClass(wrapper_classes);
    transition_timing_function_wrapper->setStyleClass(wrapper_classes);
    transition_delay_wrapper->setStyleClass(wrapper_classes);
    animation_wrapper->setStyleClass(wrapper_classes);

    // add widgets
    combobox_map_["transition_propriety"] = transition_propriety_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["transition_propriety"].getClasses()));
    combobox_map_["transition_duration"] = transition_duration_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["transition_duration"].getClasses()));
    combobox_map_["transition_timing_function"] = transition_timing_function_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["transition_timing_function"].getClasses()));
    combobox_map_["transition_delay"] = transition_delay_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["transition_delay"].getClasses()));
    combobox_map_["animation"] = animation_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["animation"].getClasses()));

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

void TransitionsAndAnimationP::setCustomTestValues()
{
    classes_data_map_["transition_propriety"] = "transition-all";
    classes_data_map_["transition_duration"] = "duration-300";
    classes_data_map_["transition_timing_function"] = "ease-in-out";
    classes_data_map_["transition_delay"] = "delay-300";
    classes_data_map_["animation"] = "animate-spin";
}