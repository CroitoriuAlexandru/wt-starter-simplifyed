#pragma once
#include "002-Dbo/Session.h"
#include "002-Dbo/Tables.h"
#include "101-Stylus/XMLBrain.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

#include <Wt/WSignal.h>
#include <memory>

class EdditorPanel;
class SettingsPanel;
class QuickCommandsPanel;

class Stylus
{
public:
    Stylus(Session &session, Wt::WString templates_root_path);
    void setXmlBrains(std::shared_ptr<Stylus> stylus);

    TailwindConfig *tailwind_config_;
    std::map<std::string, std::shared_ptr<XMLBrain>> xml_brains_;

    void addFileToDbo(Wt::WString folder_name, Wt::WString file_path);
    void saveFileFromDbo(Wt::WString folder_name, Wt::WString file_name);

    EdditorPanel *edditor_panel_;
    SettingsPanel *settings_panel_;
    QuickCommandsPanel *quick_commands_panel_;

    Session &session_;
    Wt::WString templates_root_path_;
    Wt::WString default_folder_name = "default";

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain);

    std::shared_ptr<XMLBrain> xml_brain_;

    Wt::Signal<std::shared_ptr<XMLBrain>> &node_selected() { return node_selected_; }

    // void processKeyEvent(Wt::WKeyEvent e);

private:
    Wt::Signal<std::shared_ptr<XMLBrain>> node_selected_;
};