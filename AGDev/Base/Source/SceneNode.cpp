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