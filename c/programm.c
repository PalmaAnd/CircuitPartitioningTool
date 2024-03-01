#include <stdio.h>
#include <stdlib.h>
#include "gate.h"
#include "connection.h"
#include "queue.h"

int main(int argc, char *argv[]) {

    /**
     * Counter for the given args: the program name, and 2 .dat files
     */
    const int NUM_EXPECTED_ARGS = 2;
    if (argc < NUM_EXPECTED_ARGS + 1) {
        fputs("Usage: programm gate.dat connection.dat\n", stderr);
        exit(1);
    }
    GateList *gateList = newGateList();
    getGates(gateList, argv[1]);
    ConnectionList *connectionList = newConnectionList();
    getConnections(connectionList, argv[2]);

    markAllSubcircuits(gateList, connectionList);

    printf("Output: -----------------------------------\n");
    for (int i = 0; i < gateList->count - 1; ++i) {
        printf("Gate[%d]: marked = %d\n", gateList->gates[i]->gateId, gateList->gates[i]->marked);
    }
    printf("-------------------------------------------\n");

    deleteGateList(gateList);
    deleteConnectionList(connectionList);
    printf("Finished marking all subcurcuits.\nProgramm end.\n");
    return 0;
}
