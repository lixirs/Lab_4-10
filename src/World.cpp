#include "World.h"
#include <algorithm>

World::~World() {
    for (GameObject* obj : objects) {
        delete obj;
    }
    objects.clear();
    byName.clear();
}

bool World::AddObject(GameObject* obj) {
    if (!obj) return false;
    
    const std::string& name = obj->GetName();
    
    // Check for duplicate names
    if (byName.find(name) != byName.end()) {
        //Name already exists
        return false;
    }
    
    objects.push_back(obj);
    byName[name] = obj;
    return true;
}

void World::RemoveObject(GameObject* obj) {
    if (!obj) return;
    
    objects.erase(
        std::remove(objects.begin(), objects.end(), obj),
        objects.end()
    );

    auto it = byName.find(obj->GetName());
    if (it != byName.end()) {
        byName.erase(it);
    }

    delete obj;
}

void World::UpdateAll(float dt) {
    for (GameObject* obj : objects) {
        if (!obj->IsDestroyed()) {
            obj->Update(dt);
        }
    }

    std::vector<GameObject*> toDestroy;
    for (GameObject* obj : objects) {
        if (obj->IsDestroyed()) {
            toDestroy.push_back(obj);
        }
    }
    
    for (GameObject* obj : toDestroy) {
        RemoveObject(obj);
    }
}

void World::DrawAll() {
    for (GameObject* obj : objects) {
        obj->Draw();
    }
}

GameObject* World::FindByName(const std::string& name) {
    auto it = byName.find(name);
    if (it != byName.end()) {
        return it->second;
    }
    return nullptr;
}
