#include "App.h"

#include "003-TreePreview/TreePreview.h"
#include "004-TempPreview/TempPreview.h"
#include "003-Preview/Preview.h"
#include "005-ClassesEdditor/ClassesEdditor.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/PanelDialogs/SettingsPanel.h"
#include "101-Stylus/PanelDialogs/QuickCommandsPanel.h"

App::App(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "../dbo.db")
//   stylus_(session_, appRoot() + "../xml-templates/")

{
    // class="? ??" // this is for tailwind to compile the two classes
    stylus_ = std::make_shared<Stylus>(session_, appRoot() + "../../xml-templates/");
    stylus_->setXmlBrains(stylus_);
    // stylus_->left_panel_ = root()->addChild(std::make_unique<LeftPanel>(stylus_));
    // stylus_->right_panel_ = root()->addChild(std::make_unique<RightPanel>(stylus_));
    stylus_->edditor_panel_ = root()->addChild(std::make_unique<EdditorPanel>(stylus_));
    stylus_->settings_panel_ = root()->addChild(std::make_unique<SettingsPanel>(stylus_));
    stylus_->quick_commands_panel_ = root()->addChild(std::make_unique<QuickCommandsPanel>(stylus_));

    // stylus_->left_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.left_active_);
    // stylus_->right_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.right_active_);
    stylus_->edditor_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.edditor_active_);
    stylus_->settings_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.settings_active_);
    stylus_->quick_commands_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.quick_commands_active_);

    // stylus_->tailwind_config_ = new TailwindConfig(stylus_);
    // stylus_->tailwind_config_->readConfigurationXMLs();

    setTitle("Starter App");

    // messageResourceBundle().use("../xml-templates/app/test");
    // messageResourceBundle().use("../xml-templates/default/app");
    // messageResourceBundle().use("../xml-templates/default/strings");
    // messageResourceBundle().use("../xml-templates/app/inputs");
    // messageResourceBundle().use("../xml-templates/app/calendar");
    messageResourceBundle().use(appRoot() + "../../xml-templates/stylus/stylus-flex-and-grid-svgs");

    // messageResourceBundle().use("../xml-templates/overide-wt/auth_test");
    // messageResourceBundle().use("../xml-templates/default/auth");
    // messageResourceBundle().use("../xml-templates/default/auth_strings");

    // CSS
    require("https://cdn.tailwindcss.com");

    useStyleSheet("static/css/tailwind-out.css");
    useStyleSheet("static/css/questionmark.css");

    // JSs
    require(docRoot() + "/static/js/utils.js");

    root()->setStyleClass("flex !max-w-[100vw] m-0 p-0 flex");
    // auto treePreview = root()->addWidget(std::make_unique<TreePreview>(stylus_));
    // auto tempPreview = root()->addWidget(std::make_unique<TempPreview>(stylus_));
    auto tempPreview_new = root()->addWidget(std::make_unique<Preview>(stylus_));
    auto classesEdditor = root()->addWidget(std::make_unique<ClassesEdditor>(stylus_));

    // tempPreview->setXmlBrain(stylus_->xml_brains_["app-cv.ui"]);
    dbo::Transaction transaction(session_);

    auto main_preview = session_.find<PreviewDisplaySelected>().where("preview_panel=?").bind(PreviewPanel::Main).resultValue();
    if (main_preview->xml_template)
    {
        auto selected_template = main_preview->xml_template;
        auto main_display_xml_brain = stylus_->xml_brains_[selected_template->temp_id.toUTF8()];
        tempPreview_new->setXmlBrain(main_display_xml_brain);
        stylus_->xml_brain_ = main_display_xml_brain;
    }

    transaction.commit();

    globalKeyWentDown().connect([=](Wt::WKeyEvent e)
                                { processKeyEvent(e); });
}

void App::processKeyEvent(Wt::WKeyEvent e)
{
    std::cout << "\n\n processKeyEvent: \n\n";

    if (e.modifiers().test(Wt::KeyboardModifier::Alt))
    {
        std::cout << "\n\n Alt key is pressed \n\n";
        if (e.key() == Wt::Key::Key_1)
        {
            std::cout << "\n\n Alt + 1 key is pressed but nothing happens \n\n";
        }
        else if (e.key() == Wt::Key::Key_3)
        {
            std::cout << "\n\n Alt + 3 key is pressed but nothing happens \n\n";
        }
        else if (e.key() == Wt::Key::Key_5)
        {
            stylus_->settings_panel_->toggleQuickCommandsDialogActive();
        }
        else if (e.key() == Wt::Key::Key_7)
        {
            stylus_->settings_panel_->toggleEdditorDialogActive();
        }
        else if (e.key() == Wt::Key::Key_9)
        {
            stylus_->settings_panel_->toggleSettingsDialogActive();
        }

        else if (e.key() == Wt::Key::Left)
        {
            if (!stylus_->xml_brain_->selected_node_)
                return;
            if (stylus_->xml_brain_->selected_node_ == stylus_->xml_brain_->message_node_)
                return;
            stylus_->xml_brain_->selected_node_ = stylus_->xml_brain_->selected_node_->Parent();
            stylus_->setXmlBrain(stylus_->xml_brain_);
        }
        else if (e.key() == Wt::Key::Right)
        {
            if (!stylus_->xml_brain_->selected_node_)
                return;
            if (!stylus_->xml_brain_->selected_node_->FirstChild())
                return;
            stylus_->xml_brain_->selected_node_ = stylus_->xml_brain_->selected_node_->FirstChild();
            stylus_->setXmlBrain(stylus_->xml_brain_);
        }
        else if (e.key() == Wt::Key::Down)
        {
            if (!stylus_->xml_brain_->selected_node_)
                return;
            if (!stylus_->xml_brain_->selected_node_->NextSibling())
                return;
            stylus_->xml_brain_->selected_node_ = stylus_->xml_brain_->selected_node_->NextSibling();
            stylus_->setXmlBrain(stylus_->xml_brain_);
        }
        else if (e.key() == Wt::Key::Up)
        {
            if (!stylus_->xml_brain_->selected_node_)
                return;
            if (!stylus_->xml_brain_->selected_node_->PreviousSibling())
                return;
            stylus_->xml_brain_->selected_node_ = stylus_->xml_brain_->selected_node_->PreviousSibling();
            stylus_->setXmlBrain(stylus_->xml_brain_);
        }
        else if (e.key() == Wt::Key::C)
        {
            stylus_->settings_panel_->copyNode(stylus_->xml_brain_, stylus_->xml_brain_->selected_node_);
        }
        else if (e.key() == Wt::Key::V)
        {
            stylus_->settings_panel_->pasteNode(stylus_->xml_brain_, stylus_->xml_brain_->selected_node_);
        }
    }
    else if (e.modifiers().test(Wt::KeyboardModifier::Shift))
    {
        if (!stylus_->xml_brain_->selected_node_)
            return;

        if (e.key() == Wt::Key::Up)
        {
            if (!stylus_->xml_brain_->selected_node_->ToElement())
                return;
            if (stylus_->xml_brain_->selected_node_->PreviousSibling())
            {
                auto prev = stylus_->xml_brain_->selected_node_->PreviousSibling();
                if (prev->PreviousSibling())
                {
                    stylus_->xml_brain_->selected_node_->Parent()->InsertAfterChild(prev->PreviousSibling(), stylus_->xml_brain_->selected_node_);
                }
                else
                {
                    stylus_->xml_brain_->selected_node_->Parent()->InsertFirstChild(stylus_->xml_brain_->selected_node_);
                }
            }
            else if (stylus_->xml_brain_->selected_node_->NextSibling())
            {
                stylus_->xml_brain_->selected_node_->Parent()->InsertEndChild(stylus_->xml_brain_->selected_node_);
            }
            stylus_->setXmlBrain(stylus_->xml_brain_);
            stylus_->xml_brain_->saveXmlToDbo();
        }
        else if (e.key() == Wt::Key::Down)
        {
            if (!stylus_->xml_brain_->selected_node_->ToElement())
                return;
            if (stylus_->xml_brain_->selected_node_->NextSibling())
            {
                auto next = stylus_->xml_brain_->selected_node_->NextSibling();
                stylus_->xml_brain_->selected_node_->Parent()->InsertAfterChild(next, stylus_->xml_brain_->selected_node_);
            }
            else if (stylus_->xml_brain_->selected_node_->PreviousSibling())
            {
                stylus_->xml_brain_->selected_node_->Parent()->InsertFirstChild(stylus_->xml_brain_->selected_node_);
            }
            stylus_->setXmlBrain(stylus_->xml_brain_);
            stylus_->xml_brain_->saveXmlToDbo();
        }
        else if (e.key() == Wt::Key::Left)
        {
            if (!stylus_->xml_brain_->selected_node_->ToElement() ||
                !stylus_->xml_brain_->selected_node_->Parent() ||
                stylus_->xml_brain_->selected_node_->Parent() == stylus_->xml_brain_->message_node_)
                return;

            auto parent = stylus_->xml_brain_->selected_node_->Parent();
            auto grand_parent = parent->Parent();
            if (parent->PreviousSibling())
            {
                grand_parent->InsertAfterChild(parent->PreviousSibling(), stylus_->xml_brain_->selected_node_);
            }
            else
            {
                grand_parent->InsertFirstChild(stylus_->xml_brain_->selected_node_);
            }
            stylus_->setXmlBrain(stylus_->xml_brain_);
            stylus_->xml_brain_->saveXmlToDbo();
        }
        else if (e.key() == Wt::Key::Right)
        {

            if (!stylus_->xml_brain_->selected_node_->ToElement() ||
                !stylus_->xml_brain_->selected_node_->NextSiblingElement() ||
                (stylus_->xml_brain_->selected_node_->NextSiblingElement()->FirstChild() && stylus_->xml_brain_->selected_node_->NextSiblingElement()->FirstChild()->ToText()))
                return;

            auto selected_node = stylus_->xml_brain_->selected_node_;
            auto next_sibling = selected_node->NextSiblingElement();
            stylus_->xml_brain_->selected_node_ = next_sibling->InsertFirstChild(selected_node);
            stylus_->xml_brain_->saveXmlToDbo();
            stylus_->setXmlBrain(stylus_->xml_brain_);
        }
        else if (e.key() == Wt::Key::Delete)
        {
            if (stylus_->xml_brain_->selected_node_ == stylus_->xml_brain_->message_node_)
                return;
            auto parent = stylus_->xml_brain_->selected_node_->Parent();
            auto prev_sibling = stylus_->xml_brain_->selected_node_->PreviousSibling();
            auto next_sibling = stylus_->xml_brain_->selected_node_->NextSibling();
            parent->DeleteChild(stylus_->xml_brain_->selected_node_);
            if (prev_sibling)
                stylus_->xml_brain_->selected_node_ = prev_sibling;
            else if (next_sibling)
                stylus_->xml_brain_->selected_node_ = next_sibling;
            else
                stylus_->xml_brain_->selected_node_ = parent;

            stylus_->setXmlBrain(stylus_->xml_brain_);
            stylus_->xml_brain_->saveXmlToDbo();
        }
        else if (e.key() == Wt::Key::Enter)
        {
            std::cout << "\n\n deleted \n\n";

            if (stylus_->xml_brain_->selected_node_->ToText())
            {
                std::cout << "\n\n selected node is text \n\n";
                return;
            }
            else if (stylus_->xml_brain_->selected_node_->ToElement()->FirstChild() && stylus_->xml_brain_->selected_node_->ToElement()->FirstChild()->ToText())
            {
                std::cout << "\n\n selected node is element but it has a first child text \n\n";
                return;
            }
            std::cout << "\n\n deleted \n\n";

            auto new_child = stylus_->xml_brain_->xml_doc_->NewElement("div");
            new_child->SetAttribute("class", "bg-gray-700 p-12");
            stylus_->xml_brain_->selected_node_->ToElement()->InsertFirstChild(new_child);
            stylus_->xml_brain_->saveXmlToDbo();
            stylus_->setXmlBrain(stylus_->xml_brain_);
        }
    }
}