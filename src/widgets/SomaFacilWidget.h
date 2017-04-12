#ifndef SOMAFACILWIDGET_H
#define SOMAFACILWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WMenu>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

#include "../application.h"

class SomaFacilWidget : public Wt::WContainerWidget {
public:
  SomaFacilWidget(Wt::WContainerWidget *parent);
  SomaFacilWidget();
  ~SomaFacilWidget();

  void showUI();
private:
  void putMenuButton();
};

#endif // SOMAFACILWIDGET_H
