#include "101-Stylus/PanelDialogs/QuickCommandsPanel.h"
#include "101-Stylus/Stylus.h"

#include <Wt/WApplication.h>

QuickCommandsPanel::QuickCommandsPanel(std::shared_ptr<Stylus> stylus)
    : BaseDialogPanel(stylus)
{
    // addStyleClass("rounded-md z-[999999]");
    titleBar()->addStyleClass("!text-black rounded-t-md");
    contents()->addStyleClass("flex items-stretch !text-black rounded-b-md");
    setOffsets(300, Wt::Side::Bottom);
    setOffsets(Wt::WLength(40, Wt::LengthUnit::Percentage), Wt::Side::Left | Wt::Side::Right);
    // setOffsets(580, Wt::Side::Right | Wt::Side::Left);

    line_eddit_ = contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    line_eddit_->setPlaceholderText("Enter command here");
    line_eddit_->setStyleClass("min-w-fit border text-md rounded-md block w-full p-2.5 focus:ring-green-500 focus:border-green-500");

    line_eddit_->keyWentDown().connect(this, [=](Wt::WKeyEvent e)
                                       { Wt::WApplication::instance()->globalKeyWentDown().emit(e); });
    // stylus_brain_->m_signal_node_selected_.connect(this, [=](std::shared_ptr<XMLBrain> xml_brain)
    //    { line_eddit_->setText(""); });
}
