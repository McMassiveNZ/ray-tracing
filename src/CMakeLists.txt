set(current_target ray-tracing)

add_executable(
    ${current_target} 
    main.cpp
    vec3.h
    ray.h
    ray.cpp
    color.h
    hittable.h
    sphere.h
    sphere.cpp
    hittable_list.h
    hittable_list.cpp
    common.h
    camera.h
    camera.cpp
    material.h
    metal.h
    metal.cpp
    lambertian.h
    lambertian.cpp
    dielectric.h
    dielectric.cpp
)

target_include_directories(${current_target} PUBLIC ../external)

if( ENABLE_ALL_REASONABLE_WARNINGS )
    MESSAGE("-- Additional Warnings Enabled")
    target_enable_warnings(${current_target})
endif()

if( ENABLE_WARNINGS_AS_ERRORS )
    MESSAGE("-- Warnings as Errors")
    target_warnings_as_errors(${current_target})
endif()

if( ENABLE_SANITIZERS )
    MESSAGE("-- Sanitizers Enabled")
    target_enable_sanitizers(${current_target})
endif()

if( ENABLE_STATIC_ANALYSIS )
    MESSAGE("-- Static Analysis Enabled")
    target_enable_static_analysis(${current_target})
endif()
