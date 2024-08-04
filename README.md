# Kudo
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

# Prebuilt
If you run the same system as the workflow servers, you can use a prebuilt release from [Actions](https://github.com/Jacoblightning/kudo/actions) or [Nightly.link](https://nightly.link/Jacoblightning/kudo/workflows/build/main/build.zip)
