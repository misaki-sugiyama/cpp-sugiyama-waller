// Some helper macros to reduce CRTP boilerplate (static_cast)
#pragma once

// Just some small convenient syntactic sugars
#define DERIVED (static_cast<Derived&>(*this))
#define DERIVEDC (static_cast<const Derived&>(*this))
