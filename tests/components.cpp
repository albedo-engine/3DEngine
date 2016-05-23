#include "engine.hpp"

#include "components/transform.hpp"
#include "components/geometry/geometry.hpp"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;

int main()
{
    // Create a camera
    Node::NodePtr parent = Node::create("parent");
    Node::NodePtr child = Node::create();

    parent->add_child(child);

    assert(parent->get_child_at(0) == child);


    return 0;
}
