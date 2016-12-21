#include "SceneEditor.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "KeyboardController.h"
#include "MouseController.h"
/*#include "SpatialPartition.h"

#define TIME_BETWEEN_INPUT 0.3f
#define POINTER_DISTANCE 30.f
#define POINTER_CHECK_DIST 40.f
#define COUT_DELAY 3.f
SceneEditor::SceneEditor()
{
}

SceneEditor::SceneEditor(FPSCamera* _cameraPtr)
{
    AttachCamera(_cameraPtr);
}

SceneEditor::~SceneEditor()
{
}

void SceneEditor::Init()
{
    point_mesh = MeshBuilder::GetInstance()->GenerateCube("Point", Color(1.0f, 0.0f, 0.0f), 1.0f);
    MeshBuilder::GetInstance()->GenerateCube("Pointer", Color(1.0f, 1.0f, 1.0f), 1.0f);
    inputDelay = 0;
    ShiftMode = Mode::Normal;
    pointer_position = Vector3(0, 0, 0);
    Rotation = Vector3(0, 0, 0);
    selectedEntity = NULL;
    selectedNode = NULL;
    coutDelay = 0;
	togglePointer = false;
}
void SceneEditor::Update(double dt)
{
    if (inputDelay < TIME_BETWEEN_INPUT)
        inputDelay += dt;
    if (coutDelay < COUT_DELAY)
        coutDelay += dt;
	if (KeyboardController::GetInstance()->IsKeyDown('B'))
	{
		togglePointer = true;
	}
	else
		togglePointer = false;
    if (KeyboardController::GetInstance()->IsKeyDown('X')
        && inputDelay > TIME_BETWEEN_INPUT)
    {
		inputDelay = 0;
        AddPoint(attachedCamera->GetCameraPos());
    }
    if (KeyboardController::GetInstance()->IsKeyDown(VK_CONTROL)
        && KeyboardController::GetInstance()->IsKeyDown('Z')
        && inputDelay > TIME_BETWEEN_INPUT)
    {
        inputDelay = 0;
        DeletePoint();
    }
    Shift_Mode();
    SelectObject();
    CalculatePositionOfPointer(POINTER_DISTANCE);
    ModeAction(dt);
}
void SceneEditor::Render()
{
    MS& ms = GraphicsManager::GetInstance()->GetModelStack();
    //Render pointer
	if (togglePointer)
	{
		ms.PushMatrix();
		ms.Translate(pointer_position.x, pointer_position.y, pointer_position.z);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Pointer"));
		ms.PopMatrix();
		ModeRender();
		vector<Vector3>::iterator it;
		for (it = ListOfPoints.begin(); it != ListOfPoints.end(); it++)
		{
			ms.PushMatrix();
			ms.Translate((*it).x, (*it).y, (*it).z);
			RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Point"));
			string text = to_string((*it).x);
			text += ", ";
			text += to_string((*it).y);
			text += +", ";
			text += to_string((*it).z);
			ms.Translate((*it).x, (*it).y + 3.0f, (*it).z);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), text, Color(1.f, 1.f, 1.f));
			ms.PopMatrix();
		}
	}
}

void SceneEditor::AddPoint(Vector3 point)
{
    ListOfPoints.push_back(point);
}

void SceneEditor::DeletePoint()
{
    ListOfPoints.pop_back();
}

void SceneEditor::DeletePoint(Vector3 point)
{
    vector<Vector3>::iterator it;
    for (it = ListOfPoints.begin(); it != ListOfPoints.end(); it++)
    {
        if (*it == point)
        {
            ListOfPoints.erase(it);
            return;
        }
    }
}

void SceneEditor::Shift_Mode()
{
	if (KeyboardController::GetInstance()->IsKeyDown(VK_SHIFT)
		&& KeyboardController::GetInstance()->IsKeyDown('1')
		&& inputDelay > TIME_BETWEEN_INPUT)
	{
		inputDelay = 0;
		ShiftMode = Mode::Normal;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(VK_SHIFT)
		&& KeyboardController::GetInstance()->IsKeyDown('2')
		&& inputDelay > TIME_BETWEEN_INPUT)
	{
		inputDelay = 0;
		ShiftMode = Mode::FreeCam;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(VK_SHIFT)
		&& KeyboardController::GetInstance()->IsKeyDown('3')
		&& inputDelay > TIME_BETWEEN_INPUT)
	{
		inputDelay = 0;
		ShiftMode = Mode::Translate;
	}

	else if (KeyboardController::GetInstance()->IsKeyDown(VK_SHIFT)
		&& KeyboardController::GetInstance()->IsKeyDown('4')
		&& inputDelay > TIME_BETWEEN_INPUT)
    {
		inputDelay = 0;
        ShiftMode = Mode::Rotate;
    }
	else if (KeyboardController::GetInstance()->IsKeyDown(VK_SHIFT)
		&& KeyboardController::GetInstance()->IsKeyDown('5')
		&& inputDelay > TIME_BETWEEN_INPUT)
    {
		inputDelay = 0;
        ShiftMode = Mode::Scale;
    }	
}

void SceneEditor::ModeAction(double dt)
{
    dt = 1;
#define SHIFT_SPEED 2.f
#define QUICK_INPUT_DELAY 0.15f
#define KEY_DOWN_I KeyboardController::GetInstance()->IsKeyDown('I') && inputDelay > QUICK_INPUT_DELAY
#define KEY_DOWN_J KeyboardController::GetInstance()->IsKeyDown('J') && inputDelay > QUICK_INPUT_DELAY
#define KEY_DOWN_O KeyboardController::GetInstance()->IsKeyDown('O') && inputDelay > QUICK_INPUT_DELAY
#define KEY_DOWN_K KeyboardController::GetInstance()->IsKeyDown('K') && inputDelay > QUICK_INPUT_DELAY
#define KEY_DOWN_P KeyboardController::GetInstance()->IsKeyDown('P') && inputDelay > QUICK_INPUT_DELAY
#define KEY_DOWN_L KeyboardController::GetInstance()->IsKeyDown('L') && inputDelay > QUICK_INPUT_DELAY
	if (selectedEntity == NULL)
        return;
    if (KeyboardController::GetInstance()->IsKeyDown('Q')
        && inputDelay > TIME_BETWEEN_INPUT)
    {
        ClearSelectedObject();
        return;
    }
    switch (ShiftMode)
    {
    case SceneEditor::Normal:
        break;
    case SceneEditor::FreeCam:
        break;
    case SceneEditor::Translate:
        // X AXIS-----------------------------------------------------
#define ENTITY_POS selectedEntity->GetPosition()
    {                                   
        if (KEY_DOWN_I)
        {
            inputDelay = 0;
            selectedEntity->SetPosition(Vector3(ENTITY_POS.x + 2.f * dt, ENTITY_POS.y, ENTITY_POS.z));
            //selectedNode->ApplyTranslate(SHIFT_SPEED * dt, 0, 0);
        }
        else if (KEY_DOWN_J)
        {
            inputDelay = 0;
            selectedEntity->SetPosition(Vector3(ENTITY_POS.x - 2.f * dt, ENTITY_POS.y, ENTITY_POS.z));
            //selectedNode->ApplyTranslate(-SHIFT_SPEED * dt, 0, 0);
        }
        //------------------------------------------------------------
        // Y AXIS-----------------------------------------------------
        if (KEY_DOWN_O)
        {
            inputDelay = 0;
            selectedEntity->SetPosition(Vector3(ENTITY_POS.x, ENTITY_POS.y + SHIFT_SPEED * dt, ENTITY_POS.z));
            //selectedNode->ApplyTranslate(0, SHIFT_SPEED * dt, 0);
        }
        else if (KEY_DOWN_K)
        {
            inputDelay = 0;
            selectedEntity->SetPosition(Vector3(ENTITY_POS.x, ENTITY_POS.y - SHIFT_SPEED * dt, ENTITY_POS.z));
            //selectedNode->ApplyTranslate(0, -SHIFT_SPEED * dt, 0);
        }
        //------------------------------------------------------------
        // Z AXIS-----------------------------------------------------
        if (KEY_DOWN_P)
        {
            inputDelay = 0;
            selectedEntity->SetPosition(Vector3(ENTITY_POS.x, ENTITY_POS.y, ENTITY_POS.z + SHIFT_SPEED * dt));
            //selectedNode->ApplyTranslate(0, 0, SHIFT_SPEED * dt);
        }
        else if (KEY_DOWN_L)
        {
            inputDelay = 0;
            selectedEntity->SetPosition(Vector3(ENTITY_POS.x, ENTITY_POS.y, ENTITY_POS.z - SHIFT_SPEED * dt));
            //selectedNode->ApplyTranslate(0, 0, -SHIFT_SPEED * dt);
        }
        //------------------------------------------------------------
    }
        
        break;
    case SceneEditor::Rotate:
#define ENTITY_ROT selectedEntity->GetRotation()
		// X AXIS-----------------------------------------------------
        if (KEY_DOWN_I)
        {
            inputDelay = 0;
			selectedEntity->SetRotation(Vector3(ENTITY_ROT.x + 2.f * dt, ENTITY_ROT.y, ENTITY_ROT.z));
			//selectedNode->ApplyRotate(1.f, 1.f, 0, 0);
            //Rotation.x += 1.f;
        }
        else if (KEY_DOWN_J)
        {
            inputDelay = 0;
			selectedEntity->SetRotation(Vector3(ENTITY_ROT.x - 2.f * dt, ENTITY_ROT.y, ENTITY_ROT.z));
			//selectedNode->ApplyRotate(-1.f, 1.f, 0, 0);
			//Rotation.x -= 1.f;
        }
        //------------------------------------------------------------
        // Y AXIS-----------------------------------------------------
        if (KEY_DOWN_O)
        {
            inputDelay = 0;
			selectedEntity->SetRotation(Vector3(ENTITY_ROT.x, ENTITY_ROT.y + 2.f * dt, ENTITY_ROT.z));
			//selectedNode->ApplyRotate(1.f, 0, 1.f, 0);
			//Rotation.y += 1.f;
        }
        else if (KEY_DOWN_K)
        {
            inputDelay = 0;
			selectedEntity->SetRotation(Vector3(ENTITY_ROT.x, ENTITY_ROT.y - 2.f * dt, ENTITY_ROT.z));
			//selectedNode->ApplyRotate(-1.f, 0, 1.f, 0);
			//Rotation.y -= 1.f;
        }
        //------------------------------------------------------------
        // Z AXIS-----------------------------------------------------
        if (KEY_DOWN_P)
        {
            inputDelay = 0;
			selectedEntity->SetRotation(Vector3(ENTITY_ROT.x, ENTITY_ROT.y, ENTITY_ROT.z + 2.f * dt));
			//selectedNode->ApplyRotate(1.f, 0, 0, 1.f);
			//Rotation.z += 1.f;
        }
        else if (KEY_DOWN_L)
        {
            inputDelay = 0;
			selectedEntity->SetRotation(Vector3(ENTITY_ROT.x, ENTITY_ROT.y, ENTITY_ROT.z - 2.f * dt));
			//selectedNode->ApplyRotate(-1.f, 0, 0, 1.f);
			//Rotation.z -= 1.f;
        }
        //------------------------------------------------------------
        break;
    case SceneEditor::Scale:
        // X AXIS-----------------------------------------------------
#define ENTITY_SCALE selectedEntity->GetScale()
#define SCALE_INCREASE 1.f
        if (KEY_DOWN_I)
        {
            inputDelay = 0;
            selectedEntity->SetScale(Vector3(ENTITY_SCALE.x + SCALE_INCREASE, ENTITY_SCALE.y, ENTITY_SCALE.z));
        }
        else if (KEY_DOWN_J)
        {
            inputDelay = 0;
            selectedEntity->SetScale(Vector3(ENTITY_SCALE.x - SCALE_INCREASE, ENTITY_SCALE.y, ENTITY_SCALE.z));
        }
        //------------------------------------------------------------
        // Y AXIS-----------------------------------------------------
        if (KEY_DOWN_O)
        {
            inputDelay = 0;
            selectedEntity->SetScale(Vector3(ENTITY_SCALE.x, ENTITY_SCALE.y + SCALE_INCREASE, ENTITY_SCALE.z));
        }
        else if (KEY_DOWN_K)
        {
            inputDelay = 0;
            selectedEntity->SetScale(Vector3(ENTITY_SCALE.x, ENTITY_SCALE.y - SCALE_INCREASE, ENTITY_SCALE.z));
        }
        //------------------------------------------------------------
        // Z AXIS-----------------------------------------------------
        if (KEY_DOWN_P)
        {
            inputDelay = 0;
            selectedEntity->SetScale(Vector3(ENTITY_SCALE.x, ENTITY_SCALE.y, ENTITY_SCALE.z + SCALE_INCREASE));
        }
        else if (KEY_DOWN_L)
        {
            inputDelay = 0;
            selectedEntity->SetScale(Vector3(ENTITY_SCALE.x, ENTITY_SCALE.y, ENTITY_SCALE.z - SCALE_INCREASE));
        }
        //------------------------------------------------------------
        break;
    default:
        break;
    }
}

void SceneEditor::CalculatePositionOfPointer(float dist)
{
    pointer_position = attachedCamera->GetCameraPos() + ((attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos()).Normalized() * dist);
}

void SceneEditor::SelectObject()
{
    if (!KeyboardController::GetInstance()->IsKeyDown('G'))
        return;
    vector<EntityBase*> ExportList = CSpatialPartition::GetInstance()->GetObjects(pointer_position, POINTER_CHECK_DIST);
    if (ExportList.size() == 0)
        return;
    selectedEntity = *ExportList.begin();
    Vector3 dist_from_pointer_to_obj = (pointer_position - selectedEntity->GetPosition()).LengthSquared();
    if (ExportList.size() == 1)
        return;
    vector<EntityBase*>::iterator it;
    for (it = ++ExportList.begin(); it != ExportList.end(); ++it)
    {
        Vector3 temp = (pointer_position - (*it)->GetPosition()).LengthSquared();
        if (temp < dist_from_pointer_to_obj)
        {
            dist_from_pointer_to_obj = temp;
            selectedEntity = (*it);
            selectedNode = CSceneGraph::GetInstance()->theRoot->GetEntity(selectedEntity);
        }
    }
}

void SceneEditor::ClearSelectedObject()
{
    selectedEntity = NULL;
}

void SceneEditor::ModeRender()
{
    if (coutDelay > COUT_DELAY)
    {
        coutDelay = 0;
    }
    else
        return;
    if (selectedEntity == NULL)
        return;
    MS& ms = GraphicsManager::GetInstance()->GetModelStack();
    ms.PushMatrix();
    switch (ShiftMode)
    {
    case SceneEditor::Normal:
        break;
    case SceneEditor::FreeCam:
        break;
    case SceneEditor::Translate:
        cout << "X: " << selectedEntity->GetPosition().x
            << " Y: " << selectedEntity->GetPosition().y
            << " Z: " << selectedEntity->GetPosition().z
            << endl;
        break;
    case SceneEditor::Rotate:
		cout << "X: " << selectedEntity->GetRotation().x
			<< " Y: " << selectedEntity->GetRotation().y
			<< " Z: " << selectedEntity->GetRotation().z
            << endl;
        break;
    case SceneEditor::Scale:
        if (coutDelay > COUT_DELAY)
        {
            coutDelay = 0;
            cout << "X: " << selectedEntity->GetScale().x
                << " Y: " << selectedEntity->GetScale().y
                << " Z: " << selectedEntity->GetScale().z
                << endl;
        }

        break;
    default:
        break;
    }
    ms.PopMatrix();
}

void SceneEditor::AttachCamera(FPSCamera* _cameraPtr)
{
    attachedCamera = _cameraPtr;
}

void SceneEditor::DetachCamera()
{
    attachedCamera = nullptr;
}*/