#pragma once

namespace Engine
{
  class Engine
  {
    public:
      Engine() = delete;

      static void initialize(void* (*)(const char *name));
  };
}
