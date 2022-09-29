/*
CH-230-A
creature.cpp
Faraz Ahmad
fahmad@jacobs.university.de
 */
#include <iostream>
using namespace std;

//PARTENT CLASS
class Creature
{
public:
    Creature();
    void run() const;

protected:
    int distance;
};

Creature::Creature() : distance(10)
{
    cout << "Creating a Creature.\n";
}

void Creature::run() const
{
    cout << "running " << distance << " meters!\n";
}

//CHILD CLASSS
class Wizard : public Creature
{
public:
    Wizard();
    void hover() const;

private:
    int distFactor;
};

Wizard::Wizard() : distFactor(3)
{
    cout << "\nCreating a Wizard.\n";
}

void Wizard::hover() const
{
    cout << "hovering " << (distFactor * distance) << " meters!\n";
}
//CHILD CLASS
class Dementor : public Creature
{
private:
    string feed;

public:
    Dementor();
    ~Dementor();
    void eats();
};

Dementor::Dementor()
{
    cout << "\nCreating a dementor.\n";
    feed = "Harry Potter";
}
void Dementor::eats()
{
    cout << "feeding on flesh of " << feed << endl;
}
Dementor::~Dementor()
{
}
//CHILD CLASS
class Elf : public Creature
{
private:
    bool isSlave;
    string name;

public:
    Elf();
    void setName(string name);
    ~Elf();
    void status();
};

Elf::Elf()
{
    cout << "\nCreating an elf.\n";
    isSlave = false;
}
void Elf::setName(string newname)
{
    name = newname;
}

Elf::~Elf()
{
}
void Elf::status()
{
    if (isSlave)
    {
        cout << name << " is a slave\n";
    }
    else
    {
        cout << name << " is free\n";
    }
}

int main()
{
    Creature c;
    c.run();

    //creating creatures

    Wizard w;
    w.run();
    w.hover();

    Dementor d;
    d.run();
    d.eats();

    Elf e;
    e.setName("Dobby");
    e.run();
    e.status();

    return 0;
}