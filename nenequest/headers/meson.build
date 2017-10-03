conf = configuration_data()
conf.set_quoted('PACKAGE_DATADIR',
                join_paths(get_option('prefix'), pkgdatadir))
configure_file(output: 'config.hpp', configuration: conf)
