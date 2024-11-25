#include "./001-App/App.h"
#include <Wt/WServer.h>

int main(int argc, char **argv)
{
    // ! easy way to run the app
    // return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
    //   return std::make_unique<App>(env);
    // });
    // for (int i = 0; i < argc; i++)
    // {
    //     std::cout << "\nArg: " << argv[i] << std::endl;
    // }
    try
    {

        Wt::WServer server(argv[0]);

        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        server.addEntryPoint(
            Wt::EntryPointType::Application,
            [=](const Wt::WEnvironment &env)
            {
                return std::make_unique<App>(env);
            },
            "/");

        server.run();
    }
    catch (Wt::WServer::Exception &e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (std::exception &e)
    {
        std::cerr << "exception: " << e.what() << "\n";
        return 1;
    }
}
