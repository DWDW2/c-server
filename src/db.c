#include "db.h"
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>

static void exit_nicely(PGconn *con) {
  PQfinish(con);
  exit(1);
}

char *connect_and_fetch(void) {
    PGconn   *con;
    PGresult *res;
    char     *value;

    const char *conninfo = "some_connection_string";

    con = PQconnectdb(conninfo);
    if (PQstatus(con) != CONNECTION_OK) {
        fprintf(stderr, "Connection failed: %s\n", PQerrorMessage(con));
        PQfinish(con);
        return NULL;
    }

    res = PQexec(con, "SELECT * FROM \"user\"");  
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(con));
        PQclear(res);
        PQfinish(con);
        return NULL;
    }

    value = strdup(PQfname(res, 1));

    PQclear(res);
    PQfinish(con);
    return value;
}
