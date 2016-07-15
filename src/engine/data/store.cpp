//
// Created by david on 12/07/16.
//

#include "store.hpp"

namespace Engine
{
  namespace Data
  {
    Store::~Store()
    {
      for (auto p : attributes_)
      {
        if (p.second != nullptr)
          delete p.second;
      }
    }
  } // namespace Data
} // namespace Engine

