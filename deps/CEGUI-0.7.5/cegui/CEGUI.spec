################################################################################
# RPM .spec file for CEGUI.
#
# This creates a set of packages as follows:
#   CEGUI: Main CEGUI libs with Expat and SILLY as defaults.
#   CEGUI-opengl: The OpenGL renderer module.
#   CEGUI-ogre: The Ogre renderer module.
#   CEGUI-irrlicht: The Irrlicht renderer module.
#   CEGUI-lua: The Lua script module.
#   CEGUI-xerces-c: The Xerces-C++ XML parser module.
#   CEGUI-libxml: The libxml2 XML parser module.
#   CEGUI-tinyxml: The tinyxml parser module.
#   CEGUI-devil: The DevIL ImageCodec module.
#   CEGUI-freeimage: The freeimage ImageCodec module.
#
# Plus the following devel packages:
#   CEGUI-devel
#   CEGUI-opengl-devel
#   CEGUI-ogre-devel
#   CEGUI-irrlicht-devel
#   CEGUI-lua-devel
#
# NB: The xml parsers and image codecs do not have devel packages, since they
# are supposed to be dynamically loaded as plugins.
#
# TODO: We do not currently build and package the documentation files.
################################################################################

# we disable this because there are a handful of installed files we do not need
# to include in any package (the dev libs for the loadable modules)
%define _unpackaged_files_terminate_build 0

%define name CEGUI
%define version 0.7.5
%define release 1

Name: %{name}
Version: %{version}
Release: %{release}
Summary: Crazy Eddie's GUI System
License: MIT
URL: http://www.cegui.org.uk
Group: System Environment/Libraries
Source0: %{name}-%{version}.tar.gz
BuildRequires: pkgconfig >= 0.9.0
BuildRequires: freetype-devel >= 2.0.0, pcre-devel
BuildRequires: SILLY-devel, DevIL-devel, freeimage-devel
BuildRequires: expat-devel, libxml2-devel, tinyxml-devel, xerces-c-devel,
BuildRequires: libGLU-devel, glew-devel
BuildRequires: ogre-devel >= 1.6.0, irrlicht-devel >= 1.5.0
BuildRequires: lua-devel >= 5.1, tolua++-devel >= 1.0.92
BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot

%description
This is Crazy Eddie's GUI System Mk-2; a free library providing windowing and
widgets for graphics APIs and engines where such functionality is not natively
available or is severely lacking.

%package devel
Summary: Headers and development libraries for Crazy Eddie's GUI System.
Group: Development/Libraries 
Requires: %{name} = %{version}-%{release}, glew-devel, libGLU-devel

%description devel
This package contains the development headers and libraries for Crazy Eddie's
GUI System Mk-2; a free library providing windowing and widgets for graphics
APIs and engines where such functionality is not natively available or is
severely lacking.

################################################################################
%package opengl
Summary: The official OpenGL based renderer module for Crazy Eddie's GUI System
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description opengl
This package provides the OpenGL based renderer module for Crazy Eddie's GUI
System, allowing CEGUI rendering via OpenGL.

################################################################################
%package opengl-devel
Summary: Development libraries for the OpenGL renderer module for CEGUI
Group: Development/Libraries 
Requires: %{name}-opengl = %{version}-%{release}

%description opengl-devel
This package provides development libraries for the OpenGL based renderer module
for Crazy Eddie's GUI System, allowing CEGUI rendering via OpenGL.

################################################################################
%package ogre
Summary: The official Ogre based renderer module for Crazy Eddie's GUI System
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description ogre
This package provides the Ogre based renderer module for Crazy Eddie's GUI
System, allowing CEGUI rendering via OpenGL.

################################################################################
%package ogre-devel
Summary: Development libraries for the Ogre renderer module for CEGUI
Group: Development/Libraries 
Requires: %{name}-ogre = %{version}-%{release}, ogre-devel >= 1.6.0

%description ogre-devel
This package provides development libraries for the Ogre based renderer module
for Crazy Eddie's GUI System, allowing CEGUI rendering via Ogre.

################################################################################
%package irrlicht
Summary: The official Irrlicht based renderer module for Crazy Eddie's GUI System
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description irrlicht
This package provides the Irrlicht based renderer module for Crazy Eddie's GUI
System, allowing CEGUI rendering via OpenGL.

################################################################################
%package irrlicht-devel
Summary: Development libraries for the Irrlight renderer module for CEGUI
Group: Development/Libraries 
Requires: %{name}-irrlicht = %{version}-%{release}, irrlicht-devel >= 1.5.0

%description irrlicht-devel
This package provides development libraries for the Irrlight based renderer
module for Crazy Eddie's GUI System, allowing CEGUI rendering via Irrlicht.


################################################################################
%package lua
Summary: Lua Scripting module for Crazy Eddie's GUI System.
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description lua
This package contains the lua scripting module for Crazy Eddie's GUI System,
allowing CEGUI interfaces to be created and scripted via the lua language.

################################################################################
%package lua-devel
Summary: Development libraries for the CEGUI Lua scripting module.
Group: Development/Libraries 
Requires: %{name}-lua-%{version}-%{release}

%description lua-devel
This package contains the development libraries for the Lua scripting component
of Crazy Eddie's GUI System, which allows CEGUI interfaces to be created and
scripted via the lua language.

################################################################################
%package devil
Summary: DevIL based ImageCodec module for Crazy Eddie's GUI System.
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description devil
This package contains the DevIL based ImageCodec module for Crazy Eddie's GUI
System, allowing CEGUI to load images via the DevIL library.

################################################################################
%package freeimage
Summary: FreeImage based ImageCodec module for Crazy Eddie's GUI System.
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description freeimage
This package contains the FreeImage based ImageCodec module for Crazy Eddie's GUI
System, allowing CEGUI to load images via the FreeImage library.

################################################################################
%package xerces-c
Summary: Xerces-C++ based XML parser module for Crazy Eddie's GUI System.
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description xerces-c
This package contains the Xerces-C++ based XML parser module for Crazy Eddie's
GUI System, allowing CEGUI to parse XML files via the Xerces-C++ library.

################################################################################
%package libxml
Summary: libxml2 based XML parser module for Crazy Eddie's GUI System.
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description libxml
This package contains the libxml2 based XML parser module for Crazy Eddie's
GUI System, allowing CEGUI to parse XML files via the libxml2 library.

################################################################################
%package tinyxml
Summary: TinyXML based XML parser module for Crazy Eddie's GUI System.
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description tinyxml
This package contains the TinyXML based XML parser module for Crazy Eddie's
GUI System, allowing CEGUI to parse XML files via the TinyXML library.

################################################################################
%prep
%setup -q

%build
%configure \
	--with-default-parser=ExpatParser \
	--with-default-image-codec=SILLYImageCodec \
	--disable-corona \
	--disable-tga \
	--disable-samples

make -sj2

%install
rm -rf $RPM_BUILD_ROOT
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

################################################################################
%files
%defattr(-,root,root)
%{_libdir}/libCEGUIBase-%{version}.so
%{_libdir}/libCEGUIFalagardWRBase-%{version}.so
%{_libdir}/libCEGUIExpatParser-%{version}.so
%{_libdir}/libCEGUISILLYImageCodec-%{version}.so
%{_datadir}/CEGUI/

%files devel
%defattr(-,root,root)
%{_libdir}/libCEGUIBase.so
%{_libdir}/libCEGUIBase.la
%{_libdir}/libCEGUIFalagardWRBase.so
%{_libdir}/libCEGUIFalagardWRBase.la
%{_libdir}/libCEGUIExpatParser.so
%{_libdir}/libCEGUIExpatParser.la
%{_libdir}/libCEGUISILLYImageCodec.so
%{_libdir}/libCEGUISILLYImageCodec.la
%{_libdir}/pkgconfig/CEGUI.pc
%{_includedir}/CEGUI/

################################################################################
%files opengl
%defattr(-,root,root)
%{_libdir}/libCEGUIOpenGLRenderer-%{version}.so

%files opengl-devel
%defattr(-,root,root)
%{_libdir}/libCEGUIOpenGLRenderer.so
%{_libdir}/libCEGUIOpenGLRenderer.la
%{_libdir}/pkgconfig/CEGUI-OPENGL.pc

################################################################################
%files ogre
%defattr(-,root,root)
%{_libdir}/libCEGUIOgreRenderer-%{version}.so

%files ogre-devel
%defattr(-,root,root)
%{_libdir}/libCEGUIOgreRenderer.so
%{_libdir}/libCEGUIOgreRenderer.la
%{_libdir}/pkgconfig/CEGUI-OGRE.pc

################################################################################
%files irrlicht
%defattr(-,root,root)
%{_libdir}/libCEGUIIrrlichtRenderer-%{version}.so

%files irrlicht-devel
%defattr(-,root,root)
%{_libdir}/libCEGUIIrrlichtRenderer.so
%{_libdir}/libCEGUIIrrlichtRenderer.la

################################################################################
%files lua
%defattr(-,root,root)
%{_libdir}/libCEGUILuaScriptModule-%{version}.so

%files lua-devel
%defattr(-,root,root)
%{_libdir}/libCEGUILuaScriptModule.so
%{_libdir}/libCEGUILuaScriptModule.la

################################################################################
%files xerces-c
%defattr(-,root,root)
%{_libdir}/libCEGUIXercesParser-%{version}.so

################################################################################
%files libxml
%defattr(-,root,root)
%{_libdir}/libCEGUILibxmlParser-%{version}.so

################################################################################
%files tinyxml
%defattr(-,root,root)
%{_libdir}/libCEGUITinyXMLParser-%{version}.so

################################################################################
%files devil
%defattr(-,root,root)
%{_libdir}/libCEGUIDevILImageCodec-%{version}.so

################################################################################
%files freeimage
%defattr(-,root,root)
%{_libdir}/libCEGUIFreeImageImageCodec-%{version}.so

################################################################################

