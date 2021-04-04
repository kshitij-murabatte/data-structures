class LinkedList
{
public:
    int data;
    LinkedList *next;
    LinkedList(int input)
    {
        data = input;
        next = NULL;
    }
    ~LinkedList()
    {
        delete next;
    }
};

LinkedList *rear = NULL;

LinkedList *Last()
{
    return rear;
}

void Add(const int value, LinkedList *&head)
{
    LinkedList * temp = new LinkedList(value);
    if (head == NULL)
    {
        head = temp;
    }
    (*temp).next = head;
    head = temp;
}

void Push(const int value, LinkedList *&head)
{
    LinkedList *temp = new LinkedList(value);
    if (head == NULL)
    {
        head = temp;
        rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void Display(LinkedList *temp)
{
    std::cout << '\n';
    while (temp != NULL)
    {
        std::cout << (*temp).data << " ";
        temp = (*temp).next;
    }
}

LinkedList *Reverse(LinkedList *head)
{
    LinkedList *prev, *temp;
    temp = head;
    prev = NULL;
    
    while (head != NULL)
    {
        temp = head->next;
        head->next = prev;
        prev = head;
        head = temp;
    }
    return prev;
}