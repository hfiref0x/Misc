Summary: QV Tools driver
Name: iqvlinux
Version: 1.1.4.5
Release: 0
BuildArch: noarch
License: GPL
Vendor: Intel
Group: System Environment/Kernel
URL: http://www.intel.com

Source: iqvlinux.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root


%description
Network adapter driver for QV Tools.

%prep
%setup -c %{name} -n %{name}

%build

%install
if [ -d %{buildroot} ]; then
    rm -fr %{buildroot}
fi
mkdir -p %{buildroot}/%{_datadir}/%{name}-%{version}-root
make -f Makefile -C src/linux/driver \
     NALDIR=/usr/src/redhat/BUILD/%{name} \
     DESTDIR=%{buildroot}/%{_datadir}/%{name}-%{version}-root installrpm

%post
# V=1 if you want verbose output
make -f Makefile -C %{_datadir}/%{name}-%{version}-root/src/linux/driver \
     NALDIR=%{_datadir}/%{name}-%{version}-root/
%{_datadir}/%{name}-%{version}-root/src/linux/driver/nalinstall %{_datadir}/%{name}-%{version}-root/src/linux/driver
rm -fr %{_datadir}/%{name}-%{version}-root/*

%verifyscript
if [ ! -e /lib/modules/`uname -r`/kernel/drivers/net/iqvlinux.ko ]
then
	echo "QV Linux Driver is missing"
	exit 1
fi

%clean
rm -fr %{buildroot}

%files
%defattr(-, root, root, 0755)
%{_datadir}/%{name}-%{version}-root/

%changelog
* %(date "+%a %b %d %Y") %name %{version}
- Automatic build.
