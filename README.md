# ndigo5g_babel
Wrappers, Utilities and Examples for using the Ndigo5G-10 and Ndigo250M with various programming languages.


## License

The code in this repository is licensed under the [Mozilla Public License 2.0](LICENSE). This more or less means that you can do with this code whatever you want, but if you improve the code you shall make your changes available ot others upon request. Please read the license for additional details. 

We encourage you to contribute to this repository. By uploading to this repository you agree to make your changes available under the beforementioned license.


# Examples
User Guide Example project and code provided:
1. [Ndigo5G ug_example](./ug_example).
2. [Ndigo250M ug_example_250M](./ug_examplug_example_250M).

# Ndigo250M 
Ndigo250M requires cronologic_linux_kernel version of 1.1.0 or newer because of contiguous buffers usage.
A Ndigo 250Mbuffer of 2 MB of requires 512 4K pages that are sequential in the physical memory (and below 4G). This is normally not a problem a short time after booting, but after a while, the memory is fragmented and contiguous blocks are no longer available.
When using lower frequencies you can reduce the buffer size and the allocation should work.
If larger buffers are needed and guarantee that the contiguous memory is available at all times, it is recommended to use CMA (Contiguous Memory Allocator), which reserves memory at boot time. Depending on the distribution it might be already enabled (some newer Red Hat derivatives) or not (most Debian distros). 

You can test it by executing:

cat /boot/config-$(uname -r)|grep CONFIG_DMA_CMA

If not enabled please recompile the kernel by changing this is option to the enabled, after copying the current .config in the following instructions:
https://davidaugustat.com/linux/how-to-compile-linux-kernel-on-ubuntu
CONFIG_DMA_CMA=y

The other CMA options can be left to default.

The boot option should be changed to include this flag now

cma=64M@0-4G

This reserves 64MB in the lower 4GB of ram (250M requires 32bit DMA addresses) 

* It can be built on Windows and Linux.
* The provided prebuilt linux libraries are tested on Ubuntu/Debian, and might work for other distributions, if they didn't work with you, please contact cronologic support team.
