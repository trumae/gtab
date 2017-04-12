#ifndef __SMD_APPLICATION__
#define __SMD_APPLICATION__

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <string>

class HomeWidget; 

class GTABApplication : public Wt::WApplication {
public:
  GTABApplication(const Wt::WEnvironment& env);
  ~GTABApplication();

  static GTABApplication* Application() {
    return (GTABApplication *) WApplication::instance();
  };

  std::string email;
  long usuario_id;
  std::string token;

  int pergunta;
  int acertos;
  int numperguntas;

  HomeWidget *homeWidget() { return home_; }
  void setHomeWidget(HomeWidget *hw) { home_ = hw; }
private:
  HomeWidget *home_;
};

#endif
