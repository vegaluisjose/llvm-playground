add_library(HelloPass MODULE
    HelloPass.cpp
)

set_property(TARGET HelloPass PROPERTY CXX_STANDARD 14)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(HelloPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
