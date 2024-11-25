#pragma once
#include <Wt/WApplication.h>
#include "002-Dbo/Session.h"

class Stylus;

class App : public Wt::WApplication
{
public:
    App(const Wt::WEnvironment &env);

    Session session_;
    std::shared_ptr<Stylus> stylus_;

private:
};