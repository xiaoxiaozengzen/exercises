project(desigin_patterns)

add_executable(dp_builder builder/builder.cpp)
add_executable(dp_pimpl pimpl/pimpl.cpp pimpl/person_impl.cpp pimpl/person.cpp)