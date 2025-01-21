#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "101-Stylus/XMLBrain.h"

#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>

class EdditorPanel : public BaseDialogPanel
{
public:
    EdditorPanel(std::shared_ptr<Stylus> stylus);

private:
    Wt::WContainerWidget *folders_menu_wrapper_;
    Wt::WContainerWidget *files_menu_wrapper_;
    Wt::WContainerWidget *content_wrapper_;

    int selected_folder_id_ = 0;
    int selected_file_id_ = 0;

    void createFoldersMenu();
    void createFilesMenu(int folder_id);
    void createFileTemplates(int file_id);
};