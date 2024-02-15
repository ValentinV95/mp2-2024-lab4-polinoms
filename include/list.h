template <class T>
class List
{
private:

    class Node
    {
    public:
        T data;
        Node* next;
        Node(const T& _data = {}, Node* _next = nullptr) : data(_data), next(_next) {}
        Node(const Node& node) : data(node.data), next(node.next) {}
    };

    Node* ptr(size_t pos) const
    {
        Node* node = head;
        for (size_t n = 0; n != pos; node = node->next, n++);

        return node;
    }

    Node* split(Node*& node)
    {
        if (node == nullptr) throw std::invalid_argument("node shouldn't be equal to nullptr");

        Node* tmp = node;
        int len = 0;
        while (tmp!=nullptr) { tmp = tmp->next; len++; }
        
        Node* cur = node;
        for (int i = 0; i < len / 2 - 1; i++)
            cur = cur->next;

        Node* res = cur->next;
        cur->next = nullptr;
        return res;
    }

    Node* merge(Node* first, Node* second, int (*comparator) (const T&, const T&) )
    {
        if (first == nullptr || second == nullptr) throw std::invalid_argument("first and second shouldn't be equal to nullptr");

        Node dummy(T{}, nullptr);
        Node* cur = &dummy;

        while (first!=nullptr && second!=nullptr) {
            Node* max;
            if (comparator(first->data, second->data)>0) 
            {
                max = first;
                first = first->next;
            }
            else 
            {
                max = second;
                second = second->next;
            }
            cur = cur->next = max;
        }
        cur->next = first ? first : second;
        return dummy.next;
    }

    Node* sort(Node*& first, int (*comparator) (const T&, const T&))
    {
        if (first == nullptr || first->next == nullptr) return first;

        Node* second = split(first);

        first = sort(first, comparator);
        second = sort(second, comparator);

        first = merge(first, second, comparator);

        return first;
    }

    Node* head;
    Node* tail;
    size_t size;

public:

    List() : head(nullptr), tail(nullptr), size(0) {}

    List(const List& l): head(nullptr), tail(nullptr), size(l.size)
    {
        if (!l.isEmpty())
        {
            Node* node = head = new Node(*l.head);
            for (; node->next != nullptr; node = node->next)
                node->next = new Node(*node->next);
            
            tail = node;
        }
    }

    ~List()
    {
        Node* tmp;
        while (!isEmpty())
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
        size = 0; head = tail = nullptr;
    }

    void swap(List& lhs, List& rhs) noexcept
    {
        std::swap(lhs.head, rhs.head);
        std::swap(lhs.tail, rhs.tail);
        std::swap(lhs.size, rhs.size);
    }

    List& operator=(const List& l)
    {
        if (this != &l)
        {
            List tmp(l);
            swap(*this, tmp);
        }
        return *this;
    }

    class iterator
    {
    private:
        Node* node;

    public:

        iterator() : node(nullptr) {}

        iterator(Node* _node) : node(_node) {}

        iterator& operator++() 
        {
            if (node != nullptr) node = node->next;
            return *this; 
        }
        
        T& operator*() { return node->data; }

        bool operator==(const Node* _node) const { return node == _node; }

        bool operator!=(const Node* _node) const { return node != _node; }

        Node* get_node_ptr() const noexcept { return node; }

    };

    Node* begin() const { return head; }

    Node* end() const { return nullptr; }

    size_t get_size() const noexcept { return size; }

    bool isEmpty() const noexcept { return head == nullptr; }

    void push_front(const T& val)
    {
        Node* node = new Node(val, head);
        head = node;
        if (tail == nullptr) tail = head;
        size++;
    }

    void pop_front()
    {
        if (isEmpty()) throw std::exception("list is empty");

        Node* node = head->next;
        delete head;
        head = node;

        if (isEmpty()) tail = head;
        size--;
    }

    void push_back(const T& val)
    {
        Node* node = new Node(val);
        if (tail != nullptr) tail->next = node;
        else head = node;

        tail = node;
        size++;
    }

    void ins_after(size_t pos, const T& val)
    {
        if (pos > size - 1) throw std::out_of_range("too large pos");

        Node* node = head;
        for (size_t i = 0; i != pos; node = node->next, i++);

        Node* node2 = new Node(val, node->next);
        node->next = node2;

        if (pos + 1 == size) tail = node2;
        size++;
    }

    void ins_after(Node* node, const T& val, const bool& secure)
    {
        if (!node) throw std::invalid_argument("node shoudn't be equal to nullptr");
        if (secure)
        {
            bool flag1=false;
            for (Node* cur = head; cur != nullptr; cur = cur->next)
                if (cur == node) flag1 = true;
            if (!flag1) throw std::invalid_argument("Node* node isn't from this list");
        }

        Node* node2 = new Node(val, node->next);
        node->next = node2;

        if (node2->next == nullptr) tail = node2;
        size++;
    }

    void del_after(size_t pos)
    {
        if (pos > size - 2) throw std::out_of_range("pos cannot be greater than size - 2");

        Node* node = head;
        for (size_t i = 0; i != pos; node = node->next, i++);
        
        Node* next = node->next->next;

        delete node->next;
        node->next = next;

        if (node->next == nullptr) tail = node;
        size--;
    }

    void del_after(Node* node, const bool& secure)
    {
        if (!node || !node->next) throw std::invalid_argument("node cannot be last in list or equal to nullptr");

        if (secure)
        {
            bool flag1 = false;
            for (Node* cur = head; cur != nullptr; cur = cur->next)
                if (cur == node) flag1 = true;
            if (!flag1) throw std::invalid_argument("Node* node isn't from this list");
        }

        Node* next = node->next->next;

        delete node->next;
        node->next = next;

        if (node->next == nullptr) tail = node;
        size--;
    }
    
    bool operator==(const List& l) const
    {
        if (this != &l) 
        {
            if (size != l.size) return false;

            Node* node1 = head;
            Node* node2 = l.head;
            for (; node1 != nullptr; node1 = node1->next, node2 = node2->next)
                if (node1->data != node2->data) return false;
        }
        
        return true;
    }
    
    bool operator!=(const List& l) const { return !(*this == l); }

    void merge_sort(int (*comparator) (const T&, const T&), size_t begin, size_t end)
    { 
        if ((begin > size - 1) || end > (size - 1)) throw std::invalid_argument("begin and end should be less than (size - 1)");

        if (begin >= end) throw std::invalid_argument("begin should be less than end");

        Node* start = ptr(begin); 
        Node* start_prev = nullptr; 
        
        Node* finish = ptr(end);
        Node* finish_next = nullptr;

        if (begin) start_prev = ptr(begin - 1);
        if (end != size - 1) { finish_next = finish->next; finish->next = nullptr;}
        

        if (!begin) head = sort(start, comparator);
        else start_prev->next = sort(start, comparator);

        if (end != size - 1) 
        {
            Node* tmp = head;
            for (; tmp->next != nullptr; tmp = tmp->next) {}
            tmp->next = finish_next;
        }

        if (end == size - 1) 
        {
            Node* tmp = head;
            for (; tmp->next!=nullptr; tmp = tmp-> next){}

            tail = tmp;
        }
    }

    void print() 
    { 
        for (Node* cur = head; cur != nullptr; cur = cur->next)
            std::cout << cur->data << " ";

        std::cout << std::endl;
    }
};
