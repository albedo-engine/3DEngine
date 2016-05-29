#pragma once

#include <iostream>

#include <utils/headers/common.hpp>
#include <scene/node.hpp>
#include <components/transform/transform.hpp>
#include <components/geometry/geometry.hpp>
#include <components/camera/perspective-camera.hpp>

namespace Engine
{
  class Engine
  {
    public:
      Engine() = delete;

      static void initialize();

  };
}
