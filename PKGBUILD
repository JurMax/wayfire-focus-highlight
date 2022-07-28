pkgname=wayfire-focus-flash
pkgver=0.1
pkgrel=1
pkgdesc="Add a flash when focusing a window in Wayfire."
arch=('x86_64')
url="https://github.com/JurMax/wayfire-focus-flash"
license=('MIT')
depends=('wayfire')
makedepends=('git' 'meson' 'ninja' 'cmake')
provides=('wayfire-focus-flash')
conflicts=("$pkgname")
replaces=()
options=()

source=()
sha256sums=()

build() {
    cd ../
    meson build --buildtype=release
    ninja -C build
}


package() {
    cd ../
    DESTDIR="$pkgdir/" ninja -C build install
}
