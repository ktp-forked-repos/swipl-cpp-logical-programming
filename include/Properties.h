#pragma once

#include <PrologInterface.h>

#include <iostream>
#include <map>
#include <vector>

class PropertyValue {
protected:
  class UUID {
  public:
    UUID();
    UUID(std::string uuid);

    std::string str() const;

  private:
    std::string uuid_;
  };

public:
  PropertyValue();
  PropertyValue(PrologTerm term);
  PropertyValue(UUID uuid, PrologTerm term);

  PrologTerm term() const;

  std::string uuid() const;

private:
  UUID uuid_;
  PrologTerm term_;
};

class PropertyVariable : public PropertyValue {
public:
  PropertyVariable();

  // Get the PropertyValue this variable is bound to in a query.
  PropertyValue get() const;
};

class PropertyVector {
public:
  PropertyVector(std::initializer_list<PropertyValue> values);
  PropertyVector(std::vector<PropertyValue> values);
  PropertyVector(PrologTermVector terms);

  PrologTermVector term() const;

  size_t size() const;

private:
  PrologTermVector terms_;
};

class PropertyFunctor : public PropertyValue {
public:
  PropertyFunctor(std::string property, PropertyVector vector);
};

class PropertyList : public PropertyValue {
public:
  PropertyList(std::vector<PropertyValue> vector);
};

class PropertyConjunction : public PropertyValue {
public:
  PropertyConjunction(PropertyList args);
};

class PropertySolution {
public:
  PropertySolution(PrologSolution solution);

  PropertyValue get(PropertyValue var) const;

private:
  PrologSolution solution_;
};

class PropertyQuery {
public:
  PropertyQuery(PropertyFunctor functor);

  std::vector<PropertySolution> solutions() const;

private:
  PrologQuery query_;
};

namespace std {
  template<> struct std::less<PropertyValue> {
    bool operator()(const PropertyValue& lhs, const PropertyValue& rhs) const;
  };
}

