#include <iostream>

constexpr double PI = 3.141592653589793238463;

class Figure
{
protected:
    double m_x;
    double m_y;
public:
    explicit Figure(double t_x = 0, double t_y = 0)
        : m_x(t_x), m_y(t_y)
    {
    }
    virtual double area() = 0;
    virtual void getName() = 0;
};

class Rectangle: public Figure
{
public:
    explicit Rectangle(double t_x = 0, double t_y = 0)
        : Figure(t_x, t_y)
    {
    }
    double area() override
    {
        return (m_x * m_y);
    }
    void getName() override
    {
        std::cout << "figure name : Rectangle\n";
    }
};

class Circle: public Figure
{
public:
    explicit Circle(double t_x = 0, double t_y = 0)
        : Figure(t_x, 0)
    {
    }
    double area() override
    {
        return (m_x * m_x * PI);
    }
    void getName() override
    {
        std::cout << "figure name : Circle\n";
    }
};

class FigureList: public Figure
{
private:
    int m_quantity;

    struct Node
    {
        Figure *figure;
        Node *next;
    } *m_head;

    void push(Node **head, Figure *a_newFigure)
    {
        Node *newNode = new Node();
        Node *last = *head;
        newNode->figure = a_newFigure;
        newNode->next = nullptr;
        if (*head == nullptr)
        {
            *head = newNode;
            return;
        }
        while (last->next != nullptr)
            last = last->next;
        last->next = newNode;
    };

    void printList(Node *head)
    {
        while (head != nullptr)
        {
            head->figure->getName();
            std::cout << "area : " << head->figure->area();
            std::cout << "\n\n";
            head = head->next;
        }
    }
public:
    double area() override
    {
        double listArea{};
        Node* temporary = m_head;
        while (temporary != nullptr)
        {
            listArea += temporary->figure->area();
            temporary = temporary->next;
        }
        std::cout << "list area is : " << listArea << std::endl;
        return listArea;
    }

    void getName() override
    {
        std::cout << "list is an abstract source of figures!\n";
    }

    FigureList()
        : m_quantity{}, m_head{nullptr}
    {
    }

    FigureList(const FigureList& a_other)
        : m_quantity{a_other.m_quantity}
    {
        m_head = a_other.m_head;
    }

    void append(Figure *t_newFigure)
    {
        push(&m_head, t_newFigure);
    }
    //output function (name of figure and it's area)
    //global list area
    void check()
    {
        printList(m_head);
    }
    ~FigureList()
    {
        Node* current = m_head;
        Node* next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            free(current);
            current = next;
        }
        m_head = nullptr;
    }
};

int main()
{
    Rectangle fig1{1, 2};
    Circle fig2{1};
    std::cout << fig1.area() << std::endl;
    std::cout << fig2.area() << std::endl;
    FigureList list1{};
    list1.append(&fig1);
    list1.append(&fig2);
    list1.check();
    list1.getName();
    list1.area();
    FigureList list2 = list1;
    list2.check();
    return 0;
}
