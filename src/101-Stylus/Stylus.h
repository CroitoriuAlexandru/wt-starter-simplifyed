#pragma once
#include "002-Dbo/Session.h"
#include "002-Dbo/Tables.h"
#include "101-Stylus/XMLBrain.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

#include <Wt/WSignal.h>

class LeftPanel;
class RightPanel;
class EdditorPanel;
class SettingsPanel;
class QuickCommandsPanel;

class Stylus
{
public:
    Stylus(Session &session, Wt::WString templates_root_path);

    TailwindConfig *tailwind_config_;

    void addFileToDbo(Wt::WString folder_name, Wt::WString file_path);
    void saveFileFromDbo(Wt::WString folder_name, Wt::WString file_name);

    LeftPanel *left_panel_;
    // RightPanel *right_panel_;
    EdditorPanel *edditor_panel_;
    SettingsPanel *settings_panel_;
    QuickCommandsPanel *quick_commands_panel_;

    Session &session_;
    Wt::WString templates_root_path_;
    Wt::WString default_folder_name = "default";

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain);

    std::shared_ptr<XMLBrain> xml_brain_;

    Wt::Signal<std::shared_ptr<XMLBrain>> &node_selected() { return node_selected_; }

private:
    void processKeyEvent(Wt::WKeyEvent e);

    Wt::Signal<std::shared_ptr<XMLBrain>> node_selected_;
};