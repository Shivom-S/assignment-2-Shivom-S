 #include <iostream>
            #include <vector>
            #include <cmath>

            class HashTable {
            private:
                std::vector<int> table;
                std::vector<bool> occupied;
                int size;
                int count;
                const double loadFactorThreshold = 0.8;

                int hash(int key) {
                    return key % size;
                }

                bool isPrime(int n) {
                    if (n <= 1) return false;
                    if (n <= 3) return true;
                    if (n % 2 == 0 || n % 3 == 0) return false;
                    for (int i = 5; i * i <= n; i += 6) {
                        if (n % i == 0 || n % (i + 2) == 0) return false;
                    }
                    return true;
                }

                int nextPrime(int n) {
                    while (!isPrime(n)) {
                        n++;
                    }
                    return n;
                }

                void resize() {
                    int oldSize = size;
                    size = nextPrime(size * 2);
                    std::vector<int> oldTable = table;
                    std::vector<bool> oldOccupied = occupied;

                    table = std::vector<int>(size, -1);
                    occupied = std::vector<bool>(size, false);
                    count = 0;

                    for (int i = 0; i < oldSize; i++) {
                        if (oldOccupied[i]) {
                            insert(oldTable[i]);
                        }
                    }
                }

            public:
                void printTable() {
    bool first = true; // Flag to handle the first element without preceding separator
    for (int i = 0; i < size; i++) {
        if (!first) {
            std::cout << " - "; // Add separator between elements
        }
        if (occupied[i]) {
            std::cout << table[i];
        } else {
            std::cout << "-";
        }
        first = false; // After first element, always add separator before next element
    }
    std::cout << std::endl;
}
                    std::cout << std::endl;
                }

                HashTable(int initialSize) {
                    size = nextPrime(initialSize);
                    table = std::vector<int>(size, -1);
                    occupied = std::vector<bool>(size, false);
                    count = 0;
                }

                // Move constructor
                HashTable(HashTable&& other) noexcept
                    : table(std::move(other.table)),
                      occupied(std::move(other.occupied)),
                      size(other.size),
                      count(other.count),
                      loadFactorThreshold(other.loadFactorThreshold) {
                    other.size = 0;
                    other.count = 0;
                }

                // Move assignment operator
                HashTable& operator=(HashTable&& other) noexcept {
                    if (this != &other) {
                        table = std::move(other.table);
                        occupied = std::move(other.occupied);
                        size = other.size;
                        count = other.count;
                        // loadFactorThreshold is const, no need to assign

                        other.size = 0;
                        other.count = 0;
                    }
                    return *this;
                }

                void insert(int key) {
                    if ((double)count / size >= loadFactorThreshold) {
                        resize();
                    }

                    int index = hash(key);
                    int i = 0;
                    while (occupied[(index + i * i) % size]) {
                        i++;
                    }
                    table[(index + i * i) % size] = key;
                    occupied[(index + i * i) % size] = true;
                    count++;
                }

                bool search(int key) {
                    int index = hash(key);
                    int i = 0;
                    while (occupied[(index + i * i) % size]) {
                        if (table[(index + i * i) % size] == key) {
                            return true;
                        }
                        i++;
                    }
                    return false;
                }

                void remove(int key) {
                    int index = hash(key);
                    int i = 0;
                    while (occupied[(index + i * i) % size]) {
                        if (table[(index + i * i) % size] == key) {
                            occupied[(index + i * i) % size] = false;
                            count--;
                            return;
                        }
                        i++;
                    }
                }
            };
