#pragma once
#include <Wt/Auth/Login.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/WString.h>

#include "101-Stylus/Tables.h"

using namespace Wt;

namespace dbo = Wt::Dbo;

class Session : public dbo::Session
{
public:
    explicit Session(const std::string &sqliteDb);

private:
    void createInitialData();
};