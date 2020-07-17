// Some convenient macros for dealing with rule-of-five
#pragma once

// Rule of 5
#define SUGIYAMA_RO5_DEC(ClassName) \
  ~ClassName(); \
  ClassName(ClassName&& rhs) noexcept; \
  ClassName& operator=(ClassName&& rhs) noexcept; \
  ClassName(const ClassName& rhs); \
  ClassName& operator=(const ClassName& rhs);
#define SUGIYAMA_RO5_DEF(ClassType, ClassName) \
  ClassType::~ClassName() = default; \
  ClassType::ClassName(ClassType&& rhs) noexcept = default; \
  ClassType& ClassType::operator=(ClassType&& rhs) noexcept = default; \
  ClassType::ClassName(const ClassType& rhs) = default; \
  ClassType& ClassType::operator=(const ClassType& rhs) = default;

// Rule of 5 decleration + virtual
#define SUGIYAMA_RO5_DEC_V(ClassName) \
  virtual ~ClassName(); \
  ClassName(ClassName&& rhs) noexcept; \
  virtual ClassName& operator=(ClassName&& rhs) noexcept; \
  ClassName(const ClassName& rhs); \
  virtual ClassName& operator=(const ClassName& rhs);

// Rule of 5 definition but no copy
#define SUGIYAMA_RO5_DEF_NOCOPY(ClassType, ClassName) \
  ClassType::~ClassName() = default; \
  ClassType::ClassName(ClassType&& rhs) noexcept = default; \
  ClassType& ClassType::operator=(ClassType&& rhs) noexcept = default; \
  ClassType::ClassName(const ClassType& rhs) = delete; \
  ClassType& ClassType::operator=(const ClassType& rhs) = delete;
