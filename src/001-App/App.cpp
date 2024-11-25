#include "App.h"
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include "003-TreePreview/TreePreview.h"
#include "004-TempPreview/TempPreview.h"

App::App(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "../dbo.db")
//   stylus_(session_, appRoot() + "../xml-templates/")

{
    stylus_ = std::make_shared<Stylus>(session_, appRoot() + "../xml-templates/");
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

    root()->setStyleClass("flex");
    auto treePreview = root()->addWidget(std::make_unique<TreePreview>(stylus_));
    auto tempPreview = root()->addWidget(std::make_unique<TempPreview>(stylus_));
}
