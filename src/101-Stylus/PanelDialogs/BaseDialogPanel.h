#pragma once
#include <Wt/WDialog.h>
// #include "200-Stylus/StylusBrain.h"

class Stylus;

class BaseDialogPanel : public Wt::WDialog
{
public:
    BaseDialogPanel(Stylus *stylus_);
    Stylus *stylus_;

private:
};