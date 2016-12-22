#ifndef SCENE_EDITOR_H
#define SCENE_EDITOR_H

#include "SingletonTemplate.h"
#include "Vector3.h"
#include <vector>
#include "FPSCamera.h"
#include "EntityBase.h"
/*#include "SceneGraph.h"

class Mesh;

using namespace std;
class SceneEditor : public Singleton<SceneEditor>
{
public:
    SceneEditor();
    SceneEditor(FPSCamera* _cameraPtr);
    ~SceneEditor();

    void Init();
    void Update(double dt);
    void Render();
    void AddPoint(Vector3 point);
    void DeletePoint();
    void DeletePoint(Vector3 point);
    void Shift_Mode();
    void ModeAction(double dt);
    void CalculatePositionOfPointer(float dist);
    void SelectObject();
    void ClearSelectedObject();
    void ModeRender();
    enum Mode
    {
		Normal,
		FreeCam,
        Translate,
        Rotate,
        Scale
    };
	Mode ShiftMode;
    //camera
    void AttachCamera(FPSCamera* _cameraPtr);
    void DetachCamera(void);

private:
    vector<Vector3> ListOfPoints;
    Mesh* point_mesh;
    FPSCamera* attachedCamera;
    float inputDelay;
    Vector3 pointer_position;
    Vector3 Rotation;
    EntityBase* selectedEntity;
    CSceneNode* selectedNode;
    float coutDelay;
	bool togglePointer;
};*/



#endif