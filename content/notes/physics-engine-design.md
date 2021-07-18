---
title: "Physics engine design"
date: 2021-07-05T12:33:21+02:00
mermaid: 1
tags: ["physics"]
category: "Note"
layout: single
---

*(primarly written [for an existing project](https://github.com/LunarWatcher/Genesis))*

The main problem with integrating a physics engine architecture on top of the existing planned AI architecture is that they're separate, but still have overlap.

Optimally, the physics engine needs to track all the entities, and the AI controllers track a subset. This difference is unfortunately why things get hard.

Each AI controller can get away with a linear container, where the physics engine also need to store its controlled entities in a tree-like data structure, primarily to optimize for click events. The entity controllers themselves can also take advantage of a tree-like structure, to tell what not to render. This essentially establishes the following structure:

{{<mermaid>}}
classDiagram
class PhysicsEngine{
    +std::vector~PhysicsController~
}

class PhysicsController {
    +Container~Entities~
    +tick()
}
class EntityController {
    +tick()
    +render()
}

PhysicsEngine --&gt; ControllerImpl : contains
PhysicsController &lt;|-- ControllerImpl : extends
EntityController &lt;|-- ControllerImpl : extends - only necessary for AI
{{</mermaid>}}

Note that ControllerImpl is any class that implements PhysicsController and optionally EntityController - it's not a real class, but a representation of any number of classes.

The immediate downside to this approach is that it doesn't fully optimize the controllers for layers - notably, all the entities are stored by their respective EntityController, as opposed to all entities in that layer being associated to a PhysicsController.

While that is a viable design choice, it creates two places where entities need to be managed, which means in cases where entities are added or removed, they need to be added or removed in two places, causing unnecessary work.

The entire implementation may be backwards, though. If that's the case, that stems from various other design choices in this specific project.

Most proper, dedicated physics engines with substantially more physics features than what this one needs seem to use static methods for creating pointers, that're manually destroyed, presumably in the destructor or when the physics aspects cease to exist.

Might've been a lot easier if the physical attributes were connected to a PhysicsObject instead of an entity, which would've simplified this clusterfuck:

{{<mermaid>}}
classDiagram
class Entity {
    +std::shared_ptr~Collider~
}
class Collider {
    &lt;&lt;Super-class for collider shapes>>
    +collidesWith(const Rectangle& rect)
    +collidesWith(...) : Future 
}

Entity --> Collider : Contains
PhysicsController --> Collider : Manages and checks for collisions
PhysicsEngine "1" --> "n" PhysicsController : Manages controllers and does logical collision checks
PhysicsController "1" --> "n" Entity : Contains
{{</mermaid>}}

PhysicsController itself deals with the actual physics for its entities, though there's not that many at the time of writing aside collision. Implementing the raw physics processing things in a super-class prevents reimplementation for each physics controller, though the physics API has to be implemented in a way that allows varying physics for varying types of entities. Gravity isn't particularly a problem in this type of game, but it should be compatible if it's needed.
