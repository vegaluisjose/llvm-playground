add_library(hello MODULE
    hello.cc
)

set_property(TARGET hello PROPERTY CXX_STANDARD 14)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(hello PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
