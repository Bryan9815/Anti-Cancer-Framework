#include "SceneNode.h"

Node::Node()
{
}

Node::Node(EntityBase* Entity)
{
    this->Entity = Entity;
}

Node::~Node()
{
    delete Entity;
    while (ChildrenList.size() > 0)
    {
        Node* temp = ChildrenList.back();
        delete temp;
        temp = NULL;
        ChildrenList.pop_back();
    }
}

void Node::Init()
{

}

void Node::Update(double dt)
{

}

void Node::Set_Parent(Node* Parent_Node)
{
    Parent = Parent_Node;
}

EntityBase* Node::Get_Entity()
{
    return Entity;
}

Node* Node::Get_Parent()
{
    return Parent;
}

vector<Node*>& Node::Get_ChildrenList()
{
    return ChildrenList;
}

Node* Node::Add_ChildEntity(EntityBase* Child_Entity)
{
    Node* child_node = Create::node(Child_Entity);
    ChildrenList.push_back(child_node);
}

Node* Node::Add_ChildNode(Node* Child_Node)
{
    ChildrenList.push_back(Child_Node);
}


bool Node::Delete_Child(EntityBase* Child_Entity)
{
    if (this->Get_Entity() == Child_Entity)
    {
        if (this->ChildrenList.size() != 0)
            this->Delete_AllChildren();
        return true;
    }
    vector<Node*>::iterator it;
    for (it = ChildrenList.begin(); it != ChildrenList.end(); it++)
    {
        if ((*it)->Delete_Child(Child_Entity))
        {
            Node* temp = (*it);
            delete temp;            
            temp = NULL;
            ChildrenList.erase(it);
            break;
        }
    }
    return false;
}

bool Node::Delete_ChildNode(Node* Child_Node)
{

}

bool Node::Delete_AllChildren()
{
    while (this->ChildrenList.size() != 0)
    {
        Node* temp = ChildrenList.back();
        if (temp->Delete_AllChildren())
        {
            delete temp;
            temp = NULL;
            ChildrenList.pop_back();
        }
    }
    return true;
}

Node* Node::Detach_Child(EntityBase* Child_Entity)
{
    vector<Node*>::iterator it;
    for (it = ChildrenList.begin(); it != ChildrenList.end(); it++)
    {
        if ((*it)->Get_Entity() == Child_Entity)
        {
            Node* temp = (*it);
            ChildrenList.erase(it);
            return temp;
        }
    }
    return NULL;
}

Node* Node::Detach_ChildNode(Node* Child_Node)
{
    vector<Node*>::iterator it;
    for (it = ChildrenList.begin(); it != ChildrenList.end(); it++)
    {
        if ((*it) == Child_Node)
        {
            Node* temp = (*it);
            ChildrenList.erase(it);
            return temp;
        }
    }
    return NULL;
}

bool Node::Detach_AllChildren()
{

}

Node* Node::Find_ChildEntity(EntityBase* Child_Entity)
{
    vector<Node*>::iterator it;
    for (it = ChildrenList.begin(); it != ChildrenList.end(); it++)
    {
        if ((*it)->Get_Entity() == Child_Entity)
        {
            Node* temp = (*it);
            return temp;
        }
    }
    return NULL;
}
Node* Node::Find_ChildNode(Node* Child_Entity)
{
    vector<Node*>::iterator it;
    for (it = ChildrenList.begin(); it != ChildrenList.end(); it++)
    {
        if ((*it) == Child_Entity)
        {
            Node* temp = (*it);
            return temp;
        }
    }
    return NULL;
}

int Node::Get_NumberOfChilren()
{
    return ChildrenList.size();
}

void Node::Render(void)
{
    if (!Parent)
    {
        Entity->Render();
        return;
    }
    Vector3 temp = Parent->Get_Entity()->GetPosition() + Entity->GetPosition();
    Vector3 original = Entity->GetPosition();
    Entity->SetPosition(temp);
    Entity->Render();
    Entity->SetPosition(original);
    
}

Node* Create::node(EntityBase* Entity)
{
    Node* temp = new Node(Entity);
    return temp;
}