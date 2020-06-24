# -*- mode: shell-script;-*-
# Maintainer: Johan Thorén <johan@thoren.xyz>
pkgname=dwm-jt
_pkgname=dwm
builddir="$(pwd)"
pkgver=6.2.r6.gf04cac6
pkgrel=1
pkgdesc="A dynamic window manager for X - Patched by Johan Thorén"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft')
optdepends=('dmenu' 'picom' 'st')
makedepends=('git')
install=dwm.install
provides=('dwm')
conflicts=('dwm')
source=(dwm.desktop
        dwm-swallow.diff
        dwm-fibonacci.diff
        dwm-center.diff
        dwm-hide_vacant_tags.diff
        dwm-combo.diff
        dwm-cool-autostart.diff
        dwm-cyclelayouts.diff
        dwm-dwmc.diff
        dwm-uselessgap.diff
        dwm-systray.diff
        dwm-actualfullscreen.diff
        personal_config.diff
        "$_pkgname::git+http://git.suckless.org/dwm")
md5sums=('939f403a71b6e85261d09fc3412269ee'
         'c589a9b055c6a48133921a3d92bbcfb3'
         '1fc41126262be2d1587e44ee4c096bbd'
         'c7934768bd42be5b6ccc76581c1509ab'
         '3b0f29d3c8f2bb386c1f022ec1f061ba'
         '90faf76c5c83425b9ee695bd4229ea2a'
         '3ef8266f45fb29b3d9aa4bfe919371d6'
         '74a6f28f47b6859efd3fd44bccdc13c9'
         '07efb439cb3591ef282875fc0cef6de4'
         '915ffe23e967692a55f892962c5c51f2'
         'f7470f9ca04225b0cdb9700e842bc8ca'
         'a8139561397258633df0b19309db3bc1'
         'SKIP'
         'SKIP')

pkgver(){
  cd $_pkgname
  git describe --long --tags | sed -E 's/([^-]*-g)/r\1/;s/-/./g'
}

_patch_it() {
    echo "Adding patch $1"
    patch --forward --strip=1 --input="${srcdir}/${1}"
    echo ""
}

prepare() {
  cd $_pkgname
  find "${srcdir}/" -name fibonacci.c -delete
  find "${srcdir}/" -name dwmc -delete

  patches=(dwm-swallow.diff
           dwm-fibonacci.diff
           dwm-center.diff
           dwm-hide_vacant_tags.diff
           dwm-combo.diff
           dwm-cool-autostart.diff
           dwm-cyclelayouts.diff
           dwm-dwmc.diff
           dwm-uselessgap.diff
           dwm-systray.diff
           dwm-actualfullscreen.diff
           personal_config.diff)

  for p in "${patches[@]}"; do
      _patch_it "$p"
  done

  # This package provides a mechanism to provide a custom config.h. Multiple
  # configuration states are determined by the presence of two files in
  # $_pkgname:
  #
  # config.h  config.def.h  state
  # ========  ============  =====
  # absent    absent        Initial state. The user receives a message on how
  #                         to configure this package.
  # absent    present       The user was previously made aware of the
  #                         configuration options and has not made any
  #                         configuration changes. The package is built using
  #                         default values.
  # present                 The user has supplied his or her configuration. The
  #                         file will be copied to $srcdir and used during
  #                         build.
  #
  # After this test, config.def.h is copied from $srcdir/src/st to $srcdir to
  # provide an up to date template for the user.
  if [ -e "${builddir}/config.h" ]
  then
    cp "${builddir}/config.h" "${srcdir}/${_pkgname}/config.h"
  elif [ ! -e "${builddir}/config.def.h" ]
  then
    msg='This package can be configured in config.h. Move the config.def.h '
    msg+='that was just placed into the package directory to config.h and '
    msg+='modify it to change the configuration. Or just leave it alone to '
    msg+='continue to use default values.'
    warning "$msg"
  fi
  cp "${srcdir}/${_pkgname}/config.def.h" "${builddir}/config.def.h"
}

build() {
  cd $_pkgname
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $_pkgname
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
  install -m644 -D ../dwm.desktop "$pkgdir/usr/share/xsessions/dwm.desktop"
}

# vim:set ts=2 sw=2 et:
