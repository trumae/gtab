#include <Wt/WApplication>
#include <Wt/WText>
#include <Wt/WImage>
#include <Wt/WPanel>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WBorderLayout>
#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WDialog>
#include <Wt/WAnchor>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WValidator>
#include <Wt/WLabel>
#include <Wt/WRegExpValidator>

#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>          
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>         
#include <iostream>
#include <sstream>
#include <vector>

#include "../logic/usuario.h"
#include "../utils/utils.h"
#include "MenuWidget.h"
#include "HomeWidget.h"
#include "SomaFacilWidget.h"

using namespace Wt;

MenuWidget::MenuWidget(Wt::WContainerWidget *parent)
:WContainerWidget(parent){
  showUI();
}

MenuWidget::MenuWidget()
:WContainerWidget(){
  showUI();
}

MenuWidget::~MenuWidget() {
}

void MenuWidget::showUI() {
  GTABApplication *app = GTABApplication::Application();

  clear();

  auto cont = new Wt::WContainerWidget(this);
  cont->setMargin(WLength(20), Wt::Left);
  cont->setMargin(WLength(20), Wt::Right);

  WPushButton *btnAdicao10 = new WPushButton(cont);
  btnAdicao10->setText("Soma Facil - 10");
  btnAdicao10->addStyleClass("btn-lg");
  btnAdicao10->addStyleClass("btn-block");
  btnAdicao10->addStyleClass("btn-default");
  btnAdicao10->clicked().connect(std::bind([=]() {
      app->pergunta = 0;
      app->acertos = 0;
      app->numperguntas = 10;

      app->homeWidget()->showContents(new SomaFacilWidget());
  }));

  WPushButton *btnAdicao20 = new WPushButton(cont);
  btnAdicao20->setText("Soma Facil - 20");
  btnAdicao20->addStyleClass("btn-lg");
  btnAdicao20->addStyleClass("btn-block");
  btnAdicao20->addStyleClass("btn-default");
  btnAdicao20->clicked().connect(std::bind([=]() {
      app->pergunta = 0;
      app->acertos = 0;
      app->numperguntas = 20;

      app->homeWidget()->showContents(new SomaFacilWidget());
  }));

  WPushButton *btnAdicao50 = new WPushButton(cont);
  btnAdicao50->setText("Soma Facil - 50");
  btnAdicao50->addStyleClass("btn-lg");
  btnAdicao50->addStyleClass("btn-block");
  btnAdicao50->addStyleClass("btn-default");
  btnAdicao50->clicked().connect(std::bind([=]() {
      app->pergunta = 0;
      app->acertos = 0;
      app->numperguntas = 50;

      app->homeWidget()->showContents(new SomaFacilWidget());
  }));

}
