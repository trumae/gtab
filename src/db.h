#ifndef __DB__
#define __DB__

#include <cppdb/frontend.h>

#define STRCONN "sqlite3:db=gtab.db;busy_timeout=2000"

void setupDB(); 
#endif
