#include <Wt/WText>

#include "RecordesWidget.h"

using namespace Wt;

RecordesWidget::RecordesWidget(Wt::WContainerWidget *parent)
:WContainerWidget(parent){
  showUI();
}

RecordesWidget::RecordesWidget()
:WContainerWidget(){
  showUI();
}

RecordesWidget::~RecordesWidget() {
}

void RecordesWidget::showUI() {
    clear();
    auto cont = new Wt::WContainerWidget(this);
    cont->setMargin(WLength(20), Wt::Left);
    cont->setMargin(WLength(20), Wt::Right);

    new WText("Recordes", cont);
}

