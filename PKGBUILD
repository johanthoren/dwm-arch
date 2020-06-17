pkgname=dwm-jt
_pkgname=dwm
pkgver=6.2.r6.gf04cac6
pkgrel=1
pkgdesc="A dynamic window manager for X - Patched by Johan Thorén"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft')
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
        "$_pkgname::git+http://git.suckless.org/dwm"
        config.h)
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
         'SKIP') # Skipping MD5 check to allow you to put you own config here.

pkgver(){
  cd $_pkgname
  git describe --long --tags | sed -E 's/([^-]*-g)/r\1/;s/-/./g'
}

prepare() {
  cd $_pkgname
  echo "Adding patch dwm-swallow:"
  patch --forward --strip=1 --input="${srcdir}/dwm-swallow.diff"
  echo ""
  echo "Adding patch dwm-fibonacci:"
  find "${srcdir}/" -name fibonacci.c -delete
  patch --forward --strip=1 --input="${srcdir}/dwm-fibonacci.diff"
  echo ""
  echo "Adding patch dwm-center:"
  patch --forward --strip=1 --input="${srcdir}/dwm-center.diff"
  echo ""
  echo "Adding patch dwm-hide_vacant_tags:"
  patch --forward --strip=1 --input="${srcdir}/dwm-hide_vacant_tags.diff"
  echo ""
  echo "Adding patch dwm-combo:"
  patch --forward --strip=1 --input="${srcdir}/dwm-combo.diff"
  echo ""
  echo "Adding patch dwm-cool-autostart:"
  patch --forward --strip=1 --input="${srcdir}/dwm-cool-autostart.diff"
  echo ""
  echo "Adding patch dwm-cyclelayouts:"
  patch --forward --strip=1 --input="${srcdir}/dwm-cyclelayouts.diff"
  echo ""
  echo "Adding patch dwm-dwmc:"
  find "${srcdir}/" -name dwmc -delete
  patch --forward --strip=1 --input="${srcdir}/dwm-dwmc.diff"
  echo ""
  echo "Adding patch dwm-uselessgap:"
  patch --forward --strip=1 --input="${srcdir}/dwm-uselessgap.diff"
  echo ""
  echo "Adding patch dwm-systray:"
  patch --forward --strip=1 --input="${srcdir}/dwm-systray.diff"
  echo ""
  echo "Adding patch dwm-actualfullscreen:"
  patch --forward --strip=1 --input="${srcdir}/dwm-actualfullscreen.diff"
  echo ""

  # If the provided config.h contains something (not empty),
  # then copy it to be used at build. This way you can customize
  # the settings.
  if [[ -s "${srcdir}/config.h" ]]; then
      cp -fv "${srcdir}/config.h" config.h
  fi
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
# -*- mode: shell-script;-*-
