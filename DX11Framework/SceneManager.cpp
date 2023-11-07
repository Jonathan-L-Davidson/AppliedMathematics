#include "sceneManager.h"
#include "ModelManager.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Monkey.h"

//Tells  yaml it is a .lib with no .dll
#define YAML_CPP_STATIC_DEFINE
#include "yaml-cpp/yaml.h"
//Functionally equivalent to adding dependency in project
#pragma comment(lib, "lib\\x64\\yaml-cppd.lib")


SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
    delete _objectManager;
    delete _modelManager;

    delete _cam;
}

HRESULT SceneManager::Initialise(Renderer* renderer) {
    HRESULT hr = S_OK;

    _renderManager = renderer;

    // ModelManager Init
    _modelManager = new ModelManager();
    _modelManager->SetRenderManager(renderer);
    _modelManager->Initialise();

    // ObjManager Init
    _objectManager = new ObjectManager();
    _objectManager->SetRenderManager(renderer);
    _objectManager->SetModelManager(_modelManager);
    InitHardcodedObjects(); // Renderer Class

    // Camera Init
    XMFLOAT3X3 CamPos = XMFLOAT3X3(0, 0, -10.0f, // eye
        0, 0, 0, // at
        0, 1, 0); // up

    _cam = new Camera(CamPos);
    _renderManager->SetCamera(_cam);

    return hr;
}

void SceneManager::Update(float deltaTime) {
    _objectManager->Update(deltaTime);
}

void SceneManager::InitHardcodedObjects() {
    Texture* defaultTexture = _modelManager->GetTexture("Default");

    Object* cube = new Cube();
    cube->SetName("Test Cube");
    _objectManager->AddObject(cube, XMFLOAT3(5.0f, 0.0f, 0.0f));
    Texture* tex = _modelManager->GetTexture("Crate");
    cube->SetTexture(tex);

    Pyramid* _pyramid = new Pyramid();
    _pyramid->SetName("Test Pyramid");
    _objectManager->AddObject(_pyramid, XMFLOAT3(-3.0f, 0.0f, 5.0f));

    cube->SetParent(_pyramid);

    Monkey* monkey = new Monkey();
    monkey->SetName("Monkey");
    _objectManager->AddObject(monkey, XMFLOAT3(-5, 0.0f, 5.0f));
    monkey->GetModel()->SetShader("VertexShading");

    Monkey* monkey2 = new Monkey();
    monkey2->SetName("Monkey2");
    _modelManager->LoadModelFromFile("monkey.obj", "Monkey2");
    _objectManager->AddObject(monkey2, XMFLOAT3(5, 0.0f, 5.0f));

    //Object* photogrammetry = new Object();
    //photogrammetry->SetName("Photogrammetry");
    //_modelManager->LoadModelFromFile("photogrammetry.obj", "Photogrammetry");
    //_objectManager->AddObject(photogrammetry, XMFLOAT3(0.0f, -80.0f, 0.0f));
    //Texture* photoTex = _modelManager->GetTexture("photogrammetry");
    //photogrammetry->SetTexture(photoTex);

    Object* plane = new Object();
    plane->SetName("Plane");
    plane->SetColor(XMFLOAT4(0.05f, 0.1f, 0.1f, 1.0f));

    _modelManager->LoadModelFromFile("plane.obj", "Plane");
    _objectManager->AddObject(plane, XMFLOAT3(0.0f, -5.0f, 0.0f));

    cube->transform->parent = _pyramid->transform;
}

bool SceneManager::LoadScene(const char* path) {
    // Load yaml.

    return true;
}