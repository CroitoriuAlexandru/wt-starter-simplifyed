#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "101-Stylus/XMLBrain.h"

class TempPreview : public Wt::WContainerWidget
{
public:
    TempPreview(std::shared_ptr<Stylus> stylus);

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain = nullptr);
    Wt::WContainerWidget *preview_wrapper_;

    void setFolders();
    void setFiles(std::string folder_name);
    void setTemplates(std::string file_name);

private:
    std::shared_ptr<XMLBrain> xml_brain_;
    std::shared_ptr<Stylus> stylus_;

    Wt::WComboBox *folder_combo_box_;
    Wt::WComboBox *file_combo_box_;
    Wt::WComboBox *template_combo_box_;
};