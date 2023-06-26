#include <iostream>
#include "property.h"
#include "owner.h"

using namespace std;

Property::Property()
{
}

Property::Property(const string &property_name, int area, Owner *owner)
{
    this->property_name = property_name;
    this->area = area;
    this->owner = owner;
    owner->add_property(this);
}

void Property::set_owner(Owner *owner)
{
    this->owner = owner;
}

float Property::valuate()
{

}

string &Property::get_name()
{
    return this->property_name;
}

void Property::print_info()
{
    if (this->owner != NULL){
        std::cout << this->property_name << " (" << this->area <<" m2) Owner: " << this->owner->get_name() << '\n';
    }
    else{
        std::cout << this->property_name << " (" << this->area <<" m2) Owner: No owner" << '\n';
    }
}