#include "App.h"

#include "003-TreePreview/TreePreview.h"
#include "004-TempPreview/TempPreview.h"
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
    stylus_ = std::make_shared<Stylus>(session_, appRoot() + "../xml-templates/");

    // stylus_->left_panel_ = root()->addChild(std::make_unique<LeftPanel>(stylus_));
    // stylus_->right_panel_ = root()->addChild(std::make_unique<RightPanel>(stylus_));
    stylus_->edditor_panel_ = root()->addChild(std::make_unique<EdditorPanel>(stylus_));
    stylus_->settings_panel_ = root()->addChild(std::make_unique<SettingsPanel>(stylus_));
    // stylus_->quick_commands_panel_ = root()->addChild(std::make_unique<QuickCommandsPanel>(stylus_));

    // stylus_->left_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.left_active_);
    // stylus_->right_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.right_active_);
    stylus_->edditor_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.edditor_active_);
    stylus_->settings_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.settings_active_);
    // stylus_->quick_commands_panel_->setHidden(!stylus_->settings_panel_->stylus_state_.quick_commands_active_);

    // stylus_->tailwind_config_ = new TailwindConfig(stylus_);
    // stylus_->tailwind_config_->readConfigurationXMLs();

    setTitle("Starter App");

    // messageResourceBundle().use("../xml-templates/app/test");
    // messageResourceBundle().use("../xml-templates/default/app");
    // messageResourceBundle().use("../xml-templates/default/strings");
    // messageResourceBundle().use("../xml-templates/app/inputs");
    // messageResourceBundle().use("../xml-templates/app/calendar");
    messageResourceBundle().use("../xml-templates/stylus/stylus-flex-and-grid-svgs");

    // messageResourceBundle().use("../xml-templates/overide-wt/auth_test");
    // messageResourceBundle().use("../xml-templates/default/auth");
    // messageResourceBundle().use("../xml-templates/default/auth_strings");

    // CSS
    require("https://cdn.tailwindcss.com");

    useStyleSheet("static/css/tailwind-out.css");
    // JSs
    require(docRoot() + "/static/js/utils.js");

    root()->setStyleClass("flex !max-w-[100vw] m-0 p-0");
    auto treePreview = root()->addWidget(std::make_unique<TreePreview>(stylus_));
    auto tempPreview = root()->addWidget(std::make_unique<TempPreview>(stylus_));
    auto classesEdditor = root()->addWidget(std::make_unique<ClassesEdditor>(stylus_));
}
