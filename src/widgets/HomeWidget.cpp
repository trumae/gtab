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
#include "HomeWidget.h"
#include "MenuWidget.h"
#include "RecordesWidget.h"

using namespace Wt;

HomeWidget::HomeWidget(Wt::WContainerWidget *parent = 0)
:WContainerWidget(parent), contents_(NULL){
  const WEnvironment& env = WApplication::instance()->environment();
  GTABApplication *app = GTABApplication::Application();

  auto cookies = env.cookies();
  if (cookies.count("gtab__") == 1) {
    std::string token = cookies["gtab__"];

    std::string email;
    long usuario_id;
    if (sessaoUsuarioValida(token, email, usuario_id)) {
      app->email = email;
      app->usuario_id = usuario_id;
      createUI();
      return;
    }
  }
  loginUI();
}

HomeWidget::~HomeWidget() {
}

void HomeWidget::showContents(Wt::WContainerWidget *w) {
	contents_->clear();
	contents_->addWidget(w);
}

void HomeWidget::createUI() {
    GTABApplication *app = GTABApplication::Application();
    clear();
    
    Wt::WContainerWidget *container = this;   
    /// Put navigation bar
    // Create a navigation bar with a link to a web page.
    Wt::WNavigationBar *navigation_ = new Wt::WNavigationBar(container);
    navigation_->setTitle("GTAB", "#");
    navigation_->setResponsive(true);

    contents_ = new Wt::WContainerWidget(container);
    contents_->addStyleClass("contents");

    // Setup a Left-aligned menu.
    Wt::WMenu *leftMenu = new Wt::WMenu(container);
    navigation_->addMenu(leftMenu);

    auto mlistas = leftMenu->addItem("Jogos", this, &HomeWidget::showListas);
    mlistas->setLink(WLink(WLink::InternalPath, "/listas"));

    auto mrecordes = leftMenu->addItem("Recordes", this, &HomeWidget::showRecordes);
    mrecordes->setLink(WLink(WLink::InternalPath, "/recordes"));
    
    // Setup a Right-aligned menu.
    Wt::WMenu *rightMenu = new Wt::WMenu();
    navigation_->addMenu(rightMenu, Wt::AlignRight);

    // Create a popup submenu for the Help menu.
    Wt::WPopupMenu *popup = new Wt::WPopupMenu();
    popup->addItem("Meus dados");
    popup->addSeparator();
    popup->addItem("Sair");
    popup->itemSelected().connect(std::bind([=] (Wt::WMenuItem *item) {
	  if (item->text() != "Sair") {
	    Wt::WMessageBox *messageBox = new Wt::WMessageBox
	      ("Sobre",
	       Wt::WString::fromUTF8("<p>Mostrando ajuda: {1}</p>").arg(item->text()),
	       Wt::Information, Wt::Ok);
	    
	    messageBox->buttonClicked().connect(std::bind([=] () {
		  delete messageBox;
		}));
	    messageBox->show();
	    return;
	  } 
	  logout();
          }, std::placeholders::_1));
    Wt::WMenuItem *item = new Wt::WMenuItem(app->email);
    item->setMenu(popup);
    rightMenu->addItem(item);

    // Add a Search control.
    ///Wt::WLineEdit *edit = new Wt::WLineEdit();
    ///edit->setEmptyText("Enter a search item");
    ///edit->enterPressed().connect(std::bind([=] () {
    ///	  leftMenu->select(2); // is the index of the "Sales"
    ///	  searchResult->setText(Wt::WString("Nothing found for {1}.")
    ///				.arg(edit->text()));
    ///	}));
    ///navigation->addSearch(edit, Wt::AlignRight);

    workArea_ = new Wt::WContainerWidget(this);

    Wt::WBorderLayout *layout = new Wt::WBorderLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    workArea_->setLayout(layout);
    
    // create CabureAdsContainer
    ///CabureAdsWidget *ads = new CabureAdsWidget();
    ///layout->addWidget(ads, Wt::WBorderLayout::East);
    // put contentsStack in workarea
    layout->addWidget(contents_, Wt::WBorderLayout::Center);

    showListas();
}

void HomeWidget::loginUI(){
  GTABApplication *app = GTABApplication::Application();
  clear();

  Wt::WContainerWidget *container = this;   

  auto tmpl = new WTemplate(container);
  tmpl->setTemplateText("<br/><br/><br/>"
  "<div style='width: 360px; margin: 0px auto;'>"
  " <h3>GTAB</h3>"
  " <form class='form-signin'>"
  "    <label for='inputEmail' class='sr-only'>Email</label>"
  "    ${email}"
  "    <br/>"			
  "    <label for='inputPassword' class='sr-only'>Senha</label>"
  "    ${senha}"
			//  "    <div class='checkbox'>"
			//  "       <label><input type='checkbox' value='remember-me'>Lembre-me</label>"
			//  "    </div>"
  "    <br/>${entrar}"
  "    ${registre}"
  " </form></div>", XHTMLUnsafeText);
 
  auto email = new WLineEdit();
  email->setStyleClass("form-control");
  email->setPlaceholderText("Email");

  auto senha = new WLineEdit();
  senha->setStyleClass("form-control");
  senha->setPlaceholderText("Senha");
  senha->setEchoMode(WLineEdit::Password);

  auto btnEntrar = new WPushButton();
  btnEntrar->setText("Entrar");
  btnEntrar->setStyleClass("btn btn-lg btn-primary btn-block");
  btnEntrar->clicked().connect(std::bind([=]() {
	auto uemail = email->text().toUTF8();
	auto usenha = senha->text().toUTF8();

	try {
	  long usuario_id;
	  bool ok = loginOk(uemail, usenha, usuario_id);
	  if (ok) {	    
	    std::string token = criaSessaoUsuario(uemail, usuario_id, false);
        app->setCookie("gtab__", token, 3600000);
	    app->email = uemail;
	    app->usuario_id = usuario_id;
	    createUI();
	  } else {
	    senha->setText("");
	  }
	} catch (std::exception &e) {
	  senha->setText("");
	}  
      }));
    
  auto btnRegistre = new WPushButton();
  btnRegistre->setText("Registre-se");
  btnRegistre->setStyleClass("btn btn-lg btn-success btn-block");
  btnRegistre->clicked().connect(std::bind([=]() {
	registerUI();
      }));

  tmpl->bindWidget("email", email);
  tmpl->bindWidget("senha", senha);
  tmpl->bindWidget("entrar", btnEntrar);
  tmpl->bindWidget("registre", btnRegistre);
}

void HomeWidget::registerUI(){
  clear();

    Wt::WContainerWidget *container = this;   

    auto tmpl = new WTemplate(container);
    tmpl->setTemplateText("<br/><br/><br/>"
  "<div style='width: 360px; margin: 0px auto;'>"
  " <h3>Registre-se</h3>"
  " ${aviso}"
  " <form class='form-signin'>"
  "    <label for='inputEmail' class='sr-only'>Email</label>"
  "    ${email}"
  "    <br/>"
  "    <label for='inputPassword' class='sr-only'>Senha</label>"
  "    ${senha}"
  "    <br/>"
  "    <label for='inputPassword' class='sr-only'>Senha novamente</label>"
  "    ${senha2}"
  "    <br/>"
  "    ${registrar}"
  "    ${voltar}"
  " </form></div>", XHTMLUnsafeText);
 
    auto email = new WLineEdit();
    email->setStyleClass("form-control");
    email->setPlaceholderText("Email");
    //email->setFocus(true);
    
    auto senha = new WLineEdit();
    senha->setStyleClass("form-control");
    senha->setPlaceholderText("Senha");
    senha->setEchoMode(WLineEdit::Password);

    auto senha2 = new WLineEdit();
    senha2->setStyleClass("form-control");
    senha2->setPlaceholderText("Senha novamente");
    senha2->setEchoMode(WLineEdit::Password);

    auto aviso = new WText();
    
    auto btnRegistrar = new WPushButton();
    btnRegistrar->setText("Registrar");
    btnRegistrar->setStyleClass("btn btn-lg btn-primary btn-block");
    btnRegistrar->clicked().connect(std::bind([=]() {
	  auto uemail = email->text().toUTF8();
	  auto usenha1 = senha->text().toUTF8();
	  auto usenha2 = senha2->text().toUTF8();

	  if (!is_email_valid(uemail)) {
	    aviso->setText("Isso nao parece um email!");
	    return;
	  }
	  
 	  if (usenha1.size() < 6) {
	    aviso->setText("Senhas devem ter mais de 6 letras!");
	    return;
	  }

 	  if (usenha1 != usenha2) {
	    aviso->setText("Senhas devem ser iguais!");
	    return;
	  }
	  
	  try {
	    registraUsuario(uemail, usenha1, usenha2);
	    loginUI();
	  } catch(const std::exception& e) {
	    std::cerr << e.what() << std::endl;
	    
	    aviso->setText("Email ja usado no sistema!");
	  }
	}));
    
    auto btnVoltar = new WPushButton();
    btnVoltar->setText("Voltar");
    btnVoltar->setStyleClass("btn btn-lg btn-success btn-block");
    btnVoltar->clicked().connect(std::bind([=]() {
	  loginUI();
	}));

    tmpl->bindWidget("aviso", aviso);
    tmpl->bindWidget("email", email);
    tmpl->bindWidget("senha", senha);
    tmpl->bindWidget("senha2", senha2);
    tmpl->bindWidget("registrar", btnRegistrar);
    tmpl->bindWidget("voltar", btnVoltar);
}

void HomeWidget::forgotPassUI(){
  clear();

  Wt::WContainerWidget *container = this;   
  new WText("ForgotPassword" , container);
}

void HomeWidget::viewHome(){
    createUI();
}

void HomeWidget::logout(){
  GTABApplication *app = GTABApplication::Application();
  app->setCookie("gtab__", "", 0);
  app->redirect("/");
}

void HomeWidget::showListas(){
  showContents(new MenuWidget());
}

void HomeWidget::showRecordes(){
  showContents(new RecordesWidget());
}

void HomeWidget::googleAnalyticsLogger(std::string url){
    doJavaScript("var pageTracker = _gat._getTracker('UA-34134276-1');"
                 "pageTracker._trackPageview('" + url + "');");
}

