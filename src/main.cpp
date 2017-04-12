#include <stdlib.h>
#include <Wt/WServer>
#include <Wt/Auth/AuthService>
#include <Wt/Auth/GoogleService>
#include <Wt/WLoadingIndicator>
#include <Wt/WOverlayLoadingIndicator>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WHBoxLayout>
#include <Wt/WBootstrapTheme>
#include <Wt/WCssTheme>
#include <Wt/WPushButton>

#include "application.h"
#include "db.h"
#include "widgets/HomeWidget.h"

using namespace Wt;

WApplication *createApplication(const WEnvironment& env) {
    GTABApplication *app = new GTABApplication(env);
    app->setTitle("SMD");

    // Choice of theme: defaults to bootstrap3 but can be overridden using
    // a theme parameter (for testing)
    const std::string *themePtr = env.getParameter("theme");
    std::string theme;
    if (!themePtr)
      theme = "bootstrap3";
    else
      theme = *themePtr;
    
    if (theme == "bootstrap3") {
      Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(app);
      bootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
      bootstrapTheme->setResponsive(true);
      app->setTheme(bootstrapTheme);
      
      // load the default bootstrap3 (sub-)theme
      ///app->useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
      app->useStyleSheet("resources/themes/bootstrap/3/flatly.min.css");
      app->useStyleSheet("resources/themes/bootstrap/3/app.css");
    } else if (theme == "bootstrap2") {
      Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(app);
      bootstrapTheme->setResponsive(true);
      app->setTheme(bootstrapTheme);
    } else
      app->setTheme(new Wt::WCssTheme(theme));
   
    app->setHomeWidget(new HomeWidget(app->root()));
    
    return app;
}

void init() {
    srand(time(0));
    setupDB();
}

int main(int argc, char **argv) {
    init();

    try {
        Wt::WServer server(argv[0]);

        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        server.addEntryPoint(Wt::Application, createApplication);

        if(server.start()) {
            Wt::WServer::waitForShutdown();
            server.stop();
        }
    } catch(Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
    } catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}



