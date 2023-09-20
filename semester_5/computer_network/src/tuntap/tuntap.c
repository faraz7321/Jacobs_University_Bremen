/*
 * http://backreference.org/2010/03/26/tuntap-interface-tutorial/
 *
 * TUN=tun0
 * ip link set $TUN up
 * ip addr add 10.0.0.1/24 dev $TUN
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

/*
 * Create a tun/tap interface. Return the interface name in dev which
 * should be at least of size IFNAMSIZ. The flags control whether a
 * TUN (layer 3) or TAP (layer 2) interface is created. The function
 * returns an errno if system calls fail.
 */
 
int tun_alloc(char *dev, size_t dev_len, int flags)
{
    struct ifreq ifr;
    int fd, err;
    const char *clonedev = "/dev/net/tun";

    /*
     * Open the clone device that is used to create TUN/TAP
     * interfaces.
     */

    fd = open(clonedev , O_RDWR);
    if (fd < 0) {
	perror("open(\"/dev/net/tun\")");
	return fd;
    }

    /*
     * Initialize a structure used to request the creation of a
     * TUN/TAP interface. If the caller requests a specific interface
     * name, copy the name to the interface request structure.
     */

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = flags;
    if (*dev) {
	strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    /*
     * Try to allocate the interface using an ioctl on the clone
     * device.
     */

    err = ioctl(fd, TUNSETIFF, (void *) &ifr);
    if (err < 0 ) {
	perror("ioctl(TUNSETIFF)");
	(void) close(fd);
	return err;
    }

    /*
     * Copy the interface name that got allocated into the
     * dev buffer (if it is large enough).
     */

    if (strlen(ifr.ifr_name) >= dev_len) {
	errno = EINVAL;
	perror("interface device name string too short");
	(void) close(fd);
	return -1;
    }

    strncpy(dev, ifr.ifr_name, dev_len);
    return fd;
}

static int
get_mtu(char *ifname)
{
    struct ifreq ifr;
    int fd, err;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
	return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    if (*ifname) {
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
    }

    err = ioctl(fd, SIOCGIFMTU, (void *) &ifr);
    if (err < 0 ) {
	(void) close(fd);
	return -1;
    }

    (void) close(fd);
    return ifr.ifr_mtu;
}

int main(int argc, char *argv[])
{
    int tap_fd = 0;
    // int flags = IFF_TUN;	/* layer three */
    int flags = IFF_TAP;	/* layer two */
    char if_name[IFNAMSIZ] = "";

    char buf[65535];
    ssize_t len;

    tap_fd = tun_alloc(if_name, sizeof(if_name), flags | IFF_NO_PI);
    if (tap_fd < 0) {
	fprintf(stderr, "Error connecting to tun/tap interface %s!\n", if_name);
	exit(1);
    }

    printf("tun/tap interface '%s' created, mtu = %d\n",
	   if_name, get_mtu(if_name));

    while (1) {
	len = read(tap_fd, buf, sizeof(buf));
	if (len == 0) {
	    break;
	}
	if (len < 0) {
	    perror("read()");
	    break;
	}
	fprintf(stderr, "[%d]\n", (int) len);
    }

    (void) close(tap_fd);

    return 0;
}
