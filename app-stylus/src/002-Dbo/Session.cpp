#include "002-Dbo/Session.h"
#include "002-Dbo/Tables.h"
#include <Wt/Dbo/ptr.h>

// #include <Wt/Dbo/backend/Postgres.h>

#include <Wt/WString.h>
#include <iostream>

using namespace Wt;

Session::Session(const std::string &sqliteDb)
{
  // const char *postgres_password = std::getenv("POSTGRES_PASSWORD");
  // if (postgres_password)
  //   std::cout << "POSTGRES_PASSWORD: recived succesfuly" << std::endl;
  // else
  //   std::cout << "POSTGRES_PASSWORD is not set." << std::endl;

  // const char *vps_ip = std::getenv("VPS_IP");
  // if (vps_ip)
  //   std::cout << "VPS_IP: recived succesfuly" << std::endl;
  // else
  //   std::cout << "VPS_IP is not set." << std::endl;

  // std::string postgres_conn_str = "host=" + std::string(vps_ip) + " dbname=postgres user=postgres password=" + std::string(postgres_password);
  // auto connection = std::make_unique<Dbo::backend::Postgres>(postgres_conn_str.c_str());
  auto connection = std::make_unique<Dbo::backend::Sqlite3>(sqliteDb);
  setConnection(std::move(connection));

  mapClass<XmlTemplate>("xml_template");
  mapClass<TemplateFile>("template_file");
  mapClass<TemplateFolder>("template_folder");
  mapClass<PreviewDisplaySelected>("preview_display_selected");

  try
  {
    createTables();
    createInitialData();
    std::cerr << "Created database.\n";
  }
  catch (Wt::Dbo::Exception &e)
  {
    std::cerr << e.what() << '\n';
    std::cerr << "Using existing database\n";
  }
}

void Session::createInitialData()
{
  dbo::Transaction transaction(*this);

  // dbo::ptr<TemplateFolder> folder = add(std::make_unique<TemplateFolder>());
  // folder.modify()->folder_name = "default";
  // folder.modify()->folder_description = "Default folder for templates";

  // dbo::ptr<TemplateFile> file = add(std::make_unique<TemplateFile>());
  // file.modify()->file_name = "default";
  // file.modify()->template_folder = folder;

  // dbo::ptr<XmlTemplate> xml_template = add(std::make_unique<XmlTemplate>());
  // xml_template.modify()->temp_id = "default";
  // xml_template.modify()->xml_temp = "<xml></xml>";
  // xml_template.modify()->template_files = file;

  dbo::ptr<PreviewDisplaySelected> preview_display_selected = add(std::make_unique<PreviewDisplaySelected>());
  preview_display_selected.modify()->preview_panel = PreviewPanel::Main;

  transaction.commit();
}
