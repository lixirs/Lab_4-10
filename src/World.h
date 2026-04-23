#pragma once
#include "GameObject.h"
#include <vector>
#include <map>
#include <string>

class World {
public:
    World() = default;
    ~World();

    bool AddObject(GameObject* obj);

    void RemoveObject(GameObject* obj);

    void UpdateAll(float dt);

    void DrawAll();

    GameObject* FindByName(const std::string& name);

    inline std::vector<GameObject*>& GetObjects() { return objects; }

private:
    std::vector<GameObject*> objects;
    std::map<std::string, GameObject*> byName;
};