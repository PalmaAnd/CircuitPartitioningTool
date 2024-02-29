#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <set>

// So we can use istream instead of std::istream down below
using namespace std;

class EOFException {
};

/**
 * @brief A connection between two gates over two pins.
 */
class Connection
{
public:
    // Default constructor using istream to initialize Connection
    Connection (istream &s, int counter){
        s >> vonGateId >> vonPin >> nachGateId >> nachPin;
        id = counter;
        if (!s) throw EOFException();
    }

    // Operator to compare connections based on vonGateId
    bool operator< (const Connection &c) const { return id < c.id; }

    int getVonGateId() const{return vonGateId;}
    int getNachGateId() const{return nachGateId;}

private:
    int vonGateId;      // The id of the source gate
    int vonPin;         // The pin at which the connection is established at the source gate
    int nachGateId;     // The id of the destination gate
    int nachPin;        // The pin at which the connection is established at the destination gate
    int id;             // Used to sort the connections
};

class ConnectionList{
public:
    /**
     * @brief Creates a new ConnectionList by reading connections from the given file and storing them.
     * @param fileName The name of the file containing connection data
     */
    ConnectionList(char *fileName);
    set<Connection> getConnections(){return connections;};
private:
    set<Connection> connections;
};

#endif //CONNECTION_H
