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
        dwm-resetlayout.diff
        dwm-combo.diff
        "$_pkgname::git+http://git.suckless.org/dwm")
md5sums=('939f403a71b6e85261d09fc3412269ee'
         'c589a9b055c6a48133921a3d92bbcfb3'
         '1fc41126262be2d1587e44ee4c096bbd'
         'c7934768bd42be5b6ccc76581c1509ab'
         '3b0f29d3c8f2bb386c1f022ec1f061ba'
         'e4784697bc9fcdcd8182db9b67499209'
         '6957740bb75079fe95d352c308734b78'
         'SKIP')

pkgver(){
  cd $_pkgname
  git describe --long --tags | sed -E 's/([^-]*-g)/r\1/;s/-/./g'
}

prepare() {
  cd $_pkgname
  patch --forward --strip=1 --input="${srcdir}/dwm-swallow.diff"
  patch --forward --strip=1 --input="${srcdir}/dwm-fibonacci.diff"
  patch --forward --strip=1 --input="${srcdir}/dwm-center.diff"
  patch --forward --strip=1 --input="${srcdir}/dwm-hide_vacant_tags.diff"
  patch --forward --strip=1 --input="${srcdir}/dwm-resetlayout.diff"
  patch --forward --strip=1 --input="${srcdir}/dwm-combo.diff"
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
