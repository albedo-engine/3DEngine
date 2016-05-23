#include "utils/test_utils.hpp"

#include "engine.hpp"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;

void test_components()
{
    Node::NodePtr parent = Node::create("parent");
    Node::NodePtr child = Node::create();

    parent->add_child(child);

    ASSERT(parent->get_child_at(0) == child, "get_child_at");
}

int main()
{
    // Create a camera

    LAUNCH(test_components);

    return 0;
}
