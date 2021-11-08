// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_MYPTR_HPP_
#define INCLUDE_MYPTR_HPP_
#include <iostream>
#include <atomic>

template <typename T>
class SharedPtr {
 public:
  SharedPtr() : myPtr(nullptr), myCount(nullptr){}
  explicit SharedPtr(T* ptr) : myPtr(ptr),
                               myCount(new std::atomic_uint(1)) {
    (*myCount) = 1;
  }
  SharedPtr(const SharedPtr& r) : myPtr(r.myPtr),
                                  myCount(r.myCount) {
    (*myCount)++;
  }
  SharedPtr(SharedPtr&& r) noexcept : myPtr(r.myPtr),
                                      myCount(r.myCount)  {
    r.myPtr = nullptr;
    r.myCount = nullptr;
  }
  ~SharedPtr(){
//    if (!myCount){
//      return;
//    }
//    if (*myCount == 0){
//      delete myCount;
//      delete myPtr;
//      return;
//    }
//    if (--(*myCount) == 0){
//      delete myPtr;
//      delete myCount;
//    }
    if (*myCount == 1){
      delete myCount;
      delete myPtr;
    } else {
      (*myCount)--;
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr&{
    if (this != &r) {
      if (myCount) {
        //если до этого указывал на объект, то у него был счетчик
//        if (*myCount == 1) { // если это последний указатель, то удаляем все
//          delete myPtr;      // и записываем новые данные, если не последний,
//          delete myCount;    // то уменьшаем на 1 и заменяем данные
//        } else {
//          (*myCount)--;
//        }
          this->~SharedPtr();
      }
      myPtr = r.myPtr;
      myCount = r.myCount;
      (*myCount)++;
    }
    return *this;
  }

  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&{
    if (this != &r){
//      if (myCount) {  // аналогичная проверка как в присваивание копированием
//        if (*myCount == 1) {
//          delete myPtr;
//          delete myCount;
//        } else {
//          (*myCount)--;
//        }
        this->~SharedPtr();
      }
      myPtr = r.myPtr;
      myCount = r.myCount;
      r.myCount = r.myPtr = nullptr; //удаляем указатель, т.к. теперь он в this
      return *this;
    }

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const {
    if (myCount != nullptr) {
      return true;
    } else {
      return false;
    }
  }
  auto operator*() const -> T& { return (*myPtr); }

  auto operator->() const -> T* { return myPtr; }

  auto get() -> T* { return myPtr; }


//  void reset() { SharedPtr().mswap(*this); }
  void reset(){
    if (myCount) {
      if (*myCount == 1) {
        delete myCount;
        delete myPtr;
      } else {
        (*myCount)--;
      }
    }
    myPtr = nullptr;
    myCount = nullptr;
  }

//  void reset(T* ptr){ SharedPtr(ptr).mswap(*this);}
  void reset(T* ptr){
    if (myCount) {
      if (*myCount == 1) {
        delete myCount;
        delete myPtr;
      } else {
        (*myCount)--;
      }
    }
    myPtr = ptr;
    *myCount = 1;
  }

  void mswap(SharedPtr& r){
    SharedPtr<T> tmp;
    tmp = r;
    r = *this;
    *this = tmp;
  }

  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот же управляемый объект
  [[nodiscard]]auto use_count() const -> size_t {
    if (myCount) {
      return *myCount;
    } else {
      return 0;
    }
  }

 private:
  T* myPtr;
  std::atomic_uint* myCount;
};

#endif //INCLUDE_MYPTR_HPP_
