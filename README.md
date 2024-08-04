# kudo
Like sudo but runs code in the kernel. Because Why Not?

# Installing
## Clone the repo
Run `git clone https://github.com/Jacoblightning/kudo`
## Ensure dependencies
Ensure that you have installed your kernel headers.
## Make
Run `make` to build and `make install` to install the kernel module.

You can now run `sudo ./kudo` to run code in the kernel.

(I am currently working on getting stdin/out working.)
