#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

struct StylusState
{
    tinyxml2::XMLDocument *settings_xml_doc_;
    tinyxml2::XMLElement *edditor_xml_node_;
    tinyxml2::XMLElement *quick_commands_xml_node_;
    tinyxml2::XMLElement *settings_xml_node_;
    tinyxml2::XMLElement *copy_node_;
    bool edditor_active_ = false;
    bool quick_commands_active_ = false;
    bool settings_active_ = false;
};

class SettingsPanel : public BaseDialogPanel
{
public:
    SettingsPanel(std::shared_ptr<Stylus> stylus);
    std::string radio_checkbox_btn_styles_;

    StylusState stylus_state_;

    Wt::WCheckBox *left_toggler_;
    // Wt::WCheckBox *right_toggler_;
    Wt::WCheckBox *quick_commands_toggler_;
    Wt::WCheckBox *edditor_toggler_;

    // RIGHT_PANEL_MODE right_dialog_panels_mode_;

    // void createRefreshSessionsWidget();

    void createHeaderButtons(Wt::WContainerWidget *wrapper);
    void createLeftPanelSettings(Wt::WContainerWidget *wrapper);
    void createEdditorPanelSettings(Wt::WContainerWidget *wrapper);
    void createQuickCommandsPanelSettings(Wt::WContainerWidget *wrapper);

    void readStateFromXmlFile();

    // void toggleStylusActive();

    // void toggleRightDialogActive();
    void toggleEdditorDialogActive();
    void toggleQuickCommandsDialogActive();
    void toggleSettingsDialogActive();
    void copyNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);
    void pasteNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);

    // void togglefilesManagerDialogActive();
    // void togglefilesManagerLeftMenuActive();

    // void setFileManagerFoldersTreeState();

private:
    const char *xml_file_path = "stylus_config.xml";
};