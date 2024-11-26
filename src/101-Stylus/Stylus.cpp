#include "101-Stylus/Stylus.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/PanelDialogs/SettingsPanel.h"
#include "101-Stylus/PanelDialogs/QuickCommandsPanel.h"

#include <Wt/WApplication.h>

Stylus::Stylus(Session &session, Wt::WString templates_root_path)
    : session_(session),
      templates_root_path_(templates_root_path)
{

    // left_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<LeftPanel>(this));
    // right_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<RightPanel>(this));
    // edditor_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<EdditorPanel>(this));
    // settings_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<SettingsPanel>(this));
    // quick_commands_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<QuickCommandsPanel>(this));

    // left_panel_->setHidden(!settings_panel_->stylus_state_.left_active_);
    // right_panel_->setHidden(!settings_panel_->stylus_state_.right_active_);
    // edditor_panel_->setHidden(!settings_panel_->stylus_state_.edditor_active_);
    // settings_panel_->setHidden(!settings_panel_->stylus_state_.settings_active_);
    // quick_commands_panel_->setHidden(!settings_panel_->stylus_state_.quick_commands_active_);

    Wt::WApplication::instance()->globalKeyWentDown().connect([=](Wt::WKeyEvent e)
                                                              { std::cout << "\n\n process from stylus brain \n\n"; processKeyEvent(e); });
}

void Stylus::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    std::cout << "\n\n setXmlBrain \n\n";

    xml_brain_ = xml_brain;
    // left_panel_->setXmlBrain(xml_brain_);
    // right_panel_->setXmlBrain(xml_brain_);
    // xml_brain_->selected_node_->node_selected().emit(true);
    node_selected_.emit(xml_brain);
}

void Stylus::addFileToDbo(Wt::WString folder_name, Wt::WString file_path)
{
    file_path = templates_root_path_ + file_path;
    Wt::WString file_name = file_path.toUTF8().substr(file_path.toUTF8().find_last_of("/") + 1, file_path.toUTF8().length());

    auto transaction = Dbo::Transaction(session_);

    // find app id by app name
    auto template_folder = session_.find<TemplateFolder>().where("folder_name = ?").bind(folder_name).resultValue();
    if (!template_folder)
    {
        std::cerr << "\n Error: No app found with the name: " << folder_name << "\n";
        template_folder = session_.add(std::make_unique<TemplateFolder>());
        template_folder.modify()->folder_name = folder_name;
    }

    tinyxml2::XMLDocument doc;
    doc.LoadFile(file_path.toUTF8().c_str());
    // std::cout << "\n\n file_path: " << file_path.toUTF8() << "\n\n";
    tinyxml2::XMLElement *messages = doc.FirstChildElement("messages");
    if (!messages)
    {
        std::cerr << "\n Error: No 'messages' element found in the xml file.\n";
        return;
    }

    // create the templateFile reccord
    auto template_file = std::make_unique<TemplateFile>();
    template_file->file_name = file_name;
    template_file->template_folder = template_folder;
    auto template_file_ptr = session_.add(std::move(template_file));

    tinyxml2::XMLElement *message = messages->FirstChildElement("message");
    for (message; message; message = message->NextSiblingElement("message"))
    {
        std::string id = message->Attribute("id");
        Wt::WString value = "";
        for (auto node = message->FirstChild(); node; node = node->NextSibling())
        {
            tinyxml2::XMLPrinter printer;
            node->Accept(&printer);
            value += printer.CStr();
        }
        std::cout << "\n id: " << id << "\n";
        auto xml_template = std::make_unique<XmlTemplate>();
        xml_template->temp_id = id;
        xml_template->xml_temp = value;
        xml_template->template_files = template_file_ptr;
        session_.add(std::move(xml_template));
    }

    transaction.commit();
}

void Stylus::saveFileFromDbo(Wt::WString folder_name, Wt::WString file_name)
{
    auto file_path = templates_root_path_ + folder_name + "/" + file_name;
    auto destination_file_path = templates_root_path_ + folder_name + "/" + file_name;
    auto transaction = Dbo::Transaction(session_);

    // find app id by app name
    auto template_folder = session_.find<TemplateFolder>().where("folder_name = ?").bind(folder_name).resultValue();
    if (!template_folder)
    {
        std::cerr << "\n Error: No folder_name found with the name: " << folder_name << "\n";
        return;
    }

    // find the template file by app id and file path
    auto template_file = template_folder->template_files.find().where("file_name = ?").bind(file_name).resultValue();
    if (!template_file)
    {
        std::cerr << "\n Error: No template file found with the path: " << file_path << "\n";
        return;
    }

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode *messages = doc.NewElement("messages");
    doc.InsertFirstChild(messages);

    for (auto xml_template : template_file->xml_templates)
    {
        // std::cout << "\n " << xml_template->xml_temp.toUTF8().c_str() << "\n";
        auto message = messages->InsertEndChild(doc.NewElement("message"));
        message->ToElement()->SetAttribute("dbo_id", std::to_string(xml_template.id()).c_str());
        message->ToElement()->SetAttribute("id", xml_template->temp_id.toUTF8().c_str());
        tinyxml2::XMLDocument temp_doc;
        temp_doc.Parse(xml_template->xml_temp.toUTF8().c_str());
        auto child = temp_doc.FirstChild();
        for (child; child; child = child->NextSibling())
        {
            if (child->ToElement())
            {
                auto new_child = child->DeepClone(&doc);
                message->InsertEndChild(new_child);
            }
            else if (child->ToText())
            {
                auto new_child = doc.NewText(child->Value());
                message->InsertEndChild(new_child);
            }
        }
    }

    doc.SaveFile(destination_file_path.toUTF8().c_str());
    std::cout << "\n file saved to: " << destination_file_path.toUTF8().c_str() << "\n";
    transaction.commit();
}

void Stylus::processKeyEvent(Wt::WKeyEvent e)
{
    std::cout << "\n\n processKeyEvent: \n\n";

    if (e.modifiers().test(Wt::KeyboardModifier::Alt))
    {
        std::cout << "\n\n Alt key is pressed \n\n";
        if (e.key() == Wt::Key::Key_1)
        {
            settings_panel_->toggleLeftDialogActive();
        }
        // else if (e.key() == Wt::Key::Key_3)
        // {
        //     settings_panel_->toggleRightDialogActive();
        // }
        else if (e.key() == Wt::Key::Key_5)
        {
            settings_panel_->toggleQuickCommandsDialogActive();
        }
        else if (e.key() == Wt::Key::Key_7)
        {
            settings_panel_->toggleEdditorDialogActive();
        }
        else if (e.key() == Wt::Key::Key_9)
        {
            settings_panel_->toggleSettingsDialogActive();
        }
    }
}