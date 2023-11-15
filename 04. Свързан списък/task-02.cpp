#include <iostream>
#include "list.hpp"

template <typename T>
class Set {
    List<T> storage;

    typename List<T>::Iterator find_previous(const T& value) const {
        typename List<int>::Iterator i = storage.begin(), previous = storage.begin();
        while(i != storage.end() && i.value() < value) {
            previous = i;
            ++i;
        }

        if(i == storage.end()) return storage.end();
        return previous;
    }

public:
    void insert(const T& value) {
        if (empty() || storage.front() > value) {
            storage.push_front(value);
            return; 
        }
        if (storage.back() < value) {
            storage.push_back(value);
            return;
        }

        typename List<int>::Iterator previous = find_previous(value);
        if (previous.next().value() == value) throw(std::logic_error("Already in set!"));
        storage.insert_after(value, previous);
    }

    void remove(const T& value) {
        if (empty()) throw(std::logic_error("Set is empty!"));

        if (storage.front() == value) {
            storage.pop_front();
            return; 
        }

        typename List<int>::Iterator previous = find_previous(value);

        if (previous.next().value() != value) throw(std::logic_error("Not in set!"));
        storage.delete_after(previous);
    }
    
    bool empty() const {
        return storage.empty();
    }

    bool include(const T& value) const {
        for (typename List<T>::Iterator i = storage.begin(); i != storage.end(); ++i) {
            if (i.value() == value) return true;
        }
        return false;
    }

    Set<T> operator+(const Set<T>& other) const {
        if(this->empty()) return other; 
        if(other.empty()) return *this;

        Set<T> result = *this;
        for(typename List<T>::Iterator i = other.storage.begin(); i != other.storage.end(); ++i) {
            const T& value = i.value();
            if(!result.include(value)) {
                result.insert(value);
            }
        }

        return result;
    }

    Set<T> operator-(const Set<T>& other) const {
        if(this->empty()) throw(std::logic_error("Set is empty!"));
        if(other.empty()) return *this;

        Set<T> result = *this;
        for(typename List<T>::Iterator i = other.storage.begin(); i != other.storage.end(); ++i) {
            const T& value = i.value();
            if(result.include(value)) {
                result.remove(value);
            }
        }

        return result;
    }
};


int main () {
    Set<int> s;
    s.insert(7);                // empty set
    s.insert(5);                // at the front
    s.insert(8);                // at the back
    s.insert(6);                // at the middle

    std::cout << std::boolalpha << s.include(5) << std::endl;
    std::cout << std::boolalpha << s.include(6) << std::endl;
    std::cout << std::boolalpha << s.include(7) << std::endl;
    std::cout << std::boolalpha << s.include(8) << std::endl;
    std::cout << std::boolalpha << s.include(9) << std::endl;

    try {
        s.insert(5);
    } catch (...) {
        std::cout << "Already in set!" << std::endl;
    }


    s.remove(6);
    s.remove(8);
    std::cout << std::boolalpha << s.include(6) << std::endl;
    std::cout << std::boolalpha << s.include(8) << std::endl;

    
    try {
        s.remove(6);
    } catch (...) {
        std::cout << "Not in set!" << std::endl;
    }

    Set<int> e;                             // empty set
    try {
        e.remove(6);
    } catch (...) {
        std::cout << "Empty!" << std::endl;
    }

    e.insert(2);
    e.insert(13);
    e.insert(5);
    Set<int> r = s + e;

    std::cout << std::boolalpha << r.include(2) << std::endl;
    std::cout << std::boolalpha << r.include(5) << std::endl;
    std::cout << std::boolalpha << r.include(7) << std::endl;
    std::cout << std::boolalpha << r.include(8) << std::endl;
    std::cout << std::boolalpha << r.include(9) << std::endl;
    std::cout << std::boolalpha << r.include(13) << std::endl;

    Set<int> m = s - e;
    std::cout << std::boolalpha << m.include(5) << std::endl;
    std::cout << std::boolalpha << m.include(7) << std::endl;
    std::cout << std::boolalpha << m.include(8) << std::endl;

    return 0;
}