#include "App.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WTemplate.h>

#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>

App::App(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "../dbo.db")

{
    setTitle("Starter App");

    // messageResourceBundle().use("../xml-templates/app/test");
    // messageResourceBundle().use("../xml-templates/default/app");
    // messageResourceBundle().use("../xml-templates/default/strings");
    // messageResourceBundle().use("../xml-templates/app/inputs");
    // messageResourceBundle().use("../xml-templates/app/calendar");
    messageResourceBundle().use(appRoot() + "../../xml-templates/default/ui");

    // messageResourceBundle().use("../xml-templates/overide-wt/auth_test");
    // messageResourceBundle().use("../xml-templates/default/auth");
    // messageResourceBundle().use("../xml-templates/default/auth_strings");

    // CSS
    require("https://cdn.tailwindcss.com");

    useStyleSheet("static/css/tailwind-out.css");
    // JSs
    require(docRoot() + "/static/js/utils.js");

    root()->setStyleClass("flex !max-w-[100vw] m-0 p-0 flex");

    // auto test_temp = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("ui")));

    // auto card_1 = test_temp->bindWidget("block-1", std::make_unique<Wt::WTemplate>(Wt::WString::tr("test-card")));
    // auto card_2 = test_temp->bindWidget("block-2", std::make_unique<Wt::WTemplate>(Wt::WString::tr("test-card")));
    // auto card_3 = test_temp->bindWidget("block-3", std::make_unique<Wt::WTemplate>(Wt::WString::tr("test-card")));

    auto radio_group = std::make_shared<Wt::WButtonGroup>();

    auto button = root()->addWidget(std::make_unique<Wt::WRadioButton>("Radio Button 1"));
    radio_group->addButton(button);

    button = root()->addWidget(std::make_unique<Wt::WRadioButton>("Radio Button 2"));
    radio_group->addButton(button);

    button = root()->addWidget(std::make_unique<Wt::WRadioButton>("Radio Button 3"));
    radio_group->addButton(button);
}
