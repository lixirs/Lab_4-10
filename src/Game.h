#pragma once
#include "World.h"
#include <memory>

class Game {
public:
    Game() = default;
    virtual ~Game() = default;

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    virtual void Deinit() = 0;

    // Access to world
    World& GetWorld() { return world; }

    // Find object by name
    GameObject* FindObjectByName(const std::string& name) {
        return world.FindByName(name);
    }

    void Destroy(GameObject* obj) {
        if (obj) {
            obj->DestroyObject();
        }
    }

    void AddGameObject(GameObject* obj) {
        world.AddObject(obj);
    }
protected:
    void UpdateObjects(float dt) {
        world.UpdateAll(dt);
    }

    void DrawObjects() {
        world.DrawAll();
    }
private:
    World world;
};