#pragma once

#include <memory>

class DataContainer
{
  public:
    typedef std::shared_ptr<DataContainer>  DataContainerPtr;

    template <typename DataType>
    using DataListPtr       =   std::shared_ptr<std::vector<DataType>>;
    using DataListContainer =   std::vector<DataListPtr>;

  public:
    DataContainerPtr
    static inline
    instance()
    {
      if (instance_ == nullptr)
        instance_ = std::make_shared<DataContainer>();
      return instance_;
    }

  public:
    DataContainer();

  public:
    template <typename DataType>
    std::vector<DataType>&
    get_list()
    {
      for (auto& elt : data_)
      {
        auto list = boost::get<std::shared_ptr<std::vector<DataType>>(elt);
        if (list != nullptr)
          return *list;
      }

      return nullptr;
    }

  private:
    DataContainerPtr    instance_;

    DataListContainer   data_;
};
