#include "101-Stylus/TCategory/AccesibilityP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

AccesibilityP::AccesibilityP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{
    classes_data_map_ = {
        {"screen_readers", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"screen_readers", tailwind_config->accesibility.screenReaders}};

    title->setText("Accesibility");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto screen_readers_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    screen_readers_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["screen_readers"].docs_link, "Screen Readers")));

    screen_readers_wrapper->setStyleClass(wrapper_classes);

    // add widgets
    combobox_map_["screen_readers"] = screen_readers_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["screen_readers"].getClasses()));

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

void AccesibilityP::setCustomTestValues()
{
    classes_data_map_["screen_readers"] = "not-sr-only";
}
