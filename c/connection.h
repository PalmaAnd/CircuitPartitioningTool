#ifndef CONNECTION_H
#define CONNECTION_H

/**
 * @brief A connection between two gates over two pins.
 * @param vonGateId The id of the from gate
 * @param vonPin The pin at which the connection is established at the from gate
 * @param nachGateId The id of the to gate
 * @param nachPin The pin at which the connection is established at the to gate
 */
typedef struct {
    int vonGateId;
    int vonPin;
    int nachGateId;
    int nachPin;
} Connection;

typedef struct {
    Connection** connections;
    int count;
    int allocated;
} ConnectionList;

/**
 * Add a new Connection to the given connectionList
 * @param connectionList The connectionList to which the connection will be added
 * @return The updated connectionList
 */
Connection *newConnection (ConnectionList *connectionList);

/**
 * Creates a new connectionlist while also allocating enough space for its content
 * @return the newly created ConnectionList
 */
ConnectionList *newConnectionList();

/**
 * Deletes the given list and clears all used space
 * @param list The list that will be deleted;
 */
void deleteConnectionList(ConnectionList *list);

/**
 * @brief Reads connection data from a file and stores it in a ConnectionList.
 *
 * @param connectionList The list that will be filled with the given data
 * @param filename The name of the file containing (connection) data
 * @return A pointer to an array of connections
 */
void getConnections(ConnectionList *connectionList, char* filename);

#endif //CONNECTION_H
