# Makefile.in generated by automake 1.15.1 from Makefile.am.
# src/m/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994-2017 Free Software Foundation, Inc.

# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



#To generate list of directories
#
#find . -type d -exec ls -d {} \;


am__is_gnu_make = { \
  if test -z '$(MAKELEVEL)'; then \
    false; \
  elif test -n '$(MAKE_HOST)'; then \
    true; \
  elif test -n '$(MAKE_VERSION)' && test -n '$(CURDIR)'; then \
    true; \
  else \
    false; \
  fi; \
}
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/issm
pkgincludedir = $(includedir)/issm
pkglibdir = $(libdir)/issm
pkglibexecdir = $(libexecdir)/issm
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-pc-linux-gnu
host_triplet = x86_64-pc-linux-gnu
target_triplet = x86_64-pc-linux-gnu
#am__append_1 = ${ISSM_DIR}/src/m/qmu/*.m \
#					${ISSM_DIR}/src/m/archive/*.m \
#					${ISSM_DIR}/src/m/qmu/setupdesign/*.m \
#					${ISSM_DIR}/src/m/qmu/plot/*.m \
#					${ISSM_DIR}/src/m/qmu/examples/*.m \
#					${ISSM_DIR}/src/m/kml/*.m \
#					${ISSM_DIR}/src/m/dev/issmversion.m \
#					${ISSM_DIR}/src/m/classes/*.m \
#					${ISSM_DIR}/src/m/classes/qmu/*.m \
#					${ISSM_DIR}/src/m/classes/qmu/@dakota_method/*.m \
#					${ISSM_DIR}/src/m/classes/clusters/*.m \
#					${ISSM_DIR}/src/m/consistency/*.m \
#					${ISSM_DIR}/src/m/array/*.m \
#					${ISSM_DIR}/src/m/boundaryconditions/*.m \
#					${ISSM_DIR}/src/m/exp/*.m \
#					${ISSM_DIR}/src/m/exp/operation/*.m \
#					${ISSM_DIR}/src/m/geometry/*.m \
#					${ISSM_DIR}/src/m/interp/*.m \
#					${ISSM_DIR}/src/m/coordsystems/*.m \
#					${ISSM_DIR}/src/m/mech/*.m \
#					${ISSM_DIR}/src/m/mesh/*.m \
#					${ISSM_DIR}/src/m/mesh/planet/spheretri/*.m \
#					${ISSM_DIR}/src/m/mesh/planet/gmsh/*.m \
#					${ISSM_DIR}/src/m/mesh/rifts/*.m \
#					${ISSM_DIR}/src/m/miscellaneous/*.m \
#					${ISSM_DIR}/src/m/modules/*.m \
#					${ISSM_DIR}/src/m/os/*.m \
#					${ISSM_DIR}/src/m/plot/*.m \
#					${ISSM_DIR}/src/m/plot/colormaps/*.m \
#					${ISSM_DIR}/src/m/string/*.m \
#					${ISSM_DIR}/src/m/extrusion/*.m \
#					${ISSM_DIR}/src/m/inversions/*.m \
#					${ISSM_DIR}/src/m/io/*.m \
#					${ISSM_DIR}/src/m/parameterization/*.m \
#					${ISSM_DIR}/src/m/partition/*.m \
#					${ISSM_DIR}/src/m/print/*.m \
#					${ISSM_DIR}/src/m/regional/*.m \
#					${ISSM_DIR}/src/m/solve/*.m \
#					${ISSM_DIR}/src/m/solvers/*.m \
#					${ISSM_DIR}/src/m/materials/*.m

am__append_2 = ${ISSM_DIR}/src/m/archive/*.py \
					${ISSM_DIR}/src/m/classes/*.py \
					${ISSM_DIR}/src/m/classes/clusters/*.py \
					${ISSM_DIR}/src/m/consistency/*.py \
					${ISSM_DIR}/src/m/dev/issmversion.py \
					${ISSM_DIR}/src/m/boundaryconditions/*.py \
					${ISSM_DIR}/src/m/exp/*.py \
					${ISSM_DIR}/src/m/geometry/*.py \
					${ISSM_DIR}/src/m/coordsystems/*.py \
					${ISSM_DIR}/src/m/interp/*.py \
					${ISSM_DIR}/src/m/inversions/*.py \
					${ISSM_DIR}/src/m/mech/*.py \
					${ISSM_DIR}/src/m/mesh/*.py \
					${ISSM_DIR}/src/m/mesh/rifts/*.py \
					${ISSM_DIR}/src/m/miscellaneous/*.py \
					${ISSM_DIR}/src/m/modules/*.py \
					${ISSM_DIR}/src/m/os/*.py \
					${ISSM_DIR}/src/m/plot/*.py \
					${ISSM_DIR}/src/m/extrusion/*.py \
					${ISSM_DIR}/src/m/io/*.py \
					${ISSM_DIR}/src/m/parameterization/*.py \
					${ISSM_DIR}/src/m/solve/*.py \
					${ISSM_DIR}/src/m/solvers/*.py \
					${ISSM_DIR}/src/m/materials/*.py

#am__append_3 = issm-bin.js
subdir = src/m
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/m4/analyses.m4 \
	$(top_srcdir)/m4/ar-lib.m4 $(top_srcdir)/m4/libtool.m4 \
	$(top_srcdir)/m4/ltoptions.m4 $(top_srcdir)/m4/ltsugar.m4 \
	$(top_srcdir)/m4/ltversion.m4 $(top_srcdir)/m4/lt~obsolete.m4 \
	$(top_srcdir)/m4/issm_options.m4 $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
DIST_COMMON = $(srcdir)/Makefile.am $(am__DIST_COMMON)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/./config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = f=`echo $$p | sed -e 's|^.*/||'`;
am__install_max = 40
am__nobase_strip_setup = \
  srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*|]/\\\\&/g'`
am__nobase_strip = \
  for p in $$list; do echo "$$p"; done | sed -e "s|$$srcdirstrip/||"
am__nobase_list = $(am__nobase_strip_setup); \
  for p in $$list; do echo "$$p $$p"; done | \
  sed "s| $$srcdirstrip/| |;"' / .*\//!s/ .*/ ./; s,\( .*\)/[^/]*$$,\1,' | \
  $(AWK) 'BEGIN { files["."] = "" } { files[$$2] = files[$$2] " " $$1; \
    if (++n[$$2] == $(am__install_max)) \
      { print $$2, files[$$2]; n[$$2] = 0; files[$$2] = "" } } \
    END { for (dir in files) print dir, files[dir] }'
am__base_list = \
  sed '$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;s/\n/ /g' | \
  sed '$$!N;$$!N;$$!N;$$!N;s/\n/ /g'
am__uninstall_files_from_dir = { \
  test -z "$$files" \
    || { test ! -d "$$dir" && test ! -f "$$dir" && test ! -r "$$dir"; } \
    || { echo " ( cd '$$dir' && rm -f" $$files ")"; \
         $(am__cd) "$$dir" && rm -f $$files; }; \
  }
am__installdirs = "$(DESTDIR)$(bindir)"
SCRIPTS = $(bin_SCRIPTS)
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 = 
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 = 
SOURCES =
DIST_SOURCES =
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) $(LISP)
am__DIST_COMMON = $(srcdir)/Makefile.in
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /home/pf4d/software/issm/trunk/aux-config/missing aclocal-1.15
ADIC2INCL = 
ADIC2LIB = 
ADOLCINCL = 
ADOLCLIB = 
AMPIINCL = 
AMPILIB = 
AMTAR = $${TAR-tar}
AM_DEFAULT_VERBOSITY = 0
ANDROID_NDKINCL = 
AR = ar
ATLASLIB = 
AUTOCONF = ${SHELL} /home/pf4d/software/issm/trunk/aux-config/missing autoconf
AUTOHEADER = ${SHELL} /home/pf4d/software/issm/trunk/aux-config/missing autoheader
AUTOMAKE = ${SHELL} /home/pf4d/software/issm/trunk/aux-config/missing automake-1.15
AWK = gawk
BLACSINCL = 
BLACSLIB = 
BLASLAPACKINCL = 
BLASLAPACKLIB = -L/home/pf4d/local/openblas/lib -lopenblas 
BOOSTINCL = -I/home/pf4d/local/boost-1.67.0/include
BOOSTLIB = -L/home/pf4d/local/boost-1.67.0/lib -lboost_python
CC = mpicc
CCDEPMODE = depmode=gcc3
CFLAGS = -O3
CHACOINCL = 
CHACOLIB = 
CPP = mpicc -E
CPPFLAGS = 
CXX = mpicxx
CXXCPP = mpicxx -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -O3 -std=c++11
CXXOPTFLAGS = -g -O2 -fPIC
CYGPATH_W = echo
DAKOTAFLAGS = 
DAKOTAINCL = 
DAKOTALIB = 
DATE = /bin/date
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DLLTOOL = false
DSYMUTIL = 
DUMPBIN = 
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
ESMFINCL = 
ESMFLIB = 
EXEEXT = 
F77 = mpifort
FFLAGS = -O3
FGREP = /bin/grep -F
FORTRANLIB = -L/usr/lib/x86_64-linux-gnu -lgfortran
GRAPHICSLIB = 
GREP = /bin/grep
GSLINCL = 
GSLLIB = 
HYPREINCL = 
HYPRELIB = 
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
ISSMEXT = .exe
JAVASCRIPTWRAPPEREXT = .js
LD = /usr/bin/x86_64-linux-gnu-ld -m elf_x86_64
LDFLAGS = 
LIBOBJS = 
LIBS = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIPO = 
LN_S = ln -s
LTLIBOBJS = 
LT_SYS_LIBRARY_PATH = 
M1QN3LIB = /home/pf4d/software/issm/trunk/externalpackages/m1qn3/install/libm1qn3.a /home/pf4d/software/issm/trunk/externalpackages/m1qn3/install//libddot.a
MAKEINFO = ${SHELL} /home/pf4d/software/issm/trunk/aux-config/missing makeinfo
MANIFEST_TOOL = :
MATH77LIB = 
MATHLIB = 
MATLABINCL = 
MATLABWRAPPEREXT = 
METEOIOINCL = 
METEOIOLIB = 
METISINCL = 
METISLIB = 
MEXLIB = 
MEXLINK = 
MKDIR_P = /bin/mkdir -p
MKLINCL = 
MKLLIB = 
MLINCL = 
MLLIB = 
MPIINCL = -I/usr/include/mpich
MPILIB = -L/usr/lib/x86_64-linux-gnu -lmpichcxx -lmpichfort -lmpich -ldl -lrt -lpthread
MULTITHREADINGLIB = -lpthread -lrt
MUMPSINCL = -I/home/pf4d/local/petsc-3.7.6/include
MUMPSLIB = -L/home/pf4d/local/petsc-3.7.6/lib -ldmumps -lcmumps  -lmumps_common -lpord -lparmetis -lzmumps -lmetis
NEOPZINCL = 
NEOPZLIB = 
NM = /usr/bin/nm -B
NMEDIT = 
OBJDUMP = objdump
OBJEXT = o
OSLIBS = 
OTOOL = 
OTOOL64 = 
PACKAGE = issm
PACKAGE_BUGREPORT = issm@jpl.nasa.gov
PACKAGE_NAME = Ice Sheet System Model (ISSM)
PACKAGE_STRING = Ice Sheet System Model (ISSM) 4.12
PACKAGE_TARNAME = issm
PACKAGE_URL = http://issm.jpl.nasa.gov
PACKAGE_VERSION = 4.12
PASTIXINCL = 
PASTIXLIB = 
PATH_SEPARATOR = :
PETSCINCL =  -I/home/pf4d/local/petsc-3.7.6/include
PETSCLIB = -L/home/pf4d/local/petsc-3.7.6/lib -lpetsc -ldl -lparmetis -lmetis
PLAPACKINCL = 
PLAPACKLIB = 
PROJ4INCL = 
PROJ4LIB = 
PROMETHEUSINCL = 
PROMETHEUSLIB = 
PYTHONINCL = -I/home/pf4d/local/python-2.7.15/include/python2.7
PYTHONLIB = -L/home/pf4d/local/python-2.7.15/lib -lpython2.7
PYTHONLINK = -shared
PYTHONWRAPPEREXT = .so
PYTHON_NUMPYINCL = -I/home/pf4d/local/python-2.7.15/lib/python2.7/site-packages/numpy -I/home/pf4d/local/python-2.7.15/lib/python2.7/site-packages/numpy/core/include/numpy
RANLIB = ranlib
ROSEINCL = 
ROSELIB = 
SCALAPACKLIB = -L/home/pf4d/local/petsc-3.7.6/ -lscalapack
SCOTCHINCL = 
SCOTCHLIB = 
SED = /bin/sed
SET_MAKE = 
SHAPELIBINCL = 
SHAPELIBLIB = 
SHELL = /bin/bash
SLEPCINCL = 
SLEPCLIB = 
SNOWPACKINCL = 
SNOWPACKLIB = 
SPAIINCL = 
SPAILIB = 
SPOOLESINCL = 
SPOOLESLIB = 
STRIP = strip
SUPERLUINCL = 
SUPERLULIB = 
TAOINCL = 
TAOLIB = 
TRIANGLEINCL = -I/home/pf4d/software/issm/trunk/externalpackages/triangle/install/
TRIANGLELIB = /home/pf4d/software/issm/trunk/externalpackages/triangle/install/triangle.a
UMFPACKINCL = 
UMFPACKLIB = 
VERSION = 4.12
abs_builddir = /home/pf4d/software/issm/trunk/src/m
abs_srcdir = /home/pf4d/software/issm/trunk/src/m
abs_top_builddir = /home/pf4d/software/issm/trunk
abs_top_srcdir = /home/pf4d/software/issm/trunk
ac_ct_AR = ar
ac_ct_CC = 
ac_ct_CXX = 
ac_ct_DUMPBIN = 
ac_ct_F77 = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = $${TAR-tar} chof - "$$tardir"
am__untar = $${TAR-tar} xf -
bindir = ${exec_prefix}/bin
build = x86_64-pc-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = pc
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = x86_64-pc-linux-gnu
host_alias = 
host_cpu = x86_64
host_os = linux
host_vendor = pc
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /home/pf4d/software/issm/trunk/aux-config/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(MKDIR_P)
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /home/pf4d/local/issm-4.12
program_transform_name = s,x,x,
psdir = ${docdir}
runstatedir = ${localstatedir}/run
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target = x86_64-pc-linux-gnu
target_alias = 
target_cpu = x86_64
target_os = linux-gnu
target_vendor = pc
top_build_prefix = ../../
top_builddir = ../..
top_srcdir = ../..
bin_SCRIPTS = $(am__append_1) $(am__append_2) $(am__append_3)
#js_scripts = ${ISSM_DIR}/src/m/array/arrayoperations.js \
#				${ISSM_DIR}/src/m/boundaryconditions/SetIceShelfBC.js \
#				${ISSM_DIR}/src/m/classes/autodiff.js \
#				${ISSM_DIR}/src/m/classes/balancethickness.js \
#				${ISSM_DIR}/src/m/classes/basalforcings.js \
#				${ISSM_DIR}/src/m/classes/calving.js \
#				${ISSM_DIR}/src/m/classes/clusters/generic.js \
#				${ISSM_DIR}/src/m/classes/clusters/local.js \
#				${ISSM_DIR}/src/m/classes/constants.js \
#				${ISSM_DIR}/src/m/classes/damage.js \
#				${ISSM_DIR}/src/m/classes/debug.js \
#				${ISSM_DIR}/src/m/classes/flowequation.js \
#				${ISSM_DIR}/src/m/classes/friction.js \
#				${ISSM_DIR}/src/m/classes/geometry.js \
#				${ISSM_DIR}/src/m/classes/giaivins.js \
#				${ISSM_DIR}/src/m/classes/esa.js \
#				${ISSM_DIR}/src/m/classes/groundingline.js \
#				${ISSM_DIR}/src/m/classes/hydrologyshreve.js \
#				${ISSM_DIR}/src/m/classes/initialization.js \
#				${ISSM_DIR}/src/m/classes/inversion.js \
#				${ISSM_DIR}/src/m/classes/mask.js \
#				${ISSM_DIR}/src/m/classes/maskpsl.js \
#				${ISSM_DIR}/src/m/classes/masstransport.js \
#				${ISSM_DIR}/src/m/classes/matice.js \
#				${ISSM_DIR}/src/m/classes/mesh2d.js \
#				${ISSM_DIR}/src/m/classes/mesh3dsurface.js \
#				${ISSM_DIR}/src/m/classes/miscellaneous.js \
#				${ISSM_DIR}/src/m/classes/model.js \
#				${ISSM_DIR}/src/m/classes/outputdefinition.js \
#				${ISSM_DIR}/src/m/classes/pairoptions.js \
#				${ISSM_DIR}/src/m/classes/plotoptions.js \
#				${ISSM_DIR}/src/m/classes/priv.js \
#				${ISSM_DIR}/src/m/classes/qmu.js \
#				${ISSM_DIR}/src/m/classes/radaroverlay.js \
#				${ISSM_DIR}/src/m/classes/rifts.js \
#				${ISSM_DIR}/src/m/classes/slr.js \
#				${ISSM_DIR}/src/m/classes/settings.js \
#				${ISSM_DIR}/src/m/classes/SMBforcing.js \
#				${ISSM_DIR}/src/m/classes/steadystate.js \
#				${ISSM_DIR}/src/m/classes/stressbalance.js \
#				${ISSM_DIR}/src/m/classes/template.js \
#				${ISSM_DIR}/src/m/classes/thermal.js \
#				${ISSM_DIR}/src/m/classes/timestepping.js \
#				${ISSM_DIR}/src/m/classes/toolkits.js \
#				${ISSM_DIR}/src/m/classes/levelset.js \
#				${ISSM_DIR}/src/m/classes/trans.js \
#				${ISSM_DIR}/src/m/classes/verbose.js \
#				${ISSM_DIR}/src/m/consistency/checkfield.js \
#				${ISSM_DIR}/src/m/consistency/ismodelselfconsistent.js \
#				${ISSM_DIR}/src/m/geometry/FlagElements.js \
#				${ISSM_DIR}/src/m/inversions/marshallcostfunctions.js \
#				${ISSM_DIR}/src/m/io/fileptr.js \
#				${ISSM_DIR}/src/m/io/savemodel.js \
#				${ISSM_DIR}/src/m/io/loadmodel.js \
#				${ISSM_DIR}/src/m/io/saveAsFile.js \
#				${ISSM_DIR}/src/m/io/writetofile.js \
#				${ISSM_DIR}/src/m/io/download.js \
#				${ISSM_DIR}/src/m/io/writetofile.js \
#				${ISSM_DIR}/src/m/materials/paterson.js \
#				${ISSM_DIR}/src/m/mesh/triangle.js \
#				${ISSM_DIR}/src/m/miscellaneous/colorbars.js \
#				${ISSM_DIR}/src/m/miscellaneous/fielddisplay.js \
#				${ISSM_DIR}/src/m/miscellaneous/rgbcolor.js \
#				${ISSM_DIR}/src/m/parameterization/setflowequation.js \
#				${ISSM_DIR}/src/m/parameterization/setmask.js \
#				${ISSM_DIR}/src/m/plot/slider.js \
#				${ISSM_DIR}/src/m/plot/applyoptions.js \
#				${ISSM_DIR}/src/m/plot/checkplotoptions.js \
#				${ISSM_DIR}/src/m/plot/plot_manager.js \
#				${ISSM_DIR}/src/m/plot/plot_mesh.js \
#				${ISSM_DIR}/src/m/plot/plot_overlay.js \
#				${ISSM_DIR}/src/m/plot/plot_unit.js \
#				${ISSM_DIR}/src/m/plot/plot_quiver.js \
#				${ISSM_DIR}/src/m/plot/plotdoc.js \
#				${ISSM_DIR}/src/m/plot/plotmodel.js \
#				${ISSM_DIR}/src/m/plot/processdata.js \
#				${ISSM_DIR}/src/m/plot/processmesh.js \
#				${ISSM_DIR}/src/m/plot/gauge.js \
#				${ISSM_DIR}/src/m/plot/webgl.js \
#				${ISSM_DIR}/src/m/print/sprintf.js \
#				${ISSM_DIR}/src/m/solve/loadresultsfrombuffer.js \
#				${ISSM_DIR}/src/m/solve/marshall.js \
#				${ISSM_DIR}/src/m/solve/parseresultsfrombuffer.js \
#				${ISSM_DIR}/src/m/solve/solve.js \
#				${ISSM_DIR}/src/m/solve/WriteData.js \
#				${ISSM_DIR}/src/m/solvers/issmgslsolver.js 

all: all-am

.SUFFIXES:
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --foreign src/m/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --foreign src/m/Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure:  $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):
install-binSCRIPTS: $(bin_SCRIPTS)
	@$(NORMAL_INSTALL)
	@list='$(bin_SCRIPTS)'; test -n "$(bindir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(bindir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(bindir)" || exit 1; \
	fi; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  if test -f "$$d$$p"; then echo "$$d$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n' \
	    -e 'h;s|.*|.|' \
	    -e 'p;x;s,.*/,,;$(transform)' | sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1; } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) { files[d] = files[d] " " $$1; \
	      if (++n[d] == $(am__install_max)) { \
		print "f", d, files[d]; n[d] = 0; files[d] = "" } } \
	    else { print "f", d "/" $$4, $$1 } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	     if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	     test -z "$$files" || { \
	       echo " $(INSTALL_SCRIPT) $$files '$(DESTDIR)$(bindir)$$dir'"; \
	       $(INSTALL_SCRIPT) $$files "$(DESTDIR)$(bindir)$$dir" || exit $$?; \
	     } \
	; done

uninstall-binSCRIPTS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_SCRIPTS)'; test -n "$(bindir)" || exit 0; \
	files=`for p in $$list; do echo "$$p"; done | \
	       sed -e 's,.*/,,;$(transform)'`; \
	dir='$(DESTDIR)$(bindir)'; $(am__uninstall_files_from_dir)

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs
tags TAGS:

ctags CTAGS:

cscope cscopelist:


distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile $(SCRIPTS)
installdirs:
	for dir in "$(DESTDIR)$(bindir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libtool mostlyclean-am

distclean: distclean-am
	-rm -f Makefile
distclean-am: clean-am distclean-generic

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am: install-binSCRIPTS

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-binSCRIPTS

.MAKE: install-am install-strip

.PHONY: all all-am check check-am clean clean-generic clean-libtool \
	cscopelist-am ctags-am distclean distclean-generic \
	distclean-libtool distdir dvi dvi-am html html-am info info-am \
	install install-am install-binSCRIPTS install-data \
	install-data-am install-dvi install-dvi-am install-exec \
	install-exec-am install-html install-html-am install-info \
	install-info-am install-man install-pdf install-pdf-am \
	install-ps install-ps-am install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-generic \
	mostlyclean-libtool pdf pdf-am ps ps-am tags-am uninstall \
	uninstall-am uninstall-binSCRIPTS

.PRECIOUS: Makefile


#issm-bin.js: ${js_scripts}
#	cat ${js_scripts}  > issm-bin.js

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
