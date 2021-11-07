// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_MYPTR_HPP
#define INCLUDE_MYPTR_HPP
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  SharedPtr();
  explicit SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r) noexcept;
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
  [[nodiscard]]auto use_count() const -> size_t;

 private:
  T* myPtr;
  std::atomic_uint* myCount;
};

#endif //INCLUDE_MYPTR_HPP
