#include <iostream>

#include "db.h"

/*! \brief inicia banco de dados e cria tabelas se necessario
 */

static void criaTabelaUsuario(cppdb::session sess)
{
    sess <<
      "create table if not exists usuario ("
      "   id integer  not null primary key autoincrement, "
      "   uuid text not null, "
      "   email text not null, "
      "   nome text , "
      "   habilitado integer not null default 1, "
      "   verificado integer not null default 1, "
      "   data_entrada datetime not null, "
      "   ultimo_login datetime, "
      "   senha text not null "
      " ) " << cppdb::exec;
    sess << " create unique index if not exists uuid_idx_unique_usuario on usuario(uuid) " << cppdb::exec;
    sess << " create unique index if not exists email_idx_unique_usuario on usuario(email) " << cppdb::exec;
}

static void criaTabelaSessaoUsuario(cppdb::session sess)
{
    sess <<
      "create table if not exists sessao_usuario ("
      "   id integer  not null primary key autoincrement, "
      "   token text not null, "
      "   email text not null, "
      "   usuario_id int not null, "
      "   expire datetime not null, "
      "   begin_at datetime not null, "
      "   is_admin integer not null default 0) " << cppdb::exec;
    sess << " create unique index if not exists token_idx_unique_sessao_usuario on sessao_usuario (token) " << cppdb::exec;
}

void setupDB() {
  cppdb::session sess(STRCONN);

  try{
    //user table
    criaTabelaUsuario(sess);
    criaTabelaSessaoUsuario(sess);
  } catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
