#pragma once
#include <Wt/WApplication.h>
#include "002-Dbo/Session.h"
#include "101-Stylus/Stylus.h"

class App : public Wt::WApplication
{
public:
    App(const Wt::WEnvironment &env);

    Session session_;
    std::shared_ptr<Stylus> stylus_;

    void processKeyEvent(Wt::WKeyEvent e);

private:
};