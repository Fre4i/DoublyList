#include <iostream>

using namespace std;

//Исключения
struct FindElementException : public std::exception {
    const char* what() const throw() {
        return "Element doesn't find";
    }
};

struct Node {
    string book_num;
    unsigned group_num;
    unsigned mark;

    Node* next;
    Node* prev;

    Node(string _book_num, unsigned _group_num, unsigned _mark) :
        book_num(_book_num), group_num(_group_num), mark(_mark), 
        next(nullptr), prev(nullptr) {}

    bool equals(const Node* p) {
        return this->book_num == p->book_num &&
            this->group_num == p->group_num &&
            this->mark == p->mark;
    }
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    bool is_empty() {
        return first == nullptr;
    }
    void push_back(string _book_num, unsigned _group_num, unsigned _mark) {
        Node* p = new Node(_book_num, _group_num, _mark);
        //Инициализация списка 1 элементом
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        Node* t = last;
        last = p;
        last->prev = t;
    }
    void remove(string _book_num, unsigned _group_num, unsigned _mark) {
        Node* _val = new Node(_book_num, _group_num, _mark);
        if (is_empty()) {
            return;
        }
        if (first->equals(_val)) {
            remove_first();
            return;
        } else if (last->equals(_val)) {
            remove_last();
            return;
        }

        Node* slow = first;
        Node* fast = first->next;
        while (fast && !fast->equals(_val)) {
            fast = fast->next;
            slow = slow->next;
        }

        if (!fast) {
            cout << "This element does not exist" << endl;
            return;
        }

        slow->next = fast->next;
        fast->next->prev = slow;
        delete fast;
    }
    void remove_first() {
        if (is_empty()) 
            throw FindElementException();
        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
            return;
        }

        Node* new_first = first->next;
        delete first;
        first = new_first;
    }
    void remove_last() {
        if (is_empty())
            throw FindElementException();
        if (first == last) {
            delete last;
            first = nullptr;
            last = nullptr;
            return;
        }

        Node* new_last = last->prev;
        new_last->next = nullptr;
        delete last;
        last = new_last;
    }
    void print() {
        if (is_empty())
            return;

        Node* p = first;
        while (p) {
            cout << p->book_num << ' ' << p->group_num << ' ' << p->mark << '\n';
            p = p->next;
        }
        cout << endl;
    }
    void print_reverse() {
        if (is_empty())
            return;

        Node* p = last;
        while (p) {
            cout << p->book_num << ' ' << p->group_num << ' ' << p->mark << '\n';
            p = p->prev;
        }
        cout << endl;
    }
    Node* find(string _book_num, unsigned _group_num, unsigned _mark) {
        Node* s = new Node(_book_num, _group_num, _mark);
        Node* p = first;
        while (p && p != s)
            p = p->next;
        return (p && p == s) ? p : nullptr;
    }
    //Вставка узла перед узлом с таким же ключом
    void insert(string _book_num, unsigned _group_num, unsigned _mark) {
        if (is_empty())
            return;
        
        Node* _val = new Node(_book_num, _group_num, _mark);
        Node* iter = first;
        Node* max = first;
        while (_val->book_num != iter->book_num || iter == nullptr) {
            if (max->book_num < iter->book_num) {
                max = iter;
            }
            iter = iter->next;
        }
        if (iter == nullptr) {
            _val->next = max;
            _val->
        }
    }
};



int main()
{
    list L;

    L.push_back("1AAA1", 1, 5);
    L.push_back("2BBB2", 2, 5);
    L.push_back("3CCC3", 3, 5);
    L.push_back("4DDD4", 4, 5);
    L.push_back("5III5", 5, 5);

    L.print();

    L.remove("2BBB2", 2, 5);

    L.print();
    L.print_reverse();

    return 0;
}