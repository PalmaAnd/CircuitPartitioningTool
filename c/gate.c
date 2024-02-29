#include <stdio.h>
#include <stdlib.h>
#include "gate.h"
#include "queue.h"

Gate *newGate(GateList *gateList) {
    if (gateList->count >= gateList->allocated) {
        gateList->gates = (Gate **) realloc(gateList->gates, gateList->allocated * sizeof(Gate *));
    }
    Gate *gate = (Gate *) malloc(sizeof(Gate));
    gateList->gates[gateList->count++] = gate;
    return gate;
}

GateList *newGateList() {
    GateList *gateList = (GateList *) malloc(sizeof(GateList));
    gateList->count = 0;
    gateList->allocated = 100;
    gateList->gates = (Gate **) calloc(gateList->allocated, sizeof(Gate *));
    return gateList;
}

void deleteGateList(GateList *gatelist) {
    for (int i = 0; i < gatelist->count; ++i) {
        free(gatelist->gates[i]);
    }
    free(gatelist->gates);
    free(gatelist);
}

void getGates(GateList *gateList, char *filename) {
    int result;
    FILE *gatesInput = fopen(filename, "r");

    if (filename == NULL || gatesInput == NULL) {
        perror("Given file not found or not readable");
        exit(1);
    }

    do  {
        Gate *gate = newGate(gateList);
        result = fscanf(gatesInput, "%d %d", &gate->gateId, &gate->typeId);
        gate->marked = 0;
    } while (result != EOF);
    fclose(gatesInput);
}

int findNextUnmarkedGate(GateList *gateList, int lastUnmarked) {
    for (int i = lastUnmarked; i < gateList->count; ++i)
        if (gateList->gates[i]->marked == 0) return gateList->gates[i]->gateId;
    return -1;
}

Gate *getGateById(GateList *gatesList, int gateId) {
    for (int i = 0; i < gatesList->count; ++i) {
        if (gatesList->gates[i]->gateId == gateId)
            return (gatesList->gates[i]);
    }
    fprintf(stderr, "Gate with Id %d not found\n", gateId);
    exit(1);
}

void markConnectedGates(int startGateId, int n, GateList *gateList, ConnectionList *connectionList) {
    Queue* queue = createQueue(100);
    if (queue == NULL){
        perror("Error occurred while trying to allocate memory for the Queue");
    }

    Gate* currentGate = getGateById(gateList, startGateId);
    if (currentGate == NULL) {
        free(queue);
    }

    currentGate->marked = n;
    enqueue(queue, startGateId);

    while (!isEmpty(queue)) {
        int gateId = dequeue(queue);
        currentGate = getGateById(gateList, gateId);

        if (currentGate == NULL) {
            free(queue->array);
            free(queue);
        }
        // Check and mark all connected gates
        for (int i = 0; i < connectionList->count; i++) {
            int vonGateId = connectionList->connections[i]->vonGateId;
            int nachGateId = connectionList->connections[i]->nachGateId;
            if (vonGateId == gateId && getGateById(gateList, nachGateId)->marked == 0) {
                getGateById(gateList, nachGateId)->marked = n;
                enqueue(queue, nachGateId);
            } else if (nachGateId == gateId && getGateById(gateList, vonGateId)->marked == 0) {
                getGateById(gateList, vonGateId)->marked = n;
                enqueue(queue, vonGateId);
            }
        }
    }
    free(queue->array);
    free(queue);
}

void markAllSubcircuits(GateList *gateList, ConnectionList *connectionList){
    int n = 1;
    int unmarkedGateId = 1;
    while (unmarkedGateId != -1) {
        markConnectedGates(unmarkedGateId, n, gateList, connectionList);
        unmarkedGateId = findNextUnmarkedGate(gateList, unmarkedGateId);
        n++;
    }
}
