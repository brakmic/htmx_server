project('htmx_server', 'cpp', version: '0.1')

os = host_machine.system()

cpp_args = [
    '-Wall',
    '-Wextra',
    '-Wpedantic',
    '-Wshadow',
    '-Wformat=2',
    '-Wconversion',
    '-Wnull-dereference',
    '-Wsign-conversion',
    '-D_FORTIFY_SOURCE=2',
    '-D__STDC_LIMIT_MACROS',
    '-DCROW_ENABLE_SSL',
    '-g3',
    '-ggdb',
    '-std=c++20',
]


triplet = 'x64-osx'
if os == 'windows'
    triplet = 'x64-mingw-static'
endif

vcpkg_root = '/Users/brakmic/projects/vcpkg'
if os == 'windows'
    vcpkg_root = 'C:/Users/Administrator/projects/vcpkg'
endif
vcpkg_packages = join_paths(vcpkg_root, 'packages')

src_root = 'src'
ssl_keys_root = 'ssl'
mingw_root = 'C:/bin/msys64/mingw64'
mingw_includes = join_paths(mingw_root, 'include')
posix_includes = ''
mingw_libs = join_paths(mingw_root, 'lib')
if os != 'windows'
    mingw_root = ''
    mingw_includes = ''
    mingw_libs = ''
    posix_includes = '/usr/local/include'
endif

vendor_dir = 'vendor'
favicon_path = 'cpp_favicon.ico'

cpp = meson.get_compiler('cpp')

if os != 'windows'
    copy = find_program('cp')
    # copy index.html to build directory
    run_command(
        copy,
        join_paths(meson.source_root(), 'index.html'),
        join_paths(meson.build_root(), 'index.html'),
    )

    # copy styles.css to build directory
    run_command(
        copy,
        join_paths(meson.source_root(), 'styles.css'),
        join_paths(meson.build_root(), 'styles.css'),
    )

    # copy vendor sources to build directory
    run_command(
        copy,
        '-r',
        join_paths(meson.source_root(), vendor_dir),
        join_paths(meson.build_root(), vendor_dir),
    )

    # copy favicon to build directory
    run_command(
        copy,
        '-r',
        join_paths(meson.source_root(), favicon_path),
        join_paths(meson.build_root(), favicon_path),
    )

    # copy ssl keys
    run_command(
        copy,
        '-r',
        join_paths(meson.source_root(), ssl_keys_root),
        join_paths(meson.build_root(), ssl_keys_root),
    )
endif

windows_includes = [
    vcpkg_packages + '/boost-align_' + triplet + '/include/',
    vcpkg_packages + '/boost-winapi_' + triplet + '/include/',
]
if os != 'windows'
    windows_includes = ''
endif

incdir = include_directories(
    posix_includes,
    mingw_includes,
    vcpkg_packages + '/crow_' + triplet + '/include/',
    vcpkg_packages + '/boost-asio_' + triplet + '/include/',
    windows_includes,
    vcpkg_packages + '/boost-optional_' + triplet + '/include/',
    vcpkg_packages + '/boost-assert_' + triplet + '/include/',
    vcpkg_packages + '/boost-core_' + triplet + '/include/',
    vcpkg_packages + '/boost-config_' + triplet + '/include/',
    vcpkg_packages + '/boost-static-assert_' + triplet + '/include/',
    vcpkg_packages + '/boost-throw-exception_' + triplet + '/include/',
    vcpkg_packages + '/boost-type-traits_' + triplet + '/include/',
    vcpkg_packages + '/boost-move_' + triplet + '/include/',
    vcpkg_packages + '/boost-utility_' + triplet + '/include/',
    vcpkg_packages + '/boost-algorithm_' + triplet + '/include/',
    vcpkg_packages + '/boost-range_' + triplet + '/include/',
    vcpkg_packages + '/boost-preprocessor_' + triplet + '/include/',
    vcpkg_packages + '/boost-mpl_' + triplet + '/include/',
    vcpkg_packages + '/boost-iterator_' + triplet + '/include/',
    vcpkg_packages + '/boost-detail_' + triplet + '/include/',
    vcpkg_packages + '/boost-concept-check_' + triplet + '/include/',
    vcpkg_packages + '/boost-container-hash_' + triplet + '/include/',
    vcpkg_packages + '/boost-describe_' + triplet + '/include/',
    vcpkg_packages + '/boost-mp11_' + triplet + '/include/',
    vcpkg_packages + '/boost-system_' + triplet + '/include/',
    vcpkg_packages + '/boost-date-time_' + triplet + '/include/',
    vcpkg_packages + '/boost-smart-ptr_' + triplet + '/include',
    vcpkg_packages + '/boost-numeric-conversion_' + triplet + '/include',
    vcpkg_packages + '/boost-bind_' + triplet + '/include',
    vcpkg_packages + '/boost-regex_' + triplet + '/include',
    vcpkg_packages + '/boost-predef_' + triplet + '/include',
    vcpkg_packages + '/boost-lexical-cast_' + triplet + '/include',
    vcpkg_packages + '/boost-integer_' + triplet + '/include',
    vcpkg_packages + '/boost-array_' + triplet + '/include',
    vcpkg_packages + '/boost-container_' + triplet + '/include',
    vcpkg_packages + '/boost-function_' + triplet + '/include',
    vcpkg_packages + '/boost-type-index_' + triplet + '/include',
    vcpkg_packages + '/boost-io_' + triplet + '/include',
    vcpkg_packages + '/boost-tokenizer_' + triplet + '/include',
)

main_cpp = src_root / 'htmx_server.cpp'

sources = [main_cpp]

libopenssl_path = vcpkg_packages + '/openssl_' + triplet + '/lib'
if os == 'windows'
    libopenssl_path = mingw_libs
endif
libopenssl = cpp.find_library(
    'ssl',
    dirs: [libopenssl_path],
)

libcrypto_path = vcpkg_packages + '/openssl_' + triplet + '/lib'
if os == 'windows'
    libcrypto_path = mingw_libs
endif
libcrypto = cpp.find_library(
    'crypto',
    dirs: [libcrypto_path],
)

libresolv = ''
if os != 'windows'
    libresolv = cpp.find_library('resolv')
endif

librpcrt4 = ''
if os == 'windows'
    librpcrt4 = cpp.find_library('rpcrt4', dirs: [mingw_libs])
endif

libcrypt32 = ''
if os == 'windows'
    libcrypt32 = cpp.find_library('crypt32', dirs: [mingw_libs])
endif

zlib_name = 'z'
zlib_path = vcpkg_packages + '/zlib_' + triplet + '/lib'
if os == 'windows'
    zlib_path = mingw_libs
endif
libz = cpp.find_library(
    zlib_name,
    dirs: [zlib_path],
)

deps = [
    libz,
    libopenssl,
    libcrypto,
]

if os == 'windows'
    deps += [
        librpcrt4,
        libcrypt32,
    ]
endif

if os != 'windows'
    deps += libresolv
endif

link_args = ''
if os == 'windows'
    link_args = ['-lws2_32', '-lwsock32', '-lssl', '-lcrypto', '-lrpcrt4', '-lcrypt32']
endif

exe = executable(
    'htmx_server',
    sources,
    cpp_args: cpp_args,
    link_args: link_args,
    include_directories: incdir,
    dependencies: deps,
    install: true,
)

test('basic', exe)
