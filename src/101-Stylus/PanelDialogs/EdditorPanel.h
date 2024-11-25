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
    EdditorPanel(Stylus *stylus_brain);

private:
    std::shared_ptr<Wt::WButtonGroup> display_set_group_;

    Wt::WContainerWidget *header_wrapper_;
    Wt::WContainerWidget *content_wrapper_;
    Wt::WContainerWidget *files_menu_;
    Wt::WContainerWidget *file_content_;

    Wt::WContainerWidget *button_btn_group_wrapper_;

    int selected_folder_id_ = 0;
    int selected_file_id_ = 0;

    void createFoldersMenu();
    void createFolderDisplay(int folder_id);
    void createFileTemplates(int file_id);
};