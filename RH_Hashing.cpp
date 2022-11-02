#include <random>
#include "rh_hash.hpp"
#include <string>

static const std::string alphanum =
    "!@:#$%^&*"
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

std::string string_random(size_t length = 1) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::string generated = "";
    for (size_t i = 0; i < length; i++) generated += alphanum[mersenne() % alphanum.length()];
    return generated;
}

static bool detailed = false;

static rh_map<int, int> nmap;
static rh_map<double, double> rmap;
static rh_map<std::string, std::string> smap;

void insert_random() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    size_t count = 0;
    char type;
    std::cout << "   LOG: enter number of random entries -> "; std::cin >> count;
    std::cout << "   LOG: select data type: integer (I) / real (R) / string (S) -> "; std::cin >> type;
    switch (type) {
    case 'i':
    case 'I':
        for (size_t i = 0; i < count; i++) {
            nmap.insert(mersenne(), mersenne());
        }
        std::cout << "   LOG: size = " << nmap.size() << " | capacity = " << nmap.capacity() <<
            " | max_size = " << nmap.max_size() << std::endl;
        if (detailed) nmap.print(false, 5);
        break;
    case 'r':
    case 'R':
        for (size_t i = 0; i < count; i++) {
            rmap.insert((mersenne() % count) / (double)count + mersenne(), (mersenne() % count) / (double)count + mersenne());
        }
        std::cout << "   LOG: size = " << rmap.size() << " | capacity = " << rmap.capacity() <<
            " | max_size = " << rmap.max_size() << std::endl;
        if (detailed) rmap.print(false, 5);
        break;
    case 's':
    case 'S':
        int ssize = 0;
        std::cout << "   LOG: enter length of random strings -> "; std::cin >> ssize;
        for (size_t i = 0; i < count; i++) {
            smap.insert(string_random(ssize), string_random(ssize));
        }
        std::cout << "   LOG: size = " << smap.size() << " | capacity = " << smap.capacity() <<
            " | max_size = " << smap.max_size() << std::endl;
        if (detailed) smap.print(false, 5);
        break;
    }
}

void insert_optional() {
    size_t count = 0;
    char type;
    std::cout << "   LOG: enter number of optional entries -> "; std::cin >> count;
    std::cout << "   LOG: select data type: integer (I) / real (R) / string (S) -> "; std::cin >> type;
    std::cout << "   LOG: enter " << count << " \"key value\" pairs" << std::endl; std::cin.get();
    switch (type) {
    case 'i':
    case 'I': {
        int key = 0, value = 0;
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i + 1 << "\tkey: "; std::cin >> key;
            std::cout << "          \tvalue: "; std::cin >> value;
            nmap.insert(key, value);
        }
        std::cout << "   LOG: size = " << nmap.size() << " | capacity = " << nmap.capacity() <<
            " | max_size = " << nmap.max_size() << std::endl;
        if (detailed) nmap.print(false, 5);
        break;
    }
    case 'r':
    case 'R': {
        double key = 0, value = 0;
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i + 1 << "\tkey: "; std::cin >> key;
            std::cout << "          \tvalue: "; std::cin >> value;
            rmap.insert(key, value);
        }
        std::cout << "   LOG: size = " << rmap.size() << " | capacity = " << rmap.capacity() <<
            " | max_size = " << rmap.max_size() << std::endl;
        if (detailed) rmap.print(false, 5);
        break;
    }
    case 's':
    case 'S': {
        std::string key = "", value = "";
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i + 1 << "\tkey: "; std::getline(std::cin, key);
            std::cout << "          \tvalue: "; std::getline(std::cin, value, '\n');
            smap.insert(key, value);
        }
        std::cout << "   LOG: size = " << smap.size() << " | capacity = " << smap.capacity() <<
            " | max_size = " << smap.max_size() << std::endl;
        if (detailed) smap.print(false, 5);
        break;
    }
    }
}

void test_insert() {
    char input;
    std::cout << "   LOG: test insert initialization..." << std::endl;
    std::cout << "   LOG: print sample data from table after 'insert'? YES (Y) / NO (N) -> "; std::cin >> input;
    switch (input) {
    case 'y':
    case 'Y': detailed = true; break;
    case 'n':
    case 'N': detailed = false; break;
    }
    std::cout << "   LOG: select input method: random (R) / optional (O) -> "; std::cin >> input;
    switch (input) {
    case 'r':
    case 'R': insert_random(); break;
    case 'o':
    case 'O': insert_optional(); break;
    }
    std::cout << "   LOG: test insert finishing..." << std::endl;
}

void erase_random() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    size_t count = 0;
    char type;
    std::cout << "   LOG: enter number of random entries -> "; std::cin >> count;
    std::cout << "   LOG: select data type: integer (I) / real (R) / string (S) -> "; std::cin >> type;
    switch (type) {
    case 'i':
    case 'I': {
        for (size_t i = 0; i < count; i++)
            nmap.erase(mersenne());
        std::cout << "   LOG: size = " << nmap.size() << " | capacity = " << nmap.capacity() <<
            " | max_size = " << nmap.max_size() << std::endl;
        if (detailed) nmap.print(false, 5);
        break;
    }
    case 'r':
    case 'R': {
        for (size_t i = 0; i < count; i++)
            rmap.erase((mersenne() % count) / (double)count + mersenne());
        std::cout << "   LOG: size = " << rmap.size() << " | capacity = " << rmap.capacity() <<
            " | max_size = " << rmap.max_size() << std::endl;
        if (detailed) rmap.print(false, 5);
        break;
    }
    case 's':
    case 'S': {
        int ssize = 0;
        std::cout << "   LOG: enter length of random strings -> "; std::cin >> ssize;
        for (size_t i = 0; i < count; i++)
            smap.erase(string_random(ssize));
        std::cout << "   LOG: size = " << smap.size() << " | capacity = " << smap.capacity() <<
            " | max_size = " << smap.max_size() << std::endl;
        if (detailed) smap.print(false, 5);
        break;
    }
    }
}

void erase_optional() {
    size_t count = 0;
    char type;
    std::cout << "   LOG: enter number of optional entries -> "; std::cin >> count;
    std::cout << "   LOG: select data type: integer (I) / real (R) / string (S) -> "; std::cin >> type;
    std::cout << "   LOG: enter " << count << " \"keys\"" << std::endl; std::cin.get();
    switch (type) {
    case 'i':
    case 'I': {
        int key = 0;
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i << "\tkey: "; std::cin >> key;
            nmap.erase(key);
        }
        std::cout << "   LOG: size = " << nmap.size() << " | capacity = " << nmap.capacity() <<
            " | max_size = " << nmap.max_size() << std::endl;
        if (detailed) nmap.print(false, 5);
        break;
    }
    case 'r':
    case 'R': {
        double key = 0;
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i << "\tkey: "; std::cin >> key;
            rmap.erase(key);
        }
        std::cout << "   LOG: size = " << rmap.size() << " | capacity = " << rmap.capacity() <<
            " | max_size = " << rmap.max_size() << std::endl;
        if (detailed) rmap.print(false, 5);
        break;
    }
    case 's':
    case 'S': {
        std::string key = "";
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i << "\tkey: "; std::getline(std::cin, key);
            smap.erase(key);
        }
        std::cout << "   LOG: size = " << smap.size() << " | capacity = " << smap.capacity() <<
            " | max_size = " << smap.max_size() << std::endl;
        if (detailed) smap.print(false, 5);
        break;
    }
    }
}

void test_erase() {
    char input;
    std::cout << "   LOG: test erase initialization..." << std::endl;
    std::cout << "   LOG: print sample data from table after 'erase'? YES (Y) / NO (N) -> "; std::cin >> input;
    switch (input) {
    case 'y':
    case 'Y': detailed = true; break;
    case 'n':
    case 'N': detailed = false; break;
    }
    std::cout << "   LOG: select input method: random (R) / optional (O) -> "; std::cin >> input;
    switch (input) {
    case 'r':
    case 'R': erase_random(); break;
    case 'o':
    case 'O': erase_optional(); break;
    }
    std::cout << "   LOG: test erase finishing..." << std::endl;
}

void find_random() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    size_t count = 0;
    char type;
    std::cout << "   LOG: enter number of random entries -> "; std::cin >> count;
    std::cout << "   LOG: select data type: integer (I) / real (R) / string (S) -> "; std::cin >> type;
    switch (type) {
    case 'i':
    case 'I': {
        for (size_t i = 0; i < count; i++) {
            int key = mersenne();
            auto it = rmap.find(key);
            if (it != rmap.end()) std::cout << "        at key: " << key << " - record: " << *it << " was found" << std::endl;
            // else std::cout << "        at key: " << key << " - nothing was found" << std::endl;
        }
        std::cout << "   LOG: size = " << nmap.size() << " | capacity = " << nmap.capacity() <<
            " | max_size = " << nmap.max_size() << std::endl;
        if (detailed) nmap.print(false, 5);
        break;
    }
    case 'r':
    case 'R': {
        for (size_t i = 0; i < count; i++) {
            double key = (mersenne() % count) / (double)count + mersenne();
            auto it = rmap.find(key);
            if (it != rmap.end()) std::cout << "        at key: " << key << " - record: " << *it << " was found" << std::endl;
            // else std::cout << "        at key: " << key << " - nothing was found" << std::endl;
        }
        std::cout << "   LOG: size = " << rmap.size() << " | capacity = " << rmap.capacity() <<
            " | max_size = " << rmap.max_size() << std::endl;
        if (detailed) rmap.print(false, 5);
        break;
    }
    case 's':
    case 'S': {
        int ssize = 0;
        std::string key = "";
        std::cout << "   LOG: enter length of random strings -> "; std::cin >> ssize;
        for (size_t i = 0; i < count; i++) {
            key = string_random(ssize);
            auto it = smap.find(key);
            if (it != smap.end()) std::cout << "        at key: " << key << " - record: " << *it << " was found" << std::endl;
            else std::cout << "        at key: " << key << " - nothing was found" << std::endl;
        }
        std::cout << "   LOG: size = " << smap.size() << " | capacity = " << smap.capacity() <<
            " | max_size = " << smap.max_size() << std::endl;
        if (detailed) smap.print(false, 5);
        break;
    }
    }
}

void find_optional() {
    size_t count = 0;
    char type;
    std::cout << "   LOG: enter number of optional entries -> "; std::cin >> count;
    std::cout << "   LOG: select data type: integer (I) / real (R) / string (S) -> "; std::cin >> type;
    std::cout << "   LOG: enter " << count << " \"keys\"" << std::endl; std::cin.get();
    switch (type) {
    case 'i':
    case 'I': {
        int key = 0;
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i << "\tkey: "; std::cin >> key;
            auto it = nmap.find(key);
            if (it != nmap.end()) std::cout << "        at key: " << key << " - record: " << *it << " was found" << std::endl;
            // else std::cout << "        at key: " << key << " - nothing was found" << std::endl;
        }
        std::cout << "   LOG: size = " << nmap.size() << " | capacity = " << nmap.capacity() <<
            " | max_size = " << nmap.max_size() << std::endl;
        if (detailed) nmap.print(false, 5);
        break;
    }
    case 'r':
    case 'R': {
        double key = 0;
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i << "\tkey: "; std::cin >> key;
            auto it = rmap.find(key);
            if (it != rmap.end()) std::cout << "        at key: " << key << " - record: " << *it << " was found" << std::endl;
            // else std::cout << "        at key: " << key << " - nothing was found" << std::endl;
        }
        std::cout << "   LOG: size = " << rmap.size() << " | capacity = " << rmap.capacity() <<
            " | max_size = " << rmap.max_size() << std::endl;
        if (detailed) rmap.print(false, 5);
        break;
    }
    case 's':
    case 'S': {
        std::string key = "";
        for (size_t i = 0; i < count; i++) {
            std::cout << "    IN: #" << i << "\tkey: "; std::getline(std::cin, key);
            auto it = smap.find(key);
            if (it != smap.end()) std::cout << "        at key: " << key << " - record: " << *it << " was found" << std::endl;
            // else std::cout << "        at key: " << key << " - nothing was found" << std::endl;
        }
        std::cout << "   LOG: size = " << smap.size() << " | capacity = " << smap.capacity() <<
            " | max_size = " << smap.max_size() << std::endl;
        break;
    }
    }
}

void test_find() {
    char input;
    std::cout << "   LOG: test find initialization..." << std::endl;
    std::cout << "   LOG: select input method: random (R) / optional (O) -> "; std::cin >> input;
    switch (input) {
    case 'r':
    case 'R': find_random(); break;
    case 'o':
    case 'O': find_optional(); break;
    }
    std::cout << "   LOG: test find finishing..." << std::endl;
}

int main(void) {
    char input;
    double mlf;
    std::cout.precision(6);
    std::cout << std::fixed;
    std::cout << "SYSTEM: HASH TABLE WITH ROBIN HOOD HASHING" << std::endl;
    std::cout << "AUTHOR: STUDENT KMBO-01-18 IBRAGIM IDRISOV" << std::endl;
    std::cout << " ABOUT: - three hash maps for strings, integers and real numbers prepared" << std::endl;
    std::cout << "        - at each branching, enter the character indicated in parentheses (...)" << std::endl;
    std::cout << "        - for more variety, you will have to modify the 'main.cpp' file" << std::endl;
    std::cout << "SYSTEM: set initial maximum load factor (between 0.0 and 1.0) of tables (0 to use default value) -> ";
    std::cin >> mlf;
    if (mlf <= 0.0 || mlf > 1.0) {
        nmap = rh_map<int, int>();
        rmap = rh_map<double, double>();
        smap = rh_map<std::string, std::string>();
    }
    else {
        nmap = rh_map<int, int>(DEFAULT_CAPACITY, mlf);
        rmap = rh_map<double, double>(DEFAULT_CAPACITY, mlf);
        smap = rh_map<std::string, std::string>(DEFAULT_CAPACITY, mlf);
    }
    std::cout << "SYSTEM: TEST SECTION" << std::endl;
    while (true) {
        std::cout << "   LOG: select action to execute: insert (I) / erase (E) / find (F) / exit (X) -> ";
        std::cin >> input;
        switch (input) {
        case 'i':
        case 'I': test_insert(); break;
        case 'e':
        case 'E': test_erase(); break;
        case 'f':
        case 'F': test_find(); break;
        }
        if (input == 'x' || input == 'X') {
            break;
        }
        std::cout << "   LOG: continue? YES (Y) / NO (N) -> "; std::cin >> input;
        if (input == 'y' || input == 'Y') {
            std::cout << "SYSTEM: clear tables? integer (I) / real (R) / string (S) / all (A) / none (N) -> ";
            std::cin >> input;
            switch (input) {
            case 'i':
            case 'I': nmap.clear(); break;
            case 'r':
            case 'R': rmap.clear(); break;
            case 's':
            case 'S': smap.clear(); break;
            case 'a':
            case 'A': {
                nmap.clear();
                rmap.clear();
                smap.clear();
                break;
            }
            }
        }
        else {
            break;
        }
    }
    return 0;
}