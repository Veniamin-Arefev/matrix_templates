project(Matrix_templates)

file(GLOB header_SRC
        "*.h"
        )

file(GLOB source_SRC
        "*.cpp"
        )

set(HEADER_FILES
        ${header_SRC}
        )

set(SOURCE_FILES
        ${source_SRC}
        )

add_library(Matrix_templates_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})