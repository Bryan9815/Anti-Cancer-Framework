#ifndef SCENE_NODE_H
#define SCENE_NODE_H

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

    Node* Detach_Child(EntityBase* Child_Entity);
    Node* Detach_ChildNode(Node* Child_Node);
    bool Detach_AllChildren();

    Node* Find_ChildEntity(EntityBase* Child_Entity);
    Node* Find_ChildNode(Node* Child_Entity);

    int Get_NumberOfChilren();
    
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