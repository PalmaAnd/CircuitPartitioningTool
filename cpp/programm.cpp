#include "connection.h"
#include "gate.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[]) {
    int const NUM_EXPECTED_ARGS = 4;
    if (argc < NUM_EXPECTED_ARGS + 1) {
        cerr << "Usage: programm gate.dat connection.dat type.dat function.dat\n" << endl;
        exit(1);
    }


    GateList gatesList (argv[1]);
    ConnectionList connectionList (argv[2]);

    gatesList.markAllSubcircuits(connectionList);

    cout << "################### Output ###################\n" << endl;
    gatesList.printAllGates();
    return 0;
}
