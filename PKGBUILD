# -*- mode: shell-script;-*-
# Maintainer: Johan Thorén <johan@thoren.xyz>
pkgname=dwm-jt
_pkgname=dwm
builddir="$(pwd)"
pkgver=6.2.r12.ga786211
pkgrel=1
pkgdesc="A dynamic window manager for X - Patched by Johan Thorén"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft')
optdepends=('dmenu' 'dunst' 'dwmblocks' 'i3lock-fancy-rapid-git'
            'libqalculate' 'mons' 'mullvad-vpn-cli' 'nm-applet' 'numlockx'
            'picom' 'st' 'xbanish' 'xss-lock')
makedepends=('git')
install=dwm.install
provides=('dwm')
conflicts=('dwm')
source=(dwm.desktop
        # jt-patches.diff is a consolidated patch containing the following
        # patches:
        #
        # - actualfullscreen
        # - center
        # - combo
        # - cool-autostart
        # - dwmc
        # - hide_vacant_tags
        # - scratchpads
        # - shiftview
        # - sticky
        # - swallow
        # - systray
        # - uselessgaps
        #
        # Some massaging has been done to make these patches play nice together.
        jt-patches.diff
        "$_pkgname::git+http://git.suckless.org/dwm#commit=a786211d6cb794fba0ea406d86002c7618998afc")

md5sums=('939f403a71b6e85261d09fc3412269ee'
         '028c1ae695f1bad231c511591e4d2796'
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
  find "${srcdir}/" -name dwmc -delete

  patches=(
      jt-patches.diff
)

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
