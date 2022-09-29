#include <stdio.h>
#include <stdlib.h>

struct coffee {
    int id;
    char property;
};

const unsigned char regular = 1<<0;
const unsigned char espresso = 1<<1;
const unsigned char double_espresso = 1<<2;
const unsigned char milk = 1<<3;
const unsigned char cream = 1<<4;
const unsigned char soy_milk = 1<<5;
const unsigned char sugar = 1<<6;
const unsigned char sweetener = 1<<7;

void set_coffee_property(struct coffee* c, const unsigned char property)
{
    //setting the bit
    c->property = c->property | 1 << property;
}

void unset_coffee_property(struct coffee* c, const unsigned char property)
{
   //checking if the bit is set (=1)
   if ( (c->property & 1 << property) != 0)
        c->property = c->property ^ 1 << property;
}

int main()
{
    struct coffee c;

    //creating a regular coffee with milk and sugar
    set_coffee_property(&c,regular);
    set_coffee_property(&c, milk);
    set_coffee_property(&c, sugar);

    printf("%c", c.property);

    return 0;
}
