#pragma once
#include "pimpl.hpp"
class Foo {
    class impl;
    pimpl<impl> impl;
};


