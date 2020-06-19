add_library(dfg MODULE
    dfg.cc
)

set_property(TARGET dfg PROPERTY CXX_STANDARD 14)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(dfg PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
