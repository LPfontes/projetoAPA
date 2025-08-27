class StationNode {
public:
    int stationId;
    StationNode* next;

    StationNode(int id) : stationId(id), next(nullptr) {}
};

class StationList {
private:
    StationNode* head;
public:
    StationList() : head(nullptr) {}

    // Adiciona um nó ao início da lista
    void add(int stationId) {
        StationNode* newNode = new StationNode(stationId);
        newNode->next = head;
        head = newNode;
    }

    // Remove o nó com stationId específico
    void remove(int stationId) {
        StationNode* current = head;
        StationNode* prev = nullptr;
        while (current != nullptr) {
            if (current->stationId == stationId) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Destrutor para liberar a lista
    ~StationList() {
        while (head != nullptr) {
            StationNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Getter para o head (caso precise iterar externamente)
    StationNode* getHead() const {
        return head;
    }
};