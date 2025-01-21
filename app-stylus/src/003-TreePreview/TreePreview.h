#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTextArea.h>

class Stylus;
class XMLBrain;

class TreePreview : public Wt::WContainerWidget
{
public:
    TreePreview(std::shared_ptr<Stylus> stylus);

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain = nullptr);

    Wt::WContainerWidget *preview_wrapper_;

private:
    std::shared_ptr<XMLBrain> xml_brain_;
    std::shared_ptr<Stylus> stylus_;
    Wt::WTextArea *text_area_;
};