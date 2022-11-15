gio_dep = dependency('gio-2.0')


libvisca = library('visca', 
            ['exceptions/ViscaNetworkException.cpp', 'exceptions/ViscaValueException.cpp', 'Visca.cpp'], 
            dependencies: [gio_dep], cpp_args : '-std=c++17')

libvisca_dep = declare_dependency(include_directories: ['.'], dependencies: [gio_dep], link_with : libvisca)
