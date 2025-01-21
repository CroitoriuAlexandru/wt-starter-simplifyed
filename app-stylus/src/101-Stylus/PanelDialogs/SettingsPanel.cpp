#include "101-Stylus/PanelDialogs/SettingsPanel.h"
#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/PanelDialogs/QuickCommandsPanel.h"

#include "101-Stylus/Stylus.h"

#include <002-Dbo/Session.h>

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

    auto header_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto left_right_panels_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto rest_of_panels_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    header_wrapper->setStyleClass("flex items-center border-solid border-b border-gray-600");
    left_right_panels_wrapper->setStyleClass("flex w-full");
    rest_of_panels_wrapper->setStyleClass("flex w-full");

    readStateFromXmlFile();

    createHeaderButtons(header_wrapper);
    createLeftPanelSettings(left_right_panels_wrapper);
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

void SettingsPanel::createHeaderButtons(Wt::WContainerWidget *wrapper)
{
    auto add_temps_to_dbo_btn = wrapper->addWidget(std::make_unique<Wt::WPushButton>("Add Temps"));
    add_temps_to_dbo_btn->clicked().connect([=]()
                                            {
                                                stylus_->addFileToDbo("app-cv", "../base-templates/app-cv/ui.xml");
                                                stylus_->addFileToDbo("app-cv", "../base-templates/app-cv/texts-en.xml");
                                                stylus_->addFileToDbo("app-cv", "../base-templates/app-cv/svg.xml");

                                                stylus_->addFileToDbo("default", "../base-templates/default/texts-en.xml");
                                                stylus_->addFileToDbo("default", "../base-templates/default/ui.xml");

                                                stylus_->addFileToDbo("test", "../base-templates/test/test-1.xml");
                                                stylus_->addFileToDbo("test", "../base-templates/test/test-2.xml");

                                                auto transaction = Dbo::Transaction(stylus_->session_);

                                                auto main_preview = stylus_->session_.find<PreviewDisplaySelected>().where("preview_panel=?").bind(PreviewPanel::Main).resultValue();
                                                auto selected_template = stylus_->session_.find<XmlTemplate>().where("temp_id=?").bind("app-cv.ui").resultValue();
                                                main_preview.modify()->xml_template = selected_template;

                                                transaction.commit();

                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/stylus-flex-and-grid-svgs.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-accesibility.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-backgrounds.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-borders.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-effects.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-filters.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-flex-and-grid.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-interactivity.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-Layout.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-sizing.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-spacing.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-svg.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-tables.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-transform.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-transition-and-animation.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-typography.xml");
                                                // stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-variants.xml");
                                            });
    auto get_temps_from_dbo_btn = wrapper->addWidget(std::make_unique<Wt::WPushButton>("Get Temps"));
    get_temps_from_dbo_btn->clicked().connect([=]()
                                              {
                                                  stylus_->saveFileFromDbo("app-cv", "texts-en.xml");
                                                  stylus_->saveFileFromDbo("app-cv", "ui.xml");
                                                  stylus_->saveFileFromDbo("app-cv", "svg.xml");

                                                  stylus_->saveFileFromDbo("default", "texts-en.xml");
                                                  stylus_->saveFileFromDbo("default", "ui.xml");

                                                  stylus_->saveFileFromDbo("test", "test-1.xml");
                                                  stylus_->saveFileFromDbo("test", "test-2.xml");

                                                  // stylus_->saveFileFromDbo("stylus", "stylus-flex-and-grid-svgs.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-accesibility.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-backgrounds.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-borders.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-effects.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-filters.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-flex-and-grid.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-interactivity.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-Layout.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-sizing.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-spacing.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-svg.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-tables.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-transform.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-transition-and-animation.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-typography.xml");
                                                  // stylus_->saveFileFromDbo("stylus", "tconf-variants.xml");
                                              });
    auto delete_temps_from_dbo_btn = wrapper->addWidget(std::make_unique<Wt::WPushButton>("Delete Temps"));
    delete_temps_from_dbo_btn->clicked().connect(this, [=]()
                                                 {
        auto transaction = Dbo::Transaction(stylus_->session_);

        auto folders = stylus_->session_.find<TemplateFolder>().resultList();
        for (auto &folder : folders)
        {
            auto files = folder->template_files;
            for (auto &file : files)
            {
                auto templates = file->xml_templates;
                for (auto &temp : templates)
                {
                    temp.remove();
                }
                file.remove();
            }
            folder.remove();
        }

        transaction.commit(); });
    add_temps_to_dbo_btn->setStyleClass("btn-style-1 !p-0.5 mr-3");
    get_temps_from_dbo_btn->setStyleClass("btn-style-1 !p-0.5 mr-3");
    delete_temps_from_dbo_btn->setStyleClass("btn-style-1 !p-0.5");
}

void SettingsPanel::createLeftPanelSettings(Wt::WContainerWidget *wrapper)
{
    auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 min-w-32 h-fit bg-gray-800 rounded-md");
    auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
    auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    content->setStyleClass("p-2");
    header->addWidget(std::make_unique<Wt::WText>("Left Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

    left_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("Tgg Vis"));
    left_toggler_->setStyleClass(radio_checkbox_btn_styles_);
}
void SettingsPanel::createEdditorPanelSettings(Wt::WContainerWidget *wrapper)
{
    auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 min-w-32 h-fit bg-gray-800 rounded-md");
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
    panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 min-w-32 h-fit bg-gray-800 rounded-md");
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
    stylus_state_.settings_xml_doc_ = new tinyxml2::XMLDocument();
    stylus_state_.settings_xml_doc_->LoadFile(xml_file_path);
    // get or set messages node
    auto messages_node = stylus_state_.settings_xml_doc_->FirstChildElement("messages");
    if (!messages_node)
    {
        messages_node = stylus_state_.settings_xml_doc_->NewElement("messages");
        stylus_state_.settings_xml_doc_->InsertFirstChild(messages_node);
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    // get or set message node
    auto message_node = messages_node->FirstChildElement("message");
    if (!message_node)
    {
        message_node = stylus_state_.settings_xml_doc_->NewElement("message");
        messages_node->InsertEndChild(message_node);
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    // Set message id attribute
    if (!message_node->Attribute("id"))
    {
        message_node->SetAttribute("id", "stylus.config");
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    else if (std::string(message_node->Attribute("id")).compare("stylus.config") != 0)
    {
        message_node->SetAttribute("id", "stylus.config");
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    // get or set left panel node

    stylus_state_.edditor_xml_node_ = message_node->FirstChildElement("edditorPanel");
    if (!stylus_state_.edditor_xml_node_)
    {
        stylus_state_.edditor_xml_node_ = stylus_state_.settings_xml_doc_->NewElement("edditorPanel");
        stylus_state_.edditor_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(stylus_state_.edditor_xml_node_);

        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(stylus_state_.edditor_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.edditor_active_ = true;
        }
        else
        {
            stylus_state_.edditor_active_ = false;
        }
    }
    // get or set quick commands panel node
    stylus_state_.quick_commands_xml_node_ = message_node->FirstChildElement("quickCommandsPanel");
    if (!stylus_state_.quick_commands_xml_node_)
    {
        stylus_state_.quick_commands_xml_node_ = stylus_state_.settings_xml_doc_->NewElement("quickCommandsPanel");
        stylus_state_.quick_commands_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(stylus_state_.quick_commands_xml_node_);
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(stylus_state_.quick_commands_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.quick_commands_active_ = true;
        }
        else
        {
            stylus_state_.quick_commands_active_ = false;
        }
    }
    // get or set settings panel node
    stylus_state_.settings_xml_node_ = message_node->FirstChildElement("settingsPanel");
    if (!stylus_state_.settings_xml_node_)
    {
        stylus_state_.settings_xml_node_ = stylus_state_.settings_xml_doc_->NewElement("settingsPanel");
        stylus_state_.settings_xml_node_->SetAttribute("active", "false");
        message_node->InsertEndChild(stylus_state_.settings_xml_node_);
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
    else
    {
        if (std::string(stylus_state_.settings_xml_node_->Attribute("active")).compare("true") == 0)
        {
            stylus_state_.settings_active_ = true;
        }
        else
        {
            stylus_state_.settings_active_ = false;
        }
    }

    stylus_state_.copy_node_ = message_node->FirstChildElement("copyNode");
    if (!stylus_state_.copy_node_)
    {
        stylus_state_.copy_node_ = stylus_state_.settings_xml_doc_->NewElement("copyNode");
        message_node->InsertEndChild(stylus_state_.copy_node_);
        stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
    }
}

void SettingsPanel::toggleQuickCommandsDialogActive()
{
    std::cout << "\n\n quick commands dialog \n\n";
    stylus_state_.quick_commands_active_ = !stylus_state_.quick_commands_active_;
    quick_commands_toggler_->setChecked(stylus_state_.quick_commands_active_);
    stylus_->quick_commands_panel_->setHidden(!stylus_state_.quick_commands_active_);
    stylus_state_.quick_commands_xml_node_->SetAttribute("active", stylus_state_.quick_commands_active_ ? "true" : "false");
    stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::toggleEdditorDialogActive()
{
    std::cout << "\n\n toggle files manager dialog \n\n";
    stylus_state_.edditor_active_ = !stylus_state_.edditor_active_;
    edditor_toggler_->setChecked(stylus_state_.edditor_active_);
    stylus_->edditor_panel_->setHidden(!stylus_state_.edditor_active_);
    stylus_state_.edditor_xml_node_->SetAttribute("active", stylus_state_.edditor_active_ ? "true" : "false");
    stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::toggleSettingsDialogActive()
{
    std::cout << "\n\n toggle settings dialog \n\n";
    stylus_state_.settings_active_ = !stylus_state_.settings_active_;
    setHidden(!stylus_state_.settings_active_);
    stylus_state_.settings_xml_node_->SetAttribute("active", stylus_state_.settings_active_ ? "true" : "false");
    stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
}

void SettingsPanel::copyNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node)
{
    stylus_state_.copy_node_->DeleteChildren();
    auto new_node = node->DeepClone(stylus_state_.settings_xml_doc_);
    stylus_state_.copy_node_->InsertEndChild(new_node);
    stylus_state_.settings_xml_doc_->SaveFile(xml_file_path);
}
void SettingsPanel::pasteNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node)
{
    if (!stylus_state_.copy_node_)
        return;
    tinyxml2::XMLNode *new_node = nullptr;
    if (stylus_state_.copy_node_->FirstChildElement())
    {
        new_node = stylus_state_.copy_node_->FirstChildElement()->DeepClone(xml_brain->xml_doc_);
    }
    else if (stylus_state_.copy_node_->FirstChild()->ToText())
    {
        new_node = xml_brain->xml_doc_->NewText(stylus_state_.copy_node_->FirstChild()->Value());
    }
    node->InsertFirstChild(new_node);
    stylus_->setXmlBrain(xml_brain);
    xml_brain->saveXmlToDbo();
}

// stylusState_->copyNode = stylusState_->selectedElement->DeepClone(&stylusState_->doc);