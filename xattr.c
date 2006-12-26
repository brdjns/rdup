/**
 * Copyright (c) 2005 - 2007 Miek Gieben
 * See LICENSE for the license
 *
 * All xattr functions are grouped here
 */

#include "rdup.h"

extern gint opt_verbose;

uid_t
read_attr_uid(__attribute__((unused))
	char *path, uid_t u)
{
#ifdef HAVE_ATTR_XATTR_H
	/* linux */
	char buf[ATTR_SIZE + 1];
	uid_t x;
	int r;

	if ((r = lgetxattr(path, "user.r_uid", buf, ATTR_SIZE)) > 0) {
		x = (uid_t)atoi(buf);
		buf[r - 1] = '\0';
		if (x > R_MAX_ID) {
			msg("Too large uid `%zd\' for `%s\', truncating", (size_t)x, 
				path);
			return R_MAX_ID;
		}
		return x;
	} else {
		if (opt_verbose > 0) {
			msg("No uid xattr for `%s\'", path);
		}
		return u;
	}
#elif HAVE_ATTROPEN
	/* solaris */
	char buf[ATTR_SIZE + 1];
	uid_t x;
	int attfd;
	int r;
	if ((attfd = attropen(path, "r_uid", O_RDONLY)) == -1) {
		if (opt_verbose > 0) {
			msg("No uid xattr for `%s\'", path);
		}
		return u;
	}
	if ((r = read(attfd, buf, ATTR_SIZE)) == -1) {
		return u;
	}
	close(attfd);
	buf[r - 1] = '\0';
	x = (uid_t)atoi(buf);
	if (x > R_MAX_ID) {
		msg("Too large gid `%zd\' for `%s\', truncating", (size_t)x, path);
		return R_MAX_ID;
	}
	return x;
#else
	return u;
#endif /* HAVE_ATTR_XATTR_H, HAVE_ATTROPEN */
}

gid_t
read_attr_gid(__attribute__((unused))
	char *path, gid_t g)
{
#ifdef HAVE_ATTR_XATTR_H
	char buf[ATTR_SIZE + 1];
	gid_t x;
	int r;

	if ((r = lgetxattr(path, "user.r_gid", buf, ATTR_SIZE)) > 0) {
		buf[r - 1] = '\0';
		x = (gid_t)atoi(buf);
		if (x > R_MAX_ID) {
			msg("Too large gid `%zd\' for `%s\', truncating", (size_t)x, 
					path);
			return R_MAX_ID;
		}
		return x;
	} else {
		if (opt_verbose > 0) {
			msg("No gid xattr for `%s\'\n", path);
		}
		return g;
	}
#elif HAVE_ATTROPEN
	/* solaris */
	char buf[ATTR_SIZE + 1];
	gid_t x;
	int attfd;
	int r;
	if ((attfd = attropen(path, "r_gid", O_RDONLY)) == -1) {
		if (opt_verbose > 0) {
			msg("No gid xattr for `%s\'", path);
		}
		return g;
	}
	if ((r = read(attfd, buf, ATTR_SIZE)) == -1) {
		return g;
	}
	close(attfd);
	buf[r - 1] = '\0';
	x = (uid_t)atoi(buf);
	if (x > R_MAX_ID) {
		msg("Too large gid `%zd\' for `%s\', truncating", (size_t)x, path);
		return R_MAX_ID;
	}
	return x;
#else
	return g;
#endif /* HAVE_ATTR_XATTR_H, HAVE_ATTROPEN */
}

mode_t
read_attr_mode(__attribute__((unused))
	char *path, mode_t m)
{
#ifdef HAVE_ATTR_XATTR_H
	/* linux */
	char buf[ATTR_SIZE + 1];
	mode_t x;
	int r;

	if ((r = lgetxattr(path, "user.r_mode", buf, ATTR_SIZE)) > 0) {
		x = (mode_t)atoi(buf);
		buf[r - 1] = '\0';
		/* range check ? */
		return x;
	} else {
		if (opt_verbose > 0) {
			msg("No mode xattr for `%s\'", path);
		}
		return m;
	}
#elif HAVE_ATTROPEN
	/* solaris */
	char buf[ATTR_SIZE + 1];
	mode_t x;
	int attfd;
	int r;
	if ((attfd = attropen(path, "r_mode", O_RDONLY)) == -1) {
		if (opt_verbose > 0) {
			msg("No mode xattr for `%s\'", path);
		}
		return m;
	}
	if ((r = read(attfd, buf, ATTR_SIZE)) == -1) {
		return m;
	}
	close(attfd);
	buf[r - 1] = '\0';
	x = (uid_t)atoi(buf);
	return x;
#else
	return m;
#endif /* HAVE_ATTR_XATTR_H, HAVE_ATTROPEN */
}