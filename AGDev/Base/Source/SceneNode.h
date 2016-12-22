#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Vector3.h"
#include <vector>
#include "EntityBase.h"
using namespace std;
class Node
{
public:
    Node();
    Node(EntityBase* Entity);
    ~Node();

    void Init();
    void Update(double dt);

    void Set_Parent(Node* Parent_Node);

    EntityBase* Get_Entity();
    Node* Get_Parent();
    vector<Node*>& Get_ChildrenList();

    Node* Add_ChildEntity(EntityBase* Child_Entity);
    Node* Add_ChildNode(Node* Child_Node);
    

    bool Delete_Child(EntityBase* Child_Entity);
    bool Delete_ChildNode(Node* Child_Node);
    bool Delete_AllChildren();

    bool Detach_Child(EntityBase* Child_Entity);
    bool Detach_ChildNode(Node* Child_Node);
    bool Detach_AllChildren();
    
    void Render(void);
private:
    Node* Parent;
    vector<Node*> ChildrenList;
    EntityBase* Entity;

};

namespace Create
{
    Node* node(EntityBase* Entity);
}

#endif