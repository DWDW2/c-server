#include "db.h"
#include <stdlib.h>
#include <libpq-fe.h>

static void exit_nicely(PGconn *con) {
  PQfinish(con);
  exit(1);
}

void connect() {
  PGresult *res;
  PGconn *con = PQconnectdb("host=localhost port=5432");
  
  if (PQstatus(con) != CONNECTION_OK)
  {
      fprintf(stderr, "%s", PQerrorMessage(con));
      exit_nicely(con);
  }

  res = PQexec(con, 
  "CREATE TABLE IF NOT EXISTS: (id primary_key,name varchar(256))");

  if(PQresultStatus(res) != PGRES_TUPLES_OK){
    exit(1);
  }
}
