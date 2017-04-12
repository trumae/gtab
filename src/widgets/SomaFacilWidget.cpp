#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WLineEdit>
#include <Wt/WPanel>
#include <Wt/WMessageBox>

#include <random>
#include <sstream>
#include <string>

#include "HomeWidget.h"
#include "MenuWidget.h"
#include "SomaFacilWidget.h"

using namespace Wt;

SomaFacilWidget::SomaFacilWidget(Wt::WContainerWidget *parent)
:WContainerWidget(parent){
  showUI();
}

SomaFacilWidget::SomaFacilWidget()
:WContainerWidget(){
  showUI();
}

SomaFacilWidget::~SomaFacilWidget() {
}

void SomaFacilWidget::showUI() {
    GTABApplication *app = GTABApplication::Application();
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 9);

    int num1 = uniform_dist(e1);
    int num2 = uniform_dist(e1);

    clear();
    auto cont = new Wt::WContainerWidget(this);
    cont->setWidth(WLength(360));
    cont->setMargin(WLength::Auto, Wt::All);

    Wt::WPanel *panel = new Wt::WPanel(cont);
    panel->setTitle("Placar");
    std::stringstream ss;
    ss << "Acertos:" << app->acertos << " pergunta: " << app->pergunta + 1 << "/" << app->numperguntas;
    panel->setCentralWidget(new Wt::WText(ss.str()));

    WLineEdit *res = new WLineEdit();
    res->setHeight(WLength(80));
    res->decorationStyle().font().setSize(WLength(60));
    res->setFocus(true);

    WPushButton *btnok = new WPushButton();
    btnok->setText("Ok");
    btnok->addStyleClass("btn-lg");
    btnok->addStyleClass("btn-block");

    WTemplate *tmpl = new WTemplate(cont);
    tmpl->setTemplateText(
                "<div class='row'>"
                "  <div class='col-md-2' style='font-size: 60px;'>${num1}</div>"
                "  <div class='col-md-1' style='font-size: 60px;'>+</div>"
                "  <div class='col-md-2' style='font-size: 60px;'>${num2}</div>"
                "  <div class='col-md-1' style='font-size: 60px;'>=</div>"
                "  <div class='col-md-6' style='font-size: 60px;'>${res}</div>"
                "</div>"
                "${btnok}"
                ,XHTMLUnsafeText);
    tmpl->bindWidget("res", res);
    tmpl->bindWidget("btnok", btnok);
    tmpl->bindInt("num1", num1);
    tmpl->bindInt("num2", num2);

    auto func = [=](){
        int soma = num1 + num2;

        std::string sres = res->text().toUTF8();
        if (sres.empty()) return;

        int rsoma = std::stoi(sres);
        if (rsoma == soma) {
            app->acertos ++;
            app->pergunta ++;
        } else {
            app->pergunta ++;
            std::stringstream ss;
            ss << num1 << "+" << num2 << "=" << soma;
            Wt::WMessageBox::show("Voce errou!!",
                              "<p>" + ss.str() + "</p>",
                              Wt::Ok);
        }

        if (app->pergunta < app->numperguntas) {
            app->homeWidget()->showContents(new SomaFacilWidget());
        } else {
            //mostra so resultado
            std::stringstream ss;
            ss << "FIM !! Acertos: " << app->acertos << " em " << app->numperguntas;
            panel->setCentralWidget(new Wt::WText(ss.str()));
            tmpl->hide();
        }
    };

    res->enterPressed().connect(std::bind(func));
    btnok->clicked().connect(std::bind(func));



    putMenuButton();
}

void SomaFacilWidget::putMenuButton() {
   GTABApplication *app = GTABApplication::Application();

   auto btn = new WPushButton("<i class='glyphicon glyphicon-align-justify'>", XHTMLUnsafeText, this);
   btn->addStyleClass("btn-circle");
   btn->addStyleClass("btn-xl");
   btn->addStyleClass("btn-primary");
   btn->addStyleClass("fixed-action-btn");
   btn->clicked().connect(std::bind([=](){
      app->homeWidget()->showContents(new MenuWidget());
   }));
}
