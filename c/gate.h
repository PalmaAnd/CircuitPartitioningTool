#ifndef GATE_H
#define GATE_H

#include "connection.h"

/**
 * @brief A object representing a gate entity given via the gate.dat file.
 * @param gateId The id of the gate
 * @param typeId The type of the gate (e.g., AND, XOR)
 * @param marked The group of unconnected subcircuits this gate is part of.
 */
typedef struct {
    int gateId;
    int typeId;
    int marked;
} Gate;

typedef struct {
    Gate** gates;
    int count;
    int allocated;
} GateList;

/**
 * Add a new Gate to the given gateList
 * @param gateList The gateList to which the gate will be added
 * @return The updated gateList
 */
Gate *newGate (GateList *gateList);

/**
 * Creates a new gatelist while also allocating enough space for its content
 * @return the newly created GateList
 */
GateList *newGateList();

/**
 * Deletes the given list and clears all used space
 * @param list The list that will be deleted;
 */
void deleteGateList(GateList *list);

/**
 * @brief Reads gate data from a file and stores it in an gatelist.
 *
 * @param gateList The GateList that will be filled
 * @param filename The name of the file containing gate data
 */
void getGates (GateList *gateList, char *fileName);

/**
 * @brief Finds a gate by its gateId.
 *
 * @param gateList The GateList which will be searched
 * @param id The id of the searched gate
 * @return A pointer to the searched gate, or NULL if not found
 */
Gate *getGateById(GateList *gateList, int id);

/**
 * @brief Finds the next unmarked gate starting from a specified index.
 *
 * @param gates The gate array which will be searched
 * @param lastUnmarked The index to start searching from
 * @return The gateId of the next unmarked gate, or -1 if none is found
 */
int findNextUnmarkedGate(GateList *gateList, int lastUnmarked);

/**
 * @brief Iterates over the given gateList and marks every gate depending on which subcircuit they are part of.
 * This updates the given GateList
 * @param gateList
 * @param connectionList
 */
void markAllSubcircuits(GateList *gateList, ConnectionList *connectionList);

/**
 * Checks all gates by going trough the connectionList, if they are connected with the startGateId and
 * if that is the case, mark it with n.
 * @param startGateId
 * @param n
 * @param gateList
 * @param connectionList
 */
void markConnectedGates(int startGateId, int n, GateList *gateList, ConnectionList *connectionList);

#endif //GATE_H
