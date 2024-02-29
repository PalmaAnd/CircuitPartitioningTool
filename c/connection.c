#include <stdio.h>
#include <stdlib.h>
#include "connection.h"

Connection *newConnection (ConnectionList *connectionList){
    if (connectionList->count >= connectionList->allocated) {
        connectionList->connections = (Connection **) realloc(connectionList->connections, connectionList->allocated * sizeof(Connection *));
    }
    Connection *connection = (Connection *) malloc(sizeof(Connection));
    connectionList->connections[connectionList->count++] = connection;
    return connection;
}

ConnectionList *newConnectionList(){
    ConnectionList *connectionList = (ConnectionList *) malloc(sizeof(ConnectionList));
    connectionList->count = 0;
    connectionList->allocated = 100;
    connectionList->connections = (Connection **) calloc(connectionList->allocated, sizeof(Connection *));
    return connectionList;
}

void deleteConnectionList(ConnectionList *list){
    for (int i = 0; i < list->count; ++i) {
        free(list->connections[i]);
    }
    free(list->connections);
    free(list);
}

void getConnections(ConnectionList *connectionList, char* filename) {
    int result;
    FILE* connectionsInput = fopen(filename, "r");

    if(filename == NULL || connectionsInput == NULL) {
        perror("Given file not found or not readable");
        exit (1);
    }

    do {
        Connection *connection = newConnection(connectionList);
        result = fscanf(connectionsInput, "%d %d %d %d",
                            &connection->vonGateId, &connection->vonPin,
                            &connection->nachGateId, &connection->nachPin);
    } while (result != EOF);

    fclose(connectionsInput);
}
