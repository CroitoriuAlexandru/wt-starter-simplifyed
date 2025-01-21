#include "101-Stylus/ClassChangers/SelectionBoxClassChanger.h"

SelectionBoxClassChanger::SelectionBoxClassChanger(std::vector<std::string> options_vec)
    : m_widget_group_(std::make_shared<Wt::WButtonGroup>())
{
    setStyleClass("flex flex-wrap items-center space-x-0.5");

    checkbox_important_ = addWidget(std::make_unique<Wt::WCheckBox>("!"));
    checkbox_important_->setStyleClass("text-center p-0.5 [&>input]:hidden [&>input:checked_~span]:text-red-500 [&>span]:px-1 [&>span]:cursor-pointer [&>span]:m-0 [&>span]:py-0  rounded-md font-bold");
    checkbox_important_->clicked().connect(this, [=]()
                                           { classChanged_.emit(getValue()); });

    for (auto &option : options_vec)
    {
        auto button = addNew<Wt::WRadioButton>(option);
        button->setAttributeValue("true-value", option);
        button->setStyleClass(
            "cursor-pointer flex w-fit h-fit outline-sky-300 "
            "[&>input]:hidden "
            "[&>span]:m-px  "
            "[&>span]:bg-cover "
            "[&>span]:hover:ring-[1px] "
            "[&>span]:rounded-md "
            "[&>span]:text-xs "
            "[&>input:checked_+_span]:ring-[1px]  "
            "[&>input:checked_+_span]:bg-gray-400/70  "
            "[&>input:checked_+_span]:ring-[1px] ");
        if (option.compare("none") == 0)
        {
            // continue;
        }
        else
        {
            button->setText(Wt::WString::tr("stylus-svg-panels-" + option));
            button->setTextFormat(Wt::TextFormat::XHTML);
        }
        // [&>span]:bg-[url(resources/icons/red-cross.svg)]
        button->setToolTip(option);
        m_widget_group_->addButton(button);
    }

    m_widget_group_->checkedChanged().connect([=](Wt::WRadioButton *checked_btn)
                                              {
        // std::cout << "checked button: " << checked_btn->attributeValue("true-value") << std::endl;
		classChanged_.emit(getValue()); });

    m_widget_group_->setCheckedButton(m_widget_group_->buttons().front());
}

void SelectionBoxClassChanger::setValue(std::string className)
{
    if (className[0] == '!')
    {
        checkbox_important_->setChecked(true);
        className = className.substr(1);
    }
    for (auto &button : m_widget_group_->buttons())
    {
        if (button->attributeValue("true-value") == className)
        {
            m_widget_group_->setCheckedButton(button);
            // button->checked().emit();
            return;
        }
    }
}

std::string SelectionBoxClassChanger::getValue()
{
    std::string imp_class_value = checkbox_important_->isChecked() ? "!" : "";
    std::string class_value = m_widget_group_->checkedButton()->attributeValue("true-value").toUTF8();
    if (class_value.compare("none") == 0)
    {
        return "none";
    }
    else
    {
        return imp_class_value + class_value;
    }
}
