### Iterator design pattern

An object that facilitates the traversal of a data structure.

#### Motivation

Iteration is a core functionality of various data structures

An iterator is a class that facilitates the traversal 
 - Keeps a reference to the current element
 - Knows how to move to a different element

Can be used implicitly
 - Range based for
 - Coroutines

#### Summary

An object can be iterated if it defines a begin()/end() pair
An iterator specifies how an object can be traversed
Typically requires != and ++ operators
The ++ operator is called sporaidcally, so it cannot be recursive
Coroutines allow recursion through generatir yielding functions

