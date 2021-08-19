#
# SPDX-FileCopyrightText: 2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: BSD-3-Clause
#

# Compiler settings

include(KDFunctions)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    kd_add_flag_if_supported(-Wunused-but-set-variable UNUSED_BUT_SET)
    kd_add_flag_if_supported(-Wlogical-op LOGICAL_OP)
    kd_add_flag_if_supported(-Wsizeof-pointer-memaccess POINTER_MEMACCESS)
    kd_add_flag_if_supported(-Wreorder REORDER)
    kd_add_flag_if_supported(-Wformat-security FORMAT_SECURITY)
    kd_add_flag_if_supported(-Wsuggest-override SUGGEST_OVERRIDE)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Woverloaded-virtual -Winit-self -Wmissing-include-dirs -Wunused -Wundef -Wpointer-arith -Wmissing-noreturn -Werror=return-type -Wswitch")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # -Wgnu-zero-variadic-macro-arguments (part of -pedantic) is triggered by every qCDebug() call and therefore results
        # in a lot of noise. This warning is only notifying us that clang is emulating the GCC behaviour
        # instead of the exact standard wording so we can safely ignore it
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments -Wdocumentation")
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Qunused-arguments -Wdocumentation")
endif()

# Do not treat the operator name keywords and, bitand, bitor, compl, not, or and xor as synonyms as keywords.
# They're not supported under Visual Studio out of the box thus using them limits the portability of code
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_C_COMPILER_ID MATCHES "Clang" OR (CMAKE_C_COMPILER_ID STREQUAL "Intel" AND NOT WIN32))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-operator-names")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244") #conversion from __int64 to int possible loss of data
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267") #conversion from size_t to int possible loss of data
endif()

if(WIN32)
    add_definitions(-DUNICODE -D_UNICODE -D_USING_V110_SDK71_=1)
endif()

if(QNXNTO)
    add_definitions(-D_QNX_SOURCE)
endif()

if(CYGWIN)
    add_definitions(-D_GNU_SOURCE)
endif()

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT APPLE) OR
    (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT APPLE) OR
    (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" AND NOT WIN32))
    # Linker warnings should be treated as errors
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--fatal-warnings ${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--fatal-warnings ${CMAKE_MODULE_LINKER_FLAGS}")

    # Do not allow undefined symbols, even in non-symbolic shared libraries
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_MODULE_LINKER_FLAGS}")
endif()