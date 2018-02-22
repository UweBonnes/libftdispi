# -*- python -*-

# Version is for the moment hardcoded but will be optained from vcs
version = '0.2'

# look at site_scons/site_init.py for options
Import("*") # for old version of scons (1.0.1 for example variable in
            # site_init.py are not directly visible from SConstruct so
            # Import/Export are used

# = Environment =======================================================
env = Environment(PREFIX  = PREFIX,
                  LIBPATH = LIBPATH,
                  CCFLAGS = CCFLAGS + ['-DEXPORT_DLL'],
                  tools   = TOOLS)

# = Configuration =====================================================
if not env.GetOption('clean'):
    conf = Configure(env)
    conferror = False
    for l in ['usb', 'ftdi1']:
        if not conf.CheckLib(l):
            conferror = True
    if conferror:
        print 'Configure failed, exiting !'
        Exit(1)
    env = conf.Finish()

# = Compilation =======================================================
lib = env.SharedLibrary(LIBDIR + '/ftdispi', ['src/ftdispi.c'])
bin = env.Program('bin/spitest', ['src/spitest.c', 'src/ftdispi.c'])

# = Default Target ====================================================
Default(lib + bin)

# = Installation ======================================================
install = env.Install('$PREFIX/include', 'src/ftdispi.h')
for i in bin:
    install += env.Install('$PREFIX/bin', i)
for i in lib:
    install += env.InstallSharedLib('$PREFIX/'+ LIBDIR, str(i), version)
env.Alias('install', install)


# = Distclean =========================================================

env.Clean('distclean', ['.sconsign.dblite',
                        '.sconf_temp',
                        'config.log',
                        LIBDIR,
                        'bin',
                        'share/doc',
                        'share/man',
                        'src/ftdispi.os'])

# Packaging does not work for the moment
#try:
#    release = '.'.join(platform.release().split('.')[-2:])
#    release = '.' + release
#except:
#    release = ''

#pkg = env.Package(NAME           = 'libftdispi',
#                  VERSION        = version,
#                  PACKAGEVERSION = '1' + release,
#                  PACKAGETYPE    = 'rpm',
#                  LICENSE        = 'new BSD',
#                  SUMMARY        = 'Library to program and control the FTDI USB controller as a SPI Master',
#                  DESCRIPTION    = 'A library (using libftdi1 and so libusb) to use FTDI devices including FT4232H and FT2232H as a SPI master',
#                  X_RPM_GROUP    = '',
#                  SOURCE_URL     = 'http://code.google.com/p/libftdispi/',
#                  source         = install)
#
#env.Alias('rpm', pkg)
