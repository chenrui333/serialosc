/**
 * Copyright (c) 2010-2015 William Light <wrl@illest.net>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

#include <stdint.h>

#ifdef WIN32
#define SOSC_PIPE_PREFIX "\\\\.\\pipe\\org.monome.serialosc-"
#define SOSC_DETECTOR_PIPE (SOSC_PIPE_PREFIX "detector")
#endif

#define SOSC_IPC_MSG_BUFFER_SIZE 256

typedef enum {
	/* device -> supervisor */
	SOSC_DEVICE_CONNECTION,
	SOSC_DEVICE_INFO,
	SOSC_DEVICE_READY,
	SOSC_DEVICE_DISCONNECTION,
	SOSC_OSC_PORT_CHANGE,

	/* supervisor -> device */
	SOSC_PROCESS_SHOULD_EXIT
} sosc_ipc_type_t;

typedef struct sosc_ipc_msg {
	sosc_ipc_type_t type;

	union {
		struct {
			char *devnode;
		} connection;

		struct {
			char *serial;
			char *friendly;
		} device_info;

		struct {
			uint16_t port;
		} port_change;
	};

	uint16_t magic;
} sosc_ipc_msg_t;

int sosc_ipc_msg_write(int fd, sosc_ipc_msg_t *msg);
int sosc_ipc_msg_read(int fd, sosc_ipc_msg_t *buf);

ssize_t sosc_ipc_msg_to_buf(uint8_t *buf, size_t nbytes, sosc_ipc_msg_t *msg);
ssize_t sosc_ipc_msg_from_buf(uint8_t *buf, size_t nbytes, sosc_ipc_msg_t **msg);
