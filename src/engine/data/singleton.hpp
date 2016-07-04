#pragma once

#include <memory>

template <class T>
class Singleton
{
  public:
    typedef std::shared_ptr<T> TypePtr;

  public:
    static TypePtr& instance()
    {
      if (instance_ == nullptr)
        instance_ = std::make_shared<T>();
      return instance_;
    }

  private:
    static TypePtr instance_;
};

template <class T>
typename Singleton<T>::TypePtr Singleton<T>::instance_ = nullptr;