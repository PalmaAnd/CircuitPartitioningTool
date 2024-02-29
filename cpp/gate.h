#ifndef GATE_H
#define GATE_H

#include "connection.h"
#include <exception>

using namespace std;


/**
 * @brief A object representing a gate entity given via the gate.dat file
 */
class Gate {
public:
    int marked = 0; // The group of unconnected subcircuits this gate is part of

    Gate(istream &s){
        s >> gateId >> typeId;
        if (!s) throw EOFException();
    }

    /**
     * Custom constructor used to use with set::find, by only having the gateId
     * @param id
     */
    explicit Gate(unsigned int id){
        this->gateId = id;
    }

    // Operator to compare connections based on vonGateId
    bool operator< (const Gate &gate) const { return gateId < gate.gateId; }

    unsigned getGateId() const{return gateId;}

    struct GateComparer {
        bool operator()(const Gate& gate1, const Gate& gate2) const {
            return gate1.getGateId() < gate2.getGateId();
        }
    };


private:
    int gateId; // The id of the gate
    int typeId; // The type of the gate (e.g., AND, XOR)
};

class GateList{
public:
    GateList(char *fileName);

    /**
     * @brief Finds a gate by its gateId.
     *
     * @param gateId The id of the searched gate
     * @return A pointer to the searched gate, or NULL if not found
     */
    Gate* getGateById(unsigned id);

    /**
     * @brief Finds the next unmarked gate starting from a specified index.
     *
     * @param lastUnmarked The index to start searching from
     * @return The gateId of the next unmarked gate, or -1 if none is found
     */
    int findNextUnmarkedGate(int lastUnmarked);


    /**
     * @brief Iterates over the given gateList and marks every gate depending on which subcircuit they are part of.
     * This updates the given GateList
     * @param connectionList
     */
    void markAllSubcircuits(const ConnectionList& connectionList);

    /**
     * Checks all gates by going trough the connectionList, if they are connected with the startGateId and
     * if that is the case, mark it with n.
     * @param startGateId
     * @param n
     * @param connectionList
     */
    void markConnectedGates(int startGateId, int n, ConnectionList& connectionList);

    /**
     * Print all gates sorted by marked
     */
    void printAllGates();

    /**
     * Reset the gates set.
     */
    void clearGateList();

private:
    set<Gate, Gate::GateComparer> gates;

    /**
     * Helper function used to sort all gates by their marked value
     * @param gate1
     * @param gate2
     * @return If gate1 has a smaller marked value than gate2
     */
    static bool compareMarked(const Gate& gate1, const Gate& gate2);
};
#endif //GATE_H
