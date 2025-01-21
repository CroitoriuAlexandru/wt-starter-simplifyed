#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/Stylus.h"
#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "004-TempPreview/PNode.h"
#include <Wt/WDialog.h>
#include <Wt/WApplication.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>

EdditorPanel::EdditorPanel(std::shared_ptr<Stylus> stylus)
    : BaseDialogPanel(stylus)
{
    // contents()->addStyleClass("!text-black flex border-x border-solid border-gray-400");
    // titleBar()->addStyleClass("!text-black");
    // contents()->addStyleClass("bg-purple-600");
    // setOffsets(0, Wt::Side::Top | Wt::Side::Bottom | Wt::Side::Right);
    setOffsets(0, Wt::Side::Top | Wt::Side::Bottom);
    setOffsets(450, Wt::Side::Right);
    // setOffsets(380, Wt::Side::Left);
    setOffsets(0, Wt::Side::Left);

    folders_menu_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    files_menu_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    content_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());

    // files_menu_ = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    // file_content_ = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    // files_menu_->setStyleClass("flex flex-col items-start h-full p-2 overflow-y-auto min-w-fit");
    // file_content_->setStyleClass("flex flex-col items-start grow h-full p-2 overflow-y-auto");
    content_wrapper_->setStyleClass("flex flex-col items-start grow h-full p-2 overflow-y-auto");

    folders_menu_wrapper_->setStyleClass("flex items-center border-solid border-b bg-gradient-dark sticky top-0 z-[999999]");
    files_menu_wrapper_->setStyleClass("flex items-center border-solid border-b bg-gradient-dark sticky top-[37px] z-[999999]");

    content_wrapper_->setStyleClass("flex flex-col items-start h-[calc(100%-70px)] pt-4");

    createFoldersMenu();

    // add folder button
}

void EdditorPanel::createFoldersMenu()
{
    auto folder_radio_group = std::make_shared<Wt::WButtonGroup>();
    folders_menu_wrapper_->clear();

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::collection<dbo::ptr<TemplateFolder>> template_folders = stylus_->session_.find<TemplateFolder>().orderBy("id").resultList();
    for (auto folder : template_folders)
    {
        auto folder_radio_btn = folders_menu_wrapper_->addWidget(std::make_unique<Wt::WRadioButton>());
        folder_radio_group->addButton(folder_radio_btn);
        auto folder_btn = folders_menu_wrapper_->addWidget(std::make_unique<Wt::WPushButton>(folder->folder_name));

        auto folder_btn_styles = "p-1.5 px-2  "
                                 "text-sm font-bold text-gray-200 "
                                 "peer-checked/a" +
                                 folder_radio_btn->id() + "z:bg-gray-200/10 "
                                                          "peer-checked/a" +
                                 folder_radio_btn->id() + "z:font-bolder";

        folder_radio_btn->setStyleClass("hidden peer/a" + folder_radio_btn->id() + "z ");
        folder_btn->setStyleClass(folder_btn_styles);
        folder_radio_btn->checked().connect([=]
                                            {
            if (folder.id() != selected_folder_id_)
            {
                createFilesMenu(folder.id());
            } });

        folder_btn->clicked().connect([=]
                                      {
            folder_radio_btn->setChecked(true);
            folder_radio_btn->checked().emit(); });
        // folder_btn->setAttributeValue("oncontextmenu ", "event.cancelBubble = true; event.returnValue = false; return false;");
    }

    transaction.commit();

    if (folder_radio_group->buttons().size() > 0)
    {

        folder_radio_group->setCheckedButton(0);
        folder_radio_group->button(0)->setChecked(true);
        folder_radio_group->button(0)->checked().emit();
    }

    auto add_folder_btn = folders_menu_wrapper_->addWidget(std::make_unique<Wt::WPushButton>("+"));
    add_folder_btn->setStyleClass("btn-style-1 !p-0.5 inline-block");

    add_folder_btn->clicked().connect([=]
                                      {
                                          auto add_folder_dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Add Folder"));
                                          add_folder_dialog->setStyleClass("!border-0 shadow-lg rounded-xl overflow-x-visible");
                                          add_folder_dialog->titleBar()->children()[0]->removeFromParent();
                                          add_folder_dialog->titleBar()->hide();
                                          add_folder_dialog->titleBar()->setStyleClass("p-0 bg-gray-500 flex items-center overflow-x-visible h-[40px]");
                                          add_folder_dialog->contents()->setStyleClass("flex flex-col items-start p-2 h-full bg-gray-800 overflow-y-auto overflow-x-visible");

                                          int zIndex = this->zIndex() + 1;
                                          add_folder_dialog->setTabIndex(zIndex);
                                          add_folder_dialog->setModal(false);
                                          add_folder_dialog->setResizable(false);
                                          add_folder_dialog->setMovable(false);
                                          add_folder_dialog->rejectWhenEscapePressed();
                                          add_folder_dialog->show();

                                          auto label = add_folder_dialog->contents()->addWidget(std::make_unique<Wt::WLabel>("Folder name"));
                                          auto error_text = add_folder_dialog->contents()->addWidget(std::make_unique<Wt::WText>());
                                          auto input = add_folder_dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
                                          label->setStyleClass("text-gray-200");
                                          error_text->setStyleClass("text-red-500");
                                          input->setStyleClass("input-style-1");
                                          label->setBuddy(input);

                                          input->enterPressed().connect([=]()
                                                                        {
                                                                            auto transaction = Dbo::Transaction(stylus_->session_);
                                                                            auto folder_search_result = stylus_->session_.find<TemplateFolder>().where("folder_name = ?").bind(input->text()).resultValue();
                                                                            if (folder_search_result){
                                                                                error_text->setText("Folder with the same name already exists");
                                                                            }else {
                                                                                auto folder = std::make_unique<TemplateFolder>();
                                                                                folder->folder_name = input->text();
                                                                                stylus_->session_.add(std::move(folder));
                                                                                transaction.commit();
                                                                                createFoldersMenu();
                                                                                add_folder_dialog->accept();
                                                                            }
                                                                            transaction.commit();
                                                                        }); });
}

void EdditorPanel::createFilesMenu(int folder_id)
{
    if (selected_folder_id_ == folder_id)
    {
        return;
    }

    selected_folder_id_ = folder_id;
    files_menu_wrapper_->clear();

    auto file_radio_grup = std::make_shared<Wt::WButtonGroup>();
    auto transaction = Dbo::Transaction(stylus_->session_);

    dbo::collection<dbo::ptr<TemplateFile>> template_files = stylus_->session_.find<TemplateFile>().where("template_folder_id = ?").bind(std::to_string(folder_id)).orderBy("id").resultList();
    for (auto file : template_files)
    {
        auto file_radio_btn = files_menu_wrapper_->addWidget(std::make_unique<Wt::WRadioButton>());
        file_radio_grup->addButton(file_radio_btn);
        auto file_btn = files_menu_wrapper_->addWidget(std::make_unique<Wt::WPushButton>(file->file_name));

        auto file_btn_styles = "p-1.5 px-2 "
                               "bg-gray-20 "
                               "text-sm font-bold text-gray-200 "
                               "peer-checked/a" +
                               file_radio_btn->id() + "z:bg-gray-200/10 "
                                                      "peer-checked/a" +
                               file_radio_btn->id() + "z:font-semibold";

        file_radio_btn->setStyleClass("hidden peer/a" + file_radio_btn->id() + "z ");
        file_btn->setStyleClass(file_btn_styles);

        file_radio_btn->checked().connect([=]
                                          {
            if (file.id() != selected_file_id_)
            {
                createFileTemplates(file.id());
            } });

        file_btn->clicked().connect([=]
                                    {
            file_radio_btn->setChecked(true);
            file_radio_btn->checked().emit(); });
        // file_btn->setAttributeValue("oncontextmenu ", "event.cancelBubble = true; event.returnValue = false; return false;");
    }
    transaction.commit();

    if (file_radio_grup->buttons().size() > 0)
    {
        file_radio_grup->setCheckedButton(0);
        file_radio_grup->button(0)->setChecked(true);
        file_radio_grup->button(0)->checked().emit();
    }
}

void EdditorPanel::createFileTemplates(int file_id)
{
    if (selected_file_id_ == file_id)
    {
        return;
    }
    selected_file_id_ = file_id;
    auto transaction = Dbo::Transaction(stylus_->session_);

    auto file_templates = stylus_->session_.find<XmlTemplate>().where("template_file_id = ?").bind(std::to_string(file_id)).orderBy("id").resultList();

    content_wrapper_->clear();
    for (auto xml_template : file_templates)
    {
        auto temp_wrapper = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
        // auto temp = temp_wrapper->addWidget(std::make_unique<Wt::WTemplate>(xml_template->xml_temp));
        // temp->addFunction("tr", &WTemplate::Functions::tr);
        temp_wrapper->setStyleClass("relative p-2 rounded-md m-2 border border-solid border-gray-500 bg-white min-w-fill-available");
        auto temp_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(std::to_string(xml_template.id())));
        temp_id_widget->setStyleClass("bg-gray-300 p-0.5 rounded-md text-nowrap");
        auto temp_dbo_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_template->temp_id));
        temp_dbo_id_widget->setStyleClass("absolute -top-4 left-0 bg-gray-300 p-0.5 px-1 rounded-md text-nowrap cursor-pointer");

        XmlDboRecord xml_temp_obj;
        xml_temp_obj.dbo_folder_id = xml_template->template_files->template_folder.id();
        xml_temp_obj.dbo_file_id = xml_template->template_files.id();
        xml_temp_obj.dbo_temp_id = xml_template.id();
        xml_temp_obj.file_name = xml_template->template_files->file_name;
        xml_temp_obj.folder_name = xml_template->template_files->template_folder->folder_name;
        xml_temp_obj.temp_id = xml_template->temp_id;
        xml_temp_obj.xml_temp = xml_template->xml_temp;

        // temp->hide();
        std::shared_ptr<XMLBrain> xml_brain = std::make_shared<XMLBrain>(stylus_->session_, xml_temp_obj, stylus_);
        auto pElem = temp_wrapper->addWidget(std::make_unique<PNode>(xml_brain, xml_brain->message_node_, xml_brain));

        // temp_dbo_id_widget->clicked().connect([=]
        //                                       {
        //     if (temp->isHidden())
        //     {
        //         temp->show();
        //         pElem->hide();
        //     }
        //     else
        //     {
        //         temp->hide();
        //         pElem->show();
        //     } });
    }
    transaction.commit();
}