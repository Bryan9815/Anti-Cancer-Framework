#include "SceneGraph.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

CSceneGraph::CSceneGraph(void)
: ID(0)
, theRoot(NULL)
{
    theRoot = new Node();
    // Assign the first ID to the root. Default is 0
    //theRoot->SetID(this->GenerateID());
}

CSceneGraph::~CSceneGraph()
{
}

void CSceneGraph::Destroy()
{
    if (theRoot)
    {
        theRoot->Delete_AllChildren();
        delete theRoot;
    }
    Singleton<CSceneGraph>::Destroy();
}

Node* CSceneGraph::GetRoot()
{
    return theRoot;
}

// Add a Node to this Scene Graph
Node* CSceneGraph::AddNode(EntityBase* theEntity)
{
    Node* aNewSceneNode = theRoot->Add_ChildEntity(theEntity);
    //	aNewSceneNode->SetID(this->GenerateID());
    return aNewSceneNode;
}

// Delete a Node from this Scene Graph using the pointer to the node
bool CSceneGraph::DeleteNode(EntityBase* theEntity)
{
    return theRoot->Delete_Child(theEntity);
}

// Delete a Node from this Scene Graph using its ID
//bool CSceneGraph::DeleteNode(const int ID)
//{
//    return theRoot->DeleteChild(ID);
//}

// Detach a Node from this Scene Graph using the pointer to the node
Node* CSceneGraph::DetachNode(Node* theNode)
{
    return theRoot->Detach_ChildNode(theNode);
}

// Detach a Node from this Scene Graph using its ID
//Node* CSceneGraph::DetachNode(const int ID)
//{
//    //return theRoot->DetachChild(ID);
//}

// Get a Node using the pointer to the node
Node* CSceneGraph::GetNode(EntityBase* theEntity)
{
    return theRoot->Find_ChildNode(theEntity);
}

// Get a Node using its ID
//Node* CSceneGraph::GetNode(const int ID)
//{
//    return theRoot->GetEntity(ID);
//}

// Return the number of nodes in this Scene Graph
int CSceneGraph::GetNumOfNode(void)
{
    return theRoot->Get_NumberOfChilren();
}

// Generate an ID for a Scene Node
//int CSceneGraph::GenerateID(void)
//{
//    // Return the ID and increment the value by 1
//    return ID++;
//}

// Update the Scene Graph
void CSceneGraph::Update(double dt)
{
    theRoot->Update(dt);
}
// Render the Scene Graph
void CSceneGraph::Render(void)
{
    theRoot->Render();
}

// PrintSelf for debug purposes
void CSceneGraph::PrintSelf(void)
{
    //theRoot->PrintSelf();
}
