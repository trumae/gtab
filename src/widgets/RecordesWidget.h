#ifndef RECORDESWIDGET_H
#define RECORDESWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WMenu>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

#include "../application.h"

class RecordesWidget : public Wt::WContainerWidget {
public:
  RecordesWidget(Wt::WContainerWidget *parent);
  RecordesWidget();
  ~RecordesWidget();

  void showUI();
};

#endif // RECORDESWIDGET_H
