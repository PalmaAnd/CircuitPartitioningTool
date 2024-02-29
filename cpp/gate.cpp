#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include "gate.h"

GateList::GateList(char *fileName) {
    fstream s (fileName);
    try {
        for (;;) {
            gates.emplace(s);
        }
    }
    catch (EOFException) {
        cout << "End of file for gates" << endl;
    }
}

Gate* GateList::getGateById(unsigned int id) {
    auto temp =  gates.find(Gate(id));
    if (temp != gates.end())
        return const_cast<Gate *>(&(*temp));
    else
        return nullptr;
}

int GateList::findNextUnmarkedGate(int lastUnmarked) {
    for (auto gate : gates) {
        if (lastUnmarked < gate.getGateId() && gate.marked == 0) {
            return gate.getGateId();
        }
    }
    return -1;

}

void GateList::markConnectedGates(int startGateId, int n, ConnectionList& connectionList) {
    queue<int> que;
    Gate* currentGate = getGateById(startGateId);
    if (currentGate == nullptr) return;
    currentGate->marked = n;
    que.push(startGateId);
    while (!que.empty()) {
        int gateId = que.front();
        que.pop();
        for (Connection currentConnection : connectionList.getConnections()) {
            int vonGateId = currentConnection.getVonGateId();
            int nachGateId = currentConnection.getNachGateId();

            if (vonGateId == gateId && getGateById(nachGateId)->marked == 0) {
                getGateById(nachGateId)->marked = n;  // TODO: Wenn die Connection Pointer zu den Gates hätte, müsste man hier gar nicht suchen.  Rade
                que.push(nachGateId);
            } else if (nachGateId == gateId && getGateById(vonGateId)->marked == 0) {
                getGateById(vonGateId)->marked = n;
                que.push(vonGateId);
            }
        }
    }
}

void GateList::markAllSubcircuits(const ConnectionList& connectionList) {
    int n = 1;
    int unmarkedGateId = 1;
    while (unmarkedGateId != -1) {
        markConnectedGates(unmarkedGateId, n, const_cast<ConnectionList &>(connectionList));
        unmarkedGateId = findNextUnmarkedGate(unmarkedGateId);
        n++;
    }
}

void GateList::printAllGates() {
    std::vector<Gate> gatesVec(gates.begin(), gates.end());
    // Used to sort the given set
    std::sort(gatesVec.begin(), gatesVec.end(), GateList::compareMarked);

    int lastMarked = -1;

    for (const auto& gate : gates) {
        if (lastMarked != gate.marked){
            lastMarked = gate.marked;
            cout << "###################################################" << endl;
            cout << "\n# ------------ Teilschaltung mit n = " << lastMarked << " -----------#" << endl;
        }
        cout << "#              Gate[" << gate.getGateId() << "]: marked = " << gate.marked << "              #" << endl;
    }
    cout << "###################################################" << endl;
}

bool GateList::compareMarked(const Gate &gate1, const Gate &gate2) {
    return gate1.marked < gate2.marked;
}

void GateList::clearGateList() {
    gates.clear();
}
