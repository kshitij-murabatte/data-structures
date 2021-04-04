class Circular
{    
public:
    int data;
    Circular *next;
    Circular(int);
    ~Circular();
};

Circular *rear = nullptr;

Circular::Circular(const int value)
{
    data = value;
    next = this;
}

Circular::~Circular()
{
    delete next;
}

Circular *Rear()
{
    return rear;
}

void Display(Circular *head)
{
    std::cout << '\n'; 
    if (head == nullptr)
    {
        return;
    }
    if (head->next == head)
    {
        std::cout << head->data << ' ';
        return;
    }
    std::cout << head->data << ' ';
    head = head->next;
    while (head != rear->next)
    {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
}

Circular *Search(const int value, Circular *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    if (head->data == value)
    {
        return head;
    }
    Circular *save = head;
    rear->next = nullptr;
    while (head != nullptr)
    {
        if (head->data == value)
        {
            rear->next = save;
            return head;
        }
        head = head->next;
    }
    rear->next = save;
    return nullptr;
}

void Push(const int value, Circular *&head)
{
    Circular *temp = new Circular(value);
    if (head == nullptr)
    {
        head = rear = temp;
        return;
    }
    rear->next = temp;
    temp->next = head;
    rear = temp;    
}

void Add(const int value, Circular *&head)
{
    Circular *temp = new Circular(value);
    if (head == nullptr)
    {
        head = rear = temp;
        return;
    }
    rear->next = temp;
    temp->next = head;
    head = temp;
}

void Pop(Circular *&head)
{
    if (head == nullptr)
    {
        return;
    }
    if (head->next == head)
    {
        delete head;
        head = nullptr;
        return;
    }
    
    Circular *temp = head;
    while (temp->next != rear)
    {
        temp = temp->next;
    }
    rear->next = nullptr;
    delete rear;
    temp->next = head;
    rear = temp;    
}

void Dequeue(Circular *&head)
{
    if (head == nullptr)
    {
        return;
    }
    if (head->next == head)
    {
        head = nullptr;
        return;
    }
    
    Circular *temp = head;
    rear->next = head->next;
    head = head->next;
    temp->next = nullptr;
    delete temp;
}

void Delete(Circular *&head)
{
    if (head->next == head)
    {
        head->next = nullptr;
        delete head;
    }
    Circular *temp = head->next;
    head->next = nullptr;
    delete temp;
    head = nullptr;
}