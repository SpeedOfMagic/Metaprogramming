#pragma once

#include "class.h"
#include "functor.h"

template<typename ...Args>
using Predicate = Functor<bool(Args...)>;
