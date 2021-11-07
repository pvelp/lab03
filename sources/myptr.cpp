// Copyright 2021 Your Name <your_email>

#include <myptr.hpp>

template <typename T>
SharedPtr<T>::SharedPtr() : myPtr(nullptr), myCount(nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) : myPtr(ptr),
                                  myCount(new std::atomic_uint(1)) {
  (*myCount)=1;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &r) : myPtr(r.myPtr),
                                                 myCount(r.myPtr) {
  (*myCount)++;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&r) noexcept : myPtr(r.myPtr),
                                                     myCount(r.myCount)  {
  r.myPtr = nullptr;
  r.myCount = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr<T>() {
  if (*myCount == 1){
    delete myCount;
    delete myPtr;
  } else {
    (*myCount)--;
  }
}

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr<T> &r) -> SharedPtr<T> & {
  if (this != r) {
    if (myCount) { //если до этого указывал на объект, то у него был счетчик
      if (*myCount == 1) { // если это последний указатель, то удаляем все
        delete myPtr;      // и записываем новые данные, если не последний,
        delete myCount;    // то уменьшаем на 1 и заменяем данные
      } else
        (*myCount)--;
    }
    myPtr = r.myPtr;
    myCount = r.myCount;
    (*myCount)++;
  }
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr<T> &&r) noexcept -> SharedPtr<T> & {
  if (this != r){
    if (myCount){ // аналогичная проверка как в присваивание копированием
      if (*myCount == 1){
        delete myPtr;
        delete myCount;
      } else
        (*myCount)--;
    }
    myPtr = r.myPtr;
    myCount = r.myCount;
    r.myCount = r.myPtr = nullptr; //удаляем указатель, т.к. теперь он в this
  }
}
template<typename T>
SharedPtr<T>::operator bool() const {
  if (myCount != nullptr){
    return true;
  } else
    return false;
}

template<typename T>
auto SharedPtr<T>::operator*() const -> T & {
  return (*myPtr);
}

template<typename T>
auto SharedPtr<T>::operator->() const -> T * {
  return myPtr;
}
template<typename T>
auto SharedPtr<T>::get() -> T * {
  return myPtr;
}

template<typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  if (myCount) {
    return *myCount;
  } else
    return 0;
}

template<typename T>
void SharedPtr<T>::reset() {
  if (myCount){
    if (*myCount == 1){
      delete myCount;
      delete myPtr;
    }
    else (*myCount)--;
  }
}