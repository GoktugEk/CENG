#include <iostream>
#include <string>
#include <vector>
#include "owner.h"

using namespace std;

Owner::Owner()
{
}

Owner::Owner(const string &name, float balance)
{
    this->name = name;
    this->balance = balance;
}

void Owner::print_info()
{
}

string &Owner::get_name()
{
    return this->name;
}

void Owner::add_property(Property *property)
{
    this->properties.push_back(property);
}

bool doesHave(std::vector<Property *> properties, Property* property){
    for (unsigned i = 0; i < properties.size(); ++i) {
        if (properties[i] == property){
            return true;
        }
    }
    return false;
}


void Owner::buy(Property *property, Owner *seller)
{
    std::cout << "[BUY] Property: " << property->get_name() <<  " Value: " << property->valuate() << "$ " << seller->get_name() << "--->" << this->name << '\n';
    if (!doesHave(seller->properties,property)){
        std::cout << "[ERROR] Transaction  on  unowned  property\n";
    }
    else if (this->balance >= property->valuate())
    {

        this->properties.push_back(property);
        property->set_owner(this);
        this->balance -= property->valuate();
        seller->balance += property->valuate();
        int n;
        for (unsigned i = 0; i < seller->properties.size(); ++i) {
            if (seller->properties[i] == property){
                n = i;
            }
        }

        seller->properties.erase(seller->properties.begin()+n);

    }
    else if (this->balance < property->valuate()){
        std::cout << "[ERROR] Unaffordable  property\n";
    }


}

void Owner::sell(Property *property, Owner *owner)
{
    std::cout << "[SELL] Property: " << property->get_name() <<  " Value: " << property->valuate() << "$ " << this->get_name() << "--->" << owner->name << '\n';
    if (!doesHave(this->properties,property)){
        std::cout << "[ERROR] Transaction  on  unowned  property\n";
    }
    else if (owner->balance >= property->valuate()){

        owner->add_property(property);
        property->set_owner(owner);
        owner->balance -= property->valuate();
        this->balance += property->valuate();
        int n;
        for (unsigned i = 0; i < this->properties.size(); ++i) {
            if (this->properties[i] == property){
                n = i;
            }
        }
        this->properties.erase(this->properties.begin()+n);

    }
    else{
        std::cout << "[ERROR] Unaffordable  property\n";
    }
}

void Owner::list_properties()
{
    std::cout << "Properties of " << this->name << ':' <<'\n';
    std::cout << "Balance: " << this->balance << '$' << '\n';

    for (unsigned i = 0; i < this->properties.size(); ++i) {
        std::cout << i+1 <<". " << properties[i]->get_name() << '\n';
    }
}