Name:		serene-update-assistant
	
Summary:	Serene linux update assistant(stub)
	
Version:	0.0.4
	
Release:	1%{?dist}

License:	MIT
	
BuildArch:	x86_64

Requires:       unzip,qt5-qtbase,qt5-qtbase-gui,qt5-qtremoteobjects,libcurl

BuildRequires: cmake,qt5-qtbase-devel,qt5-linguist,ninja-build,clang,qt5-qtremoteobjects-devel,libcurl-devel
%global debug_package %{nil}
Source0: https://github.com/FascodeNet/serene-update-assistant/archive/v0.0.0.4.tar.gz
%description
Serene Linux Updater Assistant
 
	
%prep
rm -rf %{buildroot}

%setup -n serene-update-assistant-v0.0.0.4
 
	
%build
%install
cd serene-update-assistant-gui/
mkdir -p build
cd build
cmake -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
ninja -j4
mkdir -p ${RPM_BUILD_ROOT}/usr/bin
mkdir -p ${RPM_BUILD_ROOT}/usr/share/polkit-1/actions/
cp serene-update-assistant-gui ${RPM_BUILD_ROOT}/usr/bin/
cp ../net.fascode.serene.updater.policy ${RPM_BUILD_ROOT}/usr/share/polkit-1/actions/
mkdir -p ${RPM_BUILD_ROOT}/etc/xdg/autostart/
cat <<EOF > $RPM_BUILD_ROOT/etc/xdg/autostart/serene-update-assistant.desktop
[Desktop Entry]
Type=Application
Name=Serene Update Assistant
Comment=Serene Update Assistant
Icon=serene
Exec=serene-update-assistant-gui
EOF
	
%files
/etc/xdg/autostart/serene-update-assistant.desktop
/usr/share/polkit-1/actions/net.fascode.serene.updater.policy
/usr/bin/serene-update-assistant-gui

%changelog
