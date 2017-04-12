#ifndef __HOME_WIDGET__
#define __HOME_WIDGET__

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WMenu>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

#include "../application.h"

class HomeWidget : public Wt::WContainerWidget {
public:
  HomeWidget(Wt::WContainerWidget *parent);
  ~HomeWidget();
  
  void viewHome();
  void showContents(Wt::WContainerWidget *w);

 private:
  Wt::WContainerWidget *workArea_;
  Wt::WContainerWidget *contents_;
  Wt::WNavigationBar *navigation_;
  
  void createUI();
  void loginUI();
  void registerUI();
  void forgotPassUI();
  void logout();
  void dadosContaUsuario();
  void googleAnalyticsLogger(std::string url);  
  void showListas();
  void showRecordes();
};


#endif
