/*
 * Compile with:
 * gcc $(pkg-config --cflags --libs libgpod-1.0) -o tz ./get-timezone.c
 *
 * then run:
 * ./tz <ipod-mountpoint>
 *
 * This should output something like:
 * Timezone: UTC+1 DST
 *
 * which means I'm living in an UTC+1 timezone with DST which adds a 1 hour
 * shift, ie my local time is UTC+2. DST won't be shown if not active.
 *
 */
#include <glib-object.h>
#include <errno.h>
#include <stdio.h>
#include <itdb.h>
#include <itdb_device.h>

int main (int argc, char **argv)
{
    char *mountpoint;
    Itdb_Device *device;

#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init ();
#endif

    if (argc >= 2) {
        mountpoint = argv[1];
    } else {
        char *basename = g_path_get_basename(argv[0]);
        g_print ("Usage: %s <mountpoint>\n\n", basename);
        g_free (basename);
        return -1;
    }

    device = itdb_device_new ();
    itdb_device_set_mountpoint (device, mountpoint);

    g_print ("Timezone: UTC%+d\n", device->timezone_shift/3600);

    return 0;
}
