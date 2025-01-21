#pragma once
#include <Wt/WDialog.h>
#include "101-Stylus/Stylus.h"

class BaseDialogPanel : public Wt::WDialog
{
public:
    BaseDialogPanel(std::shared_ptr<Stylus> stylus_);
    std::shared_ptr<Stylus> stylus_;

private:
};