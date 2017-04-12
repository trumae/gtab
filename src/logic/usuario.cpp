#include <Wt/Auth/HashFunction>
#include <boost/uuid/uuid.hpp>          
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>
#include <sstream>

#include "usuario.h"

using namespace std;

static const string SALT = "#$gtab$#";
static Wt::Auth::BCryptHashFunction hashcalc(7);

/*! /brief registra um novo usuario no sistema - signup
 */
void registraUsuario(string email, string pass1, string pass2) {
    cppdb::session sess(STRCONN);

    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    stringstream ss;
    ss << uuid;

    string hash = hashcalc.compute(pass1, SALT);

    sess << "insert into usuario(uuid, email, data_entrada, senha) values (?,?,datetime('now'),?)"
            << ss.str()
            << email
            << hash
            << cppdb::exec;
}

/*! /brief verifica o login
 */
bool loginOk(string email, string password, long &usuario_id) {
  cppdb::session sess(STRCONN);

  cppdb::statement st = sess << "select senha, id from usuario where email = ?" << email;
  cppdb::result r = st.row();
  
  if (!r.empty()) {
    std::string senha;
 
    string hash = hashcalc.compute(password, SALT);
    r >> senha >> usuario_id;
    if (hash == senha) 
      return true;
  }
  return false;
}

std::string criaSessaoUsuario(std::string email, long usuario_id, bool lembrar) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::stringstream ss;
    ss << uuid;

    cppdb::session sess(STRCONN);
    if (lembrar) {
        sess << "insert into sessao_usuario(token, email, usuario_id, expire, begin_at) values (?,?,?,datetime('now','+6 month'),datetime('now'))"
	     << ss.str() << email << usuario_id << cppdb::exec;
    } else {
        sess << "insert into sessao_usuario(token, email, usuario_id, expire, begin_at) values (?,?,?,datetime('now','+8 hour'),datetime('now'))"
	     << ss.str() << email << usuario_id << cppdb::exec;
    }
    return ss.str();
}

bool sessaoUsuarioValida(string token, string &email, long &usuario_id) {
    cppdb::session sess(STRCONN);

    cppdb::statement st = sess << "select email, usuario_id from sessao_usuario where expire > datetime('now') and token = ?"
            << token;
    cppdb::result r = st.row();

    if (r.empty()) {
        return false;
    }
    r >> email >> usuario_id;
    return true;
}
