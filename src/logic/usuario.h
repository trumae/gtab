#ifndef __USUARIO__
#define __USUARIO__

#include "../db.h"

void registraUsuario(std::string email, std::string pass1, std::string pass2);
bool loginOk(std::string email, std::string password, long &usuario_id);
std::string criaSessaoUsuario(std::string email, long usuario_id, bool lembrar);
bool sessaoUsuarioValida(std::string token, std::string &email, long &usuario_id);

#endif
