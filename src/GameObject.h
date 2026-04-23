#pragma once
#include "raylib.h"
#include <string>

class World;

class GameObject {
public:
    GameObject(const std::string& name, World* world)
        : name(name), world(world), destroyed(false), pos({0, 0}), size({0, 0}) {}

    virtual ~GameObject() = default;

    // Getters
    inline const std::string& GetName() { return name; }
    inline bool IsDestroyed() { return destroyed; }
    inline Vector2 GetPos() { return pos; }
    inline Vector2 GetSize() { return size; }

    // Setters
    inline void SetPos(Vector2 newPos) { pos = newPos; }
    inline void SetSize(Vector2 newSize) { size = newSize; }

    inline void DestroyObject() { destroyed = true; }

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

    inline Rectangle GetBounds() {
        return { pos.x, pos.y, size.x, size.y };
    }

protected:
    inline World* GetWorld() { return world; }
    
    Vector2 pos;
    Vector2 size;

private:
    std::string name;
    World* world;
    bool destroyed;
};