#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QVariantMap>
#include <QMetaObject>
#include <QMetaProperty>

#include <iostream>

#include "Person.hpp"


int main(int argc, char *argv[])
{   
    QCoreApplication a(argc, argv);
    Person tom;
    tom.SetName("Tom");
    tom.SetAge(24);
    QList<QVariant> children = tom.GetChildren();
    children.append("Jenny");
    children.append("Sandy");
    children.append("Maven");
    tom.SetChildren(children);
    
    QList<QVariant> cards = tom.GetCards();
    cards.append(2);
    cards.append(5);
    cards.append(11);
    cards.append(8);
    cards.append(6);
    tom.SetCards(cards);
    
    ChineseFamily & fm = tom.GetFamilyRef();
    fm.SetAddress("NY NW STR #228");
    QList<QVariant> members;
    members.push_back("James");
    members.push_back("Geoger");
    members.push_back("Bayers");
    members.push_back("Lucy");
    fm.SetMember(members);
    fm.SetSingleParent(false);
    
    QList<ChineseFamily> & upper = tom.GetUpperRef();
    upper.push_back(fm);
    upper.push_back(fm);
    
    // serialization and deserialization
    QByteArray data = tom.serialize();
    
    if(!tom.ok())
        std::cout<<"Serialize ERROR!"<<std::endl;
    else
        std::cout<<"Serialize OK!"<<std::endl;
    
    std::cout<<data.toStdString().c_str()<<std::endl;
    
    // parser
    tom.deserialize(data);
    
    if(!tom.ok())
        std::cout<<"Deserialize ERROR!"<<std::endl;
    else
        std::cout<<"Deserialize OK!"<<std::endl;
    
    std::cout<<tom.GetAge()<<std::endl;
    
    return a.exec();
}
