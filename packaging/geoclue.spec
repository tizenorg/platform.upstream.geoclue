Name:       geoclue
Summary:    Geoinformation service
Version:    0.12.0_28
Release:    0
Group:      Location/Service
Source0:    geoclue-%{version}.tar.gz
Source1001: %{name}.manifest
License:        GPL-2.0
BuildRequires:  which
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(gconf-2.0)
BuildRequires:  pkgconfig(libsoup-2.4)
BuildRequires:  pkgconfig(libxslt)


%description
Geographic information framework GeoClue provides applications access to various geographical information 
 sources using a D-Bus API or a C library. 
 .
 This package contains the master server for GeoClue.

%package -n libgeoclue
Summary:    C API for GeoClue
Requires:   %{name} = %{version}-%{release}
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description -n libgeoclue
libgeoclue is a convenience wrapper for the GeoClue service, and
the recommended way to use GeoClue in the C language.

%package -n libgeoclue-devel
Summary:    C API for GeoClue (development files)
Requires:   libgeoclue = %{version}-%{release}

%description -n libgeoclue-devel
libgeoclue is a convenience wrapper for the GeoClue service, and
the recommended way to use GeoClue in the C language.

%package -n geoclue-nominatim
Summary:    Geocode server for GeoClue (OpenStreetMap)
Requires:   %{name} = %{version}-%{release}

%description -n geoclue-nominatim
GeoClue provides applications access to various geographical information
sources using a D-Bus API or a C library.
.
This package provides a tool to search osm data by name and address and to generate synthetic addresses of osm points (reverse geocoding)


%prep
%setup -q -n %{name}-%{version}
cp %{SOURCE1001} .


%build
export CFLAGS+=" -Wall -g -fPIC"

%autogen
%configure  --enable-system-bus=yes --disable-gypsy --disable-lbs --disable-xps

make

%install
%make_install
rm -rf %{buildroot}/usr/bin/geoclue-test-gui


%post -n libgeoclue -p /sbin/ldconfig

%postun -n libgeoclue -p /sbin/ldconfig

%files
%manifest %{name}.manifest
/usr/libexec/geoclue-master
/usr/share/dbus-1/services/org.freedesktop.Geoclue.Master.service

%files -n libgeoclue
%manifest %{name}.manifest
%{_libdir}/libgeoclue.so*

%files -n libgeoclue-devel
%manifest %{name}.manifest
/usr/include/*
%{_libdir}/pkgconfig/*

%files -n geoclue-nominatim
%manifest %{name}.manifest
/usr/share/dbus-1/services/org.freedesktop.Geoclue.Providers.Nominatim.service
/usr/share/geoclue-providers/geoclue-nominatim.provider
/usr/libexec/geoclue-nominatim
