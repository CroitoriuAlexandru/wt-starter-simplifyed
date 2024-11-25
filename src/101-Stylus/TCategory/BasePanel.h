#pragma once
#include <Wt/WPanel.h>
#include <Wt/WCheckBox.h>
#include <Wt/WLabel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <string>
#include "101-Stylus/ClassChangers/ComboBoxClassChanger.h"
#include "101-Stylus/ClassChangers/SelectionBoxClassChanger.h"
#include "101-Stylus/ClassChangers/ColorsWidget.h"
#include "101-Stylus/Tailwind/Base.h"
// #include "101-Stylus/PanelDialogs/RightPanel.h"

enum RIGHT_PANEL_MODE
{
    NORMAL = 10,
    EXTRA = 11,
    BOTH = 12
};

class TailwindConfig;

class BasePanel : public Wt::WContainerWidget
{
public:
    BasePanel(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper, RIGHT_PANEL_MODE mode = RIGHT_PANEL_MODE::EXTRA);
    Wt::WContainerWidget *extra_widgets_wrapper_;
    Wt::WContainerWidget *headerWidget;
    Wt::WContainerWidget *extraButtonsWidget;
    Wt::WContainerWidget *centralWidget;
    Wt::WText *title;
    Wt::Signal<std::string> &styleChanged() { return styleChanged_; };

    std::unique_ptr<Wt::WAnchor> createAnchorToDocs(std::string link, std::string text);

    Wt::WCheckBox *addToggler(Wt::WWidget *widget, std::string label_text);

    TailwindConfig *tailwind_config_;
    std::map<std::string, std::string> classes_data_map_;

    std::string getStyles();

    std::map<std::string, ComboBoxClassChanger *> extra_combobox_map_;
    std::map<std::string, ColorsWidget *> extra_colors_map_;

    std::map<std::string, ComboBoxClassChanger *> combobox_map_;
    std::map<std::string, ColorsWidget *> colors_map_;
    std::map<std::string, Wt::WCheckBox *> checkbox_map_;
    std::map<std::string, SelectionBoxClassChanger *> selectionbox_map_;

    void setClasses(std::map<std::string, std::string> classes_data_map);

    void setExtraWidgets(std::map<std::string, Propriety> classes_vec_map);
    void setPanelMode(RIGHT_PANEL_MODE mode);
    RIGHT_PANEL_MODE panel_mode_;

protected:
    Wt::Signal<std::string> styleChanged_;
    virtual void setCustomTestValues() = 0;
    virtual void setDisplayWidgets(std::string key, std::string value);

    void resetStyles();
    std::string link_classes;
    std::string wrapper_classes;

private:
};