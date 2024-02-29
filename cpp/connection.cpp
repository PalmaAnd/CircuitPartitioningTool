#include "fstream"
#include "connection.h"

using namespace std;

ConnectionList::ConnectionList(char *fileName) {
    fstream s (fileName);
    int counter = 0;
    try { for (;;) {
            connections.insert({s, counter});
            counter++;
        }}
    catch (EOFException) {}
}
