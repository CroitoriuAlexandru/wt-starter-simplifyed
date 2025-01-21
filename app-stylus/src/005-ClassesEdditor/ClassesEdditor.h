#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>

class Stylus;
class XMLBrain;

class ClassesEdditor : public Wt::WContainerWidget
{
public:
    ClassesEdditor(std::shared_ptr<Stylus> stylus);

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain = nullptr);

    Wt::WContainerWidget *classes_inputs_wrapper_;
    std::vector<std::map<std::string, Wt::WLineEdit *>> classes_inputs_;

private:
    std::shared_ptr<XMLBrain> xml_brain_;
    std::shared_ptr<Stylus> stylus_;
    void setSelectedClasses(std::string new_classes);
};