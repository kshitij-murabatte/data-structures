class DoubleList
{
public:
    int data;
    DoubleList *next;
    DoubleList *prev;
    DoubleList(int input)
    {
        data = input;
        next = nullptr;
        prev = nullptr;
    }
    ~DoubleList()
    {
        delete next;
    }
};

DoubleList *rear = nullptr;

void Add(const int value, DoubleList *&head)
{
    DoubleList * temp = new DoubleList(value);
    if (head == nullptr)
    {
        head = rear = temp;
        return;
    }
    (*temp).next = head;
    head->prev = temp;
    head = temp;
}

void Push(const int value, DoubleList *&head)
{
    DoubleList *temp = new DoubleList(value);
    if (head == nullptr)
    {
        head = temp;
        rear = temp;
        return;
    }
    rear->next = temp;
    temp->prev = rear;
    rear = temp;
}

void Display(DoubleList *temp)
{
    std::cout << '\n';
    while (temp != nullptr)
    {
        std::cout << (*temp).data << " ";
        temp = (*temp).next;
    }
}

DoubleList *Reverse(DoubleList *head)
{
    DoubleList *temp = nullptr, *plus = head;
    while (head != nullptr)
    {
        plus = plus->next;
        head->next = temp;
        head->prev = plus;
        temp = head;
        head = plus;
    }
    return temp;
}
