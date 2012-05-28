Name:       geoclue
Summary:    Geoinformation service
Version:    0.12.0
Release:    1.8
Group:      TO_BE/FILLED_IN
License:    TO BE FILLED IN
Source0:    geoclue-%{version}.tar.gz
Source1001: geoclue.manifest 
BuildRequires:  which
BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(gconf-2.0)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(libsoup-2.4)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(libxslt)

%description
Geographic information framework GeoClue provides applications access
to various geographical information sources using a D-Bus API or a
C library.
This package contains the master server for GeoClue.

%package -n libgeoclue
Summary:        C API for GeoClue
Group:          TO_BE/FILLED
Requires:       %{name} = %{version}
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description -n libgeoclue
libgeoclue is a convenience wrapper for the GeoClue service, and
the recommended way to use GeoClue in the C language.

%package -n libgeoclue-devel
Summary:        C API for GeoClue (development files)
Group:          TO_BE/FILLED
Requires:       libgeoclue = %{version}

%description -n libgeoclue-devel
libgeoclue is a convenience wrapper for the GeoClue service, and
the recommended way to use GeoClue in the C language.

%package -n geoclue-nominatim
Summary:        Geocode server for GeoClue (OpenStreetMap)
Group:          TO_BE/FILLED
Requires:       %{name} = %{version}

%description -n geoclue-nominatim
GeoClue provides applications access to various geographical information
sources using a D-Bus API or a C library.

This package provides a tool to search osm data by name and address and 
to generate synthetic addresses of osm points (reverse geocoding)

%prep
%setup -q

%build
cp %{SOURCE1001} .
export CFLAGS+=" -Wall -g -fPIC"
export LDFLAGS+=" -Wl,-z,defs -Wl,--rpath=/usr/lib -Wl,--as-needed -Wl,--hash-style=both"

./autogen.sh
./configure --disable-static --prefix=/usr --mandir=/usr/share/man \
    --infodir=/usr/share/info --enable-system-bus=yes --disable-gypsy \
    --disable-lbs --disable-xps

make

%install
%make_install
rm -rf %{buildroot}%{_bindir}/geoclue-test-gui


%post -n libgeoclue -p /sbin/ldconfig

%postun -n libgeoclue -p /sbin/ldconfig

%files
%manifest geoclue.manifest
/usr/libexec/geoclue-master
/usr/share/dbus-1/services/org.freedesktop.Geoclue.Master.service

%files -n libgeoclue
%manifest geoclue.manifest
/usr/lib/libgeoclue.so*

%files -n libgeoclue-devel
%manifest geoclue.manifest
/usr/include/*
/usr/lib/pkgconfig/*

%files -n geoclue-nominatim
%manifest geoclue.manifest
/usr/share/dbus-1/services/org.freedesktop.Geoclue.Providers.Nominatim.service
/usr/share/geoclue-providers/geoclue-nominatim.provider
/usr/libexec/geoclue-nominatim
