#include "101-Stylus/PanelDialogs/SettingsPanel.h"
#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/PanelDialogs/QuickCommandsPanel.h"

#include "101-Stylus/Stylus.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WCheckBox.h>

SettingsPanel::SettingsPanel(std::shared_ptr<Stylus> stylus)
    : BaseDialogPanel(stylus)
{
    // addStyleClass("!text-black");
    contents()->addStyleClass("flex flex-col items-center rounded-b-md");
    titleBar()->addStyleClass("!text-black rounded-t-md");
    setOffsets(100, Wt::Side::Top | Wt::Side::Bottom);
    setOffsets(580, Wt::Side::Right | Wt::Side::Left);

    radio_checkbox_btn_styles_ = "[&>input]:hidden "
                                 "m-0.5 mb-1 "
                                 "[&>span]:bg-gray-900 "
                                 "[&>span]:text-bold "
                                 "[&>span]:text-gray-200 "
                                 "[&>span]:p-0.5 "
                                 "[&>span]:px-1 "
                                 "[&>span]:border-2 "
                                 "[&>span]:border-solid "
                                 "[&>span]:border-gray-600 "
                                 "[&>span]:rounded-md "
                                 "[&>input:checked~span]:bg-gray-300 "
                                 "[&>input:checked~span]:text-gray-900";

    //  = stylus_brain_->getXMLBrain("config");
    // readDataFromXml();
    // createRefreshSessionsWidget();

    auto left_right_panels_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto rest_of_panels_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    left_right_panels_wrapper->setStyleClass("flex w-full");
    rest_of_panels_wrapper->setStyleClass("flex w-full");

    readStateFromXmlFile();

    createLeftPanelSettings(left_right_panels_wrapper);
    createRightPanelSettings(left_right_panels_wrapper);
    createEdditorPanelSettings(rest_of_panels_wrapper);
    createQuickCommandsPanelSettings(rest_of_panels_wrapper);
}

// void SettingsPanel::createRefreshSessionsWidget()
// {
//     auto refresh_sessions_btn = titleBar()->addWidget(std::make_unique<Wt::WText>("refresh all sessions"));

//     refresh_sessions_btn->setStyleClass("text-white h-fit bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm p-1 text-center inline-flex items-center me-2 m-1 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800");

//     refresh_sessions_btn->clicked().connect([=]
//                                             { Wt::WServer::instance()->postAll([=]
//                                                                                {
//             Wt::WApplication::instance()->messageResourceBundle().keys("");
//             Wt::WApplication::instance()->refresh();
//             Wt::WApplication::instance()->triggerUpdate(); }); });
// }

void SettingsPanel::createRightPanelSettings(Wt::WContainerWidget *wrapper)
{
    auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-1/2 h-fit bg-gray-800 rounded-md");
    auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
    auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    content->setStyleClass("p-2");
    header->addWidget(std::make_unique<Wt::WText>("Right Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

    right_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("Tgg Vis"));
    right_toggler_->setStyleClass(radio_checkbox_btn_styles_);
    right_toggler_->setChecked(stylus_state_.right_active_);
    right_toggler_->changed().connect([=]()
                                      { toggleRightDialogActive(); });
}
void SettingsPanel::createLeftPanelSettings(Wt::WContainerWidget *wrapper)
{
    auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-1/2 h-fit bg-gray-800 rounded-md");
    auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
    auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    content->setStyleClass("p-2");
    header->addWidget(std::make_unique<Wt::WText>("Left Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

    left_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("Tgg Vis"));
    left_toggler_->setStyleClass(radio_checkbox_btn_styles_);
    left_toggler_->setChecked(stylus_state_.left_active_);
    left_toggler_->changed().connect([=]()
                                     { toggleLeftDialogActive(); });
}
void SettingsPanel::createEdditorPanelSettings(Wt::WContainerWidget *wrapper)
{
    auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-1/2 h-fit bg-gray-800 rounded-md");
    auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
    auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    content->setStyleClass("p-2");
    header->addWidget(std::make_unique<Wt::WText>("Template Edditor Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

    edditor_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("Tgg Vis"));
    edditor_toggler_->setStyleClass(radio_checkbox_btn_styles_);
    edditor_toggler_->setChecked(stylus_state_.edditor_active_);
    edditor_toggler_->changed().connect([=]()
                                        { toggleEdditorDialogActive(); });
}
void SettingsPanel::createQuickCommandsPanelSettings(Wt::WContainerWidget *wrapper)
{
    auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-1/2 h-fit bg-gray-800 rounded-md");
    auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
    auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    content->setStyleClass("p-2");
    header->addWidget(std::make_unique<Wt::WText>("Quick Commands Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

    quick_commands_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("Tgg Vis"));
    quick_commands_toggler_->setStyleClass(radio_checkbox_btn_styles_);
    quick_commands_toggler_->setChecked(stylus_state_.quick_commands_active_);
    quick_commands_toggler_->changed().connect([=]()
                                               { toggleQuickCommandsDialogActive(); });
}

void SettingsPanel::readStateFromXmlFile()
{
    settings_xml_doc_ = new tinyxml2::XMLDocument();
    settings_xml_doc_->LoadFile(xml_file_path);
    // get or set messages node
    auto messages_node = settings_xml_doc_->FirstChildElement("messages");
    if (!messages_node)
    {
        messages_node = settings_xml_doc_->NewElement("messages");
        settings_xml_doc_->InsertFirstChild(messages_node);
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    // get or set message node
    auto message_node = messages_node->FirstChildElement("message");
    if (!message_node)
    {
        message_node = settings_xml_doc_->NewElement("message");
        messages_node->InsertEndChild(message_node);
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    // Set message id attribute
    if (!message_node->Attribute("id"))
    {
        message_node->SetAttribute("id", "stylus.config");
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    else if (std::string(message_node->Attribute("id")).compare("stylus.config") != 0)
    {
        message_node->SetAttribute("id", "stylus.config");
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    // get or set left panel node
    left_xml_node_ = message_node->FirstChildElement("leftPanel");
    if (!left_xml_node_)
    {
        left_xml_node_ = settings_xml_doc_->NewElement("leftPanel");
        left_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(left_xml_node_);
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(left_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.left_active_ = true;
        }
        else
        {
            stylus_state_.left_active_ = false;
        }
    }
    // get or set right panel node
    right_xml_node_ = message_node->FirstChildElement("rightPanel");
    if (!right_xml_node_)
    {
        right_xml_node_ = settings_xml_doc_->NewElement("rightPanel");
        right_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(right_xml_node_);
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(right_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.right_active_ = true;
        }
        else
        {
            stylus_state_.right_active_ = false;
        }
    }
    // get or set edditor panel node
    edditor_xml_node_ = message_node->FirstChildElement("edditorPanel");
    if (!edditor_xml_node_)
    {
        edditor_xml_node_ = settings_xml_doc_->NewElement("edditorPanel");
        edditor_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(edditor_xml_node_);

        settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(edditor_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.edditor_active_ = true;
        }
        else
        {
            stylus_state_.edditor_active_ = false;
        }
    }
    // get or set quick commands panel node
    quick_commands_xml_node_ = message_node->FirstChildElement("quickCommandsPanel");
    if (!quick_commands_xml_node_)
    {
        quick_commands_xml_node_ = settings_xml_doc_->NewElement("quickCommandsPanel");
        quick_commands_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(quick_commands_xml_node_);
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(quick_commands_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.quick_commands_active_ = true;
        }
        else
        {
            stylus_state_.quick_commands_active_ = false;
        }
    }
    // get or set settings panel node
    settings_xml_node_ = message_node->FirstChildElement("settingsPanel");
    if (!settings_xml_node_)
    {
        settings_xml_node_ = settings_xml_doc_->NewElement("settingsPanel");
        settings_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(settings_xml_node_);
        settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(settings_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.settings_active_ = true;
        }
        else
        {
            stylus_state_.settings_active_ = false;
        }
    }
}

// void SettingsPanel::toggleStylusActive()
// {
//     auto stylus_active_node = xml_brain_config_->message_node_->FirstChildElement("stylus-active");
//     if (stylus_active_node)
//     {
//         if (!stylus_state_.stylus_active_)
//         {
//             stylus_active_node->FirstChildElement("active")->SetText("true");
//             stylus_state_.stylus_active_ = true;
//         }
//         else
//         {
//             stylus_active_node->FirstChildElement("active")->SetText("false");
//             stylus_state_.stylus_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     Wt::WApplication::instance()->messageResourceBundle().keys("");
//     Wt::WApplication::instance()->refresh();
// }

// void SettingsPanel::toggleSettingsPanelActive()
// {
//     std::cout << "\n\n toggle brain dialog \n\n";
//     auto brain_dialog_node = xml_brain_config_->message_node_->FirstChildElement("brain-dialog");
//     if (brain_dialog_node)
//     {
//         std::cout << "\n " << brain_dialog_node->GetText() << "\n";
//         if (std::string(brain_dialog_node->FirstChildElement("active")->GetText()) == "false")
//         {
//             brain_dialog_node->FirstChildElement("active")->SetText("true");
//             if (stylus_state_.stylus_active_)
//                 stylus_brain_->m_brain_d_->show();
//             stylus_state_.brain_active_ = true;
//         }
//         else
//         {
//             brain_dialog_node->FirstChildElement("active")->SetText("false");
//             stylus_brain_->m_brain_d_->hide();
//             stylus_state_.brain_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
// }

void SettingsPanel::toggleRightDialogActive()
{
    stylus_state_.right_active_ = !stylus_state_.right_active_;
    right_toggler_->setChecked(stylus_state_.right_active_);
    stylus_->right_panel_->setHidden(!stylus_state_.right_active_);
    right_xml_node_->SetAttribute("active", stylus_state_.right_active_ ? "true" : "false");
    settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::toggleLeftDialogActive()
{
    std::cout << "\n\n toggle control dialog \n\n";
    stylus_state_.left_active_ = !stylus_state_.left_active_;
    stylus_->left_panel_->setHidden(!stylus_state_.left_active_);
    left_toggler_->setChecked(stylus_state_.left_active_);
    left_xml_node_->SetAttribute("active", stylus_state_.left_active_ ? "true" : "false");
    settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::toggleQuickCommandsDialogActive()
{
    std::cout << "\n\n quick commands dialog \n\n";
    stylus_state_.quick_commands_active_ = !stylus_state_.quick_commands_active_;
    quick_commands_toggler_->setChecked(stylus_state_.quick_commands_active_);
    stylus_->quick_commands_panel_->setHidden(!stylus_state_.quick_commands_active_);
    quick_commands_xml_node_->SetAttribute("active", stylus_state_.quick_commands_active_ ? "true" : "false");
    settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::toggleEdditorDialogActive()
{
    std::cout << "\n\n toggle files manager dialog \n\n";
    stylus_state_.edditor_active_ = !stylus_state_.edditor_active_;
    edditor_toggler_->setChecked(stylus_state_.edditor_active_);
    stylus_->edditor_panel_->setHidden(!stylus_state_.edditor_active_);
    edditor_xml_node_->SetAttribute("active", stylus_state_.edditor_active_ ? "true" : "false");
    settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::toggleSettingsDialogActive()
{
    std::cout << "\n\n toggle settings dialog \n\n";
    stylus_state_.settings_active_ = !stylus_state_.settings_active_;
    setHidden(!stylus_state_.settings_active_);
    settings_xml_node_->SetAttribute("active", stylus_state_.settings_active_ ? "true" : "false");
    settings_xml_doc_->SaveFile(xml_file_path);
}

// void SettingsPanel::togglefilesManagerLeftMenuActive()
// {
//     std::cout << "\n\n toggle files manager dialog \n\n";
//     auto files_manager_dialog_node = xml_brain_config_->message_node_->FirstChildElement("files-manager-dialog");
//     if (files_manager_dialog_node)
//     {
//         if (std::string(files_manager_dialog_node->FirstChildElement("files-menu-minimized")->GetText()) == "false")
//         {
//             std::cout << "\n\n files menu is minimized true \n\n";
//             files_manager_dialog_node->FirstChildElement("files-menu-minimized")->SetText("true");
//             stylus_state_.files_manager_files_menu_active_ = true;
//         }
//         else
//         {
//             std::cout << "\n\n files menu is not minimized false \n\n";
//             files_manager_dialog_node->FirstChildElement("files-menu-minimized")->SetText("false");
//             stylus_state_.files_manager_files_menu_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     // stylus_brain_->m_files_manager_d_->toggle_left_menu_btn_->setChecked(stylus_state_.files_manager_files_menu_active_);
//     // stylus_brain_->m_files_manager_d_->toggle_left_menu_btn_->changed().emit();
// }

// void SettingsPanel::setFileManagerFoldersTreeState()
// {
//     std::cout << "\n\n set file manager folders tree state \n\n";
//     auto files_manager_dialog_node = xml_brain_config_->message_node_->FirstChildElement("files-manager-dialog");
//     auto open_folders_node = files_manager_dialog_node->FirstChildElement("open-folders");
//     if (!open_folders_node)
//     {
//         open_folders_node = xml_brain_config_->file_->doc_->NewElement("open-folders");
//         files_manager_dialog_node->InsertEndChild(open_folders_node);
//     }

//     // remove all child nodes from open_folder_node
//     open_folders_node->DeleteChildren();

//     for (auto folder : stylus_state_.open_folders_state_)
//     {
//         std::cout << "\n folder name is " << folder.first << " and open state is " << folder.second << "\n";
//         auto folder_node = xml_brain_config_->file_->doc_->NewElement("folder");
//         auto name_node = xml_brain_config_->file_->doc_->NewElement("name");
//         name_node->SetText(folder.first.c_str());
//         folder_node->InsertEndChild(name_node);
//         open_folders_node->InsertEndChild(folder_node);
//         if (folder.second)
//         {
//             folder_node->SetAttribute("open", "true");
//         }
//         else
//         {
//             folder_node->SetAttribute("open", "false");
//         }
//     }
//     xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
// }
