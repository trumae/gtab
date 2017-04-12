#ifndef __MENU_WIDGET__
#define __MENU_WIDGET__

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WMenu>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

#include "../application.h"

class MenuWidget : public Wt::WContainerWidget {
public:
  MenuWidget(Wt::WContainerWidget *parent);
  MenuWidget();
  ~MenuWidget();
  
  void showUI();
};



#endif
